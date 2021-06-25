/*
  ==============================================================================

    PulseShaperInput.cpp
    Created: 25 Jun 2021 12:52:41pm
    Author:  csmit

  ==============================================================================
*/

#include "PulseShaperInput.h"

void PulseShaperInput::calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42)
{
    float r_prl1 = 1.0f / (1.0f / r161 + 1.0f / (r165 + r166) + 1.0f / r170);

    float beta2 = r_prl1 * r167 * c41 * c42;
    float beta1 = r_prl1 * c41 + r167 * c41 + r_prl1 * c42;
    float beta0 = 1;
    float alpha2 = r_prl1 * r167 * c41 * c42;
    float alpha1 = r_prl1 * (c41 + c42);
    float alpha0 = 1;

    A0 = pow(K, 2.0f) * alpha2 + K * alpha1 + alpha0;

    B0 = (pow(K, 2.0f) * beta2 + K * beta1 + beta0) / A0;
    B1 = (2.0f * beta0 - 2 * pow(K, 2.0f) * beta2) / A0;
    B2 = (pow(K, 2.0f) * beta2 - K * beta1 + beta0) / A0;
    A1 = (2.0f * alpha0 - 2 * pow(K, 2.0f) * alpha2) / A0;
    A2 = (pow(K, 2.0f) * alpha2 - K * alpha1 + alpha0) / A0;
}

float PulseShaperInput::process(float v_plus)
{
    // calculate next step from the difference equation
    float v_bt1 = B0 * v_plus + B1 * v_plusPrev1 + B2 * v_plusPrev2 - A1 * v_bt1Prev1 - A2 * v_bt1Prev2;

    // update past sample variables for v_plus(n-1) and v_plus(n-2)
    v_plusPrev2 = v_plusPrev1;
    v_plusPrev1 = v_plus;

    // update past sample variables for v_bt1(n-1) and v_bt1(n-2)
    v_bt1Prev2 = v_bt1Prev1;
    v_bt1Prev1 = v_bt1;

    // return calculated value of current sample v_bt1(n)
    return v_bt1;
}