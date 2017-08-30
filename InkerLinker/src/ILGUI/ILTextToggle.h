//--------------------------------------------------------------
//  ILTextToggle.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Text Toggle element. */
//--------------------------------------------------------------

#ifndef ILTextToggle_h
#define ILTextToggle_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILTextToggle : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILTextToggle() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILTextToggle() { }
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Text Toggle Item.
		*/
		//-----------------------------------------------------
		ILTextToggle(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font, int offsetX = 0, ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			type = IL_TEXT_TOGGLE;
			
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
					if(bClicked) bClicked = false;
					else if(!bClicked) bClicked = true;
					
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
					string event = name + ":" + ofToString(bClicked);
					ofNotifyEvent(buttonPushed, event, this);
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
		/** \brief Mouse Moved
			* @return bClicked : bool.
			*
			* This method returns the state of the toggle.
		*/
		//-----------------------------------------------------
		bool getClicked()
		{
			return bClicked;
		}
	
		//-----------------------------------------------------
		/** \brief Set Clicked */
		//-----------------------------------------------------
		void setClicked()
		{
			bClicked = true;
		}
	
		//-----------------------------------------------------
		/** \brief Set Unclicked */
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


#endif /* ILTextToggle_h */
