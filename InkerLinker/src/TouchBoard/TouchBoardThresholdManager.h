//--------------------------------------------------------------
//  TouchBoardThresholdManager.h
//  InkerLinker
//  Created by David Haylock on 18/08/2017.
//! InkerLinker.
/** This is the Touch Board Manager. */
//--------------------------------------------------------------

#ifndef TouchBoardThresholdManager_h
#define TouchBoardThresholdManager_h

#include "ofMain.h"
#include "ILConstants.h"
#include "ofxJSON.h"

class TouchBoardThresholdManager
{
	public:
	
		//-----------------------------------------------------
		/** \brief Load the Thresholds File
			* @return et : thresholds
			*
			* This method Loads the thresholds from file.
		*/
		//-----------------------------------------------------
		ElectrodeThresholds loadThresholds()
		{
			ElectrodeThresholds et;
			
			ofxJSONElement loadFile;
			if(!loadFile.open(ofToDataPath("thresholds.json")))
			{
				string s = "Loading Failed. Couldn't find " +ofToDataPath("thresholds.json");
				DebugMessage("Threshold Loader" , s.c_str());
				for (int i = 0; i < 12; i++)
				{
					et.touchThresholds.push_back(0.15);
					et.releaseThresholds.push_back(0.07);
				}
				return et;
			}
			else
			{
				int electrodes = loadFile["electrodes"].size();
				
				for (int i = 0; i < electrodes; i++)
				{
					et.touchThresholds.push_back(loadFile["electrodes"][i]["touch"].asFloat());
					et.releaseThresholds.push_back(loadFile["electrodes"][i]["release"].asFloat());
				}
				return et;
			}
		}
		//-----------------------------------------------------
		/** \brief Save the Thresholds File
			* @param et : thresholds
			*
			* This method Saves the thresholds to file.
		*/
		//-----------------------------------------------------
		void saveThresholds(ElectrodeThresholds et)
		{
			ofxJSONElement file;
			for (int i = 0; i < et.touchThresholds.size(); i++)
			{
				file["electrodes"][i]["touch"] = et.touchThresholds[i];
			}
			
			for (int i = 0; i < et.releaseThresholds.size(); i++)
			{
				file["electrodes"][i]["release"] = et.releaseThresholds[i];
			}
			
			file.save(ofToDataPath("thresholds.json"), true);
		}
};


#endif /* TouchBoardThresholdManager_h */
