/*
  ==============================================================================

    "PulseShaper.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the pulse shaper block of the VA model. a nonlinear
    low shelf filter that delivers a shaped pulse to the bridged-T network's op-
    amp inverting input

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class PulseShaper
{
public:
    PulseShaper();

    //--------------------------------------------------------------------------
    /**
    Updates sample rate in the class private variables,

    Subsequently updates the discrete transfer function coefficients

    @param sample rate in Hz
    */
    void setSampleRate(float SR);

    //--------------------------------------------------------------------------
    /**
    Get current sample of the pulse shaper process block
    */
    float process(float V_trig);

private:
    /// sampling frequency in Hz
    float sampleRate = 0.0f;

    /// value of capacitor C40 (15 nF)
    float c40 = 1.5e-8;                 
    
    /// value of resistor R162 (4.7 kOhms)
    float r162 = 4.7e3;
    
    /// value of resistor R163 (100 kOhms)
    float r163 = 1.0e5;

    /// coefficients of the discretized transfer function for pulse shaper filter core
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float A1 = 0.0f;

    /// previous sample of input, v_trig(n-1)
    float v_trigPrev1 = 0.0f;

    /// previous sample of output, v_ps(n-1)
    float v_psPrev1 = 0.0f;

};