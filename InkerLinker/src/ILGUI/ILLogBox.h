//--------------------------------------------------------------
//  ILLogBox.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Log Box element. */
//--------------------------------------------------------------

#ifndef ILLogBox_h
#define ILLogBox_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILLogBox : public ILGUIObject
{
	public:
		
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILLogBox() {}
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILLogBox() {}
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Log Box Item.
		*/
		//-----------------------------------------------------
		ILLogBox(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font,int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			box = anchor;
			color = colour;
			this->font = font;
			this->name = name;
			this->offsetX = offsetX;
			type = IL_LOG_BOX;
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
			ofSetColor(GUI_HOVERING_COLOR);
			ofSetColor(0);
			ofNoFill();
			
			ofDrawRectRounded(box.x+GUI_PADDING_X,box.y,box.width-(GUI_PADDING_X*2),box.height,3);
			
			for(int i = 0; i < logs.size(); i++)
			{
				if (logs[i].size() > 0) {
					if(logs[i].at(0) != '/') {
						font->drawStringCentered(logs[i],box.getCenter().x,box.y+15+(i*15));
					}
					else {
						std::size_t found = logs[i].find_last_of("/\\");
						font->drawStringCentered(logs[i].substr(found+1),box.getCenter().x,box.y+15+(i*15));
					}
				}
			}
			ofPopStyle();
		}
		
		//-----------------------------------------------------
		/** \brief Add a new message to the log
			* @param message : new message.
			*
			* This method adds a new message into the deque.
		*/
		//-----------------------------------------------------
		void addNewMessage(string message)
		{
			if(logs.size() > 11) logs.pop_front();
			logs.push_back(message);
		}
		
		//-----------------------------------------------------
		/** \brief Add a new message to the log
			*
			* This method removes the last message from the deque.
		*/
		//-----------------------------------------------------
		void removeLastMessage()
		{
			if(!logs.empty()) logs.pop_back();
		}
		
		//-----------------------------------------------------
		/** \brief Clears message from the log
			*
			* This method clears the messages.
		*/
		//-----------------------------------------------------
		void clearLogs()
		{
			logs.clear();
		}
	
	private:
		ofColor color;
		ofxCenteredTrueTypeFont *font;
		deque <string> logs;
};



#endif /* ILLogBox_h */
