//--------------------------------------------------------------
//  VideoNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Video Node Class. */
//--------------------------------------------------------------
#ifndef VideoNode_h
#define VideoNode_h

#include "BaseNode.h"

class VideoNode : public BaseNode
{
public:
	//-----------------------------------------------------
	/** \brief Default Constructor */
	//-----------------------------------------------------
	VideoNode() { }

	//-----------------------------------------------------
	/** \brief Deconstructor */
	//-----------------------------------------------------
	~VideoNode() { }

	//-----------------------------------------------------
	/** \brief Constructor.
		* @param box  : The position of the Node.
		* @param font : The font.
		* @param name : The name of the Node.
		* @param id   : Pointer to the id of the Node.
		* @param filePath : a filePath.
		*
		* This method Constructs an Video Node from scratch
		* it generates the ports and layout of the node
	*/
	//-----------------------------------------------------
	VideoNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,string filePath)
	{
		this->portNames = {"Play", "Stop", "Reset"};

		addMouseAndCloseListeners();
		this->id = id;
		this->font = font;
		this->name = name;
		this->noOfPorts = portNames.size();
		this->box = box;
		this->filePath = filePath;
		resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

		header = ofRectangle(box.x, box.y,box.width, 23);

		generatePorts(noOfPorts);

		player.load(filePath);
		aspectRatio = player.getHeight()/player.getWidth();
		cout << aspectRatio << endl;
	}

	//-----------------------------------------------------
	/** \brief Load Constructor.
		* @param box  : The position of the Node.
		* @param font : The font.
		* @param name : The name of the Node.
		* @param id   : Pointer to the id of the Node.
		* @param ports : A vector of Port information.
		* @param filePath : a filePath.
		*
		* This method Constructs an Video Node from the
		* load file it generates the ports and layout of
		* the node.
	*/
	//-----------------------------------------------------
	VideoNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,string filePath)
	{
		addMouseAndCloseListeners();

		this->id = id;
		this->font = font;
		this->name = name;
		this->ports = ports;
		this->box = box;
		this->filePath = filePath;
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
		player.update();
		player.draw(header.getBottomLeft().x+GUI_PADDING_X,header.getBottomLeft().y+GUI_PADDING_Y,box.width-(GUI_PADDING_Y*2),box.height-header.height-(GUI_PADDING_Y*2));
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
		if(i == 0)
		{
			player.play();
		}
		else if(i == 1)
		{
			player.stop();
		}
		else if(i == 2)
		{
			player.setFrame(0);
		}
	}
	
	//-----------------------------------------------------
	/** \brief Get the File Path for Saving
		* @return filePaths : A filePath.
		*
		* This method returns the stored filePath for
		* saving.
	*/
	//-----------------------------------------------------
	string getFilePath()
	{
		return filePath;
	}

private:
string filePath;
ofVideoPlayer player;
float aspectRatio;
};

#endif /* VideoNode_h */
