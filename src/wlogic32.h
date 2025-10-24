#pragma once

#ifndef WLOGICAPI_F
#define WLOGICAPI_F

#ifdef ARDUINO
#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif
#endif

#include <String.h>
#include <SoftwareSerial.h>
#include <Wire.h>

#define WLOGIC_BUFFER_SIZE 32

#ifndef WLOGIC_BAUD_RATE
#define WLOGIC_BAUD_RATE 9600
#endif

#define CONN_SERIAL0 0x00 //"Serial"
#define CONN_SERIAL1 0x01 //"Serial1"
#define CONN_SERIAL2 0x02 //"Serial2"
#define CONN_SERIAL3 0x03 //"Serial3"
#define CONN_SERIAL4 0x04 //"Serial4"


/*!
    @brief  Class that stores state and functions for WLogicEngine
*/
class WLogicEngine
{
public:

    /**
     * @brief Configure the WLogicEngine for Hardware Serial with a baud rate
     * 
     * @param conn the serial connection
     * @param baud the baud rate
     */
    WLogicEngine(HardwareSerial *conn,int baud);

    /**
     * @brief Configure the WLogicEngine for Software Serial with a baud rate
     * 
     * @param conn the serial connection
     * @param baud the baud rate
     */
    WLogicEngine(SoftwareSerial *conn,int baud);

    /**
     * @brief Configure the WLogicEngine for Serial with specific rx and tx pins
     * 
     * @param rx the rx pin number
     * @param tx the tx pin number
     * @param baud the baud rate
     */
    WLogicEngine(int rx, int tx, int baud);

    /**
    * @brief Initializes the WLogicEngine
    * 
    */
    void begin(void);

    /**
     * @brief Initializes the WLogicEngine with a refresh speed
     * 
     * @param refspeed
     */
    void begin(const uint16_t refspeed);

    /**
    * @brief Triggers the Leia sequence on all lights
    * 
    */
    void Leia(void);

    /**
    * @brief Triggers the Leia sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void Leia(int l);

    /**
    * @brief Triggers the normal sequence on all lights
    * 
    */
    void Normal(void);

    /**
    * @brief Triggers the normal sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void Normal(int l);

    /**
    * @brief Triggers the alarm sequence on all lights
    * 
    */
    void Alarm(void);

    /**
    * @brief Triggers the alarm sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void Alarm(int l);

    /**
    * @brief Triggers the failure sequence on all lights
    * 
    */
    void Failure(void);

    /**
    * @brief Triggers the failure sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void Failure(int l);

    /**
    * @brief Triggers the red alert sequence on all lights
    * 
    */
    void RedAlert(void);

    /**
    * @brief Triggers the red alert sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void RedAlert(int l);

    /**
    * @brief Triggers the imperial march sequence on all lights
    * 
    */
    void March(void);

    /**
    * @brief Triggers the imperial march sequence on specific lights
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    */
    void March(int l);

    /**
    * @brief Set the Logic lights color
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    * 
    * C - Color Value from the list below:
    * 1 - Red
    * 2 - Orange
    * 3 - Yellow
    * 4 - Green
    * 5 - Cyan (Aqua)
    * 6 - Blue
    * 7 - Purple
    * 8 - Magenta
    * 9 - Pink
    * 0 - Default color on alarm / default to red on many effects / color cycle on march / ignored on failure and rainbow
    * @param c the color (0-9)
    * @param t the duration in seconds (integer)
    */
    void SetLightColor(int l,int c, int t);
    void SetLightColor(int c);

    /**
    * @brief Set the Logic lights to flash color
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    * 
    * C - Color Value from the list below:
    * 1 - Red
    * 2 - Orange
    * 3 - Yellow
    * 4 - Green
    * 5 - Cyan (Aqua)
    * 6 - Blue
    * 7 - Purple
    * 8 - Magenta
    * 9 - Pink
    * 0 - Default color on alarm / default to red on many effects / color cycle on march / ignored on failure and rainbow
    * @param c the color (0-9)
    * @param t the duration in seconds (integer)
    */
    void FlashLightColor(int l,int c, int t);
    void FlashLightColor(int c);

    /**
    * @brief Set lights to the Rainbow Sequence
    * 
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    * @param t the duration in seconds (integer)
    */
    void Rainbow(int l,int t);
    void Rainbow(int t);
    void Rainbow(void);

    /**
    * @brief Set lights to the Random Sequence
    * 
    * Light Selection:
    * 0 - All Lights
    * 1 - Front Lights
    * 2 - Rear Lights
    * @param l the light number (0-2)
    * @param t the duration in seconds (integer)
    */
    void Random(int l,int t);
    void Random(int t);
    void Random(void);






private:
    HardwareSerial *_serial;
    SoftwareSerial *_softserial;
    int _serialBaud;
    int connectionType;

    void transmit(String command);
    void transmit(String command, bool retry);
    void receive(void);
    void sendCommand(String command);
    void receiveData(char ch);
    void receiveData(String data);
    void processCommands(char* input);
    String getValue(String data, char separator, int index);

protected:
    char cmdBuffer[WLOGIC_BUFFER_SIZE];
    unsigned cmdPos;
    byte connection;
    int refreshSpeed;

};

#endif