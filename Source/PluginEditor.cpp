/*
  ==============================================================================

    "PluginEditor.cpp"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237
    
    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VA808BassDrumAudioProcessorEditor::VA808BassDrumAudioProcessorEditor (VA808BassDrumAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p),
    level("LEVEL", juce::Colour(245, 213, 82)),
    tone("TONE", juce::Colour(245, 243, 252)),
    decay("DECAY", juce::Colour(245, 243, 252))
{
    // set fixed window size
    setSize (327, 400);

    // adding the component class instances to the window
    addAndMakeVisible(background);
    addAndMakeVisible(level);
    addAndMakeVisible(tone);
    addAndMakeVisible(decay);
}

VA808BassDrumAudioProcessorEditor::~VA808BassDrumAudioProcessorEditor()
{
}

//==============================================================================
void VA808BassDrumAudioProcessorEditor::paint (juce::Graphics& g)
{
    

}

void VA808BassDrumAudioProcessorEditor::resized()
{
    
    // setting location of component class instances, first the background then 3 custom dials
    background.setBounds(0, 0, 327, 400);
    level.setBounds(10, 7, 100, 105);
    tone.setBounds(10, 112, 100, 105);
    decay.setBounds(10, 217, 100, 105);

}
