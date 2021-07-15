/*
  ==============================================================================

    CustomDial.cpp
    Created: 15 Jul 2021 5:00:07pm
    Author:  csmit

  ==============================================================================
*/

#include <JuceHeader.h>
#include "CustomDial.h"

//==============================================================================
CustomDial::CustomDial(juce::String dialName, juce::Colour dialColour)
{
    setSize(100, 105);
    addAndMakeVisible(dial);
    dial.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    dial.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    
    customLook.setDialColour(dialColour);

    dial.setLookAndFeel(&customLook);

    label.setText(dialName, juce::NotificationType::dontSendNotification);

    addAndMakeVisible(label);
    label.setJustificationType(juce::Justification::centred);
    label.setColour(juce::Label::textColourId, juce::Colour(242, 226, 139));

}

CustomDial::~CustomDial()
{
}

void CustomDial::paint (juce::Graphics& g)
{
    //g.fillAll(juce::Colours::white);
}

void CustomDial::resized()
{
    dial.setBounds(10, 25, 80, 80);
    label.setBounds(10, 10, 80, 15);

}
