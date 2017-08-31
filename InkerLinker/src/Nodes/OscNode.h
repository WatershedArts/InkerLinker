//--------------------------------------------------------------
//  OscNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Osc Node Class. */
//--------------------------------------------------------------
#ifndef OscNode_h
#define OscNode_h

#include "BaseNode.h"

class OscNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		OscNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~OscNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param oscData : A vector of OscData.
			*
			* This method Constructs an Osc Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		OscNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<OscData> oscData)
		{
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = oscData.size();
			this->box = box;
			this->oscData = oscData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			currentCommand = 0;
			header = ofRectangle(box.x, box.y,box.width, 23);
			for(int i = 0; i < noOfPorts; i++) {
				this->portNames.push_back("Action " + ofToString(i));
			}
			generatePorts(noOfPorts);
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param oscData : A vector of OscData.
			*
			* This method Constructs an Osc Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		OscNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<OscData> oscData)
		{
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->noOfPorts = oscData.size();
			this->oscData = oscData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			currentCommand = 0;
			header = ofRectangle(box.x, box.y,box.width, 23);
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
			ofSetColor(0);
			ofFill();
			font->drawStringCentered("Current Address", box.getCenter().x, box.getCenter().y-40);
			font->drawStringCentered(ofToString(oscData[currentCommand].address), box.getCenter().x, box.getCenter().y-20);

			font->drawStringCentered("Values", box.getCenter().x, box.getCenter().y+20);

			for(int i = 0; i < oscData[currentCommand].value.size(); i++)
			{
				font->drawStringCentered(ofToString(oscData[currentCommand].value[i]), box.getCenter().x, box.getCenter().y+40+(i*15));
			}

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
			if(!oscData.empty())
				ofNotifyEvent(oscEvent, oscData[i], this);
		}

		//-----------------------------------------------------
		/** \brief Get the Osc Data for Saving
			* @return oscData : A vector of OscData.
			*
			* This method returns the stored osc data for
			* saving.
		*/
		//-----------------------------------------------------
		vector<OscData> getOscData()
		{
			return oscData;
		}

		ofEvent<OscData> oscEvent;
	private:
		string filePath;
		vector<OscData> oscData;
		int currentCommand = 0;
};


#endif /* OscNode_h */
