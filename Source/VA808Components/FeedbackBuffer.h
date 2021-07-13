/*
  ==============================================================================

    "FeedbackBuffer.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 25th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the feedback buffer block of the VA model

  ==============================================================================
*/

#pragma once


class FeedbackBuffer
{
public:

    //--------------------------------------------------------------------------
    /**
    Updates sample rate in the class private variables,

    Subsequently updates the discrete transfer function coefficients

    @param sample rate in Hz
    */
    void setSampleRate(float SR);

    //--------------------------------------------------------------------------
    /**
    Get current sample of the feedback buffer process block
    */
    float process(float v_bt);

private:
    
    /// sampling frequency in Hz
    float sampleRate = 0.0f;

    /// value of capacitor C43 (33 microF)
    float c43 = 3.3e-8;
    
    /// value of resistor R164 (47 kOhms)
    float r164 = 4.7e4;

    /// value of resistor R169 (47 kOhms)
    float r169 = 4.7e4;

    /// maximum value of variable resistor VR6(500 kOhms)
    float  vr6 = 5.0e5;

    /// VR6 mod [0,1] -- DECAY KNOB, 0=short decay | 1=long decay
    float decay = 0.5f;

    /// voltage from rail being supplied to op-amps
    float B2 = 15.0f;

    /// coefficients of the discretized transfer function for feedback buffer
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float A1 = 0.0f;

    /// previous sample of input, v_bt(n-1)
    float v_btPrev1 = 0.0f;

    /// previous sample of output, v_fb(n-1)
    float v_fbPrev1 = 0.0f;

};