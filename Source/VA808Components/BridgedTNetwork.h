/*
  ==============================================================================

    "BridgedTNetwork.h"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237

    Class that represents the bridged-T network of the VA model

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>
#include"BridgedTComponents/PulseShaper.h"
#include"BridgedTComponents/FeedbackBuffer.h"
#include"BridgedTComponents/RetriggeringPulse.h"

class BridgedTNetwork
{
public:

    //--------------------------------------------------------------------------
    /**
    Updates sample rate in the class private variables,

    Subsequently updates the discrete transfer function coefficients

    @param sample rate in Hz
    */
    void setSampleRate(float SR);


    void updateParallelResistances();

    void updateEffectiveResistance(float v_c);

    void updateCoefficients();

    //--------------------------------------------------------------------------
    /**
    Get current sample of the bridged-T network process block
    */
    float process(float v_plus, float v_fb, float v_rp);


private:
    /// constant used in bilinear transformation
    float K = 0.0f;

    /// value of capacitor C41 (15 nF)
    float c41 = 1.5e-8;

    /// value of capacitor C42 (15 nF)
    float c42 = 1.5e-8;

    /// value of resistor R161 (1 MOhms)
    float r161 = 1.0e6;
    
    /// value of resistor R165 (47 kOhms)
    float r165 = 4.7e4;

    /// value of resistor R166 (6.8 kOhms)
    float r166 = 6.8e3;
    
    /// value of resistor R167 (1 MOhms)
    float r167 = 1e6;

    /// value of resistor R170 (470 kOhms)
    float r170 = 4.7e5;

    float r_eff;
    
    float r_prl1;

    float r_prl2;

    float r_prl3;

    float B2 = 15.0f;

    HbtOne h_btOne;

    HbtTwo h_btTwo;

    HbtThree h_btThree;

    HcOne h_cOne;

    HcTwo h_cTwo;
    
    HcThree h_cThree;

    float alpha = 14.315f;

    float V0 = -0.5560f;

    float m = 1.4765e-5;

    float interpLow = 5.3762e4;

    float interpHigh = 5.38e4;

    float interpC = 5.3775e4;
};


//=======================================





