//--------------------------------------------------------------
//  OscManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Osc Nodes. */
//--------------------------------------------------------------

#include "OscManager.h"


//--------------------------------------------------------------
OscManager::OscManager()
{
	
}

//--------------------------------------------------------------
OscManager::~OscManager()
{
	
}

//--------------------------------------------------------------
OscManager::OscManager(string host, int port)
{
	this->host = host;
	this->port = port;
	sender.setup(host, port);
	string msg  = "Setup Osc @"+host+":"+ofToString(port);
	DebugMessage("OSCManager", msg.c_str());
}

//--------------------------------------------------------------
void OscManager::sendMessage(OscData evt)
{
	ofxOscMessage e;
	e.setAddress(evt.address);
	for (int i = 0; i < evt.value.size(); i++)
	{
		e.addStringArg(evt.value[i]);
	}
	
	sender.sendMessage(e);
}
