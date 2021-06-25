/*
  ==============================================================================

    "BridgedTNetwork.cpp"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the bridged-T network of the VA model

  ==============================================================================
*/

#include "BridgedTNetwork.h"

void BridgedTNetwork::setSampleRate(float SR)
{
    // set K constant with sample rate
    K = 2 * SR;

    // updates the discrete time difference function coefficients
    updateCoefficients();
}

void BridgedTNetwork::updateCoefficients()
{
    v_btOne.calculateCoefficients(K, r161, r165, r166, r167, r170, c41, c42);
    v_btTwo.calculateCoefficients(K, r161, r165, r166, r167, r170, c41, c42);
    v_btThree.calculateCoefficients(K, r161, r165, r166, r167, r170, c41, c42);
}

float BridgedTNetwork::process(float v_plus, float v_fb, float v_rp)
{
    // superposition of the bridged-T inputs
    float v_bt = v_btOne.process(v_plus) + v_btTwo.process(v_fb) + v_btThree.process(v_rp);

    // bridged-T output op-amp clip
    if (v_bt > B2)
    {
        v_bt = B2;
    }

    return v_bt;
}


//=======================================




