//--------------------------------------------------------------
//  CloudBitManager.h
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Cloud Bit. */
//--------------------------------------------------------------

#ifndef CloudBitManager_h
#define CloudBitManager_h

#include <stdio.h>
#include "ofMain.h"
#include <curl/curl.h>
#include "ILConstants.h"

#define CLOUD_API "https://api-http.littlebitscloud.cc/v2/devices/"

class CloudBitManager : public ofThread
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		CloudBitManager();
		
		//-----------------------------------------------------
		/** \brief Constructor 
			* @param deviceID : id of cloud bit.
			* @param deviceAccessToken : access token of cloud bit.
			*
			* This constructor creates a cloud bit manager.
		*/
		//-----------------------------------------------------
		CloudBitManager(string deviceID,string deviceAccessToken);

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~CloudBitManager();
		
		//-----------------------------------------------------
		/** \brief Exit
			* 
			* This method kills the thread.
		*/
		//-----------------------------------------------------
		void exit();
		
		//-----------------------------------------------------
		/** \brief Threaded Function
			* 
			* Without this the app waits for the curl to finish
		*/
		//-----------------------------------------------------
		void threadedFunction();
		
		//-----------------------------------------------------
		/** \brief Constructor 
			* @param data : cloud bit data.
			*
			* This method sends the data to the endpoint.
		*/
		//-----------------------------------------------------
		void performEvent(CloudBitData data);
		
	private:
		
		//-----------------------------------------------------
		/** \brief Generate C strings 
			* @param deviceID : id of cloud bit.
			* @param deviceAccessToken : access token of cloud bit.
			*
			* This method generates c strings of the auth
			* credentials.
		*/
		//-----------------------------------------------------
		void generateAPIStrings(string deviceID,string deviceAccessToken);
	
		bool bLock = false;
		string tmpString;
		string apiURL;
		string authorizationHeader;
};


#endif /* CloudBitManager_h */
