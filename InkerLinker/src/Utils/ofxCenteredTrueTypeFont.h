#pragma once

#include "ofMain.h"

class ofxCenteredTrueTypeFont : public ofTrueTypeFont
{
	public:
	
		//-----------------------------------------------------
		/** \brief Get Offset
			* @param s : string.
			* @return ofVec2f : offset.
			*
			* This method gets the offset of the string s.
		*/
		//-----------------------------------------------------
		ofVec2f getOffset( string s )
		{
			ofRectangle r = getStringBoundingBox(s, 0, 0);
			return ofVec2f( floor(-r.x - r.width * 0.5f), floor(-r.y - r.height * 0.5f) );
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param x : x position.
			* @param y : y position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCentered(string s, float x, float y, bool asVector = false)
		{
			ofVec2f offset = getOffset(s);
			if (!asVector)
				drawString(s, x + offset.x, y + offset.y);
			else
				drawStringAsShapes(s, x + offset.x, y + offset.y);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCentered(string s, ofVec2f pos, bool asVector = false)
		{
			drawStringCentered(s, pos.x, pos.y, asVector);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param padding :
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawCenteredBoundingBox(string s, float x, float y, float padding = 0)
		{
			ofRectangle r = getStringBoundingBox(s, 0, 0);
			r.x -= padding;
			r.y -= padding;
			r.width += 2.0f * padding;
			r.height += 2.0f * padding;
			ofSetRectMode(OF_RECTMODE_CENTER);
			ofDrawRectangle( x, y, r.width, r.height);
			ofSetRectMode(OF_RECTMODE_CORNER);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawCenteredBoundingBox(string s, ofVec2f pos, float padding = 0)
		{
			drawCenteredBoundingBox(s, pos.x, pos.y, padding);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCenteredVertically(string s, float x, float y)
		{
			ofVec2f offset = getOffset(s);
			drawString(s, x, y + offset.y );
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCenteredVertically(string s, ofVec2f pos)
		{
			drawStringCenteredVertically(s, pos.x, pos.y);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCenteredHorizontally(string s, float x, float y)
		{
			ofVec2f offset = getOffset(s);
			drawString(s, x + offset.x, y);
		}
	
		//-----------------------------------------------------
		/** \brief Draw String Centered
			* @param s : string.
			* @param pos : position.
			* @param asVector : render as vector
			*
			* This method draws the string central
		*/
		//-----------------------------------------------------
		void drawStringCenteredHorizontally(string s, ofVec2f pos)
		{
			drawStringCenteredHorizontally(s, pos.x, pos.y);
		}
};
