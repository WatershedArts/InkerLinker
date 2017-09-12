//--------------------------------------------------------------
//  ImageNode.h
//  InkerLinker.
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Image Node Class. */
//--------------------------------------------------------------
#ifndef ImageNode_h
#define ImageNode_h

#include "BaseNode.h"
#include "ofxTween.h"
#include "ofxThreadedImageLoader.h"

class ImageNode : public BaseNode
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		ImageNode() { }

		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ImageNode() { }

		//-----------------------------------------------------
		/** \brief Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param filePaths : A vector of filePaths.
			*
			* This method Constructs an Image Node from scratch
			* it generates the ports and layout of the node
		*/
		//-----------------------------------------------------
		ImageNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,string filePath)
		{
			portNames = {"Show", "Hide","Fade In", "Fade Out"};
			type = IL_IMAGE_NODE;
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

			currentVisibilty = 0;
			maxImageWidth = 0;
			maxImageHeight = 0;

			image.load(filePath);
			
			carouselContainer.allocate(600,600);
			carouselContainer.begin();
			ofClear(0);
			carouselContainer.end();
		}

		//-----------------------------------------------------
		/** \brief Load Constructor.
			* @param box  : The position of the Node.
			* @param font : The font.
			* @param name : The name of the Node.
			* @param id   : Pointer to the id of the Node.
			* @param ports : A vector of Port information.
			* @param filePaths : A vector of filePaths.
			*
			* This method Constructs an Image Node from the
			* load file it generates the ports and layout of
			* the node.
		*/
		//-----------------------------------------------------
		ImageNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,string filePath)
		{
			type = IL_IMAGE_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->filePath = filePath;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			currentVisibilty = 0;
			maxImageWidth = 0;
			maxImageHeight = 0;

			
			carouselContainer.allocate(600,600);
			carouselContainer.begin();
			ofClear(0);
			carouselContainer.end();
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

			carouselContainer.begin();
			ofClear(0,255);
			

			if(tweenLinear.isRunning())
			{
				currentVisibilty = tweenLinear.update();
			}
	
			ofSetColor(255,currentVisibilty);
			image.draw(0,0,image.getWidth(),image.getHeight());
			ofPopMatrix();
			
			carouselContainer.end();

			ofPushStyle();
			ofSetColor(255);
			ofFill();
			carouselContainer.draw(header.getBottomLeft().x+GUI_PADDING_X,header.getBottomLeft().y+GUI_PADDING_Y,(box.width)-(GUI_PADDING_X*2),(box.height-header.height)-(GUI_PADDING_Y*2));
			BaseNode::drawTooltips();
			ofPopStyle();
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
				currentVisibilty = 255;
			}
			else if(i == 1)
			{
				currentVisibilty = 0;
			}
			else if(i == 2)
			{
				tweenLinear.setParameters(0,easingLinear,ofxTween::easeInOut,currentVisibilty,255,1000,0);
			}
			else if(i == 3)
			{
				tweenLinear.setParameters(0,easingLinear,ofxTween::easeInOut,currentVisibilty,0,1000,0);
			}
		}

		//-----------------------------------------------------
		/** \brief Get the File Path for Saving
			* @return filePath : A filePath.
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
		int currentVisibilty;
		string filePath;

		ofImage image;

		ofFbo carouselContainer;
		ofxTween tweenLinear;
		ofxEasingLinear easingLinear;

		int maxImageWidth;
		int maxImageHeight;
		int imageOffsetX;
		int imageOffsetY;
		bool bAllImagesLoaded;
};

#endif /* ImageNode_h */
