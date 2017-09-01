//--------------------------------------------------------------
//  CloudBitNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the CloudBit Node Class. */
//--------------------------------------------------------------

#ifndef CloudBitNode_h
#define CloudBitNode_h

#include "BaseNode.h"

class CloudBitNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		CloudBitNode() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~CloudBitNode() { }
		
		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param cloudBitData : A vector of CloudBitData.
			*
			* This method Constructs an CloudBit Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		CloudBitNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<CloudBitData> cloudBitData)
		{			
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = cloudBitData.size();
			this->box = box;
			this->cloudBitData = cloudBitData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			
			header = ofRectangle(box.x, box.y,box.width, 23);
			currentCommand = 0;
			
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
			* @param cloudBitData : A vector of CloudBitData.
			*
			* This method Constructs an CloudBit Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		CloudBitNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<CloudBitData> cloudBitData)
		{
			addMouseAndCloseListeners();
			
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->noOfPorts = cloudBitData.size();
			this->cloudBitData = cloudBitData;
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
			font->drawStringCentered("Current Percent", box.getCenter().x, box.getCenter().y-40);
			font->drawStringCentered(ofToString(cloudBitData[currentCommand].percent), box.getCenter().x, box.getCenter().y-20);
			
			font->drawStringCentered("Current Duration", box.getCenter().x, box.getCenter().y+20);
			if(cloudBitData[currentCommand].duration_ms == "-1") font->drawStringCentered("Always", box.getCenter().x, box.getCenter().y+40);
			else font->drawStringCentered(ofToString(cloudBitData[currentCommand].duration_ms), box.getCenter().x, box.getCenter().y+40);
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
			if(!cloudBitData.empty())
				ofNotifyEvent(cloudDataEvent, cloudBitData[i], this);
		}
		
		//-----------------------------------------------------
		/** \brief Get the CloudBitData for Saving
			* @return cloudBitData : A vector of CloudBitData.
			*
			* This method returns the stored CloudBit data for
			* saving.
		*/
		//-----------------------------------------------------
		vector <CloudBitData> getCloudBitData()
		{
			return cloudBitData;
		}
		
		ofEvent<CloudBitData> cloudDataEvent;
	private:
		vector<CloudBitData> cloudBitData;
		int currentCommand = 0;
};

#endif /* CloudBitNode_h */
