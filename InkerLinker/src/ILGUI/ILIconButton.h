//--------------------------------------------------------------
//  ILIconButton.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Icon Button element. */
//--------------------------------------------------------------

#ifndef ILIconButton_h
#define ILIconButton_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILIconButton : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILIconButton() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILIconButton() { }
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param icon : icon.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Icon Button Item.
		*/
		//-----------------------------------------------------
		ILIconButton(string name,ofRectangle anchor, IL_GUI_ICON_TYPE icon, int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			
			type = IL_ICON_BUTTON;
			box = anchor;
			
			this->name = name;
			this->icon = icon;
			this->colour = colour;
			this->hoverColour = hoverColour;
			this->offsetX = offsetX;
			
			bClicked = false;
		}
		
		//-----------------------------------------------------
		/** \brief Draw
			*
			* Draws the Node and the ports.
		*/
		//-----------------------------------------------------
		void draw()
		{
			ofPushStyle();
			ofSetColor(255);
			
			if(bHovering) ofSetColor(240, 240, 240);
			else ofSetColor(255,255);
			
			if(bClicked) ofSetColor(GUI_COLOR);
			ofFill();
			ofDrawRectRounded(box,3);
			
			ofPushMatrix();
			if(bHovering) ofSetColor(255);
			else ofSetColor(0);
			ofSetLineWidth(4);
			
			switch (icon) {
				case IL_ICON_CROSS:
				{
					ofDrawLine(box.getTopLeft()+ofPoint(5,5),box.getBottomRight()+ofPoint(-5,-5));
					ofDrawLine(box.getTopRight()+ofPoint(-5,5),box.getBottomLeft()+ofPoint(5,-5));
				}
				break;
				case IL_ICON_PLUS:
				{
					int length = (box.getBottom()-2) - (box.getTop()+2);
					ofDrawLine(box.getCenter().x,box.getTop()+2,box.getCenter().x,box.getBottom()-2);
					ofDrawLine(box.getCenter().x-(length/2),box.getCenter().y,box.getCenter().x+(length/2),box.getCenter().y);
				}
				break;
				case IL_ICON_MINUS:
				{
					int length = (box.getBottom()-2) - (box.getTop()+2);
					ofDrawLine(box.getCenter().x-(length/2),box.getCenter().y,box.getCenter().x+(length/2),box.getCenter().y);
				}
				break;
				default: break;
			}
			
			ofPopMatrix();
			ofPopStyle();
		}
		
		//-----------------------------------------------------
		/** \brief Mouse Pressed
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mousePressed(ofMouseEventArgs &e)
		{
			if(bEnabled) {
				if(box.inside(e.x,e.y))
				{
					bClicked = true;
				}
			}
		}
		
		//-----------------------------------------------------
		/** \brief Mouse Released
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseReleased(ofMouseEventArgs &e)
		{
			if(bEnabled)
			{
				if(box.inside(e.x,e.y))
				{
					ofNotifyEvent(buttonPushed, name, this);
					bClicked = false;
				}
			}
		}
		
		//-----------------------------------------------------
		/** \brief Mouse Moved
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseMoved(ofMouseEventArgs &e)
		{
			if(box.inside(e.x,e.y))
			{
				bHovering = true;
			}
			else
			{
				bHovering = false;
			}
		}
		
		//-----------------------------------------------------
		/// \brief Set Enabled
		//-----------------------------------------------------
		void setUnclicked()
		{
			bClicked = false;
		}
		
		void mouseDragged(ofMouseEventArgs &e){}
		void mouseEntered(ofMouseEventArgs &e){}
		void mouseExited(ofMouseEventArgs &e){}
		void mouseScrolled(ofMouseEventArgs &e){}
		
		ofEvent<string> buttonPushed;
		ofEvent<string> buttonReleased;
		
	private:
	
		IL_GUI_ICON_TYPE icon;
		ofColor colour;
		ofColor hoverColour;
};

#endif /* ILIconButton_h */
