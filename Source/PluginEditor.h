/*
  ==============================================================================

    "PluginEditor.h"
    Roland TR-808 Virtual Analogue Modelling - MSc Project
    
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237
    

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUIComponents/Background.h"
#include "GUIComponents/CustomDial.h"

//==============================================================================
/**
*/
class VA808BassDrumAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    VA808BassDrumAudioProcessorEditor (VA808BassDrumAudioProcessor&);
    ~VA808BassDrumAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    VA808BassDrumAudioProcessor& audioProcessor;


    Background background;

    CustomDial level;

    CustomDial tone;

    CustomDial decay;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VA808BassDrumAudioProcessorEditor)

};
