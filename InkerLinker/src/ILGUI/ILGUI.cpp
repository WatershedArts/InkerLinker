//--------------------------------------------------------------
//  ILGUI.cpp
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Handler for the GUI elments. */
//--------------------------------------------------------------

#include "ILGUI.h"

//-----------------------------------------------------
ILGUI::ILGUI() { }

//-----------------------------------------------------
ILGUI::~ILGUI() { }

//-----------------------------------------------------
ILGUI::ILGUI(string name,int x,int y,int width, int height, bool alignToRight)
{
	this->alignToRight = alignToRight;
	this->name = name;
	this->c_x = x;
	this->c_y = y;
	this->c_width = width;
	this->c_height = height;
	bVisible = false;
	
	font = new ofxCenteredTrueTypeFont();
	font->load("SF-Pro-Text-Medium.otf",10,true,true,true);
	
	if(alignToRight) {
		int newX = ofGetWidth() - (width + x);
		this->guiRect = ofRectangle(newX,y,width,height);
	}
	else {
		this->guiRect = ofRectangle(x,y,width,height);
	}
	nextElementPositionY = this->guiRect.y + GUI_PADDING_Y;
	c_last_height = 0;
}

//-----------------------------------------------------
void ILGUI::setDataType(IL_DATA_TYPE type)
{
	data.type = type;
}

