//--------------------------------------------------------------
//  ILRadioToggle.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Radio Toggle element. */
//--------------------------------------------------------------

#ifndef ILRadioToggle_h
#define ILRadioToggle_h

#include "ILGUIObject.h"
#include "ILTextToggle.h"

class ILRadioToggle : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILRadioToggle() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILRadioToggle() { }
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param names : names of the
			* @param orientation : vertical or horizontal
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Radio Toggle Item.
		*/
		//-----------------------------------------------------
		ILRadioToggle(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font, vector<string> names,bool orientation = false,int offsetX = 0, ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			type = IL_RADIO_TOGGLE;
			
			box = anchor;
			this->name = name;
			this->font = font;
			this->colour = colour;
			this->hoverColour = hoverColour;
			this->offsetX = offsetX;
			lastbuttonpushed = "";
			bClicked = false;
			
			if(!orientation)
			{
				newHeight = box.height;
				int toggleSize = (box.width / names.size()) - GUI_PADDING_X;
				for (int i = 0; i < names.size(); i++)
				{
					if(i == 0)
					{
						toggles.push_back(new ILTextToggle(names[i],ofRectangle(box.x,box.y+GUI_PADDING_Y,toggleSize,box.height-(GUI_PADDING_Y)),font,GUI_PADDING_X));
					}
					else
					{
						int posx = i * (toggleSize + GUI_PADDING_X);
					
						toggles.push_back(new ILTextToggle(names[i],ofRectangle(box.x+posx ,box.y+GUI_PADDING_Y,toggleSize,box.height-(GUI_PADDING_Y)),font,abs(posx)));
					}
				}
			}
			else {
				for (int i = 0; i < names.size(); i++)
				{
					toggles.push_back(new ILTextToggle(names[i],ofRectangle(box.x+GUI_PADDING_X/2,(box.y+GUI_PADDING_Y)+(i*box.height),box.width-GUI_PADDING_X,box.height-(GUI_PADDING_Y)),font,GUI_PADDING_X));
					newHeight += (box.height);
				}
			}
			
			for(int i = 0; i < toggles.size(); i++)
			{
				toggles[i]->setEnabled(true);
				ofAddListener(toggles[i]->buttonPushed,this,&ILRadioToggle::radioListener);
			}
			
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
			for(int i = 0; i < toggles.size(); i++)
			{
				toggles[i]->draw();
			}
			
			if(bHovering) ofSetColor(240, 240, 240);
			else ofSetColor(255,255);
			ofNoFill();
			ofDrawRectRounded(box,3);
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
			for(int i = 0; i < toggles.size(); i++)
			{
				toggles[i]->setUnclicked();
			}
		}

		//-----------------------------------------------------
		/** \brief Listen for click events
			* @param val : radio clicks
			*
			* This method listens for clicks on the radio.
		*/
		//-----------------------------------------------------
		void radioListener(string &val)
		{
			vector <string> evt = ofSplitString(val, ":");
			
			if(evt[0] == lastbuttonpushed || evt[0] == "")
			{
				for(int i = 0; i < toggles.size(); i++)
				{
					if(toggles[i]->getName() == lastbuttonpushed)
					{
						if(evt[1] == "0" && toggles[i]->getClicked()) toggles[i]->setUnclicked();
						else if(evt[1] == "1" && !toggles[i]->getClicked()) toggles[i]->setClicked();
					}
				}
				lastbuttonpushed = evt[0];
			}
			else if (lastbuttonpushed != evt[0])
			{
				lastbuttonpushed = evt[0];
				setUnclicked();
				for(int i = 0; i < toggles.size(); i++)
				{
					if(toggles[i]->getName() == evt[0])
					{
						toggles[i]->setClicked();
					}
				}
			}
			
		
			RadioEvent e;
			e.radioname = name;
			e.value = val;
			ofNotifyEvent(guiEvent, e, this);
		}
	
		//-----------------------------------------------------
		/** \brief Enables the Gui
			* @param enabled : is enable.
			*
			* This method set the gui element to enabled / un.
		*/
		//-----------------------------------------------------
		void setEnabled(bool enabled)
		{
			bEnabled = enabled;
			
			for (auto i : toggles)
			{
				i->setEnabled(enabled);
			}
		}
	
		//-----------------------------------------------------
		/** \brief Recalculates the positions of the gui element
			* @param newX : new position
			*
			* This method reports the new position of the gui.
		*/
		//-----------------------------------------------------
		void setX(int newX)
		{
			box.x = newX;
			for(int i = 0; i < toggles.size(); i++)
			{
				toggles[i]->setX(box.x+toggles[i]->getOffsetX());
			}
		}
	
		//-----------------------------------------------------
		/** \brief Get the Radio Height
			* @return newHeight : height of element.
			*
			* This method reports the new height of the radio.
		*/
		//-----------------------------------------------------
		int getRadioHeight()
		{
			return newHeight;
		}
	
		void mouseReleased(ofMouseEventArgs &e) {}
		void mouseDragged(ofMouseEventArgs &e){}
		void mouseEntered(ofMouseEventArgs &e){}
		void mouseExited(ofMouseEventArgs &e){}
		void mouseScrolled(ofMouseEventArgs &e){}
		
		ofEvent<RadioEvent> guiEvent;
		
	private:
		vector<ILTextToggle*> toggles;
		ofxCenteredTrueTypeFont *font;
		ofColor colour;
		ofColor hoverColour;
		string lastbuttonpushed;
		int newHeight = 0;
};

#endif /* ILRadioToggle_h */
