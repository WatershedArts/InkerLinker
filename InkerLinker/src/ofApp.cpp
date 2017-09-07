#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	noOfXPoints = ofGetWidth() / IL_BACKGROUND_SPACING;
	noOfYPoints = ofGetHeight() / IL_BACKGROUND_SPACING;
	
	setupGuis();
	setupTouchBoard();
	setupNodeManagers();
	patchCordManager = new PatchCordManager();
	patchCordIdentifier = 0;
	
	removeTemporaryPatchCordTimer.setup(100, "Remove Patch Cord", false);
	ofAddListener(removeTemporaryPatchCordTimer.timerFinished,this,&ofApp::removeTemporaryPatchCord);
	ofEnableAntiAliasing();
	ofSetCircleResolution(20);
	
	
	nodeFont = new ofxCenteredTrueTypeFont();
	nodeFont->load("SF-Pro-Text-Medium.otf", 10,true,true,true);
	titleFont = new ofxCenteredTrueTypeFont();
	titleFont->load("SF-Pro-Text-Regular.otf", 15,true,true,true);
}

//--------------------------------------------------------------
void ofApp::exit()
{
	deleteGuis();
}

//--------------------------------------------------------------
void ofApp::update()
{
	touchBoardManager.update();
	for(auto node : nodes) patchCordManager->updatePatchCords(node->getPorts());
}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawBackground();
	touchBoardManager.draw();
	drawNodes();
	
	if(newPatchCord != NULL) {
		ofPushStyle();
		ofNoFill();
		ofSetLineWidth(2);
		if(newPatchCord->type == TB_POINT_TYPE::TB_TOUCH_POINT) ofSetColor(102,153,153);
		else if(newPatchCord->type == TB_POINT_TYPE::TB_RELEASE_POINT) ofSetColor(255,51,51);
		ofDrawBezier(newPatchCord->startingPoint.x, newPatchCord->startingPoint.y, newPatchCord->firstCurvePoint.x, newPatchCord->firstCurvePoint.y, newPatchCord->secondCurvePoint.x, newPatchCord->secondCurvePoint.y, newPatchCord->endingPoint.x, newPatchCord->endingPoint.y);
		ofPopStyle();
	}
	
	for(auto node : nodes) node->draw();
	
	patchCordManager->draw();
	
	drawGuis();
	drawBottomBar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	switch(key)
	{
		case '1': touchBoardManager.simulateTouchEvent(0); break;
		case '2': touchBoardManager.simulateTouchEvent(1); break;
		case '3': touchBoardManager.simulateTouchEvent(2); break;
		case '4': touchBoardManager.simulateTouchEvent(3); break;
		case '5': touchBoardManager.simulateTouchEvent(4); break;
		case '6': touchBoardManager.simulateTouchEvent(5); break;
		case '7': touchBoardManager.simulateTouchEvent(6); break;
		case '8': touchBoardManager.simulateTouchEvent(7); break;
		case '9': touchBoardManager.simulateTouchEvent(8); break;
		case '0': touchBoardManager.simulateTouchEvent(9); break;
		case '-': touchBoardManager.simulateTouchEvent(10); break;
		case '=': touchBoardManager.simulateTouchEvent(11); break;
		case OF_KEY_BACKSPACE: touchBoardManager.simulateTouchEvent(12); break;
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	switch(key)
	{
		case '1': touchBoardManager.simulateReleaseEvent(0); break;
		case '2': touchBoardManager.simulateReleaseEvent(1); break;
		case '3': touchBoardManager.simulateReleaseEvent(2); break;
		case '4': touchBoardManager.simulateReleaseEvent(3); break;
		case '5': touchBoardManager.simulateReleaseEvent(4); break;
		case '6': touchBoardManager.simulateReleaseEvent(5); break;
		case '7': touchBoardManager.simulateReleaseEvent(6); break;
		case '8': touchBoardManager.simulateReleaseEvent(7); break;
		case '9': touchBoardManager.simulateReleaseEvent(8); break;
		case '0': touchBoardManager.simulateReleaseEvent(9); break;
		case '-': touchBoardManager.simulateReleaseEvent(10); break;
		case '=': touchBoardManager.simulateReleaseEvent(11); break;
		case OF_KEY_BACKSPACE: touchBoardManager.simulateReleaseEvent(12); break;
		default: break;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
	if(newPatchCord != NULL) {
		newPatchCord->endingPoint.x = x;
		newPatchCord->endingPoint.y = y;
		newPatchCord->firstCurvePoint = newPatchCord->startingPoint + ofPoint(75,0);
		newPatchCord->secondCurvePoint = newPatchCord->endingPoint + ofPoint(-50,0);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
	if(newPatchCord != NULL) {
		removeTemporaryPatchCordTimer.start();
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
	int tmpW = getNearestSnapSize(w,IL_BACKGROUND_SPACING);
	int tmpH = getNearestSnapSize(h,IL_BACKGROUND_SPACING);
	
	noOfXPoints = tmpW / IL_BACKGROUND_SPACING;
	noOfYPoints = tmpH / IL_BACKGROUND_SPACING;
	ofSetWindowShape(tmpW, tmpH);
	
	gui->windowResized(tmpW, tmpH);
	iogui->windowResized(tmpW, tmpH);
//	savegui->windowResized(w, h);
	nodegui->windowResized(tmpW, tmpH);
	debuggui->windowResized(tmpW, tmpH);
	colorNodeGui->windowResized(tmpW, tmpH);
	videoNodeGui->windowResized(tmpW, tmpH);
	soundNodeGui->windowResized(tmpW, tmpH);
	instrumentNodeGui->windowResized(tmpW, tmpH);
	cloudBitNodeGui->windowResized(tmpW, tmpH);
	arduinoNodeGui->windowResized(tmpW, tmpH);
	oscNodeGui->windowResized(tmpW, tmpH);
	qlabNodeGui->windowResized(tmpW, tmpH);
	imageCaroselNodeGui->windowResized(tmpW, tmpH);
	timerNodeGui->windowResized(tmpW, tmpH);
	serialNodeGui->windowResized(tmpW, tmpH);
	httpNodeGui->windowResized(tmpW, tmpH);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{
	debuggui->addMessageToLog(msg.message);
	if(ofIsStringInString(msg.message, "Err"))
	{
		ILSvgToggle* ret = (ILSvgToggle*)(gui->getGuiItemByName("Debug"));
		ret->setPulsing();
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
#pragma mark - IL_GUI
//--------------------------------------------------------------
void ofApp::setupGuis()
{
	//---------------------------------------------------------------
	// Main Gui
	//---------------------------------------------------------------
	gui = new ILGUI("GUI",10,10,46,120,true);
	gui->addSvgToggleDown("Nodes", "nodes.svg");
	gui->addSvgToggleDown("Debug", "debug.svg");
	gui->autoResize();
	gui->setVisible();
	
	//---------------------------------------------------------------
	// Debug Gui
	//---------------------------------------------------------------
	debuggui = new ILGUI("Debug Gui",(ofGetWidth() - gui->getBox().getLeft())+10,10,300,0,true);
	debuggui->addLabelDown("Debug",debuggui->getWidth());
	debuggui->addLogBoxDown("Log", debuggui->getWidth(),debuggui->getWidth());
	debuggui->addTextButtonDown("Clear",debuggui->getWidth());
	debuggui->autoResize();
	debuggui->setInvisible();
	
	//---------------------------------------------------------------
	// IO Node Gui
	//---------------------------------------------------------------
	iogui = new ILGUI("IO",10,gui->getBox().getBottom() + 10,46,120,true);
	iogui->addSvgButtonDown("Load", "load.svg");
	iogui->addSvgButtonDown("Save", "save.svg");
	iogui->addSvgButtonDown("Info", "info.svg");
	iogui->autoResize();
	iogui->setVisible();
	
	//---------------------------------------------------------------
	// Nodes Gui
	//---------------------------------------------------------------
	vector <string> nodes = {"Arduino","Cloud Bit","Colour","HTTP","Image","Instrument","OSC","QLab","Serial","Sound","Video"};
	nodegui = new ILGUI("Node Gui",(ofGetWidth() - gui->getBox().getLeft())+10,10,200,0,true);
	nodegui->addLabelDown("Make things happen",200);
	nodegui->addRadioDown("Nodes", nodes,true,nodegui->getBox().width,GUI_BUTTON_HEIGHT,true);
	nodegui->autoResize();
	nodegui->setInvisible();
	
	//---------------------------------------------------------------
	// Arduino Node Gui
	//---------------------------------------------------------------
	vector<string> pins = {"2","3","4","5","6","7","8","9","10","11","12","13"};
	vector<string> modes = {"DIGITAL","PWM","SERVO"};
	
	arduinoNodeGui = new ILGUI("Arduino",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	arduinoNodeGui->setDataType(IL_ARDUINO_DATA);
	arduinoNodeGui->addLabelDown("Arduino Node",arduinoNodeGui->getBox().width);
	arduinoNodeGui->addLogBoxDown("",arduinoNodeGui->getBox().width,arduinoNodeGui->getBox().width/2);
	arduinoNodeGui->addLabelDown("Select Pin",arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	arduinoNodeGui->addRadioDown("Pins", pins,false,arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5,true);
	arduinoNodeGui->addLabelDown("Select Mode",arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	arduinoNodeGui->addRadioDown("Mode", modes,false,arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	arduinoNodeGui->addLabelDown("H | L / 0 - 255 / 0 - 180",arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	arduinoNodeGui->addTextInputDown("Pin Value",arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	arduinoNodeGui->addLabelDown("Add Action",arduinoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	arduinoNodeGui->addIconButtonDown("Add Arduino", IL_ICON_PLUS,arduinoNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	arduinoNodeGui->addIconButtonRightOf("Remove Arduino", IL_ICON_MINUS, "Add Arduino",arduinoNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	arduinoNodeGui->addSvgButtonDown("Confirm Arduino Node", "confirm.svg",arduinoNodeGui->getBox().width);
	arduinoNodeGui->autoResize();
	arduinoNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// CloudBit Node Gui
	//---------------------------------------------------------------
	cloudBitNodeGui = new ILGUI("Cloud Bit",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	cloudBitNodeGui->setDataType(IL_CLOUD_BIT_DATA);
	cloudBitNodeGui->addLabelDown("CloudBit Node",cloudBitNodeGui->getBox().width);
	cloudBitNodeGui->addLogBoxDown("",cloudBitNodeGui->getBox().width,cloudBitNodeGui->getBox().width/2);
	cloudBitNodeGui->addLabelDown("Add Variables",cloudBitNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	cloudBitNodeGui->addTextInputDown("Percent",cloudBitNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	cloudBitNodeGui->addTextInputDown("Duration",cloudBitNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	cloudBitNodeGui->addLabelDown("Add Action",cloudBitNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	cloudBitNodeGui->addIconButtonDown("Add CloudBit", IL_ICON_PLUS,cloudBitNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	cloudBitNodeGui->addIconButtonRightOf("Remove CloudBit", IL_ICON_MINUS, "Add CloudBit",cloudBitNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	cloudBitNodeGui->addSvgButtonDown("Confirm CloudBit Node", "confirm.svg",cloudBitNodeGui->getBox().width);
	cloudBitNodeGui->autoResize();
	cloudBitNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Colour Node Gui
	//---------------------------------------------------------------
	colorNodeGui = new ILGUI("Colour",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	colorNodeGui->setDataType(IL_COLOUR_DATA);
	colorNodeGui->addLabelDown("Colour Node",colorNodeGui->getBox().width);
	colorNodeGui->addColorPickerDown("Colour",colorNodeGui->getBox().width,colorNodeGui->getBox().width);
	colorNodeGui->addLabelDown("Add Colours",colorNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	colorNodeGui->addIconButtonDown("Add Colour", IL_ICON_PLUS,colorNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	colorNodeGui->addIconButtonRightOf("Remove Colour", IL_ICON_MINUS, "Add Colour",colorNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	colorNodeGui->addSvgButtonDown("Confirm Colour Node", "confirm.svg",colorNodeGui->getBox().width);
	colorNodeGui->autoResize();
	colorNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// HTTP Node Gui
	//---------------------------------------------------------------
	httpNodeGui = new ILGUI("HTTP",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	httpNodeGui->setDataType(IL_HTTP_DATA);
	httpNodeGui->addLabelDown("HTTP Node",httpNodeGui->getBox().width);
	httpNodeGui->addLogBoxDown("",httpNodeGui->getBox().width,httpNodeGui->getBox().width);
	httpNodeGui->addLabelDown("Url",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	httpNodeGui->addTextInputDown("Host",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	httpNodeGui->addTextInputDown("Extension",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	httpNodeGui->addLabelDown("Fields",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	httpNodeGui->addTextInputDown("Field",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	httpNodeGui->addTextInputDown("Field Value",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	httpNodeGui->addLabelDown("Add Fields",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	httpNodeGui->addIconButtonDown("Add Field", IL_ICON_PLUS,httpNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	httpNodeGui->addIconButtonRightOf("Remove Field", IL_ICON_MINUS, "Add Field",httpNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	httpNodeGui->addLabelDown("Add Action",httpNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	httpNodeGui->addIconButtonDown("Add HTTP", IL_ICON_PLUS,httpNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	httpNodeGui->addIconButtonRightOf("Remove HTTP", IL_ICON_MINUS, "Add HTTP",httpNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	httpNodeGui->addSvgButtonDown("Confirm HTTP Node", "confirm.svg",httpNodeGui->getBox().width);
	httpNodeGui->autoResize();
	httpNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Image Node Gui
	//---------------------------------------------------------------
	imageCaroselNodeGui = new ILGUI("Image",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	imageCaroselNodeGui->setDataType(IL_IMAGE_DATA);
	imageCaroselNodeGui->addLabelDown("Image Node",imageCaroselNodeGui->getBox().width);
	imageCaroselNodeGui->addLogBoxDown("",imageCaroselNodeGui->getBox().width,imageCaroselNodeGui->getBox().width/2);
	imageCaroselNodeGui->addLabelDown("Add Images",imageCaroselNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	imageCaroselNodeGui->addIconButtonDown("Add Image", IL_ICON_PLUS,imageCaroselNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	imageCaroselNodeGui->addIconButtonRightOf("Remove Image", IL_ICON_MINUS, "Add Image",imageCaroselNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	imageCaroselNodeGui->addSvgButtonDown("Confirm Image Node", "confirm.svg",imageCaroselNodeGui->getBox().width);
	imageCaroselNodeGui->autoResize();
	imageCaroselNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Instrument Node Gui
	//---------------------------------------------------------------
	instrumentNodeGui = new ILGUI("Instrument",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	instrumentNodeGui->setDataType(IL_INSTRUMENT_DATA);
	instrumentNodeGui->addLabelDown("Instrument Node",instrumentNodeGui->getBox().width);
	instrumentNodeGui->addLogBoxDown("",instrumentNodeGui->getBox().width,instrumentNodeGui->getBox().width/2);
	instrumentNodeGui->addLabelDown("Add Instruments",instrumentNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	instrumentNodeGui->addIconButtonDown("Add Instrument", IL_ICON_PLUS,instrumentNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	instrumentNodeGui->addIconButtonRightOf("Remove Instrument", IL_ICON_MINUS, "Add Instrument",instrumentNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	instrumentNodeGui->addSvgButtonDown("Confirm Instrument Node", "confirm.svg",instrumentNodeGui->getBox().width);
	instrumentNodeGui->autoResize();
	instrumentNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// OSC Node Gui
	//---------------------------------------------------------------
	oscNodeGui = new ILGUI("OSC",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	oscNodeGui->setDataType(IL_OSC_DATA);
	oscNodeGui->addLabelDown("OSC Node",oscNodeGui->getBox().width);
	oscNodeGui->addLogBoxDown("",oscNodeGui->getBox().width,oscNodeGui->getBox().width/1.5);
	oscNodeGui->addLabelDown("Add Address",oscNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	oscNodeGui->addTextInputDown("Address",oscNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	oscNodeGui->addLabelDown("Add Argument",oscNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	oscNodeGui->addTextInputDown("OSC Value",oscNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	oscNodeGui->addIconButtonDown("Add Arg", IL_ICON_PLUS,oscNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	oscNodeGui->addIconButtonRightOf("Remove Arg", IL_ICON_MINUS, "Add Arg",oscNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	oscNodeGui->addLabelDown("Add Action",oscNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	oscNodeGui->addIconButtonDown("Add OSC", IL_ICON_PLUS,oscNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	oscNodeGui->addIconButtonRightOf("Remove OSC", IL_ICON_MINUS, "Add OSC",oscNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	oscNodeGui->addSvgButtonDown("Confirm OSC Node", "confirm.svg",oscNodeGui->getBox().width);
	oscNodeGui->autoResize();
	oscNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// QLab Node Gui
	//---------------------------------------------------------------
	qlabNodeGui = new ILGUI("Qlab",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	qlabNodeGui->setDataType(IL_QLAB_DATA);
	qlabNodeGui->addLabelDown("QLab Node",qlabNodeGui->getBox().width);
	qlabNodeGui->addLogBoxDown("",qlabNodeGui->getBox().width,qlabNodeGui->getBox().width/1.5);
	qlabNodeGui->addLabelDown("Add Argument",qlabNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	
	qlabNodeGui->addTextInputDown("Cue",qlabNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	qlabNodeGui->addTextInputDown("/command",qlabNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	qlabNodeGui->addLabelDown("Add Action",qlabNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	qlabNodeGui->addIconButtonDown("Add QLab", IL_ICON_PLUS,qlabNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	
	qlabNodeGui->addIconButtonRightOf("Remove OSC", IL_ICON_MINUS, "Add QLab",qlabNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	qlabNodeGui->addSvgButtonDown("Confirm QLab Node", "confirm.svg",qlabNodeGui->getBox().width);
	qlabNodeGui->autoResize();
	qlabNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Serial Node Gui
	//---------------------------------------------------------------
	serialNodeGui = new ILGUI("Serial",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	serialNodeGui->setDataType(IL_SERIAL_DATA);
	serialNodeGui->addLabelDown("Serial Node",serialNodeGui->getBox().width);
	serialNodeGui->addLogBoxDown("",serialNodeGui->getBox().width,serialNodeGui->getBox().width/2);
	serialNodeGui->addLabelDown("Add Command",serialNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	serialNodeGui->addTextInputDown("command",serialNodeGui->getBox().width,GUI_BUTTON_HEIGHT/1.5);
	serialNodeGui->addLabelDown("Add Action",serialNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	serialNodeGui->addIconButtonDown("Add Serial", IL_ICON_PLUS,serialNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	serialNodeGui->addIconButtonRightOf("Remove Serial", IL_ICON_MINUS, "Add Serial",serialNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	serialNodeGui->addSvgButtonDown("Confirm Serial Node", "confirm.svg",serialNodeGui->getBox().width);
	serialNodeGui->autoResize();
	serialNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Sound Node Gui
	//---------------------------------------------------------------
	soundNodeGui = new ILGUI("Sound",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	soundNodeGui->setDataType(IL_SOUND_DATA);
	soundNodeGui->addLabelDown("Sound Node",soundNodeGui->getBox().width);
	soundNodeGui->addLogBoxDown("",soundNodeGui->getBox().width,soundNodeGui->getBox().width/3);
	soundNodeGui->addLabelDown("Add Sound File",soundNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	soundNodeGui->addIconButtonDown("Add Sound", IL_ICON_PLUS,soundNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	soundNodeGui->addIconButtonRightOf("Remove Sound", IL_ICON_MINUS, "Add Sound",soundNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	soundNodeGui->addSvgButtonDown("Confirm Sound Node", "confirm.svg",soundNodeGui->getBox().width);
	soundNodeGui->autoResize();
	soundNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Timer Node Gui
	//---------------------------------------------------------------
	timerNodeGui = new ILGUI("Timer",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	timerNodeGui->setDataType(IL_TIMER_DATA);
	timerNodeGui->addLabelDown("Timer Node",timerNodeGui->getBox().width);
	timerNodeGui->addLogBoxDown("",timerNodeGui->getBox().width,timerNodeGui->getBox().width/3);
	timerNodeGui->addTextInputDown("Time",timerNodeGui->getBox().width);
	timerNodeGui->addIconButtonDown("Add Timer", IL_ICON_PLUS,timerNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	timerNodeGui->addIconButtonRightOf("Remove Timer", IL_ICON_MINUS, "Add Timer",timerNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	timerNodeGui->addSvgButtonDown("Confirm Timer Node", "confirm.svg",timerNodeGui->getBox().width);
	timerNodeGui->autoResize();
	timerNodeGui->setInvisible();
	
	//---------------------------------------------------------------
	// Video Node Gui
	//---------------------------------------------------------------
	videoNodeGui = new ILGUI("Video",(ofGetWidth() - nodegui->getBox().getLeft())+10,10,200,0,true);
	videoNodeGui->setDataType(IL_VIDEO_DATA);
	videoNodeGui->addLabelDown("Video Node",videoNodeGui->getBox().width);
	videoNodeGui->addLogBoxDown("",videoNodeGui->getBox().width,videoNodeGui->getBox().width/3);
	videoNodeGui->addLabelDown("Add Video File",videoNodeGui->getBox().width,GUI_BUTTON_HEIGHT/2);
	videoNodeGui->addIconButtonDown("Add Video", IL_ICON_PLUS,videoNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	videoNodeGui->addIconButtonRightOf("Remove Video", IL_ICON_MINUS, "Add Video",videoNodeGui->getBox().width/2,GUI_BUTTON_HEIGHT/2+5);
	videoNodeGui->addSvgButtonDown("Confirm Video Node", "confirm.svg",videoNodeGui->getBox().width);
	videoNodeGui->autoResize();
	videoNodeGui->setInvisible();
	
	addListenersToGuis(gui);
	addListenersToGuis(debuggui);
	addListenersToGuis(iogui);
	addListenersToGuis(nodegui);
	addListenersToGuis(arduinoNodeGui);
	addListenersToGuis(cloudBitNodeGui);
	addListenersToGuis(colorNodeGui);
	addListenersToGuis(httpNodeGui);
	addListenersToGuis(imageCaroselNodeGui);
	addListenersToGuis(instrumentNodeGui);
	addListenersToGuis(oscNodeGui);
	addListenersToGuis(qlabNodeGui);
	addListenersToGuis(serialNodeGui);
	addListenersToGuis(soundNodeGui);
	addListenersToGuis(timerNodeGui);
	addListenersToGuis(videoNodeGui);
}

//--------------------------------------------------------------
void ofApp::drawGuis()
{
	ofPushStyle();
	gui->draw();
	debuggui->draw();
	iogui->draw();
	nodegui->draw();
	arduinoNodeGui->draw();
	colorNodeGui->draw();
	cloudBitNodeGui->draw();
	httpNodeGui->draw();
	imageCaroselNodeGui->draw();
	instrumentNodeGui->draw();
	oscNodeGui->draw();
	qlabNodeGui->draw();
	serialNodeGui->draw();
	soundNodeGui->draw();
	timerNodeGui->draw();
	videoNodeGui->draw();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::deleteGuis()
{
	delete gui;
	delete debuggui;
	delete iogui;
	delete nodegui;
	delete arduinoNodeGui;
	delete colorNodeGui;
	delete cloudBitNodeGui;
	delete httpNodeGui;
	delete imageCaroselNodeGui;
	delete instrumentNodeGui;
	delete oscNodeGui;
	delete qlabNodeGui;
	delete serialNodeGui;
	delete soundNodeGui;
	delete timerNodeGui;
	delete videoNodeGui;
}

//--------------------------------------------------------------
void ofApp::addListenersToGuis(ILGUI *gui)
{
	for (int i = 0; i < gui->getGuiItems().size(); i++)
	{
		switch (gui->getGuiItems()[i]->getType())
		{
			case IL_COLOR_PICKER:
			{
				ILColorPicker *g = (ILColorPicker*)gui->getGuiItems()[i];
				ofAddListener(g->guiEvent, this, &ofApp::colorPickerEvents);
			}
				break;
			case IL_LABEL:
			{
				
			}
				break;
			case IL_SLIDER:
			{
				ILSlider *g = (ILSlider*)gui->getGuiItems()[i];
				ofAddListener(g->guiEvent, this, &ofApp::sliderEvents);
			}
				break;
			case IL_SVG_TOGGLE:
			{
				ILSvgToggle *g = (ILSvgToggle*)gui->getGuiItems()[i];
				ofAddListener(g->buttonPushed, this, &ofApp::svgToggleEvents);
			}
				break;
			case IL_SVG_BUTTON:
			{
				ILSvgButton *g = (ILSvgButton*)gui->getGuiItems()[i];
				ofAddListener(g->buttonPushed, this, &ofApp::svgButtonEvents);
			}
				break;
			case IL_TEXT_BUTTON:
			{
				ILTextButton *g = (ILTextButton*)gui->getGuiItems()[i];
				ofAddListener(g->buttonPushed, this, &ofApp::textButtonEvents);
			}
				break;
			case IL_LOG_BOX:
			{
				ILLogBox *g = (ILLogBox*)gui->getGuiItems()[i];
			}
				break;
			case IL_TEXT_INPUT:
			{
				ILTextInput *g = (ILTextInput*)gui->getGuiItems()[i];
				ofAddListener(g->guiEvent, this, &ofApp::textInputEvents);
			}
				break;
			case IL_TEXT_TOGGLE:
			{
				ILTextToggle *g = (ILTextToggle*)gui->getGuiItems()[i];
				ofAddListener(g->buttonPushed, this, &ofApp::textToggleEvents);
			}
				break;
			case IL_RADIO_TOGGLE:
			{
				ILRadioToggle *g = (ILRadioToggle*)gui->getGuiItems()[i];
				ofAddListener(g->guiEvent, this, &ofApp::radioEvents);
			}
				break;
			case IL_ICON_BUTTON:
			{
				ILIconButton *g = (ILIconButton*)gui->getGuiItems()[i];
				ofAddListener(g->buttonPushed, this, &ofApp::iconButtonEvents);
			}
				break;
			default: break;
		}
	}
}

//--------------------------------------------------------------
void ofApp::svgToggleEvents(string &val)
{
	cout << "Svg Toggle: " << val << endl;
	if(val == "Nodes:0")
	{
		ILRadioToggle* radio = (ILRadioToggle*)(nodegui->getGuiItemByName("Nodes"));
		radio->setUnclicked();
		nodegui->setInvisible();
		debuggui->setInvisible();
		
		hideAllNodeGuis();
	}
	else if(val == "Nodes:1")
	{
		ILSvgToggle* ret = (ILSvgToggle*)(gui->getGuiItemByName("Debug"));
		ret->setUnclicked();
		
		nodegui->setVisible();
		debuggui->setInvisible();
	}
	else if(val == "Debug:0")
	{
		nodegui->setInvisible();
		debuggui->setInvisible();
	}
	else if(val == "Debug:1")
	{
		ILRadioToggle* radio = (ILRadioToggle*)(nodegui->getGuiItemByName("Nodes"));
		radio->setUnclicked();
		
		ILSvgToggle* ret = (ILSvgToggle*)(gui->getGuiItemByName("Nodes"));
		ret->setUnclicked();
		hideAllNodeGuis();
		nodegui->setInvisible();
		debuggui->setVisible();
	}
}

//--------------------------------------------------------------
void ofApp::svgButtonEvents(string &val)
{
	if(val == "Load")
	{
		// Load Script
		loadNodes();
	}
	else if(val == "Save")
	{
		// Save Script
		saveNodes();
	}
	else if(val == "Info")
	{
		// Open the Web Server
	}
	else if(val == "Confirm Arduino Node")
	{
		int *id = new int(nextNodesId);
		ArduinoNode* arduinoNode = new ArduinoNode(ofRectangle(100,100,200,150), nodeFont, "Arduino", id, arduinoNodeGui->getData().arduinoData);
		
		attachListenersToNode(arduinoNode);
		nodes.push_back(arduinoNode);
		arduinoNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm CloudBit Node")
	{
		int *id = new int(nextNodesId);
		CloudBitNode* cloudBitNode = new CloudBitNode(ofRectangle(100,100,200,150), nodeFont, "CloudBit", id, cloudBitNodeGui->getData().cloudBitData);
		
		attachListenersToNode(cloudBitNode);
		nodes.push_back(cloudBitNode);
		cloudBitNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Colour Node")
	{
		int *id = new int(nextNodesId);
		ColourNode* colourNode = new ColourNode(ofRectangle(100,100,200,150), nodeFont, "Colour", id, colorNodeGui->getData().colourData);
		
		attachListenersToNode(colourNode);
		nodes.push_back(colourNode);
		colorNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm HTTP Node")
	{
		int *id = new int(nextNodesId);
		HTTPNode* httpNode = new HTTPNode(ofRectangle(100,100,200,150), nodeFont, "HTTP", id, httpNodeGui->getData().httpData);
		
		attachListenersToNode(httpNode);
		nodes.push_back(httpNode);
		httpNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Image Node")
	{
		int *id = new int(nextNodesId);
		ImageNode* imageNode = new ImageNode(ofRectangle(100,100,200,150), nodeFont, "Image", id, imageCaroselNodeGui->getData().imageData);
		
		attachListenersToNode(imageNode);
		nodes.push_back(imageNode);
		imageCaroselNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Instrument Node")
	{
		int *id = new int(nextNodesId);
		InstrumentNode* instrumentNode = new InstrumentNode(ofRectangle(100,100,200,150), nodeFont, "Instrument", id, instrumentNodeGui->getData().instrumentData);
		
		attachListenersToNode(instrumentNode);
		nodes.push_back(instrumentNode);
		instrumentNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm OSC Node")
	{
		int *id = new int(nextNodesId);
		OscNode* oscNode = new OscNode(ofRectangle(100,100,200,150), nodeFont, "OSC", id, oscNodeGui->getData().oscData);
		
		attachListenersToNode(oscNode);
		nodes.push_back(oscNode);
		oscNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm QLab Node")
	{
		int *id = new int(nextNodesId);
		QlabNode* qlabNode = new QlabNode(ofRectangle(100,100,200,150), nodeFont, "QLab", id, qlabNodeGui->getData().qlabData);
		
		attachListenersToNode(qlabNode);
		nodes.push_back(qlabNode);
		qlabNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Serial Node")
	{
		int *id = new int(nextNodesId);
		SerialNode* serialNode = new SerialNode(ofRectangle(100,100,200,150), nodeFont, "Serial", id, serialNodeGui->getData().serialData);
		
		attachListenersToNode(serialNode);
		nodes.push_back(serialNode);
		serialNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Sound Node")
	{
		int *id = new int(nextNodesId);
		SoundNode* soundNode = new SoundNode(ofRectangle(100,100,200,150), nodeFont, "Sound", id, soundNodeGui->getData().soundData);
		
		attachListenersToNode(soundNode);
		nodes.push_back(soundNode);
		soundNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
	else if(val == "Confirm Video Node")
	{
		int *id = new int(nextNodesId);
		VideoNode* videoNode = new VideoNode(ofRectangle(100,100,200,150), nodeFont, "Video", id, videoNodeGui->getData().videoData);
		
		attachListenersToNode(videoNode);
		nodes.push_back(videoNode);
		videoNodeGui->clearData();
		closeAllGuis();
		nextNodesId++;
	}
}
//--------------------------------------------------------------
void ofApp::iconButtonEvents(string &val)
{
	if(val == "Add Arduino")
	{
		arduinoNodeGui->addNewArduinoData(tmpArduinoData);
	}
	else if(val == "Remove Arduino")
	{
		arduinoNodeGui->removeLastData();
	}
	else if(val == "Add CloudBit")
	{
		cloudBitNodeGui->addNewCloudBitData(tmpCloudBitData);
	}
	else if(val == "Remove CloudBit")
	{
		cloudBitNodeGui->removeLastData();
	}
	else if(val == "Add Colour")
	{
		colorNodeGui->addNewColourData(tmpColor);
	}
	else if(val == "Remove Colour")
	{
		colorNodeGui->removeLastData();
	}
	else if(val == "Add Field")
	{
		tmpHttpData.data.push_back(tmpPostData);
	}
	else if(val == "Remove Field")
	{
		tmpHttpData.data.pop_back();
	}
	else if(val == "Add HTTP")
	{
		httpNodeGui->addNewHTTPData(tmpHttpData);
	}
	else if(val == "Remove HTTP")
	{
		httpNodeGui->removeLastData();
	}
	else if(val == "Add Image")
	{
		string path = ofSystemLoadDialog().getPath();
		string extChecker = path.substr(path.find_last_of(".") + 1);
		
		static string types[4];
		types[0] = "jpg";
		types[1] = "jpeg";
		types[2] = "png";
		types[3] = "gif";
		
		int i = 0;
		while (i < 3)
		{
			if (extChecker == types[i])
			{
				imageCaroselNodeGui->addNewImageData(path);
				return;
			}
			i++;
		}
		
		string ds = "Err: Invalid File Type: " + extChecker;
		DebugMessage("Image Node", ds.c_str());
	}
	else if(val == "Remove Image")
	{
		imageCaroselNodeGui->removeLastData();
	}
	else if(val == "Add Instrument")
	{
		string path = ofSystemLoadDialog().getPath();
		string extChecker = path.substr(path.find_last_of(".") + 1);
		
		static string types[4];
		types[0] = "mp3";
		types[1] = "wav";
		types[2] = "mp4";
		types[3] = "aiff";
		
		int i = 0;
		while (i < 3)
		{
			if (extChecker == types[i])
			{
				instrumentNodeGui->addNewInstrumentData(path);
				return;
			}
			i++;
		}
		
		string ds = "Err: Invalid File Type: " + extChecker;
		DebugMessage("Instrument Node", ds.c_str());
	}
	else if(val == "Remove Instrument")
	{
		instrumentNodeGui->removeLastData();
	}
	else if(val == "Add Arg")
	{
		tmpHttpData.data.push_back(tmpPostData);
	}
	else if(val == "Remove Arg")
	{
		tmpHttpData.data.pop_back();
	}
	else if(val == "Add OSC")
	{
		oscNodeGui->addNewOscData(tmpOscData);
	}
	else if(val == "Remove OSC")
	{
		oscNodeGui->removeLastData();
	}
	else if(val == "Add QLab")
	{
		qlabNodeGui->addNewQLabData(tmpQLabData);
	}
	else if(val == "Remove QLab")
	{
		qlabNodeGui->removeLastData();
	}
	else if(val == "Add Serial")
	{
		serialNodeGui->addNewSerialData(tmpSerialCommand);
	}
	else if(val == "Remove Serial")
	{
		serialNodeGui->removeLastData();
	}
	else if(val == "Add Sound")
	{
		string path = ofSystemLoadDialog().getPath();
		string extChecker = path.substr(path.find_last_of(".") + 1);
		
		static string types[4];
		types[0] = "mp3";
		types[1] = "wav";
		types[2] = "mp4";
		types[3] = "aiff";
		
		int i = 0;
		while (i < 3)
		{
			if (extChecker == types[i])
			{
				soundNodeGui->addNewSoundData(path);
				return;
			}
			i++;
		}
		
		string ds = "Err: Invalid File Type: " + extChecker;
		DebugMessage("Sound Node", ds.c_str());
	}
	else if(val == "Remove Sound")
	{
		soundNodeGui->removeLastData();
	}
	else if(val == "Add Video")
	{
		string path = ofSystemLoadDialog().getPath();
		string extChecker = path.substr(path.find_last_of(".") + 1);
		
		static string types[2];
		types[0] = "mov";
		types[1] = "mp4";
		
		int i = 0;
		while (i < 2)
		{
			if (extChecker == types[i])
			{
				videoNodeGui->addNewVideoData(path);
				return;
			}
			i++;
		}
		
		string ds = "Err: Invalid File Type: " + extChecker;
		DebugMessage("Video Node", ds.c_str());
	}
	else if(val == "Remove Video")
	{
		videoNodeGui->removeLastData();
	}
}

//--------------------------------------------------------------
void ofApp::textButtonEvents(string &val)
{
	cout << "Text Button: " << val << endl;
}
//--------------------------------------------------------------
void ofApp::textToggleEvents(string &val)
{
	cout << "Text Toggle: " << val << endl;
}
//--------------------------------------------------------------
void ofApp::textInputEvents(TextInputEvent &val)
{
	cout << "Text Input : " << val.name << " " << val.text << endl;
	if(val.name == "Pin Value")
	{
		tmpArduinoData.value = val.text;
	}
	else if(val.name == "Percent")
	{
		tmpCloudBitData.percent = val.text;
	}
	else if(val.name == "Duration")
	{
		tmpCloudBitData.duration_ms = val.text;
	}
	else if(val.name == "Host")
	{
		if(ofIsStringInString(val.text,"localhost"))
		{
			tmpHttpData.hostURL = "http://"+val.text;
		}
		else
		{
			tmpHttpData.hostURL = "http://www." + val.text;
		}
	}
	else if(val.name == "Extension")
	{
		tmpHttpData.extension = val.text;
	}
	else if(val.name == "Field")
	{
		tmpPostData.field = val.text;
	}
	else if(val.name == "Field Value")
	{
		tmpPostData.value = val.text;
	}
	else if(val.name == "Address")
	{
		tmpOscData.address = val.text;
	}
	else if(val.name == "OSC Value")
	{
		tmpOscData.value.push_back(val.text);
	}
	else if(val.name == "Cue")
	{
		tmpQLabData.cue = val.text;
	}
	else if(val.name == "/command")
	{
		tmpQLabData.type = val.text;
	}
	else if(val.name == "command")
	{
		tmpSerialCommand = val.text;
	}
}

//--------------------------------------------------------------
void ofApp::sliderEvents(SliderEvent &val)
{
	cout << "Slider: " << val.name << " " << val.value << endl;
}

//--------------------------------------------------------------
void ofApp::colorPickerEvents(ColourPickerEvent &val)
{
	cout << "Colour Picker: " << val.name << " " << val.colour << endl;
	if(val.name == "Colour")
	{
		tmpColor = val.colour;
	}
}

//--------------------------------------------------------------
void ofApp::radioEvents(RadioEvent &val)
{
	cout << "Radio: " << val.radioname << " " << val.value << endl;
	if(val.radioname == "Nodes")
	{
		vector<string> closeAllNodes = ofSplitString(val.value, ":");
		
		if(closeAllNodes[1] == "0")
		{
			hideAllNodeGuis();
		}
		else if(val.value == "Arduino:1")
		{
			hideAllNodeGuis();
			arduinoNodeGui->setVisible();
		}
		else if(val.value == "Cloud Bit:1")
		{
			hideAllNodeGuis();
			cloudBitNodeGui->setVisible();
		}
		else if(val.value == "Colour:1")
		{
			hideAllNodeGuis();
			colorNodeGui->setVisible();
		}
		else if(val.value == "HTTP:1")
		{
			hideAllNodeGuis();
			httpNodeGui->setVisible();
		}
		else if(val.value == "Image:1")
		{
			hideAllNodeGuis();
			imageCaroselNodeGui->setVisible();
		}
		else if(val.value == "Instrument:1")
		{
			hideAllNodeGuis();
			instrumentNodeGui->setVisible();
		}
		else if(val.value == "OSC:1")
		{
			hideAllNodeGuis();
			oscNodeGui->setVisible();
		}
		else if(val.value == "QLab:1")
		{
			hideAllNodeGuis();
			qlabNodeGui->setVisible();
		}
		else if(val.value == "Serial:1")
		{
			hideAllNodeGuis();
			serialNodeGui->setVisible();
		}
		else if(val.value == "Sound:1")
		{
			hideAllNodeGuis();
			soundNodeGui->setVisible();
		}
		else if(val.value == "Timer:1")
		{
			hideAllNodeGuis();
			timerNodeGui->setVisible();
		}
		else if(val.value == "Video:1")
		{
			hideAllNodeGuis();
			videoNodeGui->setVisible();
		}
	}
	else if(val.radioname == "Pins")
	{
		cout << "Pins: " << val.value << endl;
		vector<string> pinNo = ofSplitString(val.value, ":");
		tmpArduinoData.pin = pinNo[0];
	}
	else if(val.radioname == "Mode")
	{
		vector<string> mode = ofSplitString(val.value, ":");
		tmpArduinoData.mode = mode[0];
		arduinoManager->setPinMode(ofToInt(tmpArduinoData.pin), tmpArduinoData.mode);
	}
}

//--------------------------------------------------------------
void ofApp::clearContexts()
{
	arduinoNodeGui->clearData();
	cloudBitNodeGui->clearData();
	colorNodeGui->clearData();
	httpNodeGui->clearData();
	imageCaroselNodeGui->clearData();
	instrumentNodeGui->clearData();
	oscNodeGui->clearData();
	qlabNodeGui->clearData();
	serialNodeGui->clearData();
	soundNodeGui->clearData();
	timerNodeGui->clearData();
	videoNodeGui->clearData();
}

//--------------------------------------------------------------
void ofApp::hideAllNodeGuis()
{
	clearContexts();
	colorNodeGui->setInvisible();
	videoNodeGui->setInvisible();
	soundNodeGui->setInvisible();
	instrumentNodeGui->setInvisible();
	cloudBitNodeGui->setInvisible();
	arduinoNodeGui->setInvisible();
	oscNodeGui->setInvisible();
	qlabNodeGui->setInvisible();
	timerNodeGui->setInvisible();
	imageCaroselNodeGui->setInvisible();
	serialNodeGui->setInvisible();
	httpNodeGui->setInvisible();
}

//--------------------------------------------------------------
void ofApp::closeAllGuis()
{
	hideAllNodeGuis();
	nodegui->setInvisible();
	ILSvgToggle* nodesToggle = (ILSvgToggle*)(gui->getGuiItemByName("Nodes"));
	nodesToggle->setUnclicked();
}

#pragma mark - IL_TOUCH_BOARD
//--------------------------------------------------------------
void ofApp::setupTouchBoard()
{
	touchBoardManager.setup();
	ofAddListener(touchBoardManager.clickElectrode,this,&ofApp::startNewPatchCord);
	ofAddListener(touchBoardManager.touch,this,&ofApp::newTouchEvent);
	ofAddListener(touchBoardManager.release,this,&ofApp::newReleaseEvent);
}

//--------------------------------------------------------------
void ofApp::newTouchEvent(string &electrode)
{
	for(int i = 0; i < nodes.size(); i++)
	{
		for(int q = 0; q < nodes[i]->getPorts().size(); q++)
		{
			if(nodes[i]->getPorts()[q].getElectrodeId() == electrode)
			{
				nodes[i]->triggerPort(q);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::newReleaseEvent(string &electrode)
{
	for(int i = 0; i < nodes.size(); i++)
	{
		for(int q = 0; q < nodes[i]->getPorts().size(); q++)
		{
			if(nodes[i]->getPorts()[q].getElectrodeId() == electrode)
			{
				nodes[i]->triggerPort(q);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::startNewPatchCord(Electrode &e)
{
	string type = e.type ? "Release" : "Touch";
	patchCordIdentifier++;
	newPatchCord = NULL;
	newPatchCord = new PatchCord();
	newPatchCord->patchId = patchCordIdentifier;
	newPatchCord->electrodeId = e.id;
	newPatchCord->startingPoint = e.area.getCenter();
	newPatchCord->endingPoint = e.area.getCenter();
	newPatchCord->firstCurvePoint = e.area.getCenter();
	newPatchCord->secondCurvePoint = e.area.getCenter();
	newPatchCord->type = e.type;
}

//--------------------------------------------------------------
void ofApp::removeTemporaryPatchCord(string &val)
{
	newPatchCord = NULL;
}
//--------------------------------------------------------------
void ofApp::attachPatchCordToPort(Port &port)
{
	if(newPatchCord != NULL)
	{
		newPatchCord->portId = port.getPortId();
		newPatchCord->nodeId = port.getNodeId();
		
		for (int i = 0; i < nodes.size(); i++)
		{
			int id = nodes[i]->getID();
			if(id == port.getNodeId())
			{
				if(!port.getPortState())
				{
					//					nodes[i]->setPatchCoordId(newPatchCord->patchId);
					//					nodes[i]->setElectrodeId(newPatchCord->electrodeId);
					port.setPatchCordId(newPatchCord->patchId);
					port.setElectrodeId(newPatchCord->electrodeId);
					port.setPortStateActive();
					patchCordManager->addNewPatchCord(*newPatchCord);
				}
				else
				{
					newPatchCord = NULL;
					return;
				}
			}
		}
		newPatchCord = NULL;
	}
}

//--------------------------------------------------------------
void ofApp::removePatchCordFromPort(Port &port)
{
	patchCordManager->removePatchCord(port.getPatchCordId());
	port.setPortStateInactive();
	port.setPatchCordId(NULL);
	port.setElectrodeId("n");
}

//--------------------------------------------------------------
void ofApp::removeNode(int &nodeId)
{
	cout << nodeId << endl;
	for(int i = 0; i < nodes.size(); i++)
	{
		if(*nodes[i]->id == nodeId)
		{
			for(int e = 0; e < nodes[i]->getPorts().size(); e++)
			{
				removePatchCordFromPort(nodes[i]->getPorts()[e]);
			}
			nodes.erase(nodes.begin()+i);
		}
	}
}

#pragma mark - IL_NODES
//--------------------------------------------------------------
void ofApp::loadNodes()
{
	string path = ofSystemLoadDialog().filePath;
	paletteLoader.load(path);
	patchCordManager->reset();
	nodes.clear();
	patchCordManager->addNewPatchCord(paletteLoader.getPatchCords());
	nodes = paletteLoader.getNodes();
	
	attachListenersToNodes(nodes);
	
}

//--------------------------------------------------------------
void ofApp::saveNodes()
{
	paletteSaver.save(patchCordManager->getAllPatchCoords(), nodes);
}

//--------------------------------------------------------------
void ofApp::drawNodes()
{
	ofPushStyle();
	for(auto node : nodes) { node->draw(); }
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::attachListenersToNode(BaseNode *node)
{
	ofAddListener(node->attachPatchCord, this, &ofApp::attachPatchCordToPort);
	ofAddListener(node->removePatchCord, this, &ofApp::removePatchCordFromPort);
	ofAddListener(node->closedNodeId, this, &ofApp::removeNode);
	
	switch (node->getType())
	{
		case IL_BASE_NODE: /* No Action Required*/ break;
		case IL_ARDUINO_NODE:
		{
			ArduinoNode *n = (ArduinoNode*)(node);
			ofAddListener(n->arduinoEvent, this, &ofApp::arduinoEventListener);
		}
		break;
		case IL_CLOUD_BIT_NODE:
		{
			CloudBitNode *n = (CloudBitNode*)(node);
			ofAddListener(n->cloudDataEvent, this, &ofApp::cloudBitEventListener);
		}
		break;
		case IL_COLOUR_NODE: /* No Action Required*/ break;
		case IL_HTTP_NODE:
		{
			HTTPNode *n = (HTTPNode*)(node);
			ofAddListener(n->httpDataEvent, this, &ofApp::httpEventListener);
		}
		break;
		case IL_IMAGE_NODE: /* No Action Required*/ break;
		case IL_INSTRUMENT_NODE: /* No Action Required*/ break;
		case IL_OSC_NODE:
		{
			OscNode *n = (OscNode*)(node);
			ofAddListener(n->oscEvent, this, &ofApp::oscEventListener);
		}
		break;
		case IL_QLAB_NODE:
		{
			QlabNode *n = (QlabNode*)(node);
			ofAddListener(n->qlabEvent, this, &ofApp::qlabEventListener);
		}
		break;
		case IL_SERIAL_NODE:
		{
			SerialNode *n = (SerialNode*)(node);
			ofAddListener(n->serialEvent, this, &ofApp::serialEventListener);
		}
		break;
		case IL_SOUND_NODE: /* No Action Required*/ break;
		case IL_TIMER_NODE: /* No Action Required*/ break;
		case IL_VIDEO_NODE: /* No Action Required*/ break;
		default: break;
	}
	
}

//--------------------------------------------------------------
void ofApp::attachListenersToNodes(vector<BaseNode *> nodes)
{
	for(auto nod : nodes) { attachListenersToNode(nod); }
}

#pragma mark - IL_NODE_MANAGERS
//--------------------------------------------------------------
void ofApp::setupNodeManagers()
{
	qlabManager = new QLabManager("localhost",53000);
	oscManager = new OscManager("localhost",12345);
	serialManager = new SerialManager("#",9600);
	arduinoManager = new ArduinoManager();
//	serialManager = new SerialManager("/dev/tty.usbmodem1421",9600);
	httpManager = new HTTPManager();
	cloudBitManager = new CloudBitManager("deviceID","deviceAccessToken");
	
}

//--------------------------------------------------------------
void ofApp::qlabEventListener(QLabData &qlabdata)
{
	qlabManager->sendMessage(qlabdata);
}

//--------------------------------------------------------------
void ofApp::oscEventListener(OscData &oscdata)
{
	oscManager->sendMessage(oscdata);
}

//--------------------------------------------------------------
void ofApp::serialEventListener(string &serialdata)
{
	serialManager->sendData(serialdata);
}

//--------------------------------------------------------------
void ofApp::httpEventListener(HTTPData &httpdata)
{
	httpManager->postEvent(httpdata);
}

//--------------------------------------------------------------
void ofApp::cloudBitEventListener(CloudBitData &cloudbitdata)
{
	cloudBitManager->performEvent(cloudbitdata);
}

//--------------------------------------------------------------
void ofApp::arduinoEventListener(ArduinoData &arduinodata)
{
	cout << arduinodata.mode << " " << arduinodata.pin << " " << arduinodata.value << endl;
	if(arduinodata.mode == "DIGITAL") {
		if (ofIsStringInString(arduinodata.value, "H")) {
			cout << "Hot hot hot" << endl;
			arduinoManager->setDigital(ofToInt(arduinodata.pin),true);
		}
		else if (ofIsStringInString(arduinodata.value, "L")) {
			cout << "Cold Cold Cold" << endl;
			arduinoManager->setDigital(ofToInt(arduinodata.pin),false);
		}
		
	}
	else if(arduinodata.mode == "PWM") {
		int value = ofToInt(arduinodata.value);
		arduinoManager->setPWM(ofToInt(arduinodata.pin),value);
	}
	else if(arduinodata.mode == "SERVO") {
		int value = ofToInt(arduinodata.value);
		arduinoManager->setServo(ofToInt(arduinodata.pin),value);
	}
}

#pragma mark - IL_MISC
//--------------------------------------------------------------
int ofApp::getNearestSnapSize(int numToRound, int multiple)
{
	if (multiple == 0)
		return numToRound;
	
	int remainder = abs(numToRound) % multiple;
	if (remainder == 0)
		return numToRound;
	
	if (numToRound < 0)
		return -(abs(numToRound) - remainder);
	else
		return numToRound + multiple - remainder;
}

//--------------------------------------------------------------
void ofApp::drawBackground()
{
	ofBackgroundGradient(IL_BACKGROUND_COLOR_1, IL_BACKGROUND_COLOR_2,OF_GRADIENT_CIRCULAR);
	ofPushStyle();
	ofSetColor(255);
	for (int y = 1; y < noOfYPoints; y++)
	{
		for (int x = 1; x < noOfXPoints; x++)
		{
			glPointSize(2);
			glBegin(GL_POINTS);
			glVertex2i(0+(x*IL_BACKGROUND_SPACING), 0+(y*IL_BACKGROUND_SPACING));
			glEnd();
		}
	}
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::drawBottomBar()
{
	ofPushStyle();
	ofFill();
	ofSetColor(IL_DEFAULT_COLOR);
	ofDrawRectRounded(0,ofGetHeight()-(30), ofGetWidth(), 30,1);
	ofSetColor(255);
	
	int centerY = ((ofGetHeight()-30)/2) - (titleFont->getStringBoundingBox("Inkerlinker", 0, 0).height/2);
	
	titleFont->drawStringCentered("Inkerlinker", 100, ofGetHeight()-15);
	ofPopStyle();
}
