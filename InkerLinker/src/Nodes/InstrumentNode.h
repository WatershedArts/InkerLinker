//--------------------------------------------------------------
//  InstrumentNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Instrument Node Class. */
//--------------------------------------------------------------

#ifndef InstrumentNode_h
#define InstrumentNode_h

#include "BaseNode.h"
#include "ofxAvUtils.h"

class InstrumentNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		InstrumentNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~InstrumentNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param filePaths : A vector of filePaths.
			*
			* This method Constructs an Instruments Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		InstrumentNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<string> filePaths)
		{
			type = IL_INSTRUMENT_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = filePaths.size();
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			for(int i = 0; i < this->noOfPorts; i++)
			{
				this->portNames.push_back("Action " + ofToString(i));
			}

			generatePorts(this->noOfPorts);

			
			for (int i = 0; i < filePaths.size(); i++)
			{
				ofSoundPlayer s;
				s.load(filePaths[i]);
				s.setMultiPlay(true);
				players.push_back(s);
			}
			
			loadSounds(filePaths);
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param filePaths : A vector of filePaths.
			*
			* This method Constructs an Instrument Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		InstrumentNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<string> filePaths)
		{
			type = IL_INSTRUMENT_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

//			for (int i = 0; i < filePaths.size(); i++)
//			{
//				ofSoundPlayer s;
//				s.load(filePaths[i]);
//				s.setMultiPlay(true);
//				players[i] = s;
//			}
		}

		//-----------------------------------------------------
		/** \brief Draw
			*
			* Draws the Node and the ports.
		*/
		//-----------------------------------------------------
		void draw()
		{
			BaseNode::draw();

			for(int i = 0; i < fbo.size(); i++)
			{
				fbo[i].begin();
				ofClear(0);
				ofSetColor(0);
				ofFill();
				waveform[i].draw();
				ofSetColor(ofColor::green);
				float pos = ofMap(players[i].getPosition(),0.0,1.0,0,300);
				ofSetLineWidth(2);
				ofDrawLine(pos, 0, pos, 100);
				fbo[i].end();
			}
			ofPushStyle();
			ofSetColor(255);
			ofFill();
			
			int elementHeight = ((box.height-header.height)-2)/fbo.size();
			for(int i = 0; i < fbo.size(); i++)
			{
				fbo[i].draw(box.x+2, header.getBottom()+(i*elementHeight),box.width-4,elementHeight);
			}
		
			BaseNode::drawTooltips();
			ofPopStyle();
		}

		//-----------------------------------------------------
		/** \brief Load Sound
		* @param filePath : file to load
		*
		* Load the sound and generate waveform
		*/
		//-----------------------------------------------------
		void loadSounds(vector<string> filePath)
		{
			for(int i = 0; i < filePath.size(); i++)
			{
				ofMesh m = ofxAvUtils::waveformAsMesh(filePath[i], 150, this->box.width-4, this->box.height-25);
				waveform.push_back(m);
				ofFbo f;
				f.allocate(this->box.width-10,this->box.height-header.height);
				f.begin();
				ofClear(0);
				f.end();
				
				fbo.push_back(f);
			}
//			trackDuration = ofxAvUtils::duration(filePath);
		}
	
		//-----------------------------------------------------
		/** \brief Trigger Port
			* @param i : A integer of which event to trigger.
			*
			* This method trigger actions associated with the Node.
		*/
		//-----------------------------------------------------
		void triggerPort(int i)
		{
			players[i].play();
		}

		//-----------------------------------------------------
		/** \brief Get the File Paths for Saving
			* @return filePaths : A vector of filePaths.
			*
			* This method returns the stored filePaths for
			* saving.
		*/
		//-----------------------------------------------------
		vector<string> getInstruments()
		{
			return filePaths;
		}

	private:
		vector<string> filePaths;
		vector<ofSoundPlayer> players;
		vector<ofFbo> fbo;
		vector<ofMesh> waveform;
};
#endif /* InstrumentNode_h */
