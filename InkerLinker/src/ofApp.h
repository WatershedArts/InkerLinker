#pragma once

#include "ofMain.h"
#include "ILGUI.h"
#include "TouchBoardManager.h"

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
	
		#pragma mark - IL_GUI
	
		// GUI Objects
		ILGUI *gui;
		ILGUI *iogui;
		ILGUI *nodegui;
		ILGUI *debuggui;
		ILGUI *savegui;
	
		ILGUI *arduinoNodeGui;
		ILGUI *cloudBitNodeGui;
		ILGUI *colorNodeGui;
		ILGUI *httpNodeGui;
		ILGUI *imageCaroselNodeGui;
		ILGUI *instrumentNodeGui;
		ILGUI *oscNodeGui;
		ILGUI *qlabNodeGui;
		ILGUI *serialNodeGui;
		ILGUI *soundNodeGui;
		ILGUI *timerNodeGui;
		ILGUI *videoNodeGui;

		ArduinoData tmpArduinoData;
		CloudBitData tmpCloudBitData;
		HTTPData tmpHttpData;
		POSTData tmpPostData;
		QLabData tmpQLabData;
		OscData tmpOscData;
	
		ofColor tmpColor;
		string tmpImageFile;
		string tmpInstrumentFile;
		string tmpSerialCommand;
		string tmpSoundFile;
		string tmpVideoFile;
	
		//-----------------------------------------------------
		/** \brief Setup GUI's 
			* 
			* This method sets up all of the GUI's.
		*/
		//-----------------------------------------------------
		void setupGuis();
	
		//-----------------------------------------------------
		/** \brief Draw GUI's
			*
			* This method draws all the guis.
		*/
		//-----------------------------------------------------
		void drawGuis();
	
		//-----------------------------------------------------
		/** \brief Delete GUI's
			*
			* This method deletes the GUI's
		*/
		//-----------------------------------------------------
		void deleteGuis();
	
		//-----------------------------------------------------
		/** \brief Add Listeners to the GUI's
			* @param gui : pointer to the Gui. 
			*
			* This method adds the required listeners to the
			* GUI's.
		*/
		//-----------------------------------------------------
		void addListenersToGuis(ILGUI *gui);

		//-----------------------------------------------------
		/** \brief Svg Toggle Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void svgToggleEvents(string &val);

		//-----------------------------------------------------
		/** \brief Svg Button Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void svgButtonEvents(string &val);

		//-----------------------------------------------------
		/** \brief Icon Button Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void iconButtonEvents(string &val);

		//-----------------------------------------------------
		/** \brief Text Button Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void textButtonEvents(string &val);

		//-----------------------------------------------------
		/** \brief Text Toggle Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void textToggleEvents(string &val);

		//-----------------------------------------------------
		/** \brief Text Input Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void textInputEvents(TextInputEvent &val);

		//-----------------------------------------------------
		/** \brief Slider Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void sliderEvents(SliderEvent &val);

		//-----------------------------------------------------
		/** \brief Colour Picker Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void colorPickerEvents(ColourPickerEvent &val);

		//-----------------------------------------------------
		/** \brief Radio Event Listener
			* @param val : return value from gui elements.
			*
			* This method listens to events from the gui
			* elements.
		*/
		//-----------------------------------------------------
		void radioEvents(RadioEvent &val);

		//-----------------------------------------------------
		/** \brief Hide all Node Guis
			*
			* This method hides all the node guis.
		*/
		//-----------------------------------------------------
		void hideAllNodeGuis();

		//-----------------------------------------------------
		/** \brief Clear the Node Gui of Data
			*
			* This method clears the guis of data.
		*/
		//-----------------------------------------------------
		void clearContexts();
	
		#pragma mark - IL_TOUCH_BOARD
	
		TouchBoardManager touchBoardManager;
	
		//-----------------------------------------------------
		/** \brief Setup Touchboard
			*
			* This method sets up the touch board manager
			* and attaches listeners to the the electrodes
			* events.
		*/
		//-----------------------------------------------------
		void setupTouchBoard();
	
		//-----------------------------------------------------
		/** \brief New Touch Event
			* @param electrode : which electrode.
			*
			* This method listens for touch event from
			* the electrodes.
		*/
		//-----------------------------------------------------
		void newTouchEvent(string &electrode);
	
		//-----------------------------------------------------
		/** \brief New Release Event
			* @param electrode : which electrode.
			*
			* This method listens for release event from 
			* the electrodes.
		*/
		//-----------------------------------------------------
		void newReleaseEvent(string &electrode);
	
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
