/*
  ==============================================================================

    "VA808BassDrum.cpp"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 15th July 2021
    Author:  Cameron Smith, UoE s1338237

    Class used for compartmentalizing the virtual analogue model of the TR-808
    bass drum. Added to allow for flexibility and ease of transportation for use
    in other environments.

  ==============================================================================
*/

#include "VA808BassDrum.h"

void VA808BassDrum::setSampleRate(float sampleRate)
{
    triggerLogic.updateSampleRate(sampleRate);
    pulseShaper.setSampleRate(sampleRate);
    retriggeringPulse.setSampleRate(sampleRate);
    bridgedTNetwork.setSampleRate(sampleRate);
    feedbackBuffer.setSampleRate(sampleRate);
    toneStage.setSampleRate(sampleRate);
    levelStage.setSampleRate(sampleRate);
    outputStage.setSampleRate(sampleRate);
}

void VA808BassDrum::activate(float velocity)
{
    triggerLogic.setTriggerActive(velocity);
}

float VA808BassDrum::process()
{
    //===========================================
    //BRIDGED-T INPUT 1
    float v_trig = triggerLogic.triggerProcess();

    float v_plus = pulseShaper.process(v_trig);


    //===========================================
    //BRIDGED-T INPUT 3
    float v_env = triggerLogic.envProcess();

    float v_rp = retriggeringPulse.process(v_env);


    //===========================================
    //BRIDGED-T UPDATE
    float v_bt = bridgedTNetwork.process(v_plus, v_rp);


    //===========================================
    //BRIDGED-T INPUT 2
    float v_fb = feedbackBuffer.process(v_bt);

    bridgedTNetwork.updateFeedbackBuffer(v_fb);


    //===========================================
    //OUTPUT STAGES
    float v_to = toneStage.process(v_bt);

    float v_lev = levelStage.process(v_to);

    float v_out = outputStage.process(v_lev);


    //===========================================
    //FREQUENCY EFFECTS

    bridgedTNetwork.postprocessUpdate(v_plus, v_fb, v_rp);

    return v_out;
}
