/*
  ==============================================================================

    RetriggeringPulseInput.cpp
    Created: 25 Jun 2021 12:53:09pm
    Author:  csmit

  ==============================================================================
*/

#include "RetriggeringPulseInput.h"

void RetriggeringPulseInput::calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42)
{
    float r_prl3 = 1.0f / (1.0f / r170 + 1.0f / (r165 + r166));

    float beta1 = -r_prl3 * r167 * c41;
    float alpha2 = r_prl3 * r167 * r161 * c41 * c42;
    float alpha1 = r_prl3 * r161 * (c41 + c42);
    float alpha0 = r_prl3 + r161;

    A0 = pow(K, 2.0f) * alpha2 + K * alpha1 + alpha0;

    B0 = (K * beta1) / A0;
    B2 = (-K * beta1) / A0;
    A1 = (2.0f * alpha0 - 2 * pow(K, 2.0f) * alpha2) / A0;
    A2 = (pow(K, 2.0f) * alpha2 - K * alpha1 + alpha0) / A0;
}

float RetriggeringPulseInput::process(float v_rp)
{
    // calculate next step from the difference equation
    float v_bt3 = B0 * v_rp + B2 * v_rpPrev2 - A1 * v_bt3Prev1 - A2 * v_bt3Prev2;

    // update past sample variables for v_rp(n-1) and v_rp(n-2)
    v_rpPrev2 = v_rpPrev1;
    v_rpPrev1 = v_rp;

    // update past sample variables for v_bt3(n-1) and v_bt3(n-2)
    v_bt3Prev2 = v_bt3Prev1;
    v_bt3Prev1 = v_bt3;

    // return calculated value of current sample v_bt3(n)
    return v_bt3;
}