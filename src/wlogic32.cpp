#include "wlogic32.h"
#include <Stream.h>
#include <Wire.h>

#if defined(ARDUINO) && ARDUINO >=100
#include <Arduino.h>
#else
#include <WProgram.h>
#include <avr/pgmspace.h>
#define F(str) (str)
#endif

#ifdef ARDUINO_ARCH_AVR
#include <SoftwareSerial.h>
#endif

#ifdef ARDUINO_ARCH_PIC32
#include <SoftwareSerial.h>
#endif

/*!
  @brief   Start the Rseries logic engine API
*/

WLogicEngine::WLogicEngine(HardwareSerial *conn,int baud)
    : _serial(conn), _serialBaud(baud)
{
    connectionType=0x01;
}

WLogicEngine::WLogicEngine(SoftwareSerial *conn,int baud)
    : _softserial(conn), _serialBaud(baud)
{
    connectionType=0x02;
}

WLogicEngine::WLogicEngine(int rx, int tx,int baud)
    : _serialBaud(9600)
{
    #if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_PIC32)
    connectionType=0x02;
    _softserial = new SoftwareSerial(rx,tx);
    #endif
}

/*!
  @brief    Begin the Rseries logic engine API
*/
void WLogicEngine::begin(void)
{
    begin(125); // Default 125ms Refresh
}

/*!
  @brief    Begin the Rseries logic engine API
*/
void WLogicEngine::begin(const uint16_t refspeed)
{
    refreshSpeed = refspeed;
    switch (connectionType)
    {
        case 0x01:
#ifdef ARDUINO_ARCH_AVR
            _serial->begin(_serialBaud);
#elif defined ARDUINO_ARCH_SAM
            ((USARTClass *)_serial)->begin(_serialBaud);
#elif defined ARDUINO_ARCH_SAMD  // Arduino Zero, Zero Pro, M0 and M0 Pro
            ((HardwareSerial *)_serial)->begin(_serialBaud);
#elif defined ARDUINO_ARCH_PIC32
            _serial->begin(_serialBaud);
#else
            _serial->begin(_serialBaud);
#endif
            while (!_serial);
            _serial->println("Begin _serial");
            break;
        case 0x02:
#ifdef ARDUINO_ARCH_AVR
            ((SoftwareSerial *)_softserial)->begin(_serialBaud);
#elif defined ARDUINO_ARCH_PIC32
            ((SoftwareSerial *)_softserial)->begin(_serialBaud);
#endif
            while (!_softserial);
            _softserial->println("Begin _softserial");
            break;
        default:
            Serial.print("WLogicEngine: No Connection Setup Specified");
            break;
    }
}

void WLogicEngine::sendCommand(String command)
{
    String cmd = command + "\r";
    // String cmd = "~RTLE57000\r";
    transmit(cmd,false);
    Serial.println("WLogicEngine SendCommand: " + cmd);
}

void WLogicEngine::transmit(String command)
{
    String cmd = command + "\r";
    transmit(cmd,false);
    Serial.println("WLogicEngine Transmit: " + cmd);
}

void WLogicEngine::transmit(String command, bool retry)
{
    if (command == "")
    {
        return;
    }

    switch (connectionType)
    {
        case 0x01:
            _serial->write((command + "\r").c_str());
            break;
        case 0x02:
            _softserial->write((command + "\r").c_str());
            break;
        default: break;
    }
}

void WLogicEngine::receive(void)
{
    switch (connectionType)
    {
        case 0x01:
            if (_serial->available())
            {
                char ch = _serial->read();
                receiveData(ch);
            }
            break;
        case 0x02:
            if (_softserial->available())
            {
                char ch = _softserial->read();
                receiveData(ch);
            }
            break;
        default: break;
    }
}


//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------
//----------------------------------------------------

void WLogicEngine::Leia(void)
{
    String msg = "~RTLE30000";
    sendCommand(msg);
}

void WLogicEngine::Leia(int l)
{
    // Set specific lights for Leia
    if ( l < 0 || l > 2 ) return;
    String msg = "~RTLE" + String(l) + "30000";
    sendCommand(msg);
}

