//--------------------------------------------------------------
//  CustomTimer.cpp
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is a Custom Timer Object. */
//--------------------------------------------------------------

#include "CustomTimer.h"
//--------------------------------------------------------------
void CustomTimer::setup(float timerLength,string timerName,bool bLoop)
{
	bTimerReached = true;
	bInvalidate = false;
	this->bLoop = bLoop;
	this->timerLength = timerLength;
	this->timerName = timerName;
	ofAddListener(ofEvents().update, this, &CustomTimer::update);
}
//--------------------------------------------------------------
void CustomTimer::update(ofEventArgs &event)
{
	float timer = ofGetElapsedTimeMillis() - startTime;
	
	if (!bTimerReached) {
		timeLeft = timerLength - timer;
	}
	
	if (timer >= timerLength && !bTimerReached) {
		bTimerReached = true;
		if (!bInvalidate) {
			string evt = timerName + " Finished";
			ofNotifyEvent(timerFinished, evt, this);
		}
		
		if (bLoop) {
			start();
		}
	}
}
//--------------------------------------------------------------
float CustomTimer::getTimeLeft()
{
	return timeLeft;
}
//--------------------------------------------------------------
bool CustomTimer::hasTimerFinished()
{
	return bTimerReached;
}
//--------------------------------------------------------------
void CustomTimer::setNewTimerLength(int timerLength)
{
	this->timerLength = timerLength;
}
//--------------------------------------------------------------
void CustomTimer::start()
{
	bInvalidate = false;
	if (bTimerReached) {
		string evt = timerName + " Started";
		ofNotifyEvent(timerStarted, evt, this);
		bTimerReached = false;
		startTime = ofGetElapsedTimeMillis();
	}
}
//--------------------------------------------------------------
void CustomTimer::stop()
{
	bTimerReached = true;
	bLoop = false;
}
//--------------------------------------------------------------
void CustomTimer::invalidate()
{
	bInvalidate = true;
	string evt = timerName + " Invalidated";
	ofNotifyEvent(timerInvalidated, evt, this);
}
