//
//  TouchBoardManager.cpp
//  TouchBoardManager
//
//  Created by David Haylock on 02/08/2017.
//
//

#include "TouchBoardManager.h"

static float widthScale = 2.9;
static float heightScale = 2.9;
//-----------------------------------------------------
void TouchBoardManager::setup()
{
	touchRectangle = ofRectangle(0,0,0,0);
	// Load the SVG
	// This denotes the locations of the electrodes
	if(tb.load("TouchBoard/bareconductive.svg"))
	{
		vector <shared_ptr<ofxSvgRectangle> > element = tb.getElementsForType<ofxSvgRectangle>("electrodes");
		
		// Important or the keys will be flipped
		reverse(element.begin(),element.end());
		
		for(int i = 0; i < element.size(); i++)
		{
			Electrode a;
			a.id = ofToString(i);
			a.bHover = false;
			a.bAction = false;
			a.area = ofRectangle(element[i]->pos, element[i]->getWidth(), element[i]->getHeight());
			a.offset = element[i]->pos;
			a.type = TB_TOUCH_POINT;
			touchPoints.push_back(a);
			
			Electrode b;
			b.id = "-"+ofToString(i);
			b.bHover = false;
			b.bAction = false;
			b.area = ofRectangle(element[i]->pos, element[i]->getWidth(), element[i]->getHeight());
			b.offset = element[i]->pos;
			b.type = TB_RELEASE_POINT;
			releasePoints.push_back(b);
		}
		touchRectangle = tb.getViewbox();
	}
	else
	{
		DebugMessage("TouchBoard","Can't find the Svg!");
	}
	
	recalculateElectrodesPositions(25, ofGetHeight());

	
	touchBoard.setup();
	DebugMessage("TouchBoard","Connected");
	
	addListenersMouseAndTouchEvents();
	DebugMessage("TouchBoard","Adding Listeners");
}

//-----------------------------------------------------
void TouchBoardManager::addListenersMouseAndTouchEvents()
{
	ofAddListener(touchBoard.touched, this, &TouchBoardManager::touched);
	ofAddListener(touchBoard.released, this, &TouchBoardManager::released);
	ofAddListener(ofEvents().mousePressed,this,&TouchBoardManager::mousePressed);
	ofAddListener(ofEvents().mouseReleased,this,&TouchBoardManager::mouseReleased);
	ofAddListener(ofEvents().mouseDragged,this,&TouchBoardManager::mouseDragged);
	ofAddListener(ofEvents().mouseMoved,this,&TouchBoardManager::mouseMoved);
	ofAddListener(ofEvents().windowResized, this, &TouchBoardManager::windowResized);
}

//-----------------------------------------------------
void TouchBoardManager::removeListenersMouseAndTouchEvents()
{
	ofRemoveListener(touchBoard.touched, this, &TouchBoardManager::touched);
	ofRemoveListener(touchBoard.released, this, &TouchBoardManager::released);
	ofRemoveListener(ofEvents().mousePressed,this,&TouchBoardManager::mousePressed);
	ofRemoveListener(ofEvents().mouseReleased,this,&TouchBoardManager::mouseReleased);
	ofRemoveListener(ofEvents().mouseDragged,this,&TouchBoardManager::mouseDragged);
	ofRemoveListener(ofEvents().mouseMoved,this,&TouchBoardManager::mouseMoved);
	ofRemoveListener(ofEvents().windowResized, this, &TouchBoardManager::windowResized);
}

//-----------------------------------------------------
void TouchBoardManager::update()
{
	if(touchBoard.isConnected())
	{
		touchBoard.update();
	}
}

//-----------------------------------------------------
void TouchBoardManager::draw()
{
	ofPushStyle();
	ofSetColor(ofColor::white);
	ofPushMatrix();
	ofTranslate(touchRectangle.x, touchRectangle.y);
	tb.draw();
	ofPopMatrix();
	ofPopStyle();

	for (int i = 0; i < touchPoints.size(); i++)
	{
		ofSetColor(255);
		if(touchPoints[i].bHover) { ofFill(); }
		else { ofNoFill(); }
		
		if(touchBoard.isConnected())
		{
			if(touchBoard.getTouchStatus()[i])
			{
				ofFill();
				ofSetHexColor(0x82D87F);
			}
		}
		
		ofDrawRectangle(touchPoints[i].area);
	}
	
	for (int i = 0; i < releasePoints.size(); i++)
	{
		ofSetColor(255);
		if(releasePoints[i].bHover) { ofFill(); }
		else { ofNoFill(); }
		
		ofDrawRectangle(releasePoints[i].area);
	}
//
//	for (int i = 0; i < touchPoints.size(); i++) if(touchPoints[i].bHover) ofDrawBitmapStringHighlight("Touch Point " + ofToString(i),touchPoints[i].area.getCenter() + ofPoint(20,0));
//	for (int i = 0; i < releasePoints.size(); i++) if(releasePoints[i].bHover) ofDrawBitmapStringHighlight("Release Point " + ofToString(i),releasePoints[i].area.getCenter()+ ofPoint(20,0));
//	
//	ofPopStyle();
}

