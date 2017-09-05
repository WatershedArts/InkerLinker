//--------------------------------------------------------------
//  HTTPManager.h
//  InkerLinker
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Http. */
//--------------------------------------------------------------

#ifndef HTTPManager_h
#define HTTPManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ILConstants.h"

class HTTPManager
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		HTTPManager();
	
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~HTTPManager();
	
		//-----------------------------------------------------
		/** \brief Post Event 
			* @param data : data to post
			*
			* This method post the data to the script.
		*/
		//-----------------------------------------------------
		void postEvent(HTTPData data);
	
		//-----------------------------------------------------
		/** \brief Exit */
		//-----------------------------------------------------
		void exit();
	
	private:
	
		ofxHttpUtils httpUtils;

		//-----------------------------------------------------
		/** \brief Response 
			* @param response : response from the script
			*
			* This method returns whatever the script
			* echo.
		*/
		//-----------------------------------------------------
		void newResponse(ofxHttpResponse & response);
};


#endif /* HTTPManager_h */
