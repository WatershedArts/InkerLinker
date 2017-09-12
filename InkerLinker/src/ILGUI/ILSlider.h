//--------------------------------------------------------------
//  ILSlider.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Slider element. */
//--------------------------------------------------------------

#ifndef ILSlider_h
#define ILSlider_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILSlider : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILSlider() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILSlider() { }

		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param box : slider pos and size.
			* @param font : copy of font.
			* @param min : min value
			* @param max : max value
			* @param value : default value
			* @param bAsInts : cast to int
			* @param offsetX : offset of the element.
			* @param colour : colour of item./
			* @param colour : hover colour of item.
			*
			* This method creates a new Slider Item.
		*/
		//-----------------------------------------------------
		ILSlider(string name,ofRectangle box,ofxCenteredTrueTypeFont *font,float min, float max,float value,int offsetX = 0,bool bVert = false,bool bAsInts = false,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			this->box = box;
			this->font = font;
			this->name = name;
			this->offsetX = offsetX;
			
			type = IL_SLIDER;
			this->value = value;
			bVertical = bVert;
			highVal = max;
			lowVal = min;
			bAsInt = bAsInts;
			bHasFocus = false;
			bEnabled = false;
		}

		//-----------------------------------------------------
		/** \brief Sets the Value
			*
			* Sets the Value for the Slider
		*/
		//-----------------------------------------------------
		void setValue(float val)
		{
			value  = val;
		}

		//-----------------------------------------------------
		/** \brief Update the Slider via the mouse
			*
			* This method updates the slider value from the mouse
		*/
		//-----------------------------------------------------
		void updatePercentFromMouse(int mx, int my)
		{
			// Given the mouse value, compute the percentage.
			if (bVertical)
			{
				if(!bAsInt) value = ofMap(my, getY(), getY()+getHeight(), highVal,lowVal, true);
				else value = round(ofMap(my, getY(), getY()+getHeight(), highVal,lowVal, true));
			}
			else
			{
				if(!bAsInt) value = ofMap(mx, getX(), getX()+getWidth(), lowVal,highVal, true);
				else value = round(ofMap(mx, getX(), getX()+getWidth(), lowVal,highVal, true));
			}
			//evtData.value = value;
			
			SliderEvent se;
			se.name = name;
			se.value = ofToString(value);
			
			ofNotifyEvent(guiEvent,se,this);
			
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

			if(bHasFocus) ofSetColor(GUI_COLOR);
			else ofSetColor(GUI_COLOR,200);

			ofFill();

			if(!bVertical)
			{
				ofDrawRectangle(box.x+(GUI_PADDING_Y*2),box.y+(GUI_PADDING_Y*2),ofMap(value,lowVal,highVal,0,box.width-(GUI_PADDING_Y*4)),box.height-(GUI_PADDING_Y*4));
			}
			else
			{
				ofDrawRectRounded(box.x+(GUI_PADDING_Y*2),
				box.y+(GUI_PADDING_Y*2),
				box.width-(GUI_PADDING_X*4),
				ofMap(value,lowVal,highVal,box.y,box.height-(GUI_PADDING_Y*4))
				,3);
			}

			ofPushStyle();
			if(bHasFocus) ofSetColor(GUI_COLOR);
			else ofSetColor(ofColor::gray);
			ofNoFill();
			ofDrawRectRounded(box,3);
			ofPopStyle();
			ofSetColor(0);
			font->drawStringCentered(name + " " + ofToString(value),box.getCenter().x,box.getCenter().y);
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
			if(bEnabled)
			{
				bHasFocus = false;
				if (box.inside(e.x, e.y))
				{
					bHasFocus = true;
					updatePercentFromMouse (e.x, e.y);
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
				if (bHasFocus)
				{
					if (box.inside(e.x, e.y))
					{
						updatePercentFromMouse (e.x, e.y);
					}
				}
				bHasFocus = false;
			}
		}

		//-----------------------------------------------------
		/** \brief Mouse Dragged
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseDragged(ofMouseEventArgs &e)
		{
			if(bEnabled)
			{
				if (bHasFocus)
				{
					updatePercentFromMouse (e.x, e.y);
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
				bHasFocus = false;
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

		void mouseEntered(ofMouseEventArgs &e){}
		void mouseExited(ofMouseEventArgs &e){}
		void mouseScrolled(ofMouseEventArgs &e){}

		ofEvent<SliderEvent> guiEvent;
	
	private:

		float value;
		float lowVal;
		float highVal;
		bool bVertical;
		bool bHasFocus;
		bool bAsInt;
		ofxCenteredTrueTypeFont *font;
};


#endif /* ILSlider_h */
