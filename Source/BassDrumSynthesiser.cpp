/*
  ==============================================================================

    "BassDrumSynthesiser.cpp"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237

  ==============================================================================
*/

#include "BassDrumSynthesiser.h"


void BassDrumSynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{
    triggerLogic.setTriggerActive(velocity);
}

void BassDrumSynthVoice::stopNote(float /*velocity*/, bool allowTailOff)
{

}

void BassDrumSynthVoice::prepareToPlay(double sampleRate)
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

void BassDrumSynthVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    // iterate through the necessary number of samples (from startSample up to startSample + numSamples)
    for (int sampleIndex = startSample; sampleIndex < (startSample + numSamples); sampleIndex++)
    {
        //===========================================
        //BRIDGED-T INPUT 1
        float v_trig = triggerLogic.triggerProcess();

        float v_plus = pulseShaper.process(v_trig);


        //===========================================
        //BRIDGED-T INPUT 2
        float v_env = triggerLogic.envProcess();

        float v_rp = retriggeringPulse.process(v_env);


        //===========================================
        //BRIDGED-T UPDATE
        float v_bt = bridgedTNetwork.process(v_plus, v_rp);


        //===========================================
        //BRIDGED-T INPUT 3
        v_fb = feedbackBuffer.process(v_bt);

        bridgedTNetwork.updateFeedbackBuffer(v_fb);


        //===========================================
        //OUTPUT STAGES
        float v_to = toneStage.process(v_bt);

        float v_lev = levelStage.process(v_to);

        float v_out = outputStage.process(v_lev);


        //===========================================
        //FREQUENCY EFFECTS

        bridgedTNetwork.updateFeedbackBuffer(v_fb);
        bridgedTNetwork.postprocessUpdate(v_plus, v_rp);


        //===========================================
        //WRITING OUTPUT TO BUFFER

        float currentSample = v_out;

        // for each channel, write the currentSample float to the output
        for (int chan = 0; chan < outputBuffer.getNumChannels(); chan++)
        {
            // The output sample is scaled by 0.2 so that it is not too loud by default
            outputBuffer.addSample(chan, sampleIndex, currentSample * outputGain);
        }
        
    }
}