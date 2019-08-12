#pragma once

// Abstract base "interface" class
// to allow mocking out the hardware
// interface to allow the StepperMotor
// class to be used for tests

#include <functional>

namespace mgo
{

enum class PinState
{
    high,
    low
};

// concrete classes can initialise / terminate
// the GPIO library in their ctors / dtors

class IGpio
{
public:
    // Support for stepper motor:
    virtual void setStepPin( PinState ) = 0;
    virtual void setReversePin( PinState ) = 0;
    // Support for rotary encoder:
    virtual void setRotaryEncoderCallback(
        int pinA,
        int pinB,
        std::function<void(
            int      pin,
            int      level,
            uint32_t tick,
            void*    userData
            )> callback,
        void* userData
        ) = 0;
    // General:
    virtual void delayMicroSeconds( long ) = 0;
};

} // end namespace
