//--------------------------------------------------------------
//  TouchBoardManager.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Touch Board Manager. */
//--------------------------------------------------------------

#ifndef TouchBoardManager_h
#define TouchBoardManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxTouchBoard.h"
#include "ofxSvgLoader.h"

enum TB_POINT_TYPE
{
	TB_TOUCH_POINT = 0,
	TB_RELEASE_POINT = 1
};

struct Electrode
{
	string id;
	ofRectangle area;
	bool bHover;
	bool bAction;
	TB_POINT_TYPE type;
	ofPoint offset;
};

// Our Debug Message Sender
template<typename T>
void DebugMessage(T s_Class,T s_Message) {
	
	ofSendMessage(string(s_Class) + " | " + string(s_Message));
}

class TouchBoardManager
{
	public:
		//-----------------------------------------------------
		/** \brief Setup the Touch Board */
		//-----------------------------------------------------
		void setup();
	
		//-----------------------------------------------------
		/** \brief Add Listeners */
		//-----------------------------------------------------
		void addListenersMouseAndTouchEvents();
	
		//-----------------------------------------------------
		/** \brief Remove Listeners */
		//-----------------------------------------------------
		void removeListenersMouseAndTouchEvents();
	
		//-----------------------------------------------------
		/** \brief Update the Touch Board */
		//-----------------------------------------------------
		void update();
		
		//-----------------------------------------------------
		/** \brief Draw */
		//-----------------------------------------------------
		void draw();
		
		//-----------------------------------------------------
		/** \brief Draw Debug */
		//-----------------------------------------------------
		void drawDebug();
		
		//-----------------------------------------------------
		/** \brief Simulate Touch Event
			* @param i : electrode no to simulate
			*
			* This method simulates a touch event.
		*/
		//-----------------------------------------------------
		void simulateTouchEvent(int i);
		
		//-----------------------------------------------------
		/** \brief Simulate Release Event
			* @param i : electrode no to simulate
			*
			* This method simulates a Release event.
		*/
		//-----------------------------------------------------
		void simulateReleaseEvent(int i);
		
		//-----------------------------------------------------
		/** \brief Mouse Pressed
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mousePressed(ofMouseEventArgs &e);
		
		//-----------------------------------------------------
		/** \brief Mouse Dragged
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseDragged(ofMouseEventArgs &e);
		
		//-----------------------------------------------------
		/** \brief Mouse Released
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseReleased(ofMouseEventArgs &e);
		
		//-----------------------------------------------------
		/** \brief Mouse Moved
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseMoved(ofMouseEventArgs &e);
	
		//-----------------------------------------------------
		/** \brief Window Resized
			* @param e : Resize Event.
			*
			* This method receives window resizing event.
		*/
		//-----------------------------------------------------
		void windowResized(ofResizeEventArgs &e);
	
		//-----------------------------------------------------
		/** \brief Recalculate The Electrodes
			* @param w : width.
			* @param h : height.
			*
			* This method recalculates the positions of the 
			* electrodes.
		*/
		//-----------------------------------------------------
		void recalculateElectrodesPositions(int w,int h);
	
		//-----------------------------------------------------
		/** \brief Is Hit
			* @param x : x position.
			* @param y : y position.
			*
			* This method check whether the mouse is over the 
			* svg.
		*/
		//-----------------------------------------------------
		bool isHit(int x, int y);
		
		//-----------------------------------------------------
		/** \brief Check Touch Board Connectivity
			* @return bool : is connected.
			*
			* This method check the connection between the 
			* touch board and the machine.
		*/
		//-----------------------------------------------------
		bool isConnected();
	
		ofEvent<string> touch;
		ofEvent<string> release;
		ofEvent<Electrode> clickElectrode;
		ofEvent<Electrode> removePatchCord;
		
		vector <float> tThs;
		vector <float> rThs;
		
	private:

		ofxSvgLoader tb;
		ofxTouchBoard touchBoard;
		void touched(int& e);
		void released(int& e);
	
		ofRectangle touchRectangle;
		vector <Electrode> touchPoints;
		vector <Electrode> releasePoints;
	};
	
#endif /* TouchBoardManager_h */
