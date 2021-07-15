/*
  ==============================================================================

    "PluginEditor.cpp"
    Roland TR-808 Virtual Analogue Modelling - MSc Project
    
    Created: 24th June 2021
    Author:  Cameron Smith, UoE s1338237
    
    
    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
VA808BassDrumAudioProcessorEditor::VA808BassDrumAudioProcessorEditor (VA808BassDrumAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (327, 400);

    addAndMakeVisible(background);
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
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    background.setBounds(0, 0, 327, 400);
}
