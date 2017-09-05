//--------------------------------------------------------------
//  BaseNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Base Node Class. */
//--------------------------------------------------------------
#ifndef BaseNode_h
#define BaseNode_h

#include "ofxCenteredTrueTypeFont.h"
#include "ILIconButton.h"
#include "Port.h"

class BaseNode
{
	public:
	
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		BaseNode() { }
	
		//-----------------------------------------------------
		/** \brief Deconstructor 
			 *
			 * This method removes the listeners from the node object.
		 */
		//-----------------------------------------------------
		~BaseNode()
		{
			ofRemoveListener(closeNode->buttonPushed, this, &BaseNode::closeNodeEvent);
			ofRemoveListener(ofEvents().mousePressed,this,&BaseNode::mousePressed);
			ofRemoveListener(ofEvents().mouseReleased,this,&BaseNode::mouseReleased);
			ofRemoveListener(ofEvents().mouseMoved,this,&BaseNode::mouseMoved);
			ofRemoveListener(ofEvents().mouseDragged,this,&BaseNode::mouseDragged);
		}
	
		//-----------------------------------------------------
		/** \brief Constructor.
			 * @param box  : The position of the Node.
			 * @param font : The font.
			 * @param name : The name of the Node.
			 * @param id   : Pointer to the id of the Node.
			 * @param noOfPorts : Number of ports to generate
			 *
			 * This method constructs a Base Node from the
			 * load file it generates the ports and layout of
			 * the node.
		 */
		//-----------------------------------------------------
		BaseNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,int noOfPorts)
		{
			type = IL_BASE_NODE;
			bCanMoveNode = false;
			bCanResizeNode = false;
			bIsNodeSizeLocked = false;
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = noOfPorts;
			this->box = box;
			header = ofRectangle(box.x, box.y,box.width, 23);
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			
			for(int i = 0; i < noOfPorts; i++)
			{
				portNames.push_back(ofToString(i));
			}
			
			generatePorts(noOfPorts);
			
			addMouseAndCloseListeners();
		}
	
		//-----------------------------------------------------
		/** \brief Load Constructor.
			 * @param box  : The position of the Node.
			 * @param font : The font.
			 * @param name : The name of the Node.
			 * @param id   : Pointer to the id of the Node.
			 * @param ports : A vector of Port information.
			 *
			 * This method Constructs an Base Node from the
			 * load file it generates the ports and layout of
			 * the node.
		 */
		//-----------------------------------------------------
		BaseNode(ofRectangle box,ofxCenteredTrueTypeFont *font, string name, int *id,vector<Port> ports)
		{
			type = IL_BASE_NODE;
			bCanMoveNode = false;
			bCanResizeNode = false;
			bIsNodeSizeLocked = false;
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			header = ofRectangle(box.x, box.y,box.width, 23);
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);
			reGeneratePortPositions(this->ports);
			addMouseAndCloseListeners();
		}
	
		//-----------------------------------------------------
		/** \brief Add Listeners to the Node Object
			 *
			 * This method Adds listeners to the node object
			 * and creates the close button.
		 */
		//-----------------------------------------------------
		virtual void addMouseAndCloseListeners()
		{
			closeNode = new ILIconButton("Close",ofRectangle(header.getRight()-(GUI_BUTTON_WIDTH/2),header.getCenter().y-(GUI_BUTTON_HEIGHT/4),(GUI_BUTTON_WIDTH/2)-(GUI_PADDING_X*2),(GUI_BUTTON_HEIGHT/2)-(GUI_PADDING_X*2)),IL_ICON_CROSS,0,IL_DANGER_COLOR,IL_WARNING_COLOR);
			
			closeNode->setEnabled(true);
			ofAddListener(closeNode->buttonPushed, this, &BaseNode::closeNodeEvent);
			ofAddListener(ofEvents().mousePressed,this,&BaseNode::mousePressed);
			ofAddListener(ofEvents().mouseReleased,this,&BaseNode::mouseReleased);
			ofAddListener(ofEvents().mouseMoved,this,&BaseNode::mouseMoved);
			ofAddListener(ofEvents().mouseDragged,this,&BaseNode::mouseDragged);
			bCanMoveNode = false;
			bCanResizeNode = false;
		}
	
		//-----------------------------------------------------
		/** \brief Removes the Listeners
			*
			* This method removes the listeners from the node object.
		*/
		//-----------------------------------------------------
		virtual void removeMouseAndCloseListeners()
		{	
			ofRemoveListener(closeNode->buttonPushed, this, &BaseNode::closeNodeEvent);
			ofRemoveListener(ofEvents().mousePressed,this,&BaseNode::mousePressed);
			ofRemoveListener(ofEvents().mouseReleased,this,&BaseNode::mouseReleased);
			ofRemoveListener(ofEvents().mouseMoved,this,&BaseNode::mouseMoved);
			ofRemoveListener(ofEvents().mouseDragged,this,&BaseNode::mouseDragged);
		}
	
		//-----------------------------------------------------
		/** \brief Generate the Ports
			* @param noOfPorts : Number of Ports to generate.
			*
			* This method generates the number of ports specified
			* in the call.
		*/
		//-----------------------------------------------------
		virtual void generatePorts(int noOfPorts)
		{
			this->noOfPorts = noOfPorts;
			spacing = (box.height-header.height) / (20 + 5);
			for(int i = 0; i < noOfPorts; i++)
			{
				ports.push_back(Port(box.getLeft()-20,header.getBottomLeft().y+spacing+(i*(20+spacing)),i,*this->id,portNames[i]));
			}
		}
	
		//-----------------------------------------------------
		/** \brief Regenerate the Ports
			* @param pts : A vector of Ports.
			*
			* This method generates the number of ports from
			* the load file.
		*/
		//-----------------------------------------------------
		virtual void reGeneratePortPositions(vector <Port> pts)
		{
			spacing = (box.height-header.height) / (20 + 5);
			
			for(int i = 0; i < pts.size(); i++)
			{
				pts[i].setPostion(ofRectangle(box.getLeft()-20,header.getBottomLeft().y+spacing+(i*(20+spacing)),20,20));
			}
		}
	
		//-----------------------------------------------------
		/** \brief Recalculate the port positions
			*
			* This method repositions the ports.
		*/
		//-----------------------------------------------------
		virtual void recalculatePortPositions()
		{
			spacing = (box.height-header.height) / (20 + 5);
			
			for(int i = 0; i < ports.size(); i++)
			{
				ports[i].update(box.getLeft()-19,header.getBottomLeft().y+spacing+(i*(20+spacing)));
			}
		}
	
		//-----------------------------------------------------
		/** \brief Draw
			*
			* This method Draws the BaseNode
		*/
		//-----------------------------------------------------
		virtual void draw()
		{
			recalculatePortPositions();
			for(int i = 0; i < ports.size(); i++) ports[i].draw();
			
			ofFill();
			ofSetColor(255);
			ofDrawRectRounded(box,3);
			
			ofFill();
			ofSetColor(255);
			ofDrawRectRounded(header,3);
			
			ofSetColor(0);
			font->drawString(name,header.getLeft()+8,header.getCenter().y+5);
			
			closeNode->updateBox(header.getRight()-((GUI_BUTTON_WIDTH/2)+GUI_PADDING_Y),header.getCenter().y-(GUI_BUTTON_HEIGHT/6));
			closeNode->draw();
			
			ofNoFill();
			ofSetColor(0);
			ofDrawRectRounded(box,3);
		}
	
		//-----------------------------------------------------
		/** \brief Draw Tooltips
			*
			* This method Draws the tooltips for the ports.
		*/
		//-----------------------------------------------------
		virtual void drawTooltips()
		{
			for(int i = 0; i < ports.size(); i++) ports[i].drawTooltip();
		}
	
		//-----------------------------------------------------
		/** \brief Trigger Port
			* @param i : A integer of which event to trigger.
			*
			* This method trigger actions associated with the Node.
		*/
		//-----------------------------------------------------
		virtual void triggerPort(int i)
		{

		}
	
		//-----------------------------------------------------
		/** \brief Draw Tooltips
			 * @param val : Event from button push (Not useful)
			 *
			 * This method listens for an event from the close
			 * button.
		*/
		//-----------------------------------------------------
		virtual void closeNodeEvent(string &val)
		{
			removeMouseAndCloseListeners();
			ofNotifyEvent(closedNodeId,*id,this);
		}
	