//-----------------------------------------------------
void ILGUI::addColorPickerDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILColorPicker(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addColorPickerRightOf(string name, string rightOf,int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILColorPicker(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addIconButtonDown(string name,IL_GUI_ICON_TYPE icon, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILIconButton(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),icon,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addIconButtonRightOf(string name,IL_GUI_ICON_TYPE icon,string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILIconButton(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),icon,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addLabelDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	
	guiItems.push_back(new ILLabel(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addLabelRightOf(string name,string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	guiItems.push_back(new ILLabel(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addLogBoxDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILLogBox(name,ofRectangle(guiRect.x+GUI_PADDING_X,(nextElementPositionY),width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addLogBoxRightOf(string name,string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILLogBox(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - itemOffsetX)));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addRadioDown(string name, vector<string> names,bool orientation,int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILRadioToggle(name,ofRectangle(guiRect.x+GUI_PADDING_X,(nextElementPositionY),width,height),font,names,orientation,GUI_PADDING_X));
	
	int newHeight = height;
	if(orientation)
	{
		ILRadioToggle * radio = (ILRadioToggle*)(guiItems.back());
		newHeight = radio->getRadioHeight();
	}
	c_last_height = newHeight;
}

//-----------------------------------------------------
void ILGUI::addRadioRightOf(string name, vector<string> names, string rightOf,bool orientation,int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILRadioToggle(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,names,orientation,abs(guiRect.x - itemOffsetX)));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSliderDown(string name, float min, float max, float defaultVal,int width, int height,ofColor colour,ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILSlider(name,ofRectangle(guiRect.x+GUI_PADDING_X,(nextElementPositionY),width,height),font,min,max,defaultVal,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSliderRightOf(string name, string rightOf,float min, float max, float defaultVal,int width, int height,ofColor colour,ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILSlider(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,min,max,defaultVal,abs(guiRect.x - itemOffsetX)));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSvgButtonDown(string name, string iconFile, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	
	guiItems.push_back(new ILSvgButton(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),iconFile,font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSvgButtonRightOf(string name, string iconFile, string rightOf, int width, int height,ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILSvgButton(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),iconFile,font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSvgToggleDown(string name, string iconFile, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
		
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILSvgToggle(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),iconFile,font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addSvgToggleRightOf(string name, string iconFile, string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILSvgToggle(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),iconFile,font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextButtonDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	
	guiItems.push_back(new ILTextButton(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextButtonRightOf(string name, string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILTextButton(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextInputDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILTextInput(name,ofRectangle(guiRect.x+GUI_PADDING_X,(nextElementPositionY),width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextInputRightOf(string name,string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILTextInput(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - itemOffsetX)));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextToggleDown(string name, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	// To combat the extra height
	if(guiItems.empty()) { c_last_height = height; nextElementPositionY -= (height + GUI_PADDING_Y); }
	
	nextElementPositionY += (c_last_height + GUI_PADDING_Y);
	guiItems.push_back(new ILTextToggle(name,ofRectangle(guiRect.x+GUI_PADDING_X,nextElementPositionY,width,height),font,GUI_PADDING_X));
	c_last_height = height;
}

//-----------------------------------------------------
void ILGUI::addTextToggleRightOf(string name, string rightOf, int width, int height, ofColor colour, ofColor hoverColour)
{
	width -= GUI_PADDING_X*2;
	height -= GUI_PADDING_Y*2;
	
	int itemOffsetX = getPositionForGUIItemByName(rightOf).getRight() + (GUI_PADDING_X * 1);
	
	guiItems.push_back(new ILTextToggle(name,ofRectangle(itemOffsetX,(nextElementPositionY),width,height),font,abs(guiRect.x - (itemOffsetX))));
	c_last_height = height;
}

//--------------------------------------------------------------
ofRectangle ILGUI::getBox()
{
	return guiRect;
}

//--------------------------------------------------------------
int ILGUI::getX()
{
	return guiRect.x;
}

//--------------------------------------------------------------
int ILGUI::getY()
{
	return guiRect.y;
}

//--------------------------------------------------------------
int ILGUI::getWidth()
{
	return guiRect.width;
}

//--------------------------------------------------------------
int ILGUI::getHeight()
{
	return guiRect.height;
}

//-----------------------------------------------------
BaseData ILGUI::getData()
{
	return data;
}

//--------------------------------------------------------------
ofRectangle ILGUI::getPositionForGUIItemByName(string name)
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getName() == name)
		{
			return guiItems[i]->box;
		}
	}
	return ofRectangle(0,0,0,0);
}

//-----------------------------------------------------
ILGUIObject* ILGUI::getGuiItemByName(string name)
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getName() == name)
		{
			return guiItems[i];
		}
	}
	return NULL;
}

//-----------------------------------------------------
vector <ILGUIObject*> ILGUI::getGuiItems()
{
	return guiItems;
}

//-----------------------------------------------------
void ILGUI::setVisible()
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		guiItems[i]->setEnabled(true);
	}
	bVisible = true;
}

//-----------------------------------------------------
void ILGUI::setInvisible()
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		guiItems[i]->setEnabled(false);
	}
	bVisible = false;
}

//-----------------------------------------------------
void ILGUI::addMessageToLog(string message)
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getType() == IL_LOG_BOX)
		{
			ILLogBox* g = (ILLogBox*)guiItems[i];
			g->addNewMessage(message);
		}
	}
}

//-----------------------------------------------------
void ILGUI::removeLastMessageFromLog()
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getType() == IL_LOG_BOX)
		{
			ILLogBox* g = (ILLogBox*)guiItems[i];
			g->removeLastMessage();
		}
	}
}

//-----------------------------------------------------
void ILGUI::clearMessagesFromLog()
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getType() == IL_LOG_BOX)
		{
			ILLogBox* g = (ILLogBox*)guiItems[i];
			g->clearLogs();
		}
	}
}

//-----------------------------------------------------
void ILGUI::draw()
{
	if (bVisible)
	{
		ofPushStyle();
		ofSetColor(255, 255, 255);
		ofDrawRectRounded(guiRect,2);
		ofSetColor(255, 0, 0);
		for (int i = 0; i < guiItems.size(); i++)
		{
			guiItems[i]->draw();
		}
		ofPopStyle();
	}
}

//-----------------------------------------------------
void ILGUI::windowResized(int w, int h)
{
	if(alignToRight) {
		int newX = w - (c_width + c_x);
		this->guiRect.setPosition(newX,c_y);
		for (int i = 0; i < guiItems.size(); i++)
		{
			guiItems[i]->setX(guiRect.x+(guiItems[i]->getOffsetX()));
		}
	}
}

//-----------------------------------------------------
void ILGUI::autoResize()
{
	// This combats the first element being erased from the height equation
	guiRect.setHeight((nextElementPositionY-guiRect.y)+GUI_PADDING_Y + c_last_height);
}

//-----------------------------------------------------
void ILGUI::addNewArduinoData(ArduinoData newData)
{
	data.arduinoData.push_back(newData);
	addMessageToLog("Pin: " + newData.pin + " Value: " + newData.value);
}

//-----------------------------------------------------
void ILGUI::addNewCloudBitData(CloudBitData newData)
{
	data.cloudBitData.push_back(newData);
	addMessageToLog("Percent: " + newData.percent + " Time(ms): " + newData.duration_ms);
}

//-----------------------------------------------------
void ILGUI::addNewColourData(ofColor colour)
{
	for (int i = 0; i < guiItems.size(); i++)
	{
		if(guiItems[i]->getType() == IL_COLOR_PICKER)
		{
			ILColorPicker* g = (ILColorPicker*)guiItems[i];
			g->addNewColour(colour);
		}
	}
	data.colourData.push_back(colour);
}

//-----------------------------------------------------
void ILGUI::addNewHTTPData(HTTPData newData)
{
	data.httpData.push_back(newData);
	string compiledString = "Host: " + newData.hostURL + "\nExt: " + newData.extension + "\n";
	for (int i = 0; i < newData.data.size(); i++ )
	{
		compiledString += "Field: " + newData.data[i].field + " Val:" + newData.data[i].value + "\n";
	}
	
	addMessageToLog(compiledString);
}

//-----------------------------------------------------
void ILGUI::addNewImageData(string file)
{
	data.imageData.push_back(file);
	addMessageToLog(file);
}

//-----------------------------------------------------
void ILGUI::addNewInstrumentData(string file)
{
	data.instrumentData.push_back(file);
	addMessageToLog(file);
}

//-----------------------------------------------------
void ILGUI::addNewOscData(OscData newData)
{
	data.oscData.push_back(newData);
}

//-----------------------------------------------------
void ILGUI::addNewQLabData(QLabData newData)
{
	data.qlabData.push_back(newData);
	string compiledString = " /cue/"+newData.cue+"/"+newData.type;
	addMessageToLog(compiledString);
}

//-----------------------------------------------------
void ILGUI::addNewSerialData(string command)
{
	data.serialData.push_back(command);
	addMessageToLog(command);
}

//-----------------------------------------------------
void ILGUI::addNewSoundData(string file)
{
	data.soundData = file;
	addMessageToLog(file);
}

//-----------------------------------------------------
void ILGUI::addNewVideoData(string file)
{
	data.videoData = file;
	addMessageToLog(file);
}

//-----------------------------------------------------
void ILGUI::removeLastData()
{
	switch (data.type)
	{
		case IL_ARDUINO_DATA:
		{
			if(data.arduinoData.size() > 0)
			{
				data.arduinoData.pop_back();
			}
		}
		break;
		case IL_CLOUD_BIT_DATA:
		{
			if(data.cloudBitData.size() > 0)
			{
				data.cloudBitData.pop_back();
			}
		}
		break;
		case IL_COLOUR_DATA:
		{
			for (int i = 0; i < guiItems.size(); i++)
			{
				if(guiItems[i]->getType() == IL_COLOR_PICKER)
				{
					ILColorPicker* g = (ILColorPicker*)guiItems[i];
					g->removeColour();
				}
			}
			if(data.colourData.size() > 0)
				data.colourData.pop_back();
		}
		break;
		case IL_HTTP_DATA:
		{
			if(data.httpData.size() > 0)
			{
				data.httpData.pop_back();
			}
		}
		break;
		case IL_IMAGE_DATA:
		{
			if(data.imageData.size() > 0)
			{
				data.imageData.pop_back();
			}
		}
		break;
		case IL_INSTRUMENT_DATA:
		{
			if(data.instrumentData.size() > 0)
			{
				data.instrumentData.pop_back();
			}
		}
		break;
		case IL_OSC_DATA:
		{
			if(data.oscData.size() > 0)
			{
				data.oscData.pop_back();
			}
		}
		break;
		case IL_QLAB_DATA:
		{
			if(data.qlabData.size() > 0)
			{
				data.qlabData.pop_back();
			}
		}
		break;
		case IL_SERIAL_DATA:
		{
			if(data.serialData.size() > 0)
			{
				data.serialData.pop_back();
			}
		}
		break;
		case IL_SOUND_DATA:
		{
			data.soundData = "";
		}
		break;
		case IL_TIMER_DATA: break;
		case IL_VIDEO_DATA:
		{
			data.videoData = "";
		}
		break;
		default: break;
	}
	removeLastMessageFromLog();
}

//-----------------------------------------------------
void ILGUI::clearData()
{
	switch (data.type)
	{
		case IL_ARDUINO_DATA:
		{
			if(data.arduinoData.size() > 0)
			{
				data.arduinoData.clear();
			}
		}
		break;
		case IL_CLOUD_BIT_DATA:
		{
			if(data.cloudBitData.size() > 0)
			{
				data.cloudBitData.clear();
			}
		}
		break;
		case IL_COLOUR_DATA:
		{
			for (int i = 0; i < guiItems.size(); i++)
			{
				if(guiItems[i]->getType() == IL_COLOR_PICKER)
				{
					ILColorPicker* g = (ILColorPicker*)guiItems[i];
					g->clearColours();
				}
			}
			if(data.colourData.size() > 0)
				data.colourData.clear();
		}
		break;
		case IL_HTTP_DATA:
		{
			if(data.httpData.size() > 0)
			{
				data.httpData.clear();
			}
		}
		break;
		case IL_IMAGE_DATA:
		{
			if(data.imageData.size() > 0)
			{
				data.imageData.clear();
			}
		}
		break;
		case IL_INSTRUMENT_DATA:
		{
			if(data.instrumentData.size() > 0)
			{
				data.instrumentData.clear();
			}
		}
		break;
		case IL_OSC_DATA:
		{
			if(data.oscData.size() > 0)
			{
				data.oscData.clear();
			}
		}
		break;
		case IL_QLAB_DATA:
		{
			if(data.qlabData.size() > 0)
			{
				data.qlabData.clear();
				
			}
		}
		break;
		case IL_SERIAL_DATA:
		{
			if(data.serialData.size() > 0)
			{
				data.serialData.clear();
			}
		}
		break;
		case IL_SOUND_DATA:
		{
			if(data.soundData.size() > 0)
			{
				data.soundData.clear();
			}
		}
		break;
		case IL_TIMER_DATA: break;
		case IL_VIDEO_DATA:
		{
			if(data.videoData.size() > 0)
			{
				data.videoData.clear();
			}
		}
		break;
		default: break;
	}
	clearMessagesFromLog();
}
