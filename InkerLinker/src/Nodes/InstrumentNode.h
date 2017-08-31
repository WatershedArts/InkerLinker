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
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = filePaths.size();
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			for(int i = 0; i < noOfPorts; i++)
			{
				this->portNames.push_back("Action " + ofToString(i));
			}

			generatePorts(noOfPorts);

			for (int i = 0; i < filePaths.size(); i++)
			{
				ofSoundPlayer s;
				s.load(filePaths[i]);
				s.setMultiPlay(true);
				players[i] = s;
			}
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
			addMouseAndCloseListeners();

			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			for (int i = 0; i < filePaths.size(); i++)
			{
				ofSoundPlayer s;
				s.load(filePaths[i]);
				s.setMultiPlay(true);
				players[i] = s;
			}
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
			ofSetColor(255);
			ofFill();

			ofPopStyle();
			BaseNode::drawTooltips();
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
		ofSoundPlayer players[5];
};
#endif /* InstrumentNode_h */
