//--------------------------------------------------------------
//  SerialNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Serial Node Class. */
//--------------------------------------------------------------

#ifndef SerialNode_h
#define SerialNode_h

#include "BaseNode.h"

class SerialNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		SerialNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~SerialNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param commands : A vector of commands.
			*
			* This method Constructs an Serial Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		SerialNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<string> commands)
		{
			type = IL_SERIAL_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = commands.size();
			this->box = box;
			this->commands = commands;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);
			currentCommand = 0;
			this->portNames = commands;
			generatePorts(noOfPorts);
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param commands : A vector of commands.
			*
			* This method Constructs an Serial Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		SerialNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<string> commands)
		{
			type = IL_SERIAL_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->commands = commands;
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
			font->drawStringCentered(commands[0],box.getCenter().x,box.getCenter().y);
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
			if(!commands.empty())
				ofNotifyEvent(serialEvent,commands[i],this);
		}

		//-----------------------------------------------------
		/** \brief Get the Commands for Saving
			* @return command : A vector of commands.
			*
			* This method returns the stored commands for
			* saving.
		*/
		//-----------------------------------------------------
		vector <string> getCommands()
		{
			return commands;
		}

		ofEvent<string> serialEvent;
	
	private:
		int currentCommand = 0;
		vector<string> commands;
};

#endif /* SerialNode_h */
