/*
  ==============================================================================

    Background.h
    Created: 15 Jul 2021 2:16:00pm
    Author:  csmit

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class Background  : public juce::Component
{
public:
    Background();
    ~Background() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // two font sizes, large and small
    juce::Font extraLargeFont{ 35.0f };
    juce::Font bigFont{ 24.0f };
    juce::Font smallFont{ 12.0f };
    
    juce::Label B{ {}, "B" };
    juce::Label ass{ {}, "ASS" };
    juce::Label D{ {}, "D" };
    juce::Label rum{ {}, "RUM" };

    juce::Label labelOne{ {}, "TR-808 BD" };
    juce::Label labelTwo{ {}, "Virtual Analogue Model" };
    juce::Label labelAuthor{ {}, "by Cameron Smith" };
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Background)
};
