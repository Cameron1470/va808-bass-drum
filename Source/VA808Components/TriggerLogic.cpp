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

#define M_PI 3.141592653589793238462643383279f




void TriggerLogic::updateSampleRate(float _sampleRate)
{
    
    // update sample rate
    sampleRate = _sampleRate;

    // updating pulse length in samples by mulptiplying 1ms time duration and sample rate
    pulseLengthInSamples = round(pulseLengthInSeconds * sampleRate);

    // update envelope length in samples by multiplying 5ms time duration and sample rate
    envLengthInSamples = round(pulseLengthInSeconds * sampleRate);

    // calculating a tail length for the envelope decay
    int tailLength = round(0.00125f * sampleRate);

    // calculating the total length of the envelope, main pulse and tail
    float totalLength = envLengthInSamples + tailLength;

    // creating a temporary vector for storing the pulse 
    std::vector<float> envelope;
    envelope.resize(totalLength);

    // resizing envelope vector with total sample length
    v_env.resize(totalLength);

    // initializing previous value variable, v_env(n-1)
    float v_envPrev = 0;

    //=================================================
    // FILTERING THE PULSE (RISE)

    // setting first cutoff value
    float cutoffFreq = 550.0f * M_PI;

    // precomputing difference equation coefficient
    float alpha = (cutoffFreq / sampleRate) / (1 + cutoffFreq / sampleRate);

    // performing first low pass filtering on the body of the pulse to achieve a rise
    for (int n = 0; n < envLengthInSamples; n++)
    {
        envelope[n] = envAmp;
        envelope[n] = alpha * envelope[n] + (1.0f - alpha) * v_envPrev;
        v_envPrev = envelope[n];
        v_env[n] = envelope[n];
    }

    //=================================================
    // FILTERING THE PULSE (FALL/DECAY)

    // setting new cutoff value
    cutoffFreq = 1400.0f * M_PI;
    
    // updating difference coefficient
    alpha = (cutoffFreq / sampleRate) / (1.0f + cutoffFreq / sampleRate);

    // performing second low pass filtering on the tail of the pulse to shape the decay
    for (int n = envLengthInSamples; n < totalLength; n++)
    {
        envelope[n] = 0;
        envelope[n] = alpha * envelope[n] + (1.0f - alpha) * v_envPrev;
        v_envPrev = envelope[n];

        int index = 2 * envLengthInSamples - n + tailLength;

        v_env[index] = 0.05f + envAmp - envelope[n];

    }

}

void TriggerLogic::setTriggerActive(float velocity)
{
    // check if trigger is not already active, if it is then nothing happens. too quick!
    if (envActive != true)
    {
        // if trigger is not active, make it so
        pulseActive = true;
        envActive = true;


        // update the common trigger signal amplitude (4-14V)
        v_ct = 4.0f + (velocity * 10.0f);
    }
}

float TriggerLogic::triggerProcess()
{
    if (pulseActive == true && pulseIndex < pulseLengthInSamples)
    {
        // currently active, increment index and return trigger signal amplitude
        pulseIndex++;
        return v_ct;
    }
    else if (pulseActive == true && pulseIndex >= pulseLengthInSamples)
    {
        // reset index and turn active state to false
        pulseIndex = 0;
        pulseActive = false;

        // return zero output
        return 0.0f;
    }
    else
    {
        // trigger pulse is not active therefore return zero output
        return 0.0f;
    }
}

float TriggerLogic::envProcess()
{
    if (envActive && envIndex < envLengthInSamples)
    {
        // currently active, increment index and return envelope amplitude for current index
        envIndex++;
        return v_env[envIndex-1];
    }
    else if (envActive && envIndex >= envLengthInSamples)
    {
        // reset index and turn active state to false
        envIndex = 0;
        envActive = false;

        // return zero output
        return 0.0f;
    }
    else
    {
        // envelope is not active therefore return zero output
        return 0.0f;
    }
}