#pragma mark - Mouse Events
	
		//-----------------------------------------------------
		/** \brief Mouse Pressed
			* @param e : Mouse Arguements.
			*
			* This method listens for events from the mouse.
			* It also handles the remove events from the ports.
			* As well as move events.
		*/
		//-----------------------------------------------------
		virtual void mousePressed(ofMouseEventArgs &e)
		{
			// Remove Patch Cord and Electrode Event
			if(e.button == 2)
			{
				for(int i = 0; i < ports.size(); i++)
				{
					if(ports[i].getBox().inside(e.x,e.y))
					{
						currentPortId = i;
						int id = ports[i].getPatchCordId();
						ofNotifyEvent(removePatchCord, ports[i], this);
					}
				}
			}
			
			// Allow the Node to move
			if(header.inside(e.x,e.y) && !bCanMoveNode)
			{
				mouseMoveOffset = ofPoint(e.x,e.y) - header.getTopLeft();
				bCanMoveNode = true;
			}
			
			// Can the Node be resized
			if(!bIsNodeSizeLocked) {
				if(resizeNode.inside(e.x,e.y) && !bCanResizeNode)
				{
					mouseResizeOffset = ofPoint(e.x,e.y) - box.getTopLeft();
					bCanResizeNode = true;
				}
				else {
					bCanResizeNode = false;
				}
			}
		}
	
		//-----------------------------------------------------
		/** \brief Mouse Released
			* @param e : Mouse Arguements.
			*
			* This method listens for events from the mouse.
			* It also handles the addition of events to the
			* node.
		*/
		//-----------------------------------------------------
		virtual void mouseReleased(ofMouseEventArgs &e)
		{
			// If the Button is Left Release
			if( e.button == 0 )
			{
				for(int i = 0; i < ports.size(); i++)
				{
					if(ports[i].getBox().inside(e.x,e.y))
					{
						currentPortId = i;
						ofNotifyEvent(attachPatchCord,ports[i],this);
					}
				}
			}
			// If the Button is Right Release
			else if( e.button == 2 )
			{
				for(int i = 0; i < ports.size(); i++)
				{
					if(ports[i].getBox().inside(e.x,e.y))
					{
						currentPortId = i;
						ofNotifyEvent(attachPatchCord,ports[i],this);
					}
				}
			}
			
			bCanMoveNode = false;
			bCanResizeNode = false;
		}
	
		//-----------------------------------------------------
		/** \brief Mouse Dragged
			* @param e : Mouse Arguements.
			*
			* This method listens for events from the mouse.
			* As well as move events.
		*/
		//-----------------------------------------------------
		virtual void mouseDragged(ofMouseEventArgs &e)
		{
			if(bCanMoveNode)
			{
				ofPoint m(e.x,e.y);
				
				header.setPosition(m-mouseMoveOffset);
				box.setPosition(m-mouseMoveOffset);
				resizeNode.setPosition(box.getBottomRight()+ofPoint(-25,-25));
			}
			
			if(!bIsNodeSizeLocked) {
				if(bCanResizeNode)
				{
					ofPoint p = ofPoint(e.x,e.y) - box.getTopLeft();
					
					p.x = ofClamp(p.x,IL_MIN_NODE_WIDTH,IL_MAX_NODE_WIDTH);
					p.y = ofClamp(p.y,IL_MIN_NODE_HEIGHT,IL_MAX_NODE_HEIGHT);
					
					box.setSize(p.x,p.y);
					resizeNode.setPosition(box.getBottomRight()+ofPoint(-25,-25));
					header.setWidth(box.width);
				}
			}
		}
	
		//-----------------------------------------------------
		/** \brief Mouse Moved
			* @param e : Mouse Arguements.
			*
			* This method listens for events from the mouse.
			* It checks whether the mouse is hovering over the 
			* ports.
		*/
		//-----------------------------------------------------
		virtual void mouseMoved(ofMouseEventArgs &e)
		{
			for(int i = 0; i < ports.size(); i++)
			{
				if(ports[i].getBox().inside(e.x,e.y))
				{
					ports[i].setHovering(true);
				}
				else
				{
					ports[i].setHovering(false);
				}
			}
		}
	
	
