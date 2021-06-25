/*
  ==============================================================================

    PulseShaperInput.h
    Created: 25 Jun 2021 12:52:41pm
    Author:  csmit

  ==============================================================================
*/

#pragma once

#include <math.h>  

class PulseShaperInput
{
public:
    void calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42);

    float process(float v_plus);

private:
    /// coefficients of the discretized transfer functions for bridged-T network, input 1 from pulse shaper
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float B2 = 0.0f;
    float A1 = 0.0f;
    float A2 = 0.0f;

    /// previous sample of input, v_plus(n-1)
    float v_plusPrev1 = 0.0f;

    /// second previous sample of input, v_plus(n-2)
    float v_plusPrev2 = 0.0f;

    /// previous sample of output, v_bt1(n-1)
    float v_bt1Prev1 = 0.0f;

    /// second previous sample of output, v_bt1(n-2)
    float v_bt1Prev2 = 0.0f;
};