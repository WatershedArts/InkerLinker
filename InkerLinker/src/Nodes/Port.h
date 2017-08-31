//--------------------------------------------------------------
//  Port.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is a Port Object. */
//--------------------------------------------------------------

#ifndef Port_h
#define Port_h

#include "ofMain.h"
#include "Tooltip.h"
class Port
{
	public:

		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		Port() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~Port() { }

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param x  : The position of the Node.
			* @param y : The font.
			* @param portId : The name of the Node.
			* @param nodeId   : Pointer to the id of the Node.
			* @param name : A vector of Port information.
			*
			* This method Constructs an Port Object and 
			* generates the layout of ports.
		*/
		//-----------------------------------------------------
		Port(int x,int y,int portId,int nodeId,string name)
		{
			box = ofRectangle(x,y,20,20);
			this->portId = portId;
			this->name = name;
			this->nodeId = nodeId;
			bActionAttached = false;
			bHovering = false;
		}

		//-----------------------------------------------------
		/** \brief Update
			*
			* Update the ports location.
		*/
		//-----------------------------------------------------
		void update(int x,int y)
		{
			box.setPosition(x,y);
		}

		//-----------------------------------------------------
		/** \brief Draw
			*
			* Draws the Node and the ports.
		*/
		//-----------------------------------------------------
		void draw()
		{
			ofPushStyle();
			ofFill();

			if(bHovering) ofSetColor(255,255,200);
			else ofSetColor(235);

			ofDrawRectRounded(box, 1);
			ofNoFill();
			ofSetColor(0);
			ofDrawRectRounded(box, 1);

			if(bActionAttached)
			{
				ofPushStyle();
				ofSetLineWidth(4);
				ofNoFill();
				ofDrawCircle(box.getCenter(), box.getWidth()/4);
				ofPopStyle();
			}
			else
			{
				ofPushStyle();
				ofSetLineWidth(4);
				ofDrawLine(box.getLeft()+4,box.getCenter().y,box.getRight()-4,box.getCenter().y);
				ofDrawLine(box.getCenter().x,box.getTop()+4,box.getCenter().x,box.getBottom()-4);
				ofPopStyle();
			}

			ofPopStyle();
		}

		//-----------------------------------------------------
		/** \brief Draw the tooltip
			*
			* Draws the tooltip
		*/
		//-----------------------------------------------------
		void drawTooltip()
		{
			ofPushMatrix();
			if(bHovering) tt.draw(name, box.getRight(), box.getCenter().y);
			ofPopMatrix();
		}

		#pragma mark - Getters
			
		//-----------------------------------------------------
		/** \brief Get the Node Id for the port
			* @return nodeId : id of node.
			*
			* This method returns the id of the node the port
			* is attached to.
		*/
		//-----------------------------------------------------
		int getNodeId()
		{
			return nodeId;
		}

		//-----------------------------------------------------
		/** \brief Get the Port Id
			* @return portId : id of port.
			*
			* This method returns the id of the port.
		*/
		//-----------------------------------------------------
		int getPortId()
		{
			return portId;
		}

		//-----------------------------------------------------
		/** \brief Get the Patch Cord Id
			* @return nodeId : id of node.
			*
			* This method returns the id of the node the port
			* is attached to.
		*/
		//-----------------------------------------------------
		int getPatchCordId()
		{
			return patchCordId;
		}

		//-----------------------------------------------------
		/** \brief Get the Port State
			* @return bActionAttached : is something attached.
			*
			* This method returns bool whether patch cord is 
			* attached.
		*/
		//-----------------------------------------------------
		bool getPortState()
		{
			return bActionAttached;
		}

		//-----------------------------------------------------
		/** \brief Get the Port State.]
			* @return electrodeId : electrode id.
			*
			* This method returns the value of the electrode
			* connected to the port.
		*/
		//-----------------------------------------------------
		string getElectrodeId()
		{
			return electrodeId;
		}

		//-----------------------------------------------------
		/** \brief Get the Box
			* @return box : rectangle of port.
			*
			* This method returns the rectangle of the port 
			* element.
		*/
		//-----------------------------------------------------
		ofRectangle getBox()
		{
			return box;
		}

		//-----------------------------------------------------
		/** \brief Get Name
			* @return name : name of port.
			*
			* This method returns the name of the port.
		*/
		//-----------------------------------------------------
		string getName()
		{
			return name;
		}


		#pragma mark - Setters
		//-----------------------------------------------------
		/** \brief Set Position
			* @param r : new rectangle of port.
			*
			* This method set the position of the port.
		*/
		//-----------------------------------------------------
		void setPostion(ofRectangle r)
		{
			box = r;
		}

		//-----------------------------------------------------
		/** \brief Set Hover State
			* @param bHover : hovering state.
			*
			* This method set whether the mouse is
			* hovering over the port.
		*/
		//-----------------------------------------------------
		void setHovering(bool bHover)
		{
			bHovering = bHover;
		}

		//-----------------------------------------------------
		/** \brief Sets the port active
			*
			* This method set the port to active.
		*/
		//-----------------------------------------------------
		void setPortStateActive()
		{
			bActionAttached = true;
		}

		//-----------------------------------------------------
		/** \brief Sets the port inactive
			*
			* This method set the port to inactive.
		*/
		//-----------------------------------------------------
		void setPortStateInactive()
		{
			bActionAttached = false;
		}

		//-----------------------------------------------------
		/** \brief Sets Electrode Id
			* @param id : new id of electrode.
			*
			* This method set the electrode id.
		*/
		//-----------------------------------------------------
		void setElectrodeId(string id)
		{
			electrodeId = id;
		}

		//-----------------------------------------------------
		/** \brief Sets Patch Cord Id
			* @param id : new id of the patch cord.
			*
			* This method sets the id of the patch cord.
		*/
		//-----------------------------------------------------
		void setPatchCordId(int id)
		{
			patchCordId = id;
		}

	private:
		ofRectangle box;
		ofImage portImageEmpty;
		ofImage portImageAttached;
		string name;
		int nodeId;
		int portId;
		int patchCordId;
		bool bActionAttached;
		bool bHovering;
		string electrodeId;
		Tooltip tt;
};

#endif /* Port_h */
