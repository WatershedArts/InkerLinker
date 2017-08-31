//--------------------------------------------------------------
//  SerialManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Serial Nodes. */
//--------------------------------------------------------------

#include "SerialManager.h"

//--------------------------------------------------------------
SerialManager::SerialManager()
{
	
}

//--------------------------------------------------------------

SerialManager::~SerialManager()
{
	
}

//--------------------------------------------------------------
SerialManager::SerialManager(string serialDeviceName,int baud)
{
	string msg = "Setup " + serialDeviceName + " " + ofToString(baud);
	
	serialDevice.setup(serialDeviceName, baud);
	
	if(serialDevice.isInitialized())
	{
		DebugMessage("Serial Manager", msg.c_str());
	}
	else {
		DebugMessage("Serial Manager", "Can't Open Connection");
	}
}

//--------------------------------------------------------------
void SerialManager::exit()
{
	serialDevice.close();
}

//--------------------------------------------------------------
void SerialManager::sendData(string data)
{
	unsigned char *val= new unsigned char[data.length()+1];
	strcpy((char *)val,data.c_str());
	serialDevice.writeBytes(val, sizeof(val));
}
