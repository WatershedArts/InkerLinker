//--------------------------------------------------------------
//  ILColorPicker.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Color picker element. */
//--------------------------------------------------------------

#ifndef ILColorPicker_h
#define ILColorPicker_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILColorPicker : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILColorPicker() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILColorPicker() { }

		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param box : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			*
			* This method creates a new Text Toggle Item.
		*/
		//-----------------------------------------------------
		ILColorPicker(string name,ofRectangle box,ofxCenteredTrueTypeFont *font,int offsetX = 0)
		{
			ofRegisterMouseEvents(this);
			this->box = box;
			this->font = font;
			this->name = name;
			this->offsetX = offsetX;

			type = IL_COLOR_PICKER;
			colorPalette.load("defaultColorPalette.png");
			bHasFocus = false;
			bEnabled = false;
			colorPalette.resize(box.width, box.height);
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
			ofFill();
			colorPalette.draw(box.x,box.y,box.width,box.height);
			
			if(bHasFocus) ofSetColor(GUI_COLOR);
			else ofSetColor(GUI_COLOR,200);
			ofPushStyle();
			if(bHasFocus) ofSetColor(GUI_COLOR);
			else ofSetColor(ofColor::gray);
			ofNoFill();
			ofDrawRectRounded(box,3);
			ofPopStyle();
			
			ofSetColor(selectedColor);
			ofDrawRectangle((box.x+box.width+GUI_PADDING_X)-25,box.y+GUI_PADDING_Y,20,20);
			ofNoFill();
			ofSetColor(0);
			ofDrawRectangle((box.x+box.width+GUI_PADDING_X)-25,box.y+GUI_PADDING_Y,20,20);
			ofFill();
			for(int i = 0; i < tmpColours.size(); i++)
			{
				ofSetColor(tmpColours[i]);
				ofDrawRectangle((box.x+box.width+GUI_PADDING_X)-25,box.y+GUI_PADDING_Y+20+GUI_PADDING_Y+(i*(20+GUI_PADDING_Y)),20,20);
			}
		
			ofPopStyle();
		}

		//-----------------------------------------------------
		/** \brief Add New Colour
			* @param col : Temp Colour
			*
			* This method adds a temp colour into the vector
			* as a visual cue for the user.
		*/
		//-----------------------------------------------------
		void addNewColour(ofColor col)
		{
			tmpColours.push_back(col);
		}

		//-----------------------------------------------------
		/** \brief Remove Last Color
			*
			* This method removes the last color entered in to
			* the vector.
		*/
		//-----------------------------------------------------
		void removeColour()
		{
			if(tmpColours.size() > 0)
				tmpColours.pop_back();
		}

		//-----------------------------------------------------
		/** \brief Clear Color Display
			*
			* This method clears the colors stored in the 
			* temporary vector.
		*/
		//-----------------------------------------------------
		void clearColours()
		{
			tmpColours.clear();
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
					selectedColor = colorPalette.getColor(e.x-box.x,e.y-box.y);
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
						selectedColor = colorPalette.getColor(e.x-box.x,e.y-box.y);
						
						ColourPickerEvent ce;
						ce.name = name;
						ce.colour = selectedColor;
						
						ofNotifyEvent(guiEvent,ce,this);
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
					if (box.inside(e.x, e.y))
					{
						selectedColor = colorPalette.getColor(e.x-box.x,e.y-box.y);
					}
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
	
		ofEvent<ColourPickerEvent> guiEvent;
	
	private:
		vector <ofColor> tmpColours;
		ofImage colorPalette;
		ofColor selectedColor;
		bool bHasFocus;
		ofxCenteredTrueTypeFont *font;
};
#endif /* ILColorPicker_h */
