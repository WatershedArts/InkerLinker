//--------------------------------------------------------------
//  ILGUIObject.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the GUI Base Object. */
//--------------------------------------------------------------

#ifndef ILGUIObject_h
#define ILGUIObject_h

#include "ofMain.h"
#include "ILConstants.h"
#include "ofxCenteredTrueTypeFont.h"

class ILGUIObject
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ILGUIObject() { }
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ILGUIObject() { }
		
		//-----------------------------------------------------
		/** \brief Draw */
		//-----------------------------------------------------
		virtual void draw() { }
	
		//-----------------------------------------------------
		/** \brief Recalculate Position Relative to the GUI
			* @param newX : the new X coord.
			*
			* This method shifts the elements X coord.
		*/
		//-----------------------------------------------------
		virtual void setX(int newX)
		{
			box.x = newX;
		}
		
		//-----------------------------------------------------
		/** \brief Get the Offset X
			* @return offsetX : offsetX.
			*
			* This method returns element offset.
		*/
		//-----------------------------------------------------
		virtual int getOffsetX()
		{
			return offsetX;
		}
		
		//-----------------------------------------------------
		/** \brief Get Element X
			* @return x : the x coord of the element.
			*
			* This method returns element X coord.
		*/
		//-----------------------------------------------------
		virtual int getX()
		{
			return box.getX();
		}
		
		//-----------------------------------------------------
		/** \brief Get Element Y
			* @return y : the y coord of the element.
			*
			* This method returns element Y coord.
		*/
		//-----------------------------------------------------
		virtual int getY()
		{
			return box.getY();
		}
		
		//-----------------------------------------------------
		/** \brief Get Element Width
			* @return width : the width of the element.
			*
			* This method returns element width.
		*/
		//-----------------------------------------------------
		virtual int getWidth()
		{
			return box.getWidth();
		}
	
		//-----------------------------------------------------
		/** \brief Get Element Height
			* @return height : the height of the element.
			*
			* This method returns element height.
		*/
		//-----------------------------------------------------
		virtual int getHeight()
		{
			return box.getHeight();
		}
		
		//-----------------------------------------------------
		/** \brief Enable the Element
			* @param enabled : bool.
			*
			* This method enables / disables the element.
		*/
		//-----------------------------------------------------
		virtual void setEnabled(bool enabled)
		{
			bEnabled = enabled;
		}
		
		//-----------------------------------------------------
		/** \brief Get Element Name
			* @return name : the name of the Element.
			*
			* This method returns element name.
		*/
		//-----------------------------------------------------
		string getName()
		{
			return name;
		}
		
		//-----------------------------------------------------
		/** \brief Get Element Type
			* @return type : the element type
			*
			* This method returns the element type.
		*/
		//-----------------------------------------------------
		IL_GUI_OBJECT_TYPE getType()
		{
			return type;
		}
	
		string name;
		ofRectangle box;
	
		bool bClicked;
		bool bEnabled;
		bool bCenterAligned;
		bool bHovering;
	
		int offsetX = 0;
		int offsetY;
		IL_GUI_OBJECT_TYPE type;
};


#endif /* ILGUIObject_h */
