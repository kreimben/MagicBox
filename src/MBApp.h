//
// Created by ubuntu on 7/27/21.
//

#ifndef MAGICBOXWM_MBAPP_H
#define MAGICBOXWM_MBAPP_H

#include <iostream>
#include <memory>

class MBApp {

private:
    MBApp();
    static MBApp *_instance;

public:
    static MBApp *getInstance();
};


#endif //MAGICBOXWM_MBAPP_H
