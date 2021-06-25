/*
  ==============================================================================

    FeedbackBufferInput.h
    Created: 25 Jun 2021 12:52:54pm
    Author:  csmit

  ==============================================================================
*/

#pragma once

#include <math.h>  

class FeedbackBufferInput
{
public:
    void calculateCoefficients(float K, float r161, float r165, float r166, float r167, float r170, float c41, float c42);

    float process(float v_fb);

private:
    /// coefficients of the discretized transfer functions for bridged-T network, input 2 from feedback buffer
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B2 = 0.0f;
    float A1 = 0.0f;
    float A2 = 0.0f;

    /// previous sample of input, v_fb(n-1)
    float v_fbPrev1 = 0.0f;

    /// second previous sample of input, v_fb(n-2)
    float v_fbPrev2 = 0.0f;

    /// previous sample of output, v_bt2(n-1)
    float v_bt2Prev1 = 0.0f;

    /// second previous sample of output, v_bt2(n-2)
    float v_bt2Prev2 = 0.0f;
};
