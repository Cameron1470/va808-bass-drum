/*
  ==============================================================================

    "CustomDial.h"
    Part of: Roland TR-808 Virtual Analogue Modelling - MSc Project
    Created: 15th July 2021
    Author:  Cameron Smith, UoE s1338237

    A custom dial, component class that mimics the style of the knobs on the 
    TR-808. Can be initialized with different names and colours to avoid
    repetition of code
  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos, float rotaryStartAngle, float rotaryEndAngle, juce::Slider& slider) override
    {
        float diameter = width;
        float outerCircle = diameter * 0.6f;
        float middleCircle = diameter * 0.5f;
        float innerCircle = diameter * 0.4f;

        float centreX = x + width / 2;
        float centreY = y + height / 2;
 


        juce::Rectangle<int> dialArea(x, y, width, height);

        

        g.setColour(juce::Colour(6, 5, 13));
        g.fillEllipse(centreX - outerCircle / 2, centreY - outerCircle / 2, outerCircle, outerCircle);

        juce::ColourGradient middleGrad{ juce::Colour(21, 20, 25), centreX - middleCircle / 2.0f, centreY + middleCircle / 2.0f, juce::Colour(74, 74, 76), centreX, centreY, false };
        g.setGradientFill(middleGrad);
        g.fillEllipse(centreX - middleCircle / 2, centreY - middleCircle / 2, middleCircle, middleCircle);

        juce::ColourGradient innerGrad{ juce::Colour(100, 100, 100), centreX - innerCircle / 2.0f, centreY + innerCircle / 2.0f, dialColour, centreX, centreY, false };

        g.setGradientFill(innerGrad);
        g.fillEllipse(centreX - innerCircle / 2.0f, centreY - innerCircle / 2.0f, innerCircle, innerCircle);
        
        float angle = rotaryStartAngle + (sliderPos * (rotaryEndAngle - rotaryStartAngle));

        float radius = width / 2.0f;

        juce::Path indicatorTick;
        g.setColour(juce::Colours::black);
        indicatorTick.addRectangle(-2.0f, -innerCircle / 2.0f, 4.0f, innerCircle / 4.0f);

        g.fillPath(indicatorTick, juce::AffineTransform::rotation(angle).translated(centreX , centreY ));

        juce::Path outerTick;
        g.setColour(juce::Colour(242, 226, 139));
        outerTick.addRectangle(-1.0f, -radius * 0.8, 2.0f, radius * 0.15);

        for (float outAngle = rotaryStartAngle; outAngle <= rotaryEndAngle; outAngle = outAngle + 2.0f * 3.141592f / 10.0f)
        {
            g.fillPath(outerTick, juce::AffineTransform::rotation(outAngle).translated(centreX, centreY));
        }

    }

    void setDialColour(juce::Colour _dialColour)
    {
        dialColour = _dialColour;
    }

private:
    juce::Colour dialColour;

};

//==============================================================================
/*
*/
class CustomDial  : public juce::Component
{
public:
    CustomDial(juce::String dialName, juce::Colour dialColour, juce::AudioProcessorValueTreeState& parameters, juce::String paramID);
    ~CustomDial() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    using SliderStyle = juce::Slider::SliderStyle;

private:
    // dial component
    juce::Slider dial;

    // custom visual look, defined in the class above
    CustomLookAndFeel customLook;

    // label for describing the purpose of the dial
    juce::Label label;

    std::unique_ptr<SliderAttachment> attachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomDial)
};
