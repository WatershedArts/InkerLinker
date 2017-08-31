//--------------------------------------------------------------
//  HTTPNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the HTTP Node Class. */
//--------------------------------------------------------------
#ifndef HTTPNode_h
#define HTTPNode_h

#include "BaseNode.h"

class HTTPNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		HTTPNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~HTTPNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param httpData : A vector of HTTPData.
			*
			* This method Constructs an HTTP Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		HTTPNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<HTTPData> httpData)
		{
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = httpData.size();
			this->box = box;
			this->httpData = httpData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);
			for(int i = 0; i < noOfPorts; i++)
			{
				this->portNames.push_back("Action " + ofToString(i));
			}
			generatePorts(noOfPorts);
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param httpData : A vector of HTTPData.
			*
			* This method Constructs an HTTP Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		HTTPNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<HTTPData> httpData)
		{
			addMouseAndCloseListeners();

			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->noOfPorts = httpData.size();
			this->httpData = httpData;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);
		}

		//-----------------------------------------------------
		/** \brief Draw
			*
			* Draws the Node and the ports.
		*/
		//-----------------------------------------------------
		void draw()
		{
			BaseNode::draw();
			ofPushStyle();
			ofSetColor(255);
			ofFill();
			ofPopStyle();
			BaseNode::drawTooltips();
		}

		//-----------------------------------------------------
		/** \brief Trigger Port
			* @param i : A integer of which event to trigger.
			*
			* This method trigger actions associated with the Node.
		*/
		//-----------------------------------------------------
		void triggerPort(int i)
		{
			if(!httpData.empty())
				ofNotifyEvent(httpDataEvent, httpData[i], this);
		}

		//-----------------------------------------------------
		/** \brief Get the HTTP Data for Saving
			* @return httpData : A vector of HTTPData.
			*
			* This method returns the stored http data for
			* saving.
		*/
		//-----------------------------------------------------
		vector <HTTPData> getHTTPData()
		{
			return httpData;
		}

		ofEvent<HTTPData> httpDataEvent;
	private:
		vector<HTTPData> httpData;
};


#endif /* HTTPNode_h */
