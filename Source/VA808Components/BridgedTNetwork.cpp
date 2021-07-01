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

    r_eff = r165 + r166;

    updateParallelResistances();

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
    
    updateParallelResistances();

    h_btOne.calculateCoefficients(K, r_prl1, r161, r167, r170, c41, c42);
    h_btTwo.calculateCoefficients(K, r_prl2, r161, r167, r170, c41, c42);
    h_btThree.calculateCoefficients(K, r_prl3, r161, r167, r170, c41, c42);

}

void BridgedTNetwork::updateParallelResistances()
{
    r_prl1 = 1.0f / (1.0f / r161 + 1.0f / r_eff + 1.0f / r170);

    r_prl2 = 1.0f / (1.0f / r161 + 1.0f / r_eff);

    r_prl3 = 1.0f / (1.0f / r170 + 1.0f / r_eff);
}

float BridgedTNetwork::process(float v_plus, float v_fb, float v_rp)
{
    // superposition of the bridged-T inputs
    float v_bt = h_btOne.process(v_plus) + h_btTwo.process(v_fb) + h_btThree.process(v_rp);

    // bridged-T output op-amp clip
    if (v_bt > B2)
    {
        v_bt = B2;
    }


    h_cOne.calculateCoefficients(K, r_prl1, r161, r167, r170, c41, c42);
    h_cTwo.calculateCoefficients(K, r_prl2, r161, r167, r170, c41, c42);
    h_cThree.calculateCoefficients(K, r_prl3, r161, r167, r170, c41, c42);

    float v_c = h_cOne.process(v_plus) + h_cTwo.process(v_fb) + h_cThree.process(v_rp);

    updateEffectiveResistance(v_c);

    updateCoefficients();

    return v_bt;
}


//=======================================




