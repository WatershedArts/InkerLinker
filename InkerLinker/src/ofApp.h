#pragma once

#include "ofMain.h"
#include "ILGUI.h"


class ofApp : public ofBaseApp
{
	public:

		#pragma mark - oF Methods
		//-----------------------------------------------------
		void setup();
		void exit();
		void update();
		void draw();
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		#pragma mark - IL_MISC
		//-----------------------------------------------------
		/** \brief Draw Background 
			*
		*/
		//-----------------------------------------------------
		void drawBackground();
	
		//-----------------------------------------------------
		/** \brief Get a round number for the Screen Size
			* @param numToRound : number to round.
			* @param multiple : multiple number.
			* 
			* This method computes the nearest number to set
			* screen size to be.
		*/
		//-----------------------------------------------------
		int getNearestSnapSize(int numToRound, int multiple);
	
		//-----------------------------------------------------
		/** \brief Draw Bottom Bar */
		//-----------------------------------------------------
		void drawBottomBar();
	
		int noOfXPoints;
		int noOfYPoints;
};
