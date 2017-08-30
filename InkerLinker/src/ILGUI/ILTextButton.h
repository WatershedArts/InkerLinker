//--------------------------------------------------------------
//  ILTextButton.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Text Button element. */
//--------------------------------------------------------------

#ifndef ILTextButton_h
#define ILTextButton_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILTextButton : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILTextButton() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILTextButton() { }
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Text Button Item.
		 */
		//-----------------------------------------------------
		ILTextButton(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font,int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			type = IL_TEXT_BUTTON;
			
			box = anchor;
			this->name = name;
			this->font = font;
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
			
			if(bClicked) ofSetColor(255);
			else ofSetColor(0);
			font->drawStringCentered(name, box.getCenter());
			
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
		/** \brief Set Enabled */
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
		
		ofxCenteredTrueTypeFont *font;
		ofColor colour;
		ofColor hoverColour;
};


#endif /* ILTextButton_h */
