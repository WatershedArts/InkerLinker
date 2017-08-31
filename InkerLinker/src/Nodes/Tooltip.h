//--------------------------------------------------------------
//  Tooltip.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is a Tooltip Object. */
//--------------------------------------------------------------


#ifndef Tooltip_h
#define Tooltip_h

enum TOOL_TIP_ALIGN {
	LEFT_ALIGN = 0,
	RIGHT_ALIGN
};

class Tooltip : public ofRectangle
{
	public:
	
		//-----------------------------------------------------
		/// \brief Constructor
		//-----------------------------------------------------
		void draw(string info, int x, int y,TOOL_TIP_ALIGN bSided = RIGHT_ALIGN)
		{
			ofPushStyle();
			ofFill();
			
			if(bSided == LEFT_ALIGN)
			{
				ofSetColor(0, 0, 0);
				ofBeginShape();
				ofVertex(x, y);
				ofVertex(x-10, y-10);
				ofVertex(x-110, y-10);
				
				ofVertex(x-110, y+10);
				ofVertex(x-10, y+10);
				ofEndShape(true);
				
				ofSetColor(255);
				ofDrawBitmapString(info,x-100,y+3);
				
			}
			else {
				ofSetColor(0, 0, 0);
				ofBeginShape();
				ofVertex(x, y);
				ofVertex(x+10, y-10);
				ofVertex(x+110, y-10);
				
				ofVertex(x+110, y+10);
				ofVertex(x+10, y+10);
				ofEndShape(true);
				ofSetColor(255);
				ofDrawBitmapString(info,x+15,y+3);
			}
			ofPopStyle();
		}
	
	private:
};
#endif /* Tooltip_h */
