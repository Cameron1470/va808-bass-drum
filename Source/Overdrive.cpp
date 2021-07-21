/*
  ==============================================================================

    "Overdrive.h"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 21th July 2021
    Author:  Cameron Smith, UoE s1338237

    ----------------------see header file for description-----------------------
  ==============================================================================
*/

#include "Overdrive.h"
#include <math.h>

void Overdrive::setSampleRate(float SR)
{
    float timeStep = 1.0f / SR;

    A = -1.0f / (resistance * capacitance);
    B = 1.0f / (resistance * capacitance);
    C = -1.0f / capacitance;

    Ha = 1.0f / (2.0f / timeStep - A);
    Hb = 2.0f / timeStep + A;
    K = D * Ha * C + F;
    G = 2.0f * satCurrent / (diodeIdealityFac * diodeThermalVoltage);

    float p = D * Ha * (Hb * xPrev + B * uPrev + C * iPrev);
    v = p / (1.0f - K * G);
}

float Overdrive::process(float input)
{
    float p = D * Ha * (Hb * xPrev + B * uPrev + C * iPrev) + (D * Ha * B + E) * input;

    //if (firstSamp)
    //{
    //    v = p / (1.0f - K * G);
    //    firstSamp = false;
    //}
    
    float eps = 1.0f;
    int iter = 0;

    while (eps > tolerance && maxIterations > iter)
    {
        float g = p + K * satCurrent * (expf(v / (2.0f * diodeIdealityFac * diodeThermalVoltage)) - expf(-v / (diodeIdealityFac * diodeThermalVoltage))) - v;

        float J = K * satCurrent / (diodeIdealityFac * diodeThermalVoltage) * (0.5f * expf(v / (2.0f * diodeIdealityFac * diodeThermalVoltage)) + expf(-v / (diodeIdealityFac * diodeThermalVoltage))) - 1.0f;

        float vnew = v - (g / J);
        eps = fabsf(vnew - v);
        v = vnew;
        iter++;
    }

    float i0 = satCurrent * (expf(v / (2.0f * diodeIdealityFac * diodeThermalVoltage)) - expf(-v / (diodeIdealityFac * diodeThermalVoltage)));
    float x0 = Ha * (Hb * xPrev + B * (input + uPrev) + C * (i0 + iPrev));

    iPrev = i0;
    uPrev = input;
    xPrev = x0;

    return v;

}
