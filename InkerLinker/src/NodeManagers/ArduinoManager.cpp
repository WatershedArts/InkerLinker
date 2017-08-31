//--------------------------------------------------------------
//  ArduinoManager.cpp
//  InkerLinker.
//  Created by David Haylock on 30/08/2017.
//! InkerLinker.
/** This is the Manager for Arduino Nodes. */
//--------------------------------------------------------------

#include "ArduinoManager.h"

//--------------------------------------------------------------
ArduinoManager::ArduinoManager()
{
    findArduino();
}

//--------------------------------------------------------------
ArduinoManager::~ArduinoManager() 
{
    
}

//--------------------------------------------------------------
void ArduinoManager::close()
{
    ard.disconnect();
}

//--------------------------------------------------------------
void ArduinoManager::findArduino()
{
    Cougar::InterfacesOSX *interfaces;
    interfaces = new Cougar::InterfacesOSX();
    
    for (int i = 0; i < interfaces->GetDevices().size(); i++)
    {
        
        cout << interfaces->GetDevices()[i].parent.productId << " " << interfaces->GetDevices()[i].parent.vendorId << endl;
        
        if(interfaces->GetDevices()[i].parent.productId == ARDUINO_MEGA_PID && interfaces->GetDevices()[i].parent.vendorId == ARDUINO_MEGA_VID && interfaces->GetDevices()[i].parent.type != Cougar::DeviceType::BLUETOOTH_DEVICE)
        {
            string _arduinoName = "/dev/tty."+ interfaces->GetDevices()[i].name;
            
            ard.connect(_arduinoName,57600);
            ofAddListener(ard.EInitialized, this, &ArduinoManager::setupArduino);
            break;
        }
    }
    
    bSetupArduino	= false;
}

//--------------------------------------------------------------
void ArduinoManager::updateArduino()
{
    ard.update();
}

//--------------------------------------------------------------
void ArduinoManager::setDigital(int pin,bool val)
{
    ard.sendDigital(pin,val);
}

//--------------------------------------------------------------
void ArduinoManager::setPWM(int pin,int val)
{
    ard.sendPwm(pin,val);
}

//--------------------------------------------------------------
void ArduinoManager::setServo(int pin,int val)
{
    ard.sendServo(pin, val,true);
}

//--------------------------------------------------------------
void ArduinoManager::setPinMode(int pin,string mode)
{
    if(mode == "Digital")
    {
        ard.sendDigitalPinMode(pin, ARD_OUTPUT);
    }
    else if(mode == "PWM")
    {
        ard.sendDigitalPinMode(pin, ARD_PWM);
    }
    else if(mode == "Servo")
    {
        ard.sendServoAttach(pin);
    }
    
}

//--------------------------------------------------------------
bool ArduinoManager::isConnected()
{
    return ard.isInitialized();
}

//--------------------------------------------------------------
void ArduinoManager::setupArduino(const int & version)
{
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ArduinoManager::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ArduinoManager::digitalPinChanged);
    ofAddListener(ard.EAnalogPinChanged, this, &ArduinoManager::analogPinChanged);
}

//--------------------------------------------------------------
void ArduinoManager::digitalPinChanged(const int & pinNum)
{
    cout << "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum)) << endl;
}

//--------------------------------------------------------------
void ArduinoManager::analogPinChanged(const int & pinNum)
{
    cout << "analog pin: " + ofToString(pinNum) + " = " + ofToString(ard.getAnalog(pinNum)) << endl;
}