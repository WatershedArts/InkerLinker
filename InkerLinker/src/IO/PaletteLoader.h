//--------------------------------------------------------------
//  PaletteLoader.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the PaletteLoader Class. */
//--------------------------------------------------------------

#ifndef PaletteLoader_h
#define PaletteLoader_h
#include "ofMain.h"
#include "ofxJSON.h"
#include "Nodes.h"

class PaletteLoader
{
	private:
		int maxLoadedId = 0;
		vector <BaseNode*> nodes;
		vector <PatchCord> cords;
	
	public:
	
		//-----------------------------------------------------
		/** \brief Get the Next Valid Node Address
			* @return maxLoadedId : how many nodes are loaded/
			*
			* This method returns the number of nodes loaded.
		*/
		//-----------------------------------------------------
		int getNextNodeId()
		{
			return maxLoadedId+1;
		}
	
		//-----------------------------------------------------
		/** \brief Get Patch Cords
			* @return cords : loaded cords.
			*
			* This method returns the loaded patch cords.
		*/
		//-----------------------------------------------------
		vector <PatchCord> getPatchCords()
		{
			return cords;
		}
		
		//-----------------------------------------------------
		/** \brief Get Nodes
			* @return nodes : loaded nodes.
			*
			* This method returns the loaded nodes.
		*/
		//-----------------------------------------------------
		vector <BaseNode*> getNodes()
		{
			return nodes;
		}
	
