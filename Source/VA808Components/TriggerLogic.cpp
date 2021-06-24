/*
  ==============================================================================

    "TriggerLogic.cpp"
    Roland TR-808 Virtual Analogue Modelling - MSc Project

    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237


    Class that represents the trigger logic block of the VA model. When a note
    is played in the synthesiser class a 1ms square-shaped pulse is generated

  ==============================================================================
*/

#include "TriggerLogic.h"

TriggerLogic::TriggerLogic()
{

}

void TriggerLogic::setSampleRate(float SR)
{
    // update sample rate
    sampleRate = SR;

    // updating pulse length in samples by mulptiplying 1ms time duration and sample rate
    pulseLengthInSamples = round(pulseLengthInSeconds * sampleRate);
}

void TriggerLogic::setTriggerActive(float velocity)
{
    // check if trigger is not already active, if it is then nothing happens. too quick!
    if (active != true)
    {
        // if trigger is not active, make it so
        active = true;

        // update the common trigger signal amplitude (4-14V)
        v_ct = 4.0f + (velocity * 10.0f);
    }
}

float TriggerLogic::process()
{
    if (active == true && pulseIndex < pulseLengthInSamples)
    {
        // currently active, increment index and return trigger signal amplitude
        pulseIndex++;
        return v_ct;
    }
    else if (active == true && pulseIndex == pulseLengthInSamples)
    {
        // reset index and turn active state to false
        pulseIndex = 0;
        active = false;

        // return zero output
        return 0.0f;
    }
    else
    {
        // trigger pulse is not active therefore return zero output
        return 0.0f;
    }
}
