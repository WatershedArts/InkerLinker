#pragma once
//--------------------------------------------------------------
//  ILConstants.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the constants for the project including structs. */
//--------------------------------------------------------------

//-----------------------------------------------------
/** \brief GUI TYPES */
//-----------------------------------------------------
enum IL_GUI_OBJECT_TYPE
{
	IL_COLOR_PICKER = 0,
	IL_LABEL,
	IL_SLIDER,
	IL_SVG_TOGGLE,
	IL_SVG_BUTTON,
	IL_TEXT_BUTTON,
	IL_LOG_BOX,
	IL_TEXT_INPUT,
	IL_TEXT_TOGGLE,
	IL_RADIO_TOGGLE,
	IL_ICON_BUTTON
};

//-----------------------------------------------------
/** \brief ICON TYPES */
//-----------------------------------------------------
enum IL_GUI_ICON_TYPE
{
	IL_ICON_CROSS = 0,
	IL_ICON_PLUS,
	IL_ICON_MINUS
};

//-----------------------------------------------------
/** \brief GUI Constants */
//-----------------------------------------------------
#define GUI_BUTTON_WIDTH 46
#define GUI_BUTTON_HEIGHT 46
#define GUI_PADDING_X 2
#define GUI_PADDING_Y 2
#define GUI_NODE_GUI_WIDTH 250
#define GUI_COLOR ofColor(52, 152, 219) //42,32,225) Original
#define GUI_HOVERING_COLOR ofColor(236, 240, 241)//25,255,171) Original
#define IL_BACKGROUND_SPACING 20
#define IL_DEFAULT_COLOR ofColor(52, 152, 219)
#define IL_BACKGROUND_COLOR_1 ofColor(236, 240, 241)
#define IL_BACKGROUND_COLOR_2 ofColor(220, 224, 225)

//-----------------------------------------------------
/** \brief GUI Constants 
	* @param s_Class : class the error is coming from
	* @param s_Message : error message
*/
//-----------------------------------------------------
template<typename T>
void DebugMessage(T s_Class,T s_Message)
{
	ofSendMessage(string(s_Class) + " | " + string(s_Message));
}

//-----------------------------------------------------
/** \brief Data TYPES */
//-----------------------------------------------------
enum IL_DATA_TYPE
{
	IL_ARDUINO_DATA = 0,
	IL_CLOUD_BIT_DATA,
	IL_COLOUR_DATA,
	IL_HTTP_DATA,
	IL_IMAGE_DATA,
	IL_INSTRUMENT_DATA,
	IL_OSC_DATA,
	IL_QLAB_DATA,
	IL_SERIAL_DATA,
	IL_SOUND_DATA,
	IL_TIMER_DATA,
	IL_VIDEO_DATA
};

struct ColourPickerEvent
{
	string name;
	ofColor colour;
};

struct SliderEvent
{
	string name;
	string value;
};

struct RadioEvent
{
	string radioname;
	string value;
};


//-----------------------------------------------------
/** \brief Data Structures */
//-----------------------------------------------------
struct ArduinoData {
	string pin;
	string mode;
	string value;
};

struct CloudBitData {
	string percent;
	string duration_ms;
};

struct POSTData {
	string field;
	string value;
};

struct HTTPData {
	string hostURL;
	string extension;
	vector <POSTData> data;
};

struct OscData {
	string address;
	vector<string> value;
};

struct QLabData {
	string cue;
	string type;
};




struct BaseData {
	IL_DATA_TYPE type;
	vector <ArduinoData> arduinoData;
	vector <CloudBitData> cloudBitData;
	vector <ofColor> colourData;
	vector <HTTPData> httpData;
	vector <string> imageData;
	vector <string> instrumentData;
	vector <OscData> oscData;
	vector <QLabData> qlabData;
	vector <string> serialData;
	string soundData;
	string timerData;
	string videoData;
};

