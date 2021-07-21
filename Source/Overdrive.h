/*
  ==============================================================================

    "Overdrive.h"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 21th July 2021
    Author:  Cameron Smith, UoE s1338237

    This class manages the overdrive effect on the output of the bass drum.
    Based on the asymmetric diode clipper

  ==============================================================================
*/

#pragma once

class Overdrive
{
public:
    void setSampleRate(float SR);

    float process(float input);


private:
    float resistance = 1000.0f;

    float capacitance = 3.3e-8;

    float satCurrent = 2.52e-9;

    float diodeThermalVoltage = 0.02583f;

    float diodeIdealityFac = 1.752f;

    float tolerance = 1.0e-9;

    int maxIterations = 100;

    // STATE SPACE PARAMETERS
    float A;
    float B;
    float C;
    float D = 1.0f;
    float E = 0.0f;
    float F = 0.0f;
    float L = 1.0f;
    float M = 0.0f;
    float N = 0.0f;

    // DERIVED STATE SPACE PARAMETERS
    float Ha;
    float Hb;
    float K;

    float G;

    float xPrev = 0.0f;
    float iPrev = 0.0f;
    float uPrev = 0.0f;

    float v;
    bool firstSamp = true;
};