/*
  ==============================================================================

    OutputStage.cpp
    Created: 25 Jun 2021 3:01:29pm
    Author:  csmit

  ==============================================================================
*/

#include "OutputStage.h"

void OutputStage::setSampleRate(float SR)
{
    // set sample rate
    sampleRate = SR;

    // constant used in bilinear transformation substitution
    float K = 2 * sampleRate;

    // calculating coefficients of continuous-time transfer function of the tone stage
    float beta1 = r177 * c49;
    float alpha1 = r176 * c49;

    // calculating discretized coefficients for tone stage
    A0 = K * alpha1 + 1;
    B0 = (K * beta1) / A0;
    B1 = (-K * beta1) / A0;
    A1 = (1.0f - K * alpha1) / A0;
}

float OutputStage::process(float v_lev)
{
    // calculating the next step from the tone stage difference equation
    float v_out = (B0 * v_lev) + (B1 * v_levPrev1) - (A1 * v_outPrev1);

    // updating past sample variables
    v_levPrev1 = v_lev;
    v_outPrev1 = v_out;

    return v_out;

}
