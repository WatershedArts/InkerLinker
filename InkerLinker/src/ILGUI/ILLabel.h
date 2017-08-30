//--------------------------------------------------------------
//  ILLabel.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Label element. */
//--------------------------------------------------------------

#ifndef ILLabel_h
#define ILLabel_h

#include "ofMain.h"
#include "ILGUIObject.h"

class ILLabel : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILLabel() {}
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILLabel() {}

		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Label Item.
		*/
		//-----------------------------------------------------
		ILLabel(string name,ofRectangle anchor,ofxCenteredTrueTypeFont *font,int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			type = IL_LABEL;
			box = anchor;
			color = colour;
			this->font = font;
			this->name = name;
			this->offsetX = offsetX;
		}
		
		//-----------------------------------------------------
		/// \brief Draw
		//-----------------------------------------------------
		void draw()
		{
			ofPushStyle();
			ofSetColor(GUI_COLOR);
			ofFill();
			ofDrawRectRounded(box,3);
			ofPushStyle();
			ofSetColor(GUI_HOVERING_COLOR);
			font->drawStringCentered(name,box.getCenter());
			ofPopStyle();
			ofPopStyle();
		}
		
	private:
		
		ofColor color;
		ofxCenteredTrueTypeFont *font;
};


#endif /* ILLabel_h */
