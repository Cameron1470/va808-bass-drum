/*
  ==============================================================================

    "ToneStage.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 25th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the tone block of the VA model

  ==============================================================================
*/

#pragma once

class ToneStage
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
    Get current sample of the tone process block
    */
    float process(float v_bt);

private:

    /// sampling frequency in Hz
    float sampleRate = 0.0f;

    /// value of capacitor C45 (100 nF)
    float c45 = 1.0e-7;

    /// value of resistor R171 (220 Ohms)
    float r171 = 220;

    /// value of resistor R172 (10 kOhms)
    float r172 = 1.0e4;

    /// maximum value of variable resistor VR5(10 kOhms)
    float vr5 = 1.0e4;

    /// VR5 mod [0,1] -- TONE KNOB,  0=high cutoff | 1=low cutoff
    float tone = 0.3f;

    /// coefficients of the discretized transfer function for tone stage
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float A1 = 0.0f;

    /// previous sample of input, v_bt(n-1)
    float v_btPrev1 = 0.0f;

    /// previous sample of output, v_to(n-1)
    float v_toPrev1 = 0.0f;


};