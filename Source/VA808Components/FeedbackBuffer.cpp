/*
  ==============================================================================

    FeedbackBuffer.cpp
    Created: 25 Jun 2021 12:03:36pm
    Author:  csmit

  ==============================================================================
*/

#include "FeedbackBuffer.h"

void FeedbackBuffer::setSampleRate(float SR)
{
    // set sample rate
    sampleRate = SR;

    // constant used in bilinear transformation substitution
    float K = 2 * sampleRate;

    // calculating coefficients of continuous-time transfer function of the feedback buffer stage
    float beta1 = -r169 * vr6 * decay * c43;
    float beta0 = -r169;
    float alpha1 = r164 * (r169 + vr6 * decay) * c43;
    float alpha0 = r164;

    // calculating discretized coefficients for feedback buffer
    A0 = K * alpha1 + alpha0;
    B0 = (K * beta1 + beta0) / A0;
    B1 = (beta0 - K * beta1) / A0;
    A1 = (alpha0 - K * alpha1) / A0;
}

float FeedbackBuffer::process(float v_bt)
{
    // calculating the next step from the feedback buffer difference equation
    float v_fb = B0 * v_bt + B1 * v_btPrev1 - A1 * v_fbPrev1;

    // updating past sample variables
    v_btPrev1 = v_bt;
    v_fbPrev1 = v_fb;

    // feedback buffer output op-amp clip
    if (v_fb < -B2)
    {
        v_fb = -B2;
    }

    return v_fb;
    
}