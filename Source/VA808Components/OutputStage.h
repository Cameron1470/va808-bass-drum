/*
  ==============================================================================

    OutputStage.h
    Created: 25 Jun 2021 3:01:29pm
    Author:  csmit

  ==============================================================================
*/

#pragma once

class OutputStage
{
public:
    
    //--------------------------------------------------------------------------
    /**
    Updates sample rate in the class private variables,

    Subsequently updates the discrete transfer function coefficients
    
    @param sample rate in Hz
    */
    void setSampleRate(float SR);

    //--------------------------------------------------------------------------
    /**
    Get current sample of the output process block
    */
    float process(float v_to);

private:

    /// sampling frequency in Hz
    float sampleRate = 0.0f;

    /// value of capacitor C49 (0.47 microF)
    float c49 = 4.7e-7;

    /// value of resistor R176 (100 kOhms)
    float r176 = 1.0e5;

    /// value of resistor R177 (82 kOhms)
    float r177 = 8.2e4;

    /// coefficients of the discretized transfer function for outut stage
    float A0 = 0.0f;
    float B0 = 0.0f;
    float B1 = 0.0f;
    float A1 = 0.0f;

    /// previous sample of input, v_lev(n-1)
    float v_levPrev1 = 0.0f;

    /// previous sample of output, v_out(n-1)
    float v_outPrev1 = 0.0f;

};