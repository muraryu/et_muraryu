/******************************************************************************
 *  Bluetooth.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/05/29
 *  Definition of the Class Balancer
 *  Author: muraryu
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef NXT_UTIL_BLUETOOTH_H_
#define NXT_UTIL_BLUETOOTH_H_

class Bluetooth {
public:
	Bluetooth();
    virtual ~Bluetooth();

    static void sendMessage(char* message);
    static U32 receiveMessage(char* message, U32 len);
    static bool connect();

};

#endif  // NXT_UTIL_BLUETOOTH_H_
