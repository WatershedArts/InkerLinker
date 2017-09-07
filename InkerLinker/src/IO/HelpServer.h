//--------------------------------------------------------------
//  HelpServer.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Handler the help server. */
//--------------------------------------------------------------

#ifndef HelpServer_h
#define HelpServer_h

#include <stdio.h>
#include "ofMain.h"
#include "ofxHTTP.h"

class HelpServer
{
	public:
		
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		HelpServer()
		{
			ofxHTTP::SimpleFileServerSettings settings;
			settings.setPort(7890);
			settings.setServerName("InkerLinker Help");
			server.setup(settings);
			server.start();
		}
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~HelpServer() { }
		
		//-----------------------------------------------------
		/** \brief Opens the Help Window
			*
			* This Method opens the help window in the users
			* prefered browser.
		*/
		//-----------------------------------------------------
		void open()
		{
			ofLaunchBrowser(server.getURL());
		}
		
		//-----------------------------------------------------
		/** \brief Close the Help Server
			*
			* This Method shuts the help server down.
		 */
		//-----------------------------------------------------
		void close()
		{
			server.stop();
		}
		
	private:
		ofxHTTP::SimpleFileServer server;
};

#endif /* HelpServer_h */