void WLogicEngine::Normal(void)
{
    // Set all lights to normal
    String msg = "~RTLE0";
    sendCommand(msg);
}

void WLogicEngine::Normal(int l)
{
    // Set specific lights to normal
    if ( l < 0 || l > 2 ) return;
    if ( l == 0 ) {
        l = "";
    }
    String msg = "~RTLE" + String(l) + "00000";
    sendCommand(msg);
}

void WLogicEngine::Alarm(void)
{
    // Set all lights to normal
    String msg = "0T3";
    sendCommand(msg);
}

void WLogicEngine::Alarm(int l)
{
    // Set specific lights to normal
    if ( l < 0 || l > 2 ) return;
    String msg = String(l) + "T3";
    sendCommand(msg);
}

void WLogicEngine::Failure(void)
{
    // Set all lights to normal
    String msg = "0T4";
    sendCommand(msg);
}

void WLogicEngine::Failure(int l)
{
    // Set specific lights to normal
    if ( l < 0 || l > 2 ) return;
    String msg = String(l) + "T4";
    sendCommand(msg);
}

void WLogicEngine::RedAlert(void)
{
    // Set all lights to normal
    String msg = "0T5";
    sendCommand(msg);
}

void WLogicEngine::RedAlert(int l)
{
    // Set specific lights to normal
    if ( l < 0 || l > 2 ) return;
    String msg = String(l) + "T5";
    sendCommand(msg);
}

void WLogicEngine::March(void)
{
    // Set all lights to normal
    String msg = "0T11";
    sendCommand(msg);
}

void WLogicEngine::March(int l)
{
    // Set specific lights to normal
    if ( l < 0 || l > 2 ) return;
    String msg = String(l) + "T11";
    sendCommand(msg);
}

void WLogicEngine::SetLightColor(int c)
{
    // Set lights color
    if ( c < 0 || c > 9 ) return;
    String msg = "~RTLE5" + String(c) + "500";
    sendCommand(msg);
}

void WLogicEngine::SetLightColor(int l, int c, int t)
{
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( c < 0 || c > 9 ) return;
    if ( t < 0 || t > 99 ) return;
    
    String time;
    String lights;
    if ( t < 10) {
        time = "0" + String(t);
    } else {
        time = String(t);
    }
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + String(l) + "05" + String(c) + "5" + time;
    sendCommand(msg);
}

void WLogicEngine::FlashLightColor(int c)
{
    // Set lights color
    if ( c < 0 || c > 9 ) return;
    String msg = "~RTLE6" + String(c) + "500";
    sendCommand(msg);
}

void WLogicEngine::FlashLightColor(int l, int c, int t)
{
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( c < 0 || c > 9 ) return;
    if ( t < 0 || t > 99 ) return;
    
    String time;
    String lights;
    if ( t < 10) {
        time = "0" + String(t);
    } else {
        time = String(t);
    }
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + String(l) + "06" + String(c) + "5" + time;
    sendCommand(msg);
}

void WLogicEngine::Rainbow(void)
{
    String msg = "~RTLE100500";
    sendCommand(msg);
}

void WLogicEngine::Rainbow(int l, int t)
{
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( t < 0 || t > 99 ) return;
    
    String time;
    String lights;
    if ( t < 10) {
        time = "0" + String(t);
    } else {
        time = String(t);
    }
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + lights + "1005" + time;
    sendCommand(msg);
}

void WLogicEngine::Rainbow(int l)
{
    String lights;
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + lights + "100500";
    sendCommand(msg);
}

void WLogicEngine::Random(void)
{
    String msg = "~RTLE990500";
    sendCommand(msg);
}

void WLogicEngine::Random(int l, int t)
{
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( t < 0 || t > 99 ) return;
    
    String time;
    String lights;
    if ( t < 10) {
        time = "0" + String(t);
    } else {
        time = String(t);
    }
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + lights + "9905" + time;
    sendCommand(msg);
}

void WLogicEngine::Random(int l)
{
    String lights;
    // Set specificlights color
    if ( l < 0 || l > 2 ) return;
    if ( l == 0 ) {
        lights = "";
    } else {
        lights = String(l);
    }
    String msg = "~RTLE" + lights + "990500";
    sendCommand(msg);
}