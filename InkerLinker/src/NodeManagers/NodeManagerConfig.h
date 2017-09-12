//--------------------------------------------------------------
//  NodeManagerConfig
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the config loader for the node managers. */
//--------------------------------------------------------------

#ifndef NodeManagerConfig_h
#define NodeManagerConfig_h

#include "ofMain.h"
#include "ofxJSON.h"
#include "ILConstants.h"

class NodeManagerConfig
{
	public:
	
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		NodeManagerConfig()
		{
			ofxJSONElement loadFile;
			if(!loadFile.open(ofToDataPath("DocumentRoot/config.json")))
			{
				string s = "Loading Failed. Couldn't find " +ofToDataPath("DocumentRoot/config.json");
				DebugMessage("Config Loader" , s.c_str());
			}
			else
			{
				serialConfig.devicename = loadFile["serialconfig"]["devicename"].asString();
				serialConfig.baudrate = loadFile["serialconfig"]["baud"].asInt();
				
				oscConfig.host = loadFile["oscconfig"]["host"].asString();
				oscConfig.port = loadFile["oscconfig"]["port"].asInt();
				
				qlabConfig.host = loadFile["qlabconfig"]["host"].asString();
				qlabConfig.port = loadFile["qlabconfig"]["port"].asInt();
				
				cloudBitConfig.deviceID = loadFile["cloudbitconfig"]["deviceid"].asString();
				cloudBitConfig.devicetoken = loadFile["cloudbitconfig"]["deviceaccesstoken"].asString();
			}
		}
	
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		~NodeManagerConfig() { }
	
		//-----------------------------------------------------
		/** \brief Get OSC Configuration
			* @return oscConfig : as it sounds
			*
			* This method returns the osc configuration
			* loaded into the json file.
		*/
		//-----------------------------------------------------
		OSCConfig getOSCConfig()
		{
			return oscConfig;
		}
	
		//-----------------------------------------------------
		/** \brief Get QLab Configuration
			* @return qlabConfig : as it sounds
			*
			* This method returns the qlab configuration
			* loaded into the json file.
		*/
		//-----------------------------------------------------
		QLabConfig getQLabConfig()
		{
			return qlabConfig;
		}
	
	
		//-----------------------------------------------------
		/** \brief Get Serial Configuration
			* @return serialConfig : as it sounds
			*
			* This method returns the serial configuration
			* loaded into the json file.
		*/
		//-----------------------------------------------------
		SerialConfig getSerialConfig()
		{
			return serialConfig;
		}
	
		//-----------------------------------------------------
		/** \brief Get Cloud Bit Configuration
			* @return cloudBitConfig : as it sounds
			*
			* This method returns the cloudbit configuration
			* loaded into the json file.
		*/
		//-----------------------------------------------------
		CloudBitConfig getCloudBitConfig()
		{
			return cloudBitConfig;
		}
	
	private:
		QLabConfig qlabConfig;
		OSCConfig oscConfig;
		SerialConfig serialConfig;
		CloudBitConfig cloudBitConfig;
};

#endif /* NodeManagerConfig_h */
