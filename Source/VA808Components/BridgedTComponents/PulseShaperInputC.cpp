/*
  ==============================================================================
    "PulseShaperInputC.cpp"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237
  ==============================================================================
*/

#include "PulseShaperInputC.h"

void PulseShaperInputC::calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42)
{
    float r_prl1 = 1.0f / (1.0f / r161 + 1.0f / (r165 + r166) + 1.0f / r170);

    float beta2 = r_prl1 * r167 * c41 * c42;
    float beta1 = r_prl1 * (c41 + c42);
    float alpha2 = r_prl1 * r167 * c41 * c42;
    float alpha1 = r_prl1 * (c41 + c42);

    A0 = pow(K, 2.0f) * alpha2 + K * alpha1;

    B0 = (pow(K, 2.0f) * beta2 + K * beta1) / A0;
    B1 = (-2 * pow(K, 2.0f) * beta2) / A0;
    B2 = (pow(K, 2.0f) * beta2 - K * beta1) / A0;
    A1 = (2.0f - 2 * pow(K, 2.0f) * alpha2) / A0;
    A2 = (pow(K, 2.0f) * alpha2 - K * alpha1 + 1) / A0;
}

float PulseShaperInputC::process(float v_plus)
{
    // calculate next step from the difference equation
    float v_c1 = B0 * v_plus + B1 * v_plusPrev1 + B2 * v_plusPrev2 - A1 * v_c1Prev1 - A2 * v_c1Prev2;

    // update past sample variables for v_plus(n-1) and v_plus(n-2)
    v_plusPrev2 = v_plusPrev1;
    v_plusPrev1 = v_plus;

    // update past sample variables for v_bt1(n-1) and v_bt1(n-2)
    v_c1Prev2 = v_c1Prev1;
    v_c1Prev1 = v_c1;

    // return calculated value of current sample v_bt1(n)
    return v_c1;
}