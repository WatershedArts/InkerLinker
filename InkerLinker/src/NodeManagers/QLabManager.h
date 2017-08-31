//--------------------------------------------------------------
//  QLabManager.h
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for QLab Nodes. */
//--------------------------------------------------------------

#ifndef QLabManager_h
#define QLabManager_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxOsc.h"

class QLabManager
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		QLabManager();
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~QLabManager();
		
		//-----------------------------------------------------
		/** \brief Constructor 
			* @param host : host.
			* @param port : osc post.
			*
			* This constructor creates a osc sender.
		*/
		//-----------------------------------------------------
		QLabManager(string host = "localhost", int port = 53000);
		
		//-----------------------------------------------------
		/** \brief Send Data 
			* @param evt : datahost.
			*
			* This method sends data over osc.
		*/
		//-----------------------------------------------------
		void sendMessage(QLabData evt);
		
	private:
		string host;
		int port;
		ofxOscSender sender;
};

#endif /* QLabManager_h */
