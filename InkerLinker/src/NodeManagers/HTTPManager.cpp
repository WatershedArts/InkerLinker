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
	httpUtils.setMaxRetries(3);
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
	string url = data.hostURL + "/" + data.extension;
	form.method = OFX_HTTP_POST;
	form.action = url;
	cout << form.action << endl;
	for(int i = 0; i < data.data.size(); i++)
	{
		form.addFormField(data.data[i].field, data.data[i].value);
	}
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
	string thisstring = ofToString(response.status) + "|" + response.responseBody.getData();
	DebugMessage("HTTP Manager" , thisstring.c_str());
	cout << response.getURLFilename() << endl;
	cout << response.reasonForStatus << endl;
}
