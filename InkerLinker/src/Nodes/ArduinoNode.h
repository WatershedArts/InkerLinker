//--------------------------------------------------------------
//  ArduinoNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Arduino Node Class. */
//--------------------------------------------------------------

#ifndef ArduinoNode_h
#define ArduinoNode_h

#include "BaseNode.h"

class ArduinoNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		ArduinoNode() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ArduinoNode() { }
		
		//-----------------------------------------------------
		/** \brief Constructor.
			 * @param box  : The position of the Node.
			 * @param font : The font.
			 * @param name : The name of the Node.
			 * @param id   : Pointer to the id of the Node.
			 * @param arduinoData : A vector of ArduinoData.
			 *
			 * This method Constructs an Arduino Node from scratch
			 * it generates the ports and layout of the node
		 */
		//-----------------------------------------------------
		ArduinoNode(ofRectangle box,ofxCenteredTrueTypeFont *font, string name, int *id,vector<ArduinoData> arduinoData)
		{
			type = IL_ARDUINO_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = arduinoData.size();
			this->box = box;
			this->arduinoData = arduinoData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			
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
			 * @param arduinoData : A vector of ArduinoData.
			 *
			 * This method Constructs an Arduino Node from the
			 * load file it generates the ports and layout of 
			 * the node.
		 */
		//-----------------------------------------------------
		ArduinoNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<ArduinoData> arduinoData)
		{
			type = IL_ARDUINO_NODE;
			addMouseAndCloseListeners();
			
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->noOfPorts = arduinoData.size();
			this->arduinoData = arduinoData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			
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
			if(!arduinoData.empty())
				ofNotifyEvent(arduinoEvent, arduinoData[i], this);
		}
		
		//-----------------------------------------------------
		/** \brief Get the Arduino Data for Saving
			 * @return arduinoData : A vector of ArduinoData.
			 *
			 * This method returns the stored arduino data for
			 * saving.
		 */
		//-----------------------------------------------------
		vector<ArduinoData> getArduinoData()
		{
			return arduinoData;
		}
		
		ofEvent<ArduinoData> arduinoEvent;
	private:
		vector<ArduinoData> arduinoData;
};


#endif /* ArduinoNode_h */
