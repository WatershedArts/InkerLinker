//--------------------------------------------------------------
//  SerialManager.h
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Serial Nodes. */
//--------------------------------------------------------------

#ifndef SerialManager_h
#define SerialManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ILConstants.h"

class SerialManager
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		SerialManager();
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~SerialManager();
		
		//-----------------------------------------------------
		/** \brief Constructor 
			* @param serialDeviceName : serial device.
			* @param baud : baud rate.
			*
			* This constructor creates opens a connection
			* to the desired serial port.
		*/
		//-----------------------------------------------------
		SerialManager(string serialDeviceName,int baud);
		
		//-----------------------------------------------------
		/** \brief Exit */
		//-----------------------------------------------------
		void exit();
		
		//-----------------------------------------------------
		/** \brief Send Serial Data 
			* @param data : serial data.
			*
			* This method sends serial data to the device.
		*/
		//-----------------------------------------------------
		void sendData(string data);
	
	private:
		ofSerial serialDevice;
};

#endif /* SerialManager_h */
