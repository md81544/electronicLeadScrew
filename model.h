#pragma once

#include "rotaryencoder.h"
#include "stepperControl/steppermotor.h"

#include <cmath>
#include <limits>
#include <memory>
#include <vector>

// "Model", i.e. program state data

namespace mgo
{

class IGpio;

const int INF_RIGHT = std::numeric_limits<int>::min();
const int INF_LEFT  = std::numeric_limits<int>::max();

// TODO these need to be in a config file
constexpr float MAX_MOTOR_SPEED = 700.f;
constexpr float INFEED = 0.05f; // mm
// The large number below is tan 29.5°
// (Cannot use std::tan in constexpr owing to side effects)
constexpr float SIDEFEED = INFEED * 0.5657727781877700776025887010584;

struct Model
{
    Model( IGpio& gpio ) : m_gpio(gpio) {}
    IGpio& m_gpio;
    // Lead screw:
    std::unique_ptr<mgo::StepperMotor> m_zAxisMotor;
    // Cross slide:
    std::unique_ptr<mgo::StepperMotor> m_xAxisMotor;
    std::unique_ptr<mgo::RotaryEncoder> m_rotaryEncoder;
    std::vector<long> m_memory{ INF_RIGHT, INF_RIGHT, INF_RIGHT, INF_RIGHT };
    std::size_t m_currentMemory{ 0 };
    std::size_t m_threadPitchIndex{ 0 };
    std::string m_status{ "stopped" };
    bool        m_zMoving{ false };
    bool        m_quit{ false };
    long        m_targetStep{ 0 };
    float       m_zSpeed{ 100.f };
    float       m_xSpeed{ 60.f };
    float       m_oldZSpeed{ 100.f };
    bool        m_fastReturning{ false };
    int         m_keyPressed{ 0 };
    bool        m_threadCuttingOn{ false };
    int         m_threadCutAdvanceCount{ 0 };
    bool        m_useSfml{ false };
};

} // end namespace