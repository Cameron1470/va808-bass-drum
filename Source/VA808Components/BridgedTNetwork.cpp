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
    K = 2.0f * SR;

    r_eff = r165 + r166;

    // updates the discrete time difference function coefficients
    updateCoefficients();
}

void BridgedTNetwork::updateEffectiveResistance(float v_c)
{
    float i_c = -log(1.0f + exp(-alpha * (v_c - V0)))* m / alpha;

    if (v_c < -0.1f)
    {
        r_eff = (v_c * r166 * (r165 + r166)) / (v_c * (r165 + 166) - r165 * (v_c - r166 * i_c));
    }
    else if (v_c < 0.2f)
    {
        r_eff = ((interpHigh - interpLow) * v_c / 0.3f) + interpC;
    }
    else
    {
        r_eff = r165 + r166;
    }

}

void BridgedTNetwork::updateCoefficients()
{
    // firstly updating the parallel resistance values from r_eff
    r_prl1 = 1.0f / (1.0f / r161 + 1.0f / r_eff + 1.0f / r170);
    r_prl2 = 1.0f / (1.0f / r161 + 1.0f / r_eff);
    r_prl3 = 1.0f / (1.0f / r170 + 1.0f / r_eff);

    // then calling the functions in the input classes to calculate coefficients
    h_btOne.calculateCoefficients(K, r_prl1, r167, c41, c42);
    h_btTwo.calculateCoefficients(K, r_prl2, r167, r170, c41, c42);
    h_btThree.calculateCoefficients(K, r_prl3, r161, r167, c41, c42);

}

void BridgedTNetwork::updateFeedbackBuffer(float v_fb)
{
    h_btTwo.updatePastSamples(v_fb);
    h_cTwo.updatePastSamples(v_fb);
}

float BridgedTNetwork::process(float v_plus, float v_rp)
{
    float v_btOne = h_btOne.process(v_plus);
    float v_btTwo = h_btTwo.process();
    float v_btThree = h_btThree.process(v_rp);
    
    // superposition of the bridged-T inputs
    v_bt = v_btOne + v_btTwo + v_btThree;

    // bridged-T output op-amp clip
    opAmpClip();

    return v_bt;

}

void BridgedTNetwork::opAmpClip()
{
    if (v_bt > B2)
    {
        v_bt = B2;
    }
}

void BridgedTNetwork::postprocessUpdate(float v_plus, float v_rp)
{
    h_cOne.calculateCoefficients(K, r_prl1, r167, c41, c42);
    h_cTwo.calculateCoefficients(K, r_prl2, r167, r170, c41, c42);
    h_cThree.calculateCoefficients(K, r_prl3, r161, r167, c41, c42);

    float v_c = h_cOne.process(v_plus) + h_cTwo.process() + h_cThree.process(v_rp);

    updateEffectiveResistance(v_c);

    updateCoefficients();
}


//=======================================




