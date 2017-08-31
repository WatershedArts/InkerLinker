#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
	noOfXPoints = ofGetWidth() / IL_BACKGROUND_SPACING;
	noOfYPoints = ofGetHeight() / IL_BACKGROUND_SPACING;
	

}

//--------------------------------------------------------------
void ofApp::update()
{

}

//--------------------------------------------------------------
void ofApp::draw()
{
	drawBackground();
	drawBottomBar();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

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
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}

//--------------------------------------------------------------

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

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
	ofSetColor(IL_DEFAULT_COLOR);
	ofDrawRectRounded(0,ofGetHeight()-(30), ofGetWidth(), 30,2);
	ofSetColor(255);
//	font->drawString("InkerLinker",10,ofGetHeight()-font->getStringBoundingBox("InkerLinker", 0, 0).height/2);
	ofPopStyle();
}
