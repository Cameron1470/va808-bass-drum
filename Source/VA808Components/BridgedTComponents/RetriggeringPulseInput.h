/*
  ==============================================================================

    RetriggeringPulseInput.h
    Created: 25 Jun 2021 12:53:09pm
    Author:  csmit

  ==============================================================================
*/

#pragma once

#include <math.h>  

class RetriggeringPulseInput
{
public:
    void calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42);

    float process(float v_rp);

private:
    /// coefficients of the discretized transfer functions for bridged-T network, input 3 from retriggering pulse
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B2 = 0.0f;
    float A1 = 0.0f;
    float A2 = 0.0f;

    /// previous sample of input, v_rp(n-1)
    float v_rpPrev1 = 0.0f;

    /// second previous sample of input, v_rp(n-2)
    float v_rpPrev2 = 0.0f;

    /// previous sample of output, v_bt3(n-1)
    float v_bt3Prev1 = 0.0f;

    /// second previous sample of output, v_bt3(n-2)
    float v_bt3Prev2 = 0.0f;
};