#pragma mark - Getters
	
		//-----------------------------------------------------
		/** \brief Get the ID of the Node
			* @return id : Id of the Node.
			*
			* This method returns the id of the Node.
		*/
		//-----------------------------------------------------
		int getID()
		{
			return *id;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Node Name
			* @return name : Name of Node
			*
			* This method returns the Name of the Node.
		*/
		//-----------------------------------------------------
		string getName() const
		{
			return name;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Nodes Position
			* @return box : Rectangle of the Node.
			*
			* This method returns the position and size of the
			* Node.
		*/
		//-----------------------------------------------------
		ofRectangle getBox()
		{
			return box;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Number of Ports
			* @return noOfPorts : Number of Ports.
			*
			* This method returns the number of ports for the 
			* Node.
		*/
		//-----------------------------------------------------
		int getNoOfPorts()
		{
			return noOfPorts;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Type of Node
			* @return type : Number of Ports.
			*
			* This method returns the type of Node.
		*/
		//-----------------------------------------------------
		IL_NODE_TYPE getType()
		{
			return type;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Ports
			* @return ports : vector of Ports.
			*
			* This method returns the data associated with the
			* ports.
		*/
		//-----------------------------------------------------
		vector <Port> getPorts()
		{
			return ports;
		}
	
		//-----------------------------------------------------
		/** \brief Get the Current Electrode Id
			* @return electrode id : id of electrode.
			*
			* This method returns the selected electrode id.
		*/
		//-----------------------------------------------------
		string getCurrentElectrodeId()
		{
			return ports[currentPortId].getElectrodeId();
		}

		//-----------------------------------------------------
		/** \brief Get the Current Patch Cord Id
			* @return patch cord id : id of patch cord.
			*
			* This method returns the selected patch cord id.
		*/
		//-----------------------------------------------------
		int getCurrentPatchCordId()
		{
			return ports[currentPortId].getPatchCordId();
		}
	
	#pragma mark - Setters

		//-----------------------------------------------------
		/** \brief Set Patch Cord Id
			* @param id : id of Cord.
			*
			* This method stores the patch cord id in the port.
		*/
		//-----------------------------------------------------
		void setPatchCoordId(int id)
		{
			ports[currentPortId].setPatchCordId(id);
		}
	
		//-----------------------------------------------------
		/** \brief Set Electrode Id
			* @param id : id of Electrode.
			*
			* This method stores the Electrode id in the port.
		*/
		//-----------------------------------------------------
		void setElectrodeId(string id)
		{
			ports[currentPortId].setElectrodeId(id);
		}

		//-----------------------------------------------------
		/// Events
		//-----------------------------------------------------
		ofEvent<Port> attachPatchCord;
		ofEvent<Port> removePatchCord;
		ofEvent<int> closedNodeId;
	
		//-----------------------------------------------------
		/// Variables
		//-----------------------------------------------------
		ofRectangle box;
		string name;
		int *id;
		int spacing;
		vector<Port> ports;
		int currentPortId;
		vector <string> portNames;
		bool bCanMoveNode;
		bool bCanResizeNode;
		bool bIsNodeSizeLocked;
		int noOfPorts;
		ofPoint mouseMoveOffset;
		ofPoint mouseResizeOffset;
		ofRectangle header;
		ofxCenteredTrueTypeFont *font;
		ILIconButton *closeNode;
		ofRectangle resizeNode;
		IL_NODE_TYPE type;
	
	private:
};

#endif /* BaseNode_h */
