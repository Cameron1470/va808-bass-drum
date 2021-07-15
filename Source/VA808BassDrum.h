/*
  ==============================================================================

    "VA808BassDrum.h"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 15th July 2021
    Author:  Cameron Smith, UoE s1338237

    Class used for compartmentalizing the virtual analogue model of the TR-808
    bass drum. Added to allow for flexibility and ease of transportation for use
    in other environments.

  ==============================================================================
*/

#pragma once

#include "VA808Components/TriggerLogic.h"
#include "VA808Components/PulseShaper.h"
#include "VA808Components/RetriggeringPulse.h"
#include "VA808Components/BridgedTNetwork.h"
#include "VA808Components/FeedbackBuffer.h"
#include "VA808Components/ToneStage.h"
#include "VA808Components/LevelStage.h"
#include "VA808Components/OutputStage.h"

class VA808BassDrum
{
public:
    void setSampleRate(float sampleRate);
    
    void activate(float velocity);

    float process();

private:
    /// Instance of the TriggerLogic class for the trigger logic process block
    TriggerLogic triggerLogic;

    /// Instance of the PulseShaper class for the pulse shaper process block
    PulseShaper pulseShaper;

    /// Instance of the RetriggeringPulse class for the retriggering pulse process block
    RetriggeringPulse retriggeringPulse;

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
};