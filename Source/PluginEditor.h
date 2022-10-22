/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "SinAdsrComponent.h"
#include "SquAdsrComponent.h"
#include "SawAdsrComponent.h"
//==============================================================================
/**
*/
class SynthWowAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SynthWowAudioProcessorEditor (SynthWowAudioProcessor&);
    ~SynthWowAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    //void setSliderParams(juce::Slider& slider)
    // juce::ComboBox oscSelector;
    
    // using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    // std::unique_ptr<ComboBoxAttachment> oscSelAttachment1;
    // std::unique_ptr<ComboBoxAttachment> oscSelAttachment2;
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    SynthWowAudioProcessor& audioProcessor;
    SinAdsrComponent sin_adsr;
    SquAdsrComponent squ_adsr;
    SawAdsrComponent saw_adsr;
    juce::Label  sinLabel;
    juce::Label  squLabel;
    juce::Label  sawLabel;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthWowAudioProcessorEditor)
};
