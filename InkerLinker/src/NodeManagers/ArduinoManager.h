//--------------------------------------------------------------
//  ArduinoManager.h
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Arduino Nodes. */
//--------------------------------------------------------------

#ifndef ArduinoManager_h
#define ArduinoManager_h

#include <stdio.h>
#include "ofMain.h"
#include "InterfacesOSX.h"
#include "ILConstants.h"

class ArduinoManager
{
	public:
		//-----------------------------------------------------
		/** \brief Constructor */
		//-----------------------------------------------------
		ArduinoManager();
	
		//-----------------------------------------------------
		/** \brief Deconstructor */
		//-----------------------------------------------------
		~ArduinoManager();

		//-----------------------------------------------------
		/** \brief Close */
		//-----------------------------------------------------
		void close();
	
		//-----------------------------------------------------
		/** \brief Find Arduino 
			*
			* This method finds an arduino connection using
			* the brilliant Cougar Interface code.
			* All we need to do is pass in the PID and VID of
			* the arduinos.
		*/
		//-----------------------------------------------------
		void findArduino();

		//-----------------------------------------------------
		/** \brief Update the Arduino */
		//-----------------------------------------------------
		void updateArduino();

		//-----------------------------------------------------
		/** \brief Set the Digital
			* @param pin : which pin.
			* @param val : Digital val.
			* 
			* This method sets Digital val.
		*/
		//-----------------------------------------------------
		void setDigital(int pin,bool val);

		//-----------------------------------------------------
		/** \brief Set the PWM
			* @param pin : which pin.
			* @param val : pwm val.
			* 
			* This method sets pwm val.
		*/
		//-----------------------------------------------------
		void setPWM(int pin,int val);

		//-----------------------------------------------------
		/** \brief Set the Servo
			* @param pin : which pin.
			* @param val : servo val.
			* 
			* This method sets servo val.
		*/
		//-----------------------------------------------------
		void setServo(int pin,int val);

		//-----------------------------------------------------
		/** \brief Set the Pin Mode 
			* @param pin : which pin.
			* @param mode : which mode.
			* 
			* This method sets the pin mode.
		*/
		//-----------------------------------------------------
		void setPinMode(int pin,string mode);

		//-----------------------------------------------------
		/** \brief Close 
			* @return arduino is connected.
			* 
			* This method returns the connection status of the
			* arduino.
		*/
		//-----------------------------------------------------
		bool isConnected();

	private:
		ofArduino ard;
		bool bSetupArduino;

		//-----------------------------------------------------
		/** \brief Setup Arduino 
			* @param version : firmata version.
			* 
			* This method sets up the arduino and attaches
			* listeners.
		*/
		//-----------------------------------------------------
		void setupArduino(const int & version);

		//-----------------------------------------------------
		/** \brief Report if the Digital Pin Changes
			* @param pinNum : which pin.
			* 
			* This method listens for changes on all pins.
		*/
		//-----------------------------------------------------
		void digitalPinChanged(const int & pinNum);

		//-----------------------------------------------------
		/** \brief Report if the Analog Pin Changes
			* @param pinNum : which pin.
			* 
			* This method listens for changes on all pins.
		*/
		//-----------------------------------------------------
		void analogPinChanged(const int & pinNum);
};

#endif /* ArduinoManager_h */
