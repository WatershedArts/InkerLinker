//--------------------------------------------------------------
//  HTTPManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Http. */
//--------------------------------------------------------------

#include "HTTPManager.h"

//--------------------------------------------------------------
HTTPManager::HTTPManager()
{
	DebugMessage("HTTP Manager","Setup");
	ofAddListener(httpUtils.newResponseEvent, this, &HTTPManager::newResponse);
	httpUtils.start();
}

//--------------------------------------------------------------
HTTPManager::~HTTPManager()
{
	
}

//--------------------------------------------------------------
void HTTPManager::postEvent(HTTPData data)
{
	ofxHttpForm form;
	form.method = OFX_HTTP_POST;
	form.action = data.hostURL + "/" + data.extension;
	
	for(int i = 0; i < data.data.size(); i++)
	{
		form.addFormField(data.data[i].field, data.data[i].value);
	}
	
	form.addFormField("submit", "1");
	httpUtils.addForm(form);
}

//--------------------------------------------------------------
void HTTPManager::exit()
{
	ofRemoveListener(httpUtils.newResponseEvent, this, &HTTPManager::newResponse);
}

//--------------------------------------------------------------
void HTTPManager::newResponse(ofxHttpResponse & response)
{
	DebugMessage("HTTP Manager" , "Return");
	// cout << response.url << endl;
	// cout << response.responseBody << endl;
}
