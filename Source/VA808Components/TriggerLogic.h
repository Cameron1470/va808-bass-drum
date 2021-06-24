/*
  ==============================================================================

    "TriggerLogic.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the trigger logic block of the VA model. When a note
    is played in the synthesiser class a 1ms square-shaped pulse is generated

  ==============================================================================
*/

#pragma once

#include<JuceHeader.h>

class TriggerLogic
{
public:
    TriggerLogic();

    //--------------------------------------------------------------------------
    /**
    Updates sample rate and consequently the pulse length in samples
    @param sample rate in Hz
    */
    void setSampleRate(float SR);

    //--------------------------------------------------------------------------
    /**
    Set the trigger logic to an active state. it will begin outputing a pulse
    @param velocity of the MIDI note played, determines amplitude of pulse
    */
    void setTriggerActive(float velocity);

    //--------------------------------------------------------------------------
    /**
    Get current sample of the trigger logic process block
    */
    float process();

private:
    /// sampling frequency in Hz
    float sampleRate;

    /// length of the pulse in seconds (fixed as 1ms)
    float pulseLengthInSeconds = 0.001f;

    // length of the pulse in samples
    float pulseLengthInSamples;

    // is the triggering pulse currently active
    bool active = false;

    // common trigger signal voltage amplitude (4-14V)
    float v_ct = 0.0f;

    // index, used to keep track of progress through the pulse duration
    int pulseIndex = 0;

};
