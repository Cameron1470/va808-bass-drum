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
    triggerLogic.setSampleRate(sampleRate);
    pulseShaper.setSampleRate(sampleRate);
}

void BassDrumSynthVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    // iterate through the necessary number of samples (from startSample up to startSample + numSamples)
    for (int sampleIndex = startSample; sampleIndex < (startSample + numSamples); sampleIndex++)
    {
        // your sample-by-sample DSP code here!
        // An example white noise generater as a placeholder - replace with your own code
        float v_trig = triggerLogic.process();

        float v_plus = pulseShaper.process(v_trig);

        float currentSample = v_plus;

        // for each channel, write the currentSample float to the output
        for (int chan = 0; chan < outputBuffer.getNumChannels(); chan++)
        {
            // The output sample is scaled by 0.2 so that it is not too loud by default
            outputBuffer.addSample(chan, sampleIndex, currentSample * outputGain);
        }
        
    }
}