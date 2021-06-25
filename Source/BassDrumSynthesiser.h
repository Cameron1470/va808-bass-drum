/*
  ==============================================================================

    "BassDrumSynthesiser.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project
    
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "VA808Components/TriggerLogic.h"
#include "VA808Components/PulseShaper.h"
#include "VA808Components/BridgedTNetwork.h"
#include "VA808Components/FeedbackBuffer.h"
#include "VA808Components/ToneStage.h"
#include "VA808Components/LevelStage.h"
#include "VA808Components/OutputStage.h"

// ===========================
// ===========================
// SOUND
class BassDrumSynthSound : public juce::SynthesiserSound
{
public:
    bool appliesToNote      (int) override      { return true; }
    //--------------------------------------------------------------------------
    bool appliesToChannel   (int) override      { return true; }
};




// =================================
// =================================
// SYNTHESISER VOICE

/*!
 @class BassDrumSynthVoice
 @abstract struct defining the DSP associated with a specific voice.
 @discussion multiple BassDrumSynthVoice objects will be created by the Synthesiser so that it can be played polyphicially
 
 @namespace none
 @updated 2019-06-18
 */
class BassDrumSynthVoice : public juce::SynthesiserVoice
{
public:
    BassDrumSynthVoice() {}
    //--------------------------------------------------------------------------
    /**
     What should be done when a note starts

     @param midiNoteNumber
     @param velocity
     @param SynthesiserSound unused variable
     @param / unused variable
     */
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound*, int /*currentPitchWheelPosition*/) override;

    //--------------------------------------------------------------------------
    /// Called when a MIDI noteOff message is received
    /**
     What should be done when a note stops

     @param / unused variable
     @param allowTailOff bool to decie if the should be any volume decay
     */
    void stopNote(float /*velocity*/, bool allowTailOff) override;
    
    //--------------------------------------------------------------------------
    /// Prepare to play function
    /**
     What should be done when a note stops

     @param sampling frequency in Hz
     */
    void prepareToPlay(double sampleRate);

    //--------------------------------------------------------------------------
    /**
     The Main DSP Block: Put your DSP code in here
     
     If the sound that the voice is playing finishes during the course of this rendered block, it must call clearCurrentNote(), to tell the synthesiser that it has finished

     @param outputBuffer pointer to output
     @param startSample position of first sample in buffer
     @param numSamples number of smaples in output buffer
     */
    void renderNextBlock(juce::AudioSampleBuffer& outputBuffer, int startSample, int numSamples) override;

    //--------------------------------------------------------------------------
    void pitchWheelMoved(int) override {}
    //--------------------------------------------------------------------------
    void controllerMoved(int, int) override {}
    //--------------------------------------------------------------------------
    /**
     Can this voice play a sound. I wouldn't worry about this for the time being

     @param sound a juce::SynthesiserSound* base class pointer
     @return sound cast as a pointer to an instance of YourSynthSound
     */
    bool canPlaySound (juce::SynthesiserSound* sound) override
    {
        return dynamic_cast<BassDrumSynthSound*> (sound) != nullptr;
    }
    //--------------------------------------------------------------------------
private:
    //--------------------------------------------------------------------------

    /// Instance of the TriggerLogic class for the trigger logic process block
    TriggerLogic triggerLogic;

    /// Instance of the PulseShaper class for the pulse shaper process block
    PulseShaper pulseShaper;

    /// Instance of the PulseShaper class for the bridged-T network process block
    BridgedTNetwork bridgedTNetwork;

    /// Instance of the FeedbackBuffer class for the feedback buffer process block
    FeedbackBuffer feedbackBuffer;

    /// Instance of the ToneStage class for the tone stage process block
    ToneStage toneStage;

    /// Instance of the LevelStage class for the level stage process block
    LevelStage levelStage;

    /// Instance of the OutputStage class for the output stage process block
    OutputStage outputStage;

    /// adjustable gain value for the output level
    float outputGain = 0.065;

    // stored value of v_fb, updated then used in the following sample calculation
    float v_fb = 0.0f;

};
