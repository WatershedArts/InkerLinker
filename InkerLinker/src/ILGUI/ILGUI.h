//--------------------------------------------------------------
//  ILGUI.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Handler for the GUI elments. */
//--------------------------------------------------------------

#ifndef ILGUI_h
#define ILGUI_h

#include <stdio.h>
#include "ofMain.h"
#include "ILColorPicker.h"
#include "ILLabel.h"
#include "ILLogBox.h"
#include "ILIconButton.h"
#include "ILSlider.h"
#include "ILSvgButton.h"
#include "ILSvgToggle.h"
#include "ILTextButton.h"
#include "ILTextInput.h"
#include "ILTextToggle.h"
#include "ILRadioToggle.h"

class ILGUI
{
	public:
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		ILGUI();
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILGUI();
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : name of the element.
			* @param x : svg icon file.
			* @param y : width of element.
			* @param width : height of element.
			* @param height : colour.
			* @param alignToRight : hover colour.
			*
			* This method Constructs a Svg Toggle Element
			* down.
		*/
		//-----------------------------------------------------
		ILGUI(string name,int x,int y,int width, int height, bool alignToRight = false);
	
#pragma mark - Add GUI Elements
		//-----------------------------------------------------
		/** \brief Add Color Picker Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Colour Picker Element
			* down.
		*/
		//-----------------------------------------------------
		void addColorPickerDown(string name, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Color Picker Right.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Colour Picker Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addColorPickerRightOf(string name, string rightOf,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Icon Button Down.
			* @param name : name of the element.
			* @param icon : icon of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Icon Button Element
			* down.
		*/
		//-----------------------------------------------------
		void addIconButtonDown(string name,IL_GUI_ICON_TYPE icon, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Icon Button Right.
			* @param name : name of the element.
			* @param icon : icon of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Icon Button
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addIconButtonRightOf(string name,IL_GUI_ICON_TYPE icon, string rightOf,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Label Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Label Element
			* down.
		*/
		//-----------------------------------------------------
		void addLabelDown(string name, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Label Right.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Label Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addLabelRightOf(string name, string rightOf,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Log Box Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Log Box
			* down.
		*/
		//-----------------------------------------------------
		void addLogBoxDown(string name,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Log Box Right.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Log Box Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addLogBoxRightOf(string name,string rightOf, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Radio Text Toggle Down.
			* @param name : name of the element.
			* @param names : contents of the radio toggles
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Radio Text Toggle
			* down.
		*/
		//-----------------------------------------------------
		void addRadioDown(string name,vector<string> names,bool orientation = false, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Radio Text Toggle Right.
			* @param name : name of the element.
			* @param names : contents of the radio toggles
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Radio Text Toggle
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addRadioRightOf(string name,vector<string> names,string rightOf, bool orientation = false, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Slider Down.
			* @param name : name of the element.
			* @param min : min value.
			* @param max : max value;
			* @param defaultVal : default value;
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Slider
			* down.
		*/
		//-----------------------------------------------------
		void addSliderDown(string name, float min, float max, float defaultVal,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Slider Right.
			* @param name : name of the element.
			* @param min : min value.
			* @param max : max value;
			* @param defaultVal : default value;
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Slider Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addSliderRightOf(string name,string rightOf, float min, float max, float defaultVal,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Svg Button Down.
			* @param name : name of the element.
			* @param iconFile : svg icon file.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Svg Button Element
			* down.
		*/
		//-----------------------------------------------------
		void addSvgButtonDown(string name, string iconFile, int width = GUI_BUTTON_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

		//-----------------------------------------------------
		/** \brief Add Svg Button Right.
			* @param name : name of the element.
			* @param iconFile : svg icon file.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Svg Button Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addSvgButtonRightOf(string name, string iconFile, string rightOf,int width = GUI_BUTTON_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Svg Toggle Down.
			* @param name : name of the element.
			* @param iconFile : svg icon file.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Svg Toggle Element
			* down.
		*/
		//-----------------------------------------------------
		void addSvgToggleDown(string name, string iconFile, int width = GUI_BUTTON_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
		
		//-----------------------------------------------------
		/** \brief Add Svg Toggle Right.
			* @param name : name of the element.
			* @param iconFile : svg icon file.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Svg Toggle Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addSvgToggleRightOf(string name, string iconFile, string rightOf,int width = GUI_BUTTON_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Text Button Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text Button Element
			* down.
		*/
		//-----------------------------------------------------
		void addTextButtonDown(string name, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
		
		//-----------------------------------------------------
		/** \brief Add Text Button Right.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text Button Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addTextButtonRightOf(string name, string rightOf,int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Text Input Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text input Element down.
		*/
		//-----------------------------------------------------
		void addTextInputDown(string name, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
		//-----------------------------------------------------
		/** \brief Add Text Right Input.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text Input Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addTextInputRightOf(string name,string rightOf, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
	
		//-----------------------------------------------------
		/** \brief Add Text Toggle Down.
			* @param name : name of the element.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text Toggle Element
			* down.
		*/
		//-----------------------------------------------------
		void addTextToggleDown(string name, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);
		
		//-----------------------------------------------------
		/** \brief Add Text Toggle Right.
			* @param name : name of the element.
			* @param rightOf : element to find.
			* @param width : width of element.
			* @param height : height of element.
			* @param colour : colour.
			* @param hoverColour : hover colour.
			*
			* This method Constructs a Text Toggle Element
			* to the right of the specified element.
		*/
		//-----------------------------------------------------
		void addTextToggleRightOf(string name, string rightOf, int width = GUI_NODE_GUI_WIDTH, int height = GUI_BUTTON_HEIGHT, ofColor colour = GUI_COLOR, ofColor hoverColour = GUI_HOVERING_COLOR);

	
#pragma mark - Getters
	
		//-----------------------------------------------------
		/** \brief Get the GUI box
			* @return guiRect : guiRect box.
			*
			* This method returns the box of the GUI.
		*/
		//-----------------------------------------------------
		ofRectangle getBox();
	
		//-----------------------------------------------------
		/** \brief Get the Colours
			* @return colours : stored colour data.
			*
			* This method returns the colour data stored in the
			* gui.
		*/
		//-----------------------------------------------------
		BaseData getData();
	
		//-----------------------------------------------------
		/** \brief Get GUI Item position
			* @param name : name of required element.
			* @return box : position and size of gui item.
			*
			* This method returns the position and size of the
			* GUI Item.
		*/
		//-----------------------------------------------------
		ofRectangle getPositionForGUIItemByName(string name);
	
		//-----------------------------------------------------
		/** \brief Get Specific Gui Item
			* @param name : name of Gui item.
			* @return guiItem : Gui item.
			*
			* This method returns a specific Gui item
			* by name.
		*/
		//-----------------------------------------------------
		ILGUIObject* getGuiItemByName(string name);

		//-----------------------------------------------------
		/** \brief Get the GUI Items
			* @return guiItems : vector of GUI Objects.
			*
			* This method returns a vector of gui items
			* we will use these to attach events to afterwards.
		*/
		//-----------------------------------------------------
		vector <ILGUIObject*> getGuiItems();
	
		//-----------------------------------------------------
		/** \brief Get X Position
			* @return guiRect.x : guiRect x.
			*
			* This method returns the X of the guiRect.
		*/
		//-----------------------------------------------------
		int getX();
	
		//-----------------------------------------------------
		/** \brief Get Y Position
			* @return guiRect.y : guiRect y.
			*
			* This method returns the Y of the guiRect.
		*/
		//-----------------------------------------------------
		int getY();
	
		//-----------------------------------------------------
		/** \brief Get Width
			* @return guiRect.width : guiRect width.
			*
			* This method returns the width of the guiRect.
		*/
		//-----------------------------------------------------
		int getWidth();
	
		//-----------------------------------------------------
		/** \brief Get Width
			* @return guiRect.height : guiRect height.
			*
			* This method returns the width of the guiRect.
		*/
		//-----------------------------------------------------
		int getHeight();
	
#pragma mark - Setters
	
		//-----------------------------------------------------
		/** \brief Set the Type of Data Return
			* @param name : name .
			*
			* This method sets the data type of the gui return
		*/
		//-----------------------------------------------------
		void setDataType(IL_DATA_TYPE type);
	
		//-----------------------------------------------------
		/** \brief Set the GUI to Invisible
			*
			* This method sets the Gui Invisible and Disables
			* the elements.
		*/
		//-----------------------------------------------------
		void setInvisible();
	
		//-----------------------------------------------------
		/** \brief Set the GUI to Visible
			* 
			* This method sets the Gui Visible and Enables 
			* the elements.
		*/
		//-----------------------------------------------------
		void setVisible();
	
#pragma mark - Loggers
	
		//-----------------------------------------------------
		/** \brief Add a Message
			* @param message : log message.
			*
			* This method adds a message to the log box.
		*/
		//-----------------------------------------------------
		void addMessageToLog(string message);
	
		//-----------------------------------------------------
		/** \brief Remove Message
			*
			* This method removes the last added message.
		*/
		//-----------------------------------------------------
		void removeLastMessageFromLog();
	
		//-----------------------------------------------------
		/** \brief Clears Messages
			*
			* This method removes all Messages from the Log.
		*/
		//-----------------------------------------------------
		void clearMessagesFromLog();
	
#pragma mark - Misc
	
		//-----------------------------------------------------
		/** \brief Draw */
		//-----------------------------------------------------
		void draw();

		//-----------------------------------------------------
		/** \brief Window Resized
			* @param w : new width.
			* @param h : new height.
			*
			* This method passes through the changing
			* dimensions of the screen to the GUI.
		*/
		//-----------------------------------------------------
		void windowResized(int w, int h);

		//-----------------------------------------------------
		/** \brief Auto Resize the Gui */
		//-----------------------------------------------------
		void autoResize();
	
		//-----------------------------------------------------
		/** \brief Add New Arduino Data
			* @param pin : pin.
			* @param value : value.
			*
			* This method adds new arduino data to the vector
		*/
		//-----------------------------------------------------
		void addNewArduinoData(ArduinoData newData);
	
		//-----------------------------------------------------
		/** \brief Add New CloudBit Data
			* @param cloudbitdata : new Cloud Data.
			*
			* This method adds a cloud bit data to the vector.
		*/
		//-----------------------------------------------------
		void addNewCloudBitData(CloudBitData newData);
	
		//-----------------------------------------------------
		/** \brief Add New Colour
			* @param colour : new colour to add.
			*
			* This method adds a new colour to the vector.
		*/
		//-----------------------------------------------------
		void addNewColourData(ofColor colour);
	
		//-----------------------------------------------------
		/** \brief Add New HTTP Data
			* @param hostUrl : url to send the request to
			* @param extension : extension to send the request
			* @param post : data
			*
			* This method adds a http data to the vector.
		*/
		//-----------------------------------------------------
		void addNewHTTPData(HTTPData newData);
	
		//-----------------------------------------------------
		/** \brief Add Image Data
			* @param file : new image file to add.
			*
			* This method adds a new image to the vector.
		*/
		//-----------------------------------------------------
		void addNewImageData(string file);
	
		//-----------------------------------------------------
		/** \brief Add Image File
			* @param file : new instrument file to add.
			*
			* This method adds a new instrument to the vector.
		*/
		//-----------------------------------------------------
		void addNewInstrumentData(string file);
	
		//-----------------------------------------------------
		/** \brief Add Osc Data
			* @param address : address.
			* @param address : address.
			*
			* This method adds new osc data to the vector.
		*/
		//-----------------------------------------------------
		void addNewOscData(OscData newData);
	
		//-----------------------------------------------------
		/** \brief Add QLab Data
			* @param address : address.
			* @param address : address.
			*
			* This method adds new osc data to the vector.
		*/
		//-----------------------------------------------------
		void addNewQLabData(QLabData newData);
	
		//-----------------------------------------------------
		/** \brief Add Serial Data
			* @param file : new serial command to add.
			*
			* This method adds a new serial data to the vector.
		*/
		//-----------------------------------------------------
		void addNewSerialData(string command);
	
		//-----------------------------------------------------
		/** \brief Add Sound Data
			* @param file : new serial command to add.
			*
			* This method adds a new sound data to the vector.
		*/
		//-----------------------------------------------------
		void addNewSoundData(string file);
	
		//-----------------------------------------------------
		/** \brief Add Serial Command
			* @param file : new serial command to add.
			*
			* This method adds a new video data to the vector.
		*/
		//-----------------------------------------------------
		void addNewVideoData(string file);
	
		//-----------------------------------------------------
		/** \brief Remove the Last Data
			*
			* This method removes the last Colour.
		*/
		//-----------------------------------------------------
		void removeLastData();
	
		//-----------------------------------------------------
		/** \brief Clears the Colours
			*
			* This method clears the colour vector.
		*/
		//-----------------------------------------------------
		void clearData();
	
	private:
	
		ofxCenteredTrueTypeFont* font;
		vector<ILGUIObject*> guiItems;
	
		BaseData data;

		ofRectangle guiRect;
		string name;
		bool alignToRight;
		bool bVisible;
		int c_x;
		int c_y;
		int c_width;
		int c_height;
		int c_last_height;
		int nextElementPositionY;
	
	protected:

};

#endif /* ILGUI_h */
