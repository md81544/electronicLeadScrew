#pragma once

#include "igpio.h"

#include <atomic>
#include <memory>
#include <thread>
#include <mutex>

namespace mgo
{

enum class Direction
{
    forward,
    reverse
};

class StepperMotor
{
public:
    StepperMotor( IGpio& gpio, long stepsPerRevolution );
    ~StepperMotor();
    bool isRunning();
    Direction getDirection();
    long getCurrentStep();
    // Go to a specific step
    void goToStep( long step );
    // Set motor speed
    void setSpeedPercent( int percent );
    // Stop any motion
    void stop();
    // Block until the current operation completes
    void wait();
private:
    IGpio& m_gpio;
    long m_stepsPerRevolution;
    std::thread m_thread;
    std::atomic<bool>      m_terminateThread{ false };
    std::atomic<long>      m_targetStep;
    std::atomic<bool>      m_busy{ false };
    std::atomic<long>      m_currentStep{ 0 };
    std::atomic<bool>      m_stop{ false };
    std::atomic<Direction> m_direction{ Direction::forward };
    // lock should be taken before any code outside the
    // background thread changes any member variables
    std::mutex  m_mtx;
};

} // end namespace

