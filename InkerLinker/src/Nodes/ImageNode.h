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
		ImageNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<string> filePaths)
		{
			portNames = {"Next", "Previous"};
			type = IL_IMAGE_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->noOfPorts = portNames.size();
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			generatePorts(noOfPorts);

			currentPosition = 0;
			maxImageWidth = 0;
			maxImageHeight = 0;

			images.resize(filePaths.size());
			bAllImagesLoaded = false;
			for (int i = 0; i < filePaths.size(); i++)
			{
				imageLoader.loadFromDisk(images[i],filePaths[i]);
			}
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
		ImageNode(ofRectangle box,ofxCenteredTrueTypeFont * font, string name, int *id,vector<Port> ports,vector<string> filePaths)
		{
			type = IL_IMAGE_NODE;
			addMouseAndCloseListeners();
			this->id = id;
			this->font = font;
			this->name = name;
			this->ports = ports;
			this->box = box;
			this->filePaths = filePaths;
			resizeNode = ofRectangle(box.getBottomRight()+ofPoint(-25,-25),25,25);

			header = ofRectangle(box.x, box.y,box.width, 23);

			currentPosition = 0;
			maxImageWidth = 0;
			maxImageHeight = 0;

			images.resize(filePaths.size());
			bAllImagesLoaded = false;
			for (int i = 0; i < filePaths.size(); i++)
			{
				imageLoader.loadFromDisk(images[i],filePaths[i]);
			}
			carouselContainer.allocate(500,500);
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
			ofSetColor(255);

			if(tweenLinear.isRunning())
			{
				currentPosition = tweenLinear.update();
			}

			for (int i = 0; i < images.size(); i++)
			{
				ofPoint c(carouselContainer.getWidth()/2,carouselContainer.getHeight()/2);
				ofPoint mark(images[i].getWidth()/2,images[i].getHeight()/2);

				ofPoint newOffsetPos = c - mark;
				ofPushMatrix();

			//			currentPosition = -1000 + 1000 * sin(ofGetElapsedTimef());

			ofTranslate(currentPosition,0);
			images[i].draw(newOffsetPos.x + (i*600),newOffsetPos.y,images[i].getWidth(),images[i].getHeight());
			ofPopMatrix();
			}
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

		}

		//-----------------------------------------------------
		/** \brief Kill the Thread
			*
			* This method Stops the loader thread.
		*/
		//-----------------------------------------------------
		void killImageThread()
		{
			imageLoader.stopThread();
		}

		//-----------------------------------------------------
		/** \brief Get the File Paths for Saving
			* @return filePaths : A vector of filePaths.
			*
			* This method returns the stored filePaths for
			* saving.
		*/
		//-----------------------------------------------------
		vector <string> getFilePaths()
		{
			return filePaths;
		}

	private:
		int currentPosition;
		vector <string> filePaths;

		ofxThreadedImageLoader imageLoader;
		vector<ofImage> images;

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
