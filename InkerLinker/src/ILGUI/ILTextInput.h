//--------------------------------------------------------------
//  ILTextInput.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Text Input element. */
//--------------------------------------------------------------

#ifndef ILTextInput_h
#define ILTextInput_h

#include "ofMain.h"
#include "ILGUIObject.h"

struct TextInputEvent {
	string name;
	string text;
};

class ILTextInput : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILTextInput() {}
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILTextInput() {}
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Text Input Item.
		*/
		//-----------------------------------------------------
		ILTextInput(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font,int offsetX, ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofAddListener(ofEvents().keyPressed, this, &ILTextInput::keyPressed);
			ofAddListener(ofEvents().mousePressed, this, &ILTextInput::mousePressed);
			ofAddListener(ofEvents().mouseMoved, this, &ILTextInput::mouseMoved);
			
			this->font = font;
			this->name = name;
			this->offsetX = offsetX;
			
			box = anchor;
			color = colour;
			bEnabled = false;
			bHovering = false;
			bHasFocus = false;
			bFirst  = true;
			type = IL_TEXT_INPUT;
		}
		
		//-----------------------------------------------------
		/// \brief Draw
		//-----------------------------------------------------
		void draw()
		{
			ofPushStyle();
			if(bHovering) ofSetColor(GUI_COLOR,200);
			else ofSetColor(200);
			
			if(bHasFocus) ofSetColor(GUI_COLOR);
			
			ofNoFill();
			ofDrawRectRounded(box,3);
			ofPushStyle();
			ofSetColor(0);
			if(typeStr == "")
			{
				font->drawStringCentered(name,box.getCenter().x,box.getCenter().y);
			}
			else
			{
				font->drawStringCentered(typeStr,box.getCenter().x,box.getCenter().y);
			}
			
			ofPopStyle();
			ofPopStyle();
		}
		
		//-----------------------------------------------------
		/// \brief Clear
		//-----------------------------------------------------
		void clear()
		{
			typeStr.clear();
			bFirst = false;
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
			
			if(bEnabled)
			{
				if(box.inside(e.x,e.y))
				{
					bHasFocus = true;
				}
				else
				{
					bHasFocus = false;
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
			if(bEnabled)
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
		}
		
		//-----------------------------------------------------
		/** \brief Key Pressed
			* @param e : Key Events.
			*
			* This method receives the keyboard events.
		*/
		//-----------------------------------------------------
		void keyPressed(ofKeyEventArgs &e)
		{
			if(bEnabled)
			{
				if(bHasFocus)
				{
					if(e.key == OF_KEY_DEL || e.key == OF_KEY_BACKSPACE)
					{
						typeStr = typeStr.substr(0, typeStr.length()-1);
					}
					else if(e.key == OF_KEY_TAB)
					{
						
					}
					else if(e.key == OF_KEY_RETURN)
					{
						TextInputEvent te;
						te.name = name;
						te.text = typeStr;

						ofNotifyEvent(guiEvent, te, this);
//						typeStr = "";
						bHasFocus = false;
						bFirst = true;
					}
					else
					{
						if( bFirst )
						{
							typeStr.clear();
							bFirst = false;
						}
						ofAppendUTF8(typeStr,e.key);
					}
				}
			}
		}
	
	ofEvent<TextInputEvent> guiEvent;
	
	private:
		bool bFirst = true;
		bool bHasFocus = false;
		string typeStr;
		ofColor color;
		ofxCenteredTrueTypeFont *font;
};


#endif /* ILTextInput_h */
