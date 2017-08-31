//--------------------------------------------------------------
//  ColourNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Colour Node Class. */
//--------------------------------------------------------------

#ifndef ColourNode_h
#define ColourNode_h

#include "BaseNode.h"

class ColourNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		ColourNode() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ColourNode() { }
		
		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param colours : A vector of ofColor.
			*
			* This method Constructs an Colour Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		ColourNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<ofColor> colours)
		{
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = colours.size();
			this->box = box;
			this->colours = colours;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			
			currentColor = 1;
			
			header = ofRectangle(box.x, box.y,box.width, 23);
			
			for(int i = 0; i < this->colours.size(); i++)
			{
				portNames.push_back(ofToString(this->colours[i]));
			}
			
			generatePorts(this->colours.size());
		}
		
		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param colours : A vector of ofColor.
			*
			* This method Constructs an Colour Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		ColourNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector <ofColor> colours)
		{
			addMouseAndCloseListeners();
			
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->colours = colours;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			currentColor = 0;
			header = ofRectangle(box.x, box.y,box.width, 23);
			
			reGeneratePortPositions(this->ports);
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
			ofFill();
			if(!colours.empty())
				ofSetColor(this->colours[currentColor]);
			else
				ofSetColor(255,0,0);
		
			ofDrawRectangle(box.x+GUI_PADDING_X, (box.y+header.height+GUI_PADDING_Y),box.width-(GUI_PADDING_X*2), (box.height-header.height)-GUI_PADDING_Y*2);
			
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
			currentColor = i;
		}
		
		//-----------------------------------------------------
		/** \brief Get the Colour Data for Saving
			* @return colours : A vector of ofColor.
			*
			* This method returns the stored arduino data for
			* saving.
		*/
		//-----------------------------------------------------
		vector <ofColor> getColours()
		{
			return colours;
		}
	
	private:
		vector <ofColor> colours;
		int currentColor;
};

#endif /* ColorNode_h */
