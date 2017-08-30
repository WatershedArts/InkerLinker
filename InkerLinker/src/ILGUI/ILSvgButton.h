//--------------------------------------------------------------
//  ILSvgButton.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Svg Button element. */
//--------------------------------------------------------------

#ifndef ILSvgButton_h
#define ILSvgButton_h

#include "ofMain.h"
#include "ofxSvgLoader.h"
#include "ILGUIObject.h"

class ILSvgButton : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILSvgButton() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILSvgButton() { }
		
		//-----------------------------------------------------
		/** \brief Default Constructor
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param svgFile : svg filename.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item.
			* @param colour : hover colour of item.
			*
			* This method creates a new Svg Button Item.
		*/
		//-----------------------------------------------------
		ILSvgButton(string name,ofRectangle anchor, string svgFile,ofTrueTypeFont *font,int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			svg.load(svgFile);
			type = IL_SVG_BUTTON;
			group = svg.get< ofxSvgGroup >("ic");
			box = anchor;
			
			this->name = name;
			this->font = font;
			this->colour = colour;
			this->hoverColour = hoverColour;
			this->offsetX = offsetX;
			
			bClicked = false;
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
			ofSetColor(255);
			
			if(bHovering) ofSetColor(240, 240, 240);
			else ofSetColor(255,255);
			
			if(bClicked) ofSetColor(GUI_COLOR);
			ofFill();
			ofDrawRectRounded(box,3);
			
			ofPushMatrix();
			ofTranslate(box.getCenter()-ofPoint(35/2,35/2));
			svg.draw();
			ofPopMatrix();
			ofPopStyle();
		}
		
		
		//-----------------------------------------------------
		/** \brief Mouse Pressed
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mousePressed(ofMouseEventArgs &e)
		{
			if(bEnabled) {
				if(box.inside(e.x,e.y))
				{
					bClicked = true;
					
					if( group )
					{
						for( int i = 0; i < group->getElements().size(); i++ )
						{
							shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
							te->path.setFillColor( GUI_HOVERING_COLOR );
						}
					}
				}
			}
		}
		
		//-----------------------------------------------------
		/** \brief Mouse Released
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseReleased(ofMouseEventArgs &e)
		{
			if(bEnabled)
			{
				if(box.inside(e.x,e.y))
				{
					if( group )
					{
						for( int i = 0; i < group->getElements().size(); i++ )
						{
							shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
							te->path.setFillColor( ofColor::black );
						}
					}
					ofNotifyEvent(buttonPushed, name, this);
					bClicked = false;
				}
			}
		}
		
		//-----------------------------------------------------
		/** \brief Mouse Moved
			* @param e : Mouse Events.
			*
			* This method receives the mouse events.
		*/
		//-----------------------------------------------------
		void mouseMoved(ofMouseEventArgs &e)
		{
			if(box.inside(e.x,e.y))
			{
				bHovering = true;
			}
			else
			{
				bHovering = false;
			}
		}
		
		//-----------------------------------------------------
		/// \brief Set Enabled
		//-----------------------------------------------------
		void setUnclicked()
		{
			bClicked = false;
			if( group )
			{
				for( int i = 0; i < group->getElements().size(); i++ )
				{
					shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
					te->path.setFillColor( ofColor::black );
				}
			}
		}
		
		void mouseDragged(ofMouseEventArgs &e){}
		void mouseEntered(ofMouseEventArgs &e){}
		void mouseExited(ofMouseEventArgs &e){}
		void mouseScrolled(ofMouseEventArgs &e){}
		
		ofEvent<string> buttonPushed;
		ofEvent<string> buttonReleased;
		
	private:
		
		ofxSvgLoader svg;
		shared_ptr<ofxSvgGroup> group;
		ofTrueTypeFont *font;
		ofColor colour;
		ofColor hoverColour;
};



#endif /* ILSvgButton_h */
