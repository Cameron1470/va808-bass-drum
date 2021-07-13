/*
  ==============================================================================
    "FeedbackBufferInput.h"

    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 13th July 2021
    Author:  Cameron Smith, UoE s1338237

  ==============================================================================
*/

#pragma once

#include <math.h>  

class HbtTwo
{
public:
    void calculateCoefficients(float K, float r_prl2, float r161, float r167, float r170, float c41, float c42)
    {
        float beta1 = -r_prl2 * r167 * c41;
        float alpha2 = r_prl2 * r167 * r170 * c41 * c42;
        float alpha1 = r_prl2 * r170 * (c41 + c42);
        float alpha0 = r_prl2 + r170;

        A0 = K * K * alpha2 + K * alpha1 + alpha0;

        B0 = (K * beta1) / A0;
        B2 = (-K * beta1) / A0;
        A1 = (2.0f * alpha0 - 2.0f * K * K * alpha2) / A0;
        A2 = (K * K * alpha2 - K * alpha1 + alpha0) / A0;
    }

    float process(float v_fb)
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

private:
    /// coefficients of the discretized transfer functions for bridged-T network, H_bt2(z), input 2 from feedback buffer
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

class HcTwo
{
public:
    void calculateCoefficients(float K, float r_prl2, float r161, float r167, float r170, float c41, float c42)
    {
        float beta0 = r_prl2;
        float alpha2 = r_prl2 * r167 * r170 * c41 * c42;
        float alpha1 = r_prl2 * r170 * (c41 + c42);
        float alpha0 = r_prl2 + r170;

        A0 = K * K * alpha2 + K * alpha1 + alpha0;

        B0 = beta0 / A0;
        B1 = (2.0f * beta0) / A0;
        B2 = beta0 / A0;
        A1 = (2.0f * alpha0 - 2.0f * K * K * alpha2) / A0;
        A2 = (K * K * alpha2 - K * alpha1 + alpha0) / A0;
    }

    float process(float v_fb)
    {
        // calculate next step from the difference equation
        float v_c2 = B0 * v_fb + B1 * v_fbPrev1 + B2 * v_fbPrev2 - A1 * v_c2Prev1 - A2 * v_c2Prev2;

        // update past sample variables for v_fb(n-1) and v_fb(n-2)
        v_fbPrev2 = v_fbPrev1;
        v_fbPrev1 = v_fb;

        // update past sample variables for v_c2(n-1) and v_c2(n-2)
        v_c2Prev2 = v_c2Prev1;
        v_c2Prev1 = v_c2;

        // return calculated value of current sample v_c2(n)
        return v_c2;
    }

private:
    /// coefficients of the discretized transfer function for bridged-T network, H_c2(z), input 2 from feedback buffer
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float B2 = 0.0f;
    float A1 = 0.0f;
    float A2 = 0.0f;

    /// previous sample of input, v_fb(n-1)
    float v_fbPrev1 = 0.0f;

    /// second previous sample of input, v_fb(n-2)
    float v_fbPrev2 = 0.0f;

    /// previous sample of output, v_c2(n-1)
    float v_c2Prev1 = 0.0f;

    /// second previous sample of output, v_c2(n-2)
    float v_c2Prev2 = 0.0f;
};