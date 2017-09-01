//--------------------------------------------------------------
//  QLabNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the QLab Node Class. */
//--------------------------------------------------------------
#ifndef QlabNode_h
#define QlabNode_h
#include "BaseNode.h"

class QlabNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		QlabNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~QlabNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param qlabData : A vector of qlabData.
			*
			* This method Constructs an QLab Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		QlabNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<QLabData> qlabData)
		{
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = qlabData.size();
			this->box = box;
			this->qlabData = qlabData;
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
			* @param qlabData : A vector of qlabData.
			*
			* This method Constructs an QLab Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		QlabNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<QLabData> qlabData)
		{
			addMouseAndCloseListeners();

			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->noOfPorts = qlabData.size();
			this->qlabData = qlabData;
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
			if(!qlabData.empty())
				ofNotifyEvent(qlabEvent, qlabData[i], this);
		}

		//-----------------------------------------------------
		/** \brief Get the Osc Data for Saving
			* @return oscData : A vector of OscData.
			*
			* This method returns the stored osc data for
			* saving.
		*/
		//-----------------------------------------------------
		vector<QLabData> getOscData()
		{
			return qlabData;
		}
	
		ofEvent<QLabData> qlabEvent;
	private:
		string filePath;
		vector<QLabData> qlabData;
	
};

#endif /* QlabNode_h */
