//--------------------------------------------------------------
//  SoundNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Sound Node Class. */
//--------------------------------------------------------------

#ifndef SoundNode_h
#define SoundNode_h

#include "BaseNode.h"
#include "ofxAvUtils.h"

class SoundNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		SoundNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~SoundNode() { player.stop(); }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param filePath : a filePath.
			*
			* This method Constructs an Sound Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		SoundNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,string filePath)
		{
			type = IL_SOUND_NODE;
			this->portNames = {"Play", "Stop", "Reset"};
			bIsNodeSizeLocked = true;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = portNames.size();
			this->box = box;

			this->box = ofRectangle(box.x,box.y,300,100);
			this->filePath = filePath;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(this->box.x, this->box.y,this->box.width, 23);

			generatePorts(noOfPorts);

			loadSound(filePath);
			fbo.allocate(this->box.width-10,this->box.height-header.height);
			fbo.begin();
			ofClear(0);
			fbo.end();
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param filePath : a filePath.
			*
			* This method Constructs an Sound Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		SoundNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,string filePath)
		{
			type = IL_SOUND_NODE;
			addMouseAndCloseListeners();
			bIsNodeSizeLocked = true;
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->filePath = filePath;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			header = ofRectangle(box.x, box.y,box.width, 23);
			loadSound(filePath);
		}

		//-----------------------------------------------------
		/** \brief Load Sound
			* @param filePath : file to load
			*
			* Load the sound and generate waveform
		*/
		//-----------------------------------------------------
		void loadSound(string filePath)
		{
			player.load(filePath);
			waveform = ofxAvUtils::waveformAsMesh(filePath, 150, this->box.width-4, this->box.height-25);
			trackDuration = ofxAvUtils::duration(filePath);
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
			ofPushStyle();

			fbo.begin();
			ofClear(0);
			ofSetColor(0);
			ofFill();
			waveform.draw();
			ofSetColor(ofColor::green);
			float pos = ofMap(player.getPosition(),0.0,1.0,0,300);
			ofSetLineWidth(2);
			ofDrawLine(pos, 0, pos, 100);
			fbo.end();

			ofSetColor(255);
			ofFill();
			fbo.draw(box.x+2,header.getBottom(),box.width-4,(box.height-header.height)-4);

			BaseNode::drawTooltips();
			ofPopStyle();
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
			if(i == 0)
			{
				player.play();
			}
			else if(i == 1)
			{
				player.stop();
			}
			else if(i == 2)
			{
				player.setPosition(0);
				player.stop();
			}
		}

		//-----------------------------------------------------
		/** \brief Get the File Path for Saving
			* @return filePaths : A filePath.
			*
			* This method returns the stored filePath for
			* saving.
		*/
		//-----------------------------------------------------
		string getFilePath()
		{
			return filePath;
		}

	private:
		string filePath;
		ofSoundPlayer player;
		ofFbo fbo;
		ofMesh waveform;
		float trackDuration;
};


#endif /* SoundNode_h */
