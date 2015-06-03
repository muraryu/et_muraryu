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
    static void sendMessage(char* message, U32 size);
    static int connect();

};

#endif  // NXT_UTIL_BLUETOOTH_H_