		//-----------------------------------------------------
		/** \brief Load the Palette File
			* @param path : path to file.
			*
			* This method loads the selected palette file.
		*/
		//-----------------------------------------------------
		void load(string path)
		{
			DebugMessage("Palette Loader", "Loading");
			
			ofxCenteredTrueTypeFont *font;
			font = new ofxCenteredTrueTypeFont();
			font->load("SF-Pro-Text-Medium.otf", 10,true,true,true);
			
			ofxJSONElement loadFile;
			if(!loadFile.open(path))
			{
				string s = "Loading Failed. Couldn't find " +path;
				DebugMessage("Palette Loader" , s.c_str());
			}
			else
			{
				// Clear out the old cords
				cords.clear();
				
				int noOfCords = loadFile["cords"].size();
				for(int i = 0; i < noOfCords; i++)
				{
					PatchCord cord;
					cord.patchId = loadFile["cords"][i]["patchid"].asInt();
					cord.electrodeId = loadFile["cords"][i]["electrodeid"].asString();
					cord.nodeId = loadFile["cords"][i]["nodeid"].asInt();
					cord.portId = loadFile["cords"][i]["portid"].asInt();
					
					if(loadFile["cords"][i]["type"].asInt() == 0) cord.type = TB_POINT_TYPE::TB_TOUCH_POINT;
					else if(loadFile["cords"][i]["type"].asInt() == 1) cord.type = TB_POINT_TYPE::TB_RELEASE_POINT;
					
					
					cord.startingPoint.x = loadFile["cords"][i]["startpoint"]["x"].asInt();
					cord.startingPoint.y = loadFile["cords"][i]["startpoint"]["y"].asInt();
					cord.endingPoint.x = loadFile["cords"][i]["endpoint"]["x"].asInt();
					cord.endingPoint.y = loadFile["cords"][i]["endpoint"]["y"].asInt();
					cord.firstCurvePoint.x = loadFile["cords"][i]["firstcurvepoint"]["x"].asInt();
					cord.firstCurvePoint.y = loadFile["cords"][i]["firstcurvepoint"]["y"].asInt();
					cord.secondCurvePoint.x = loadFile["cords"][i]["secondcurvepoint"]["x"].asInt();
					cord.secondCurvePoint.y = loadFile["cords"][i]["secondcurvepoint"]["y"].asInt();
					
					cord.deleteCord.setFromCenter(loadFile["cords"][i]["delete"]["x"].asInt(),
												  loadFile["cords"][i]["delete"]["y"].asInt(),
												  loadFile["cords"][i]["delete"]["w"].asInt(),
												  loadFile["cords"][i]["delete"]["h"].asInt()
												  );
					
					cords.push_back(cord);
				}
				//------------------------------------------------------------------------------------
				// *
				// * NODES
				// *
				//------------------------------------------------------------------------------------
				// Clear out the old Nodes
				nodes.clear();
				
				int noOfNodes = loadFile["nodes"].size();
				for (int i = 0; i < noOfNodes; i++)
				{
					int *id;
//					string type = loadFile["nodes"][i]["name"].asString();
					
					IL_NODE_TYPE type = (IL_NODE_TYPE)(loadFile["nodes"][i]["type"].asInt());
					switch (type)
					{
						case IL_ARDUINO_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <ArduinoData> arduinoData;
							int noOfCommands = loadFile["nodes"][i]["arduinodata"].size();
							// Get the Values
							for(int c = 0; c < noOfCommands; c++)
							{
								ArduinoData ad;
								ad.pin = loadFile["nodes"][i]["arduinodata"][c]["pin"].asInt();
								ad.value = loadFile["nodes"][i]["arduinodata"][c]["value"].asInt();
								ad.mode = loadFile["nodes"][i]["arduinodata"][c]["mode"].asString();
								arduinoData.push_back(ad);
							}
	
							nodes.push_back(new ArduinoNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	   loadFile["nodes"][i]["position"]["y"].asInt(),
																	   loadFile["nodes"][i]["position"]["w"].asInt(),
																	   loadFile["nodes"][i]["position"]["h"].asInt()),
															font,
															"Arduino",
															id,
															ports,
															arduinoData));
						}
						break;
						case IL_CLOUD_BIT_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <CloudBitData> cbData;
							int noOfData = loadFile["nodes"][i]["cloudbitdata"].size();
							// Get the Values
							for(int c = 0; c < noOfData; c++)
							{
								CloudBitData d;
								d.percent = loadFile["nodes"][i]["cloudbitdata"][c]["percent"].asInt();
								d.duration_ms = loadFile["nodes"][i]["cloudbitdata"][c]["durationms"].asInt();
								cbData.push_back(d);
							}
	
							nodes.push_back(new CloudBitNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																		   loadFile["nodes"][i]["position"]["y"].asInt(),
																		   loadFile["nodes"][i]["position"]["w"].asInt(),
																		   loadFile["nodes"][i]["position"]["h"].asInt()),
															 font,
															 "Instrument",
															 id,
															 ports,
															 cbData));
						}
						break;
						case IL_COLOUR_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
							vector <ofColor> colours;
							int noOfColours = loadFile["nodes"][i]["colours"].size();
							// Get the Values
							for(int c = 0; c < noOfColours; c++)
							{
								colours.push_back(ofColor(loadFile["nodes"][i]["colours"][c]["r"].asInt(),
														  loadFile["nodes"][i]["colours"][c]["g"].asInt(),
														  loadFile["nodes"][i]["colours"][c]["b"].asInt()));
							}
	
							nodes.push_back(new ColourNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	   loadFile["nodes"][i]["position"]["y"].asInt(),
																	   loadFile["nodes"][i]["position"]["w"].asInt(),
																	   loadFile["nodes"][i]["position"]["h"].asInt()),
														   font,
														   "Colour",
														   id,
														   ports,
														   colours));
						}
						break;
						case IL_HTTP_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <HTTPData> httpData;
							int noOfData = loadFile["nodes"][i]["httpdata"].size();
							// Get the Values
							for(int c = 0; c < noOfData; c++)
							{
								HTTPData d;
								d.hostURL = loadFile["nodes"][i]["httpdata"][c]["address"].asString();
								d.extension = loadFile["nodes"][i]["httpdata"][c]["extension"].asString();
								for (int f = 0; f < loadFile["nodes"][i]["httpdata"][c]["data"].size(); f++)
								{
									POSTData dd;
									dd.field = loadFile["nodes"][i]["httpdata"][c]["data"][f]["field"].asString();
									dd.value = loadFile["nodes"][i]["httpdata"][c]["data"][f]["value"].asString();
									d.data.push_back(dd);
								}
								httpData.push_back(d);
							}
	
							nodes.push_back(new HTTPNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	   loadFile["nodes"][i]["position"]["y"].asInt(),
																	   loadFile["nodes"][i]["position"]["w"].asInt(),
																	   loadFile["nodes"][i]["position"]["h"].asInt()),
														 font,
														 "Serial",
														 id,
														 ports,
														 httpData));
						}
						break;
						case IL_IMAGE_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							nodes.push_back(new ImageNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																		   loadFile["nodes"][i]["position"]["y"].asInt(),
																		   loadFile["nodes"][i]["position"]["w"].asInt(),
																		   loadFile["nodes"][i]["position"]["h"].asInt()),
														  font,
														  "Image",
														  id,
														  ports,
														  loadFile["nodes"][i]["images"].asString()));
						}
						break;
						case IL_INSTRUMENT_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <string> files;
							int noOfFiles = loadFile["nodes"][i]["files"].size();
							// Get the Values
							for(int c = 0; c < noOfFiles; c++)
							{
								files.push_back(loadFile["nodes"][i]["files"][c].asString());
							}
	
							nodes.push_back(new InstrumentNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	  loadFile["nodes"][i]["position"]["y"].asInt(),
																	  loadFile["nodes"][i]["position"]["w"].asInt(),
																	  loadFile["nodes"][i]["position"]["h"].asInt()),
															   font,
															   "Instrument",
															   id,
															   ports,
															   files));
						}
						break;
						case IL_OSC_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <OscData> oscData;
							int noOfData = loadFile["nodes"][i]["oscdata"].size();
							// Get the Values
							for(int c = 0; c < noOfData; c++)
							{
								OscData d;
								d.address = loadFile["nodes"][i]["oscdata"][c]["address"].asString();
								for (int f = 0; f < loadFile["nodes"][i]["oscdata"][c]["values"].size(); f++)
								{
									d.value.push_back(loadFile["nodes"][i]["oscdata"][c]["values"][f].asString());
								}
								oscData.push_back(d);
							}
	
							nodes.push_back(new OscNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																		   loadFile["nodes"][i]["position"]["y"].asInt(),
																		   loadFile["nodes"][i]["position"]["w"].asInt(),
																		   loadFile["nodes"][i]["position"]["h"].asInt()),
														font,
														"OSC",
														id,
														ports,
														oscData));
						}
						break;
						case IL_SERIAL_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
	
							vector <string> commands;
							int noOfCommands = loadFile["nodes"][i]["commands"].size();
							// Get the Values
							for(int c = 0; c < noOfCommands; c++)
							{
								commands.push_back(loadFile["nodes"][i]["commands"][c].asString());
							}
	
							nodes.push_back(new SerialNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																		   loadFile["nodes"][i]["position"]["y"].asInt(),
																		   loadFile["nodes"][i]["position"]["w"].asInt(),
																		   loadFile["nodes"][i]["position"]["h"].asInt()),
														   font,
														   "Serial",
														   id,
														   ports,
														   commands));
						}
						break;
						case IL_SOUND_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
							nodes.push_back(new SoundNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	  loadFile["nodes"][i]["position"]["y"].asInt(),
																	  loadFile["nodes"][i]["position"]["w"].asInt(),
																	  loadFile["nodes"][i]["position"]["h"].asInt()),
														  font,
														  "Sound",
														  id,
														  ports,
														  loadFile["nodes"][i]["file"].asString()));
						}
						break;
						case IL_VIDEO_NODE:
						{
							id = new int(loadFile["nodes"][i]["nodeid"].asInt());
							vector <Port> ports;
							int noOfPorts = loadFile["nodes"][i]["numberofports"].asInt();
	
							// Get the Ports
							for(int p = 0; p < noOfPorts; p++)
							{
								Port port(loadFile["nodes"][i]["ports"][p]["x"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["y"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["portid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["nodeid"].asInt(),
										  loadFile["nodes"][i]["ports"][p]["name"].asString());
	
								port.setElectrodeId(loadFile["nodes"][i]["ports"][p]["electrodeid"].asString());
								port.setPatchCordId(loadFile["nodes"][i]["ports"][p]["patchcordid"].asInt());
	
								if(!loadFile["nodes"][i]["ports"][p]["electrodeattached"].asBool())
								{
									port.setPortStateInactive();
								}
								else
								{
									port.setPortStateActive();
								}
	
								ports.push_back(port);
							}
	
							nodes.push_back(new VideoNode(ofRectangle(loadFile["nodes"][i]["position"]["x"].asInt(),
																	  loadFile["nodes"][i]["position"]["y"].asInt(),
																	  loadFile["nodes"][i]["position"]["w"].asInt(),
																	  loadFile["nodes"][i]["position"]["h"].asInt()),
														  font,
														  "Video",
														  id,
														  ports,
														  loadFile["nodes"][i]["file"].asString()));
						}
						break;
						default:break;
					}
				}
			}
		}
};

#endif /* PaletteLoader_h */