//-----------------------------------------------------
void TouchBoardManager::drawDebug()
{
	touchBoard.printData(0, 25);
}

//-----------------------------------------------------
void TouchBoardManager::simulateTouchEvent(int i)
{
	string a = ofToString(i);
	ofNotifyEvent(touch, a, this);
	string mess = "[Touch Board] - Simulated Touch Event on Electrode: " + ofToString(i);
}

//-----------------------------------------------------
void TouchBoardManager::simulateReleaseEvent(int i)
{
	string a = "-"+ofToString(i);
	ofNotifyEvent(release, a, this);
	string mess = "[Touch Board] - Simulated Release Event on Electrode: " + ofToString(i);
}

//-----------------------------------------------------
void TouchBoardManager::touched(int &e)
{
	string a = ofToString(e);
	ofNotifyEvent(touch, a, this);
	string mess = "[Touch Board] - Touch Event on Electrode: " + ofToString(e);
}

//-----------------------------------------------------
void TouchBoardManager::released(int &e)
{
	string a = "-"+ofToString(e);
	ofNotifyEvent(release, a, this);
	string mess = "[Touch Board] - Release Event on Electrode: " + ofToString(e);
}

//-----------------------------------------------------
void TouchBoardManager::mousePressed(ofMouseEventArgs &e)
{
	if( e.button == 0 )
	{
		for (int i = 0; i < touchPoints.size(); i++)
		{
			if(touchPoints[i].area.inside(e.x, e.y))
			{
				ofNotifyEvent(clickElectrode,touchPoints[i], this);
			}
		}
	}
	if( e.button == 2 )
	{
		for (int i = 0; i < releasePoints.size(); i++)
		{
			if(releasePoints[i].area.inside(e.x, e.y))
			{
				ofNotifyEvent(clickElectrode,releasePoints[i], this);
			}
		}
	}
}

//-----------------------------------------------------
void TouchBoardManager::mouseDragged(ofMouseEventArgs &e)
{
	
}

//-----------------------------------------------------
void TouchBoardManager::mouseReleased(ofMouseEventArgs &e)
{
	
}

//-----------------------------------------------------
void TouchBoardManager::mouseMoved(ofMouseEventArgs &e)
{
	for (int i = 0; i < touchPoints.size(); i++)
	{
		if(touchPoints[i].area.inside(e.x, e.y)) { touchPoints[i].bHover = true; }
		else { touchPoints[i].bHover = false; }
	}
	
	for (int i = 0; i < releasePoints.size(); i++)
	{
		if(releasePoints[i].area.inside(e.x, e.y)) { releasePoints[i].bHover = true; }
		else { releasePoints[i].bHover = false; }
	}
}

//-----------------------------------------------------
void TouchBoardManager::windowResized(ofResizeEventArgs &e)
{
	recalculateElectrodesPositions(20, e.height);
}

//-----------------------------------------------------
void TouchBoardManager::recalculateElectrodesPositions(int w, int h)
{
	float thisHeight = (h/2) - touchRectangle.height/2;
	touchRectangle.y = w;
	touchRectangle.y = thisHeight;
	for (int i = 0; i < touchPoints.size(); i++)
	{
		touchPoints[i].area.setY((touchRectangle.y + touchPoints[i].offset.y));
	}
	
	for (int i = 0; i < releasePoints.size(); i++)
	{
		releasePoints[i].area.setY((touchRectangle.y + releasePoints[i].offset.y));
	}
}

//-----------------------------------------------------
bool TouchBoardManager::isHit(int x, int y)
{
	return touchRectangle.inside(x,y);
}

//-----------------------------------------------------
bool TouchBoardManager::isConnected()
{
	return touchBoard.isConnected();
}


