/*
  ==============================================================================

    FeedbackBufferInput.cpp
    Created: 25 Jun 2021 12:52:54pm
    Author:  csmit

  ==============================================================================
*/

#include "FeedbackBufferInput.h"


void FeedbackBufferInput::calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42)
{
    float r_prl2 = 1.0f / (1.0f / r161 + 1.0f / (r165 + r166));

    float beta1 = -r_prl2 * r167 * c41;
    float alpha2 = r_prl2 * r167 * r170 * c41 * c42;
    float alpha1 = r_prl2 * r170 * (c41 + c42);
    float alpha0 = r_prl2 + r170;

    A0 = pow(K, 2.0f) * alpha2 + K * alpha1 + alpha0;

    B0 = (K * beta1) / A0;
    B2 = (-K * beta1) / A0;
    A1 = (2.0f * alpha0 - 2 * pow(K, 2.0f) * alpha2) / A0;
    A2 = (pow(K, 2.0f) * alpha2 - K * alpha1 + alpha0) / A0;
}

float FeedbackBufferInput::process(float v_fb)
{
    // calculate next step from the difference equation
    float v_bt2 = B0 * v_fb + B2 * v_fbPrev2 - A1 * v_bt2Prev1 - A2 * v_bt2Prev2;

    // update past sample variables for v_fb(n-1) and v_fb(n-2)
    v_fbPrev2 = v_fbPrev1;
    v_fbPrev1 = v_fb;

    // update past sample variables for v_bt2(n-1) and v_bt2(n-2)
    v_bt2Prev2 = v_bt2Prev1;
    v_bt2Prev1 = v_bt2;

    // return calculated value of current sample v_bt1(n)
    return v_bt2;
}
