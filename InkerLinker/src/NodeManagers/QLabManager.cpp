//--------------------------------------------------------------
//  QLabManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for QLab Nodes. */
//--------------------------------------------------------------

#include "QLabManager.h"

//--------------------------------------------------------------
QLabManager::QLabManager()
{
	
}

//--------------------------------------------------------------
QLabManager::~QLabManager()
{
	
}

//--------------------------------------------------------------
QLabManager::QLabManager(string host, int port)
{
	this->host = host;
	this->port = port;
	sender.setup(host, port);
	string msg  = "Setup QLab @"+host+":"+ofToString(port);
	DebugMessage("QLabManager", msg.c_str());
}

//--------------------------------------------------------------
void QLabManager::sendMessage(QLabData evt)
{
	ofxOscMessage e;
	e.setAddress(evt.address);
	for (int i = 0; i < evt.value.size(); i++)
	{
		e.addStringArg(evt.value[i]);
	}
	
	sender.sendMessage(e);
}
