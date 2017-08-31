//--------------------------------------------------------------
//  OscManager.h
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Osc Nodes. */
//--------------------------------------------------------------

#ifndef OscManager_h
#define OscManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

class OscManager
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		OscManager();
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~OscManager();
		
		//-----------------------------------------------------
		/** \brief Constructor 
			* @param host : host.
			* @param port : osc post.
			*
			* This constructor creates a osc sender.
		*/
		//-----------------------------------------------------
		OscManager(string host, int port);
		
		//-----------------------------------------------------
		/** \brief Send Data 
			* @param evt : datahost.
			*
			* This method sends data over osc.
		*/
		//-----------------------------------------------------
		void sendMessage(OscData evt);
		
	private:
		string host;
		int port;
		ofxOscSender sender;
};

#endif /* OscManager_h */
