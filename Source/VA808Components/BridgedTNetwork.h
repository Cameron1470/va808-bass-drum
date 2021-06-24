/*
  ==============================================================================

    "BridgedTNetwork.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the bridged-T network of the VA model

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class BridgedTNetwork
{
public:
    BridgedTNetwork():

    //--------------------------------------------------------------------------
    /**
    Updates sample rate in the class private variables,

    Subsequently updates the discrete transfer function coefficients

    @param sample rate in Hz
    */
    void setSampleRate(float SR);

    //--------------------------------------------------------------------------
    /**
    Get current sample of the bridged-T network process block
    */
    float process(float V_bt1, float V_bt2, float V_bt3);


private:
    /// sampling frequency in Hz
    float sampleRate = 0.0f;

    ///
    float c41 = 1.5e-8;

    ///
    float c42 = 1.5e-8;

    /// value of resistor R165 (47 kOhms)
    float r165 = 4.7e4;

    /// value of resistor R166 (6.8 kOhms)
    float r166 = 6.8e3;
    
    /// value of resistor R167 (1 MOhms)
    float r167 = 1e6;
};