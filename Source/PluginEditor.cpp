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
    setSize (400, 300);
}

VA808BassDrumAudioProcessorEditor::~VA808BassDrumAudioProcessorEditor()
{
}

//==============================================================================
void VA808BassDrumAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("TR808 Bass Drum - Virtual Analogue Model", getLocalBounds(), juce::Justification::centred, 1);
}

void VA808BassDrumAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
