//--------------------------------------------------------------
//  CloudBitManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Cloud Bit. */
//--------------------------------------------------------------

#include "CloudBitManager.h"

//--------------------------------------------------------------
CloudBitManager::CloudBitManager()
{
	bLock = true;
}

//--------------------------------------------------------------
CloudBitManager::CloudBitManager(string deviceID,string deviceAccessToken)
{
	string msg = "Setup " + deviceID +  " " + deviceAccessToken;
	DebugMessage("CloudBit",msg.c_str());
	generateAPIStrings(deviceID, deviceAccessToken);
	bLock = true;
	startThread();
}

//--------------------------------------------------------------
CloudBitManager::~CloudBitManager()
{

}

//--------------------------------------------------------------
void CloudBitManager::exit()
{
	waitForThread(true);
}

//--------------------------------------------------------------
void CloudBitManager::threadedFunction()
{
	while(isThreadRunning())
	{
		if(!bLock)
		{
			CURL *curl;
			CURLcode res;

			curl_global_init(CURL_GLOBAL_ALL);
			curl = curl_easy_init();
			const char* jPayload = tmpString.c_str();
			
			if(curl)
			{
				struct curl_slist *header = NULL;
				header = curl_slist_append(header,authorizationHeader.c_str());
				header = curl_slist_append(header, "Content-type: application/json");
				
				res = curl_easy_setopt(curl, CURLOPT_HTTPHEADER,header);
				curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
				curl_easy_setopt(curl, CURLOPT_URL,apiURL.c_str());
				curl_easy_setopt(curl,CURLOPT_POSTFIELDS,jPayload);
				
				res = curl_easy_perform(curl);
				/* Check for errors */
				if(res != CURLE_OK) {
					DebugMessage("CloudBit","Error Sending");
					DebugMessage("CloudBit",curl_easy_strerror(res));
				}
				else {
					DebugMessage("CloudBit",curl_easy_strerror(res));
				}
				/* always cleanup */
				curl_easy_cleanup(curl);
				
				/* free the custom headers */
				curl_slist_free_all(header);
			}
			
			bLock = true;
		}
	}
}

//--------------------------------------------------------------
void CloudBitManager::performEvent(CloudBitData data)
{
	bLock = true;
	stringstream ss;
	ss << "{ \"percent\":" << ofToString(data.percent) << "," << "\"duration_ms\":" << ofToString(data.duration_ms) << "}" << endl;
	tmpString = ss.str();
	bLock = false;
}

//--------------------------------------------------------------
void CloudBitManager::generateAPIStrings(string deviceID,string deviceAccessToken)
{
	string auth = "Authorization: " + deviceAccessToken;
	string api =  CLOUD_API + deviceID + "/output";
	authorizationHeader = auth;
	apiURL = api;
}
