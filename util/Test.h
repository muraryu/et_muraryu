/******************************************************************************
 *  Test.h (for LEGO Mindstorms NXT)
 *  Created on: 2015/06/09
 *  Definition of the Class Test
 *  テスト用クラスヘッダ
 *  Author: muraryu
 *****************************************************************************/

#ifndef NXT_UTIL_TEST_H_
#define NXT_UTIL_TEST_H_

class Test {
public:
	Test();
    virtual ~Test();

    // muraryu
    void exTestWrite(bool b1, bool b2);
    bool exTestCheck();
    bool exTestGetB1();

private:

    // muraryu
    bool b1;
    bool b2;

};

#endif /* NXT_UTIL_TEST_H_ */
