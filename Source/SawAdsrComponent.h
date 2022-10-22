/*
  ==============================================================================

    SawAdsrComponent.h
    Created: 13 Oct 2022 10:37:41am
    Author:  tempp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class SawAdsrComponent  : public juce::Component
{
public:
    SawAdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~SawAdsrComponent() override;

    void paint(juce::Graphics&) override;
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SawAdsrComponent)
};
