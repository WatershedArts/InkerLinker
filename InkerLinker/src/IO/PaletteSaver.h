//--------------------------------------------------------------
//  PaletteSaver.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the PaletteSaver Class. */
//--------------------------------------------------------------
#ifndef PaletteSaver_h
#define PaletteSaver_h

#include "ofxJSON.h"
#include "ofMain.h"
#include "Nodes.h"

class PaletteSaver
{
	public:
		//-----------------------------------------------------
			/** \brief Load the Palette File
				* @param cords : vector of cords.
				* @param nodes : vector of nodes.
				*
				* This method Save the palette file.
			*/
			//-----------------------------------------------------
		void save(vector <PatchCord> cords,vector <BaseNode*> nodes)
		{
			ofxJSONElement file;

			// Cord Section
			for(int i = 0; i < cords.size(); i++)
			{
				file["cords"][i]["patchid"] = cords[i].patchId;
				file["cords"][i]["electrodeid"] = cords[i].electrodeId;
				file["cords"][i]["nodeid"] = cords[i].nodeId;
				file["cords"][i]["portid"] = cords[i].portId;
				file["cords"][i]["type"] = cords[i].type;

				file["cords"][i]["delete"]["x"] = cords[i].deleteCord.getCenter().x;
				file["cords"][i]["delete"]["y"] = cords[i].deleteCord.getCenter().y;
				file["cords"][i]["delete"]["w"] = cords[i].deleteCord.getWidth();
				file["cords"][i]["delete"]["h"] = cords[i].deleteCord.getHeight();


				file["cords"][i]["startpoint"]["x"] = cords[i].startingPoint.x;
				file["cords"][i]["startpoint"]["y"] = cords[i].startingPoint.y;
				file["cords"][i]["endpoint"]["x"] = cords[i].endingPoint.x;
				file["cords"][i]["endpoint"]["y"] = cords[i].endingPoint.y;
				file["cords"][i]["firstcurvepoint"]["x"] = cords[i].firstCurvePoint.x;
				file["cords"][i]["firstcurvepoint"]["y"] = cords[i].firstCurvePoint.y;
				file["cords"][i]["secondcurvepoint"]["x"] = cords[i].secondCurvePoint.x;
				file["cords"][i]["secondcurvepoint"]["y"] = cords[i].secondCurvePoint.y;
			}


			// NODES Section
			for(int i = 0; i < nodes.size(); i++)
			{
				file["nodes"][i]["name"] = nodes[i]->getName();
				file["nodes"][i]["numberofports"] = nodes[i]->getNoOfPorts();
				file["nodes"][i]["position"]["x"] = nodes[i]->getBox().x;
				file["nodes"][i]["position"]["y"] = nodes[i]->getBox().y;
				file["nodes"][i]["position"]["w"] = nodes[i]->getBox().width;
				file["nodes"][i]["position"]["h"] = nodes[i]->getBox().height;
				file["nodes"][i]["type"] = nodes[i]->getType();


				switch (nodes[i]->getType())
				{
					case IL_ARDUINO_NODE:
					{
						ArduinoNode a = *(ArduinoNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["electrodeattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
						}
						for (int e = 0; e < a.getArduinoData().size(); e++)
						{
							file["nodes"][i]["arduinodata"][e]["mode"] = a.getArduinoData()[e].mode;
							file["nodes"][i]["arduinodata"][e]["pin"] = a.getArduinoData()[e].pin;
							file["nodes"][i]["arduinodata"][e]["value"] = a.getArduinoData()[e].value;
						}
					}
					break;
					case IL_CLOUD_BIT_NODE:
					{
						CloudBitNode a = *(CloudBitNode*)(nodes[i]);

						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["actionattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
						}

						for (int cd = 0; cd < a.getCloudBitData().size(); cd++)
						{
							file["nodes"][i]["cloudbitdata"][cd]["percent"] = a.getCloudBitData()[cd].percent;
							file["nodes"][i]["cloudbitdata"][cd]["durationms"] = a.getCloudBitData()[cd].duration_ms;
						}
					}
					break;
					case IL_COLOUR_NODE:
					{
						ColourNode a = *(ColourNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
							if(a.getPorts()[e].getPortState())
							{
								file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
								file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							}
							else {
								file["nodes"][i]["ports"][e]["patchcordid"] = -1;
								file["nodes"][i]["ports"][e]["electrodeid"] = "n";
							}
							file["nodes"][i]["ports"][e]["electrodeattached"] = a.getPorts()[e].getPortState();

							for (int c = 0; c < a.getColours().size(); c++)
							{
								file["nodes"][i]["colours"][c]["r"] = a.getColours()[c].r;
								file["nodes"][i]["colours"][c]["g"] = a.getColours()[c].g;
								file["nodes"][i]["colours"][c]["b"] = a.getColours()[c].b;
							}
						}
					}
					break;
					case IL_HTTP_NODE:
					{
						HTTPNode a = *(HTTPNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["actionattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();

							for (int h = 0; h < a.getHTTPData().size(); h++)
							{
								file["nodes"][i]["httpdata"]["address"] = a.getHTTPData()[e].hostURL;
								file["nodes"][i]["httpdata"]["extension"] = a.getHTTPData()[e].extension;
								for (int pd = 0; pd < a.getHTTPData()[h].data.size(); pd++)
								{
									file["nodes"][i]["httpdata"]["data"][pd]["field"] = a.getHTTPData()[e].data[pd].field;
									file["nodes"][i]["httpdata"]["data"][pd]["value"] = a.getHTTPData()[e].data[pd].value;
								}
							}
						}
					}
					break;
					case IL_IMAGE_NODE:
					{
						ImageNode *a = (ImageNode*)(nodes[i]);
						for (int e = 0; e < a->getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a->getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a->getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a->getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a->getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a->getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["electrodeattached"] = a->getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a->getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a->getPorts()[e].getName();
						}

						for(int f = 0; f < a->getFilePaths().size(); f++)
						{
							file["nodes"][i]["images"][f] = a->getFilePaths()[f];
						}
					}
					break;
					case IL_INSTRUMENT_NODE:
					{
						InstrumentNode a = *(InstrumentNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["electrodeattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
						}
						for(int ins = 0; ins < a.getInstruments().size(); ins++)
						{
							file["nodes"][i]["files"][ins] = a.getInstruments()[ins];
						}
					}
					break;

					case IL_OSC_NODE:
					{
						OscNode a = *(OscNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["actionattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();

						}
						for(int g = 0; g < a.getOscData().size(); g++)
						{
							file["nodes"][i]["oscdata"][g]["address"] = a.getOscData()[g].address;
							for(int v = 0; v < a.getOscData()[g].value.size(); v++)
							{
								file["nodes"][i]["oscdata"][g]["values"][v] = a.getOscData()[g].value[v];
							}
						}
					}
					break;
					case IL_SERIAL_NODE:
					{
						SerialNode a = *(SerialNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["actionattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
						}

						for (int c = 0; c < a.getCommands().size(); c++)
						{
							file["nodes"][i]["commands"][c] = a.getCommands()[c];
						}
					}
					break;
					case IL_SOUND_NODE:
					{
						SoundNode a = *(SoundNode*)(nodes[i]);
						for (int e = 0; e < a.getPorts().size(); e++)
						{
							file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
							file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
							file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
							file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
							file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
							file["nodes"][i]["ports"][e]["electrodeattached"] = a.getPorts()[e].getPortState();
							file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
							file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
						}
						file["nodes"][i]["file"] = a.getFilePath();
					}
					break;
					case IL_VIDEO_NODE:
					{
							VideoNode a = *(VideoNode*)(nodes[i]);
							for (int e = 0; e < a.getPorts().size(); e++)
							{
								file["nodes"][i]["ports"][e]["x"] = a.getPorts()[e].getBox().x;
								file["nodes"][i]["ports"][e]["y"] = a.getPorts()[e].getBox().y;
								file["nodes"][i]["ports"][e]["nodeid"] = a.getPorts()[e].getNodeId();
								file["nodes"][i]["ports"][e]["portid"] = a.getPorts()[e].getPortId();
								file["nodes"][i]["ports"][e]["patchcordid"] = a.getPorts()[e].getPatchCordId();
								file["nodes"][i]["ports"][e]["electrodeattached"] = a.getPorts()[e].getPortState();
								file["nodes"][i]["ports"][e]["electrodeid"] = a.getPorts()[e].getElectrodeId();
								file["nodes"][i]["ports"][e]["name"] = a.getPorts()[e].getName();
							}
							file["nodes"][i]["file"] = a.getFilePath();
					}
					break;
					default:break;
				}
			}

			// Save Section
			string name = ofSystemSaveDialog("", "Name the Palette File").getName();
			DebugMessage("Palette Saver", "Saving");
			file.save(ofToDataPath(name+".json"), true);
		}
	private:

};

#endif /* PaletteSaver_h */
