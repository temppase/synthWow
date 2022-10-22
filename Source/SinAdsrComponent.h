/*
  ==============================================================================

    AdsrComponent.h
    Created: 12 Aug 2022 12:04:34pm
    Author:  tempp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SinAdsrComponent  : public juce::Component
{
public:
    SinAdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~SinAdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

    

private:
    void setSliderParams(juce::Slider& slider);
    juce::LookAndFeel_V4 lf_a;
    juce::LookAndFeel_V4 lf_d;
    juce::LookAndFeel_V4 lf_s;
    juce::LookAndFeel_V4 lf_r;
    // juce::LookAndFeel_V4 lf_tb;
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    juce::Label  attackLabel;
    juce::Label  decayLabel;
    juce::Label  sustainLabel;
    juce::Label  releaseLabel;
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SinAdsrComponent)

};
