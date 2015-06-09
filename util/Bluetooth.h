/******************************************************************************
 *  Bluetooth.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/05/29
 *  Definition of the Class Bluetooth
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_BLUETOOTH_H_
#define NXT_UTIL_BLUETOOTH_H_

class Bluetooth {
public:
	Bluetooth();
    virtual ~Bluetooth();

    static void sendMessage(char* message);
    static void sendMessage(char* message, int len);
    static int receiveMessage(char* message, int len);
    static bool connect();

};

#endif  // NXT_UTIL_BLUETOOTH_H_
