/*
  ==============================================================================

    "DrumSynthesiser.cpp"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237

    ----------------------see header file for description-----------------------
  ==============================================================================
*/

#include "DrumSynthesiser.h"


void DrumSynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/)
{

    bassDrum.activate(velocity);
}

void DrumSynthVoice::stopNote(float /*velocity*/, bool allowTailOff)
{

}

void DrumSynthVoice::prepareToPlay(double sampleRate)
{
    bassDrum.setSampleRate(sampleRate);
}

void DrumSynthVoice::renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples)
{
    // iterate through the necessary number of samples (from startSample up to startSample + numSamples)
    for (int sampleIndex = startSample; sampleIndex < (startSample + numSamples); sampleIndex++)
    {
        // get next output sample from va808 bass drum model
        float v_out = bassDrum.process();

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

void DrumSynthVoice::updateDrumParams(const float level, const float tone, const float decay)
{
    bassDrum.updateParams(level, tone, decay);
}