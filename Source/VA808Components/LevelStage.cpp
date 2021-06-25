/*
  ==============================================================================

    LevelStage.cpp
    Created: 25 Jun 2021 2:41:37pm
    Author:  csmit

  ==============================================================================
*/

#include "LevelStage.h"

void LevelStage::setSampleRate(float SR)
{
    // set sample rate
    sampleRate = SR;

    // constant used in bilinear transformation substitution
    float K = 2 * sampleRate;

    // calculating coefficients of continuous-time transfer function of the tone stage
    float beta1 = vr4 * (1 - level) * c47;
    float alpha1 = vr4 * c47;

    // calculating discretized coefficients for tone stage
    A0 = K * alpha1 + 1;
    B0 = (K* beta1) / A0;
    B1 = (-K * beta1) / A0;
    A1 = (1.0f - K * alpha1) / A0;
}

float LevelStage::process(float v_to)
{
    // calculating the next step from the tone stage difference equation
    float v_lev = (B0 * v_to) + (B1 * v_toPrev1) - (A1 * v_levPrev1);

    // updating past sample variables
    v_toPrev1 = v_to;
    v_levPrev1 = v_lev;

    return v_lev;

}