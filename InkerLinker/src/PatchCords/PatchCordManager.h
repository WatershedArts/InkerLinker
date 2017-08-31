//--------------------------------------------------------------
//  PatchCordManager.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the PatchCordManager Class. */
//--------------------------------------------------------------

#ifndef PatchCordManager_h
#define PatchCordManager_h

#include "Port.h"

class PatchCordManager
{
	public:
		//-----------------------------------------------------
		/** \brief Default Constructor */
		//-----------------------------------------------------
		PatchCordManager()
		{
			ofAddListener(ofEvents().mousePressed, this, &PatchCordManager::mousePressed);
			ofAddListener(ofEvents().mouseMoved, this, &PatchCordManager::mouseMoved);
			actionableCord = -1;
		}
		
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~PatchCordManager() {}
	
		//-----------------------------------------------------
		/** \brief Add New Patch Cord
			* @param c : patch cord.
			*
			* This method adds a new patch cord to the vector.
		*/
		//-----------------------------------------------------
		void addNewPatchCord(PatchCord c)
		{
			cords.push_back(c);
		}
		
		//-----------------------------------------------------
		/** \brief Add New Patch Cords
			* @param c : patch cords.
			*
			* This method adds a vector of patch
		*/
		//-----------------------------------------------------
		void addNewPatchCord(vector <PatchCord> c)
		{
			cords.clear();
			cords = c;
		}
		
		//-----------------------------------------------------
		/** \brief Update the Patch Cords
			* @param ports : ports.
			*
			* This method updates the patch cords ie position
			* attach points and bends.
		*/
		//-----------------------------------------------------
		void updatePatchCords(vector <Port> ports)
		{			
			for(int i = 0; i < cords.size(); i++)
			{
				for(int e = 0; e < ports.size(); e++)
				{
					if( cords[i].nodeId == ports[e].getNodeId() )
					{
						if( cords[i].portId == ports[e].getPortId() )
						{
							cords[i].endingPoint = ports[e].getBox().getCenter();
							
							ofPoint half = cords[i].startingPoint.getMiddle(cords[i].endingPoint);
														
							cords[i].deleteCord.setFromCenter(half.x,half.y,15,15);
							
							cords[i].firstCurvePoint.x = cords[i].startingPoint.x + 75;
							cords[i].firstCurvePoint.y = cords[i].startingPoint.y;
							cords[i].secondCurvePoint.x = cords[i].endingPoint.x - 50;
							cords[i].secondCurvePoint.y = cords[i].endingPoint.y;
						}
					}
				}
			}
		}
		
		//-----------------------------------------------------
		/** \brief Get the patch cords
			* @return cords : patch cords.
			*
			* This method returns the stored patch cords for
			* saving.
		*/
		//-----------------------------------------------------
		vector <PatchCord> getAllPatchCoords()
		{
			return cords;
		}
	
		//-----------------------------------------------------
		/** \brief Clear cords */
		//-----------------------------------------------------
		void reset()
		{
			cords.clear();
		}
	
		//-----------------------------------------------------
		/** \brief Find Patch Cord
			* @param id : id of cord.
			*
			* This method finds the patch cords index from
			* the vector.
		*/
		//-----------------------------------------------------
		void findPatchCordByElectrodeId(string id)
		{
			auto it = find_if(cords.begin(),cords.end(), [&id](const PatchCord &obj) { return obj.electrodeId == id; });
			if (it != cords.end())
			{
				auto index = std::distance(cords.begin(), it);
				
				cout << "Index of Wire " << index << endl;
				actionableCord = index;
			}
		}
	
		//-----------------------------------------------------
		/** \brief Remove Patch Cord By Id
			* @param id : id of cord.
			*
			* This method removes the patch cord by its index.
		*/
		//-----------------------------------------------------
		void removePatchCord(int id)
		{
			auto it = find_if(cords.begin(),cords.end(), [&id](const PatchCord &obj) { return obj.patchId == id; });
			if (it != cords.end())
			{
				auto index = std::distance(cords.begin(), it);
				string mess = "[Patch Coord] - Removed Patch Cord";
				cout << "Index of Wire " << index << endl;
				cords.erase(cords.begin() + index);
			}
		}
		
		//-----------------------------------------------------
		/** \brief Remove Patch Cord By Node Id
			* @param id : id of node.
			*
			* This method removes the patch cord by node id.
		*/
		//-----------------------------------------------------
		void removePatchCordByNodeId(int id)
		{
			auto it = find_if(cords.begin(),cords.end(), [&id](const PatchCord &obj) { return obj.nodeId == id; });
			while(it != cords.end())
			{
				auto index = std::distance(cords.begin(), it);
				cords.erase(cords.begin() + index);
			}
		}
		
		//-----------------------------------------------------
		/** \brief Draw */
		//-----------------------------------------------------
		void draw()
		{
			ofEnableAntiAliasing();
			ofPushStyle();
			ofSetLineWidth(2);
			ofNoFill();
			for (int i = 0; i < cords.size(); i++)
			{
				if(!cords[i].bHovering) ofSetColor(255);
				else ofSetColor(255,0,0);
				
				
				if(cords[i].type == TB_POINT_TYPE::TB_TOUCH_POINT) ofSetColor(102,153,153);
				else if(cords[i].type == TB_POINT_TYPE::TB_RELEASE_POINT) ofSetColor(255,51,51);
				
				ofDrawBezier(cords[i].startingPoint.x,cords[i].startingPoint.y,cords[i].firstCurvePoint.x,cords[i].firstCurvePoint.y,cords[i].secondCurvePoint.x,cords[i].secondCurvePoint.y,cords[i].endingPoint.x,cords[i].endingPoint.y);
				ofPushStyle();
				ofFill();
			
				ofPopStyle();
			}
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
			for(int i = 0; i < cords.size(); i++)
			{
				if (cords[i].deleteCord.inside(e.x,e.y))
				{
					ofNotifyEvent(deleteId, cords[i], this);
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
			for(int i = 0; i < cords.size(); i++)
			{
				if (cords[i].deleteCord.inside(e.x,e.y))
				{
					cords[i].bHovering = true;
				}
				else
				{
					cords[i].bHovering = false;
				}
			}
		}
		ofEvent<PatchCord> deleteId;
		vector <PatchCord> cords;
		int actionableCord;
};



#endif /* PatchCordManager_h */
