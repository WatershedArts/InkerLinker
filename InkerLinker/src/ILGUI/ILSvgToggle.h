//--------------------------------------------------------------
//  ILSvgToggle.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Svg Toggle element. */
//--------------------------------------------------------------

#ifndef ILSvgToggle_h
#define ILSvgToggle_h

#include "ofMain.h"
#include "ofxSvgLoader.h"
#include "ILGUIObject.h"

class ILSvgToggle : public ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILSvgToggle() { }
	
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILSvgToggle() { }
	
		//-----------------------------------------------------
		/** \brief Default Constructor 
			* @param name : element name.
			* @param anchor : toggle pos and size.
			* @param svgFile : svg filename.
			* @param font : copy of font.
			* @param offsetX : offset of the element.
			* @param colour : colour of item./
			* @param colour : hover colour of item.
			*
			* This method creates a new Svg Toggle Item.
		*/
		//-----------------------------------------------------
		ILSvgToggle(string name,ofRectangle anchor, string svgFile,ofTrueTypeFont *font, int offsetX = 0,ofColor colour = GUI_COLOR ,ofColor hoverColour = GUI_HOVERING_COLOR)
		{
			ofRegisterMouseEvents(this);
			svg.load(svgFile);

			type = IL_SVG_TOGGLE;

			group = svg.get< ofxSvgGroup >("ic");
			box = anchor;
			this->name = name;
			this->font = font;
			this->colour = colour;
			this->hoverColour = hoverColour;
			this->offsetX = offsetX;

			bClicked = false;
			bPulse = false;
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
			
			if(bPulse)
			{
				
				int r = 231 + 50 * cos(ofGetElapsedTimef()*10);
				ofSetColor(r, 76, 60);
			}
			
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
			if(bEnabled)
			{
				if(box.inside(e.x,e.y))
				{
					if(bClicked) bClicked = false;
					else if(!bClicked) bClicked = true;
					bPulse = false;
					
					if(bClicked)
					{
						if( group )
						{
							for( int i = 0; i < group->getElements().size(); i++ )
							{
								shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
								te->path.setFillColor( GUI_HOVERING_COLOR );
							}
						}
						string tmp = name + ":1";
						ofNotifyEvent(buttonPushed, tmp, this);
					}
					else
					{
						if( group )
						{
							for( int i = 0; i < group->getElements().size(); i++ )
							{
								shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
								te->path.setFillColor( ofColor::black );
							}
						}
						string tmp = name + ":0";
						ofNotifyEvent(buttonPushed, tmp, this);
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
		/** \brief Set the Toggle to Pulse
			*
			* This method Makes the toggle pulse
		*/
		//-----------------------------------------------------
		void setPulsing()
		{
			bPulse = true;
			if( group )
			{
				for( int i = 0; i < group->getElements().size(); i++ )
				{
					shared_ptr< ofxSvgElement > te = dynamic_pointer_cast< ofxSvgElement >( group->getElements()[i] );
					te->path.setFillColor( 255 );
				}
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
		bool bPulse;
};

#endif /* ILSvgToggle_h */
