/*
  ==============================================================================

    SawAdsrComponent.cpp
    Created: 13 Oct 2022 10:37:41am
    Author:  tempp

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SawAdsrComponent.h"

//==============================================================================
SawAdsrComponent::SawAdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
    // Slider attachments

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    attackAttachment = std::make_unique<SliderAttachment>(apvts, "A_SAW", attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts, "D_SAW", decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "S_SAW", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "R_SAW", decaySlider);
    setSliderParams(attackSlider);
    setSliderParams(decaySlider);
    setSliderParams(sustainSlider);
    setSliderParams(releaseSlider);
    // Colors
    lf_a.setColour(juce::Slider::thumbColourId, juce::Colours::darkred);
    lf_d.setColour(juce::Slider::thumbColourId, juce::Colours::darkmagenta);
    lf_s.setColour(juce::Slider::thumbColourId, juce::Colours::blue);
    lf_r.setColour(juce::Slider::thumbColourId, juce::Colours::lightseagreen);
    getLookAndFeel().setColour(juce::TextEditor::highlightColourId, juce::Colours::black);
    attackSlider.setLookAndFeel(&lf_a);
    decaySlider.setLookAndFeel(&lf_d);
    sustainSlider.setLookAndFeel(&lf_s);
    releaseSlider.setLookAndFeel(&lf_r);
    // Labels
    attackLabel.setText("Attack", juce::dontSendNotification);
    decayLabel.setText("Decay", juce::dontSendNotification);
    sustainLabel.setText("Sustain", juce::dontSendNotification);
    releaseLabel.setText("Release", juce::dontSendNotification);
    attackLabel.setJustificationType(juce::Justification::centred);
    decayLabel.setJustificationType(juce::Justification::centred);
    sustainLabel.setJustificationType(juce::Justification::centred);
    releaseLabel.setJustificationType(juce::Justification::centred);

}

SawAdsrComponent::~SawAdsrComponent()
{
}

void SawAdsrComponent::paint (juce::Graphics& g)
{

    juce::Image image(juce::Image::ARGB, getWidth(), getHeight(), true);
    juce::Graphics tg(image);

    juce::Colour salmon(juce::Colours::darksalmon);
    juce::Colour grey(juce::Colours::darkgrey);
    juce::ColourGradient cg = juce::ColourGradient::vertical(salmon.darker(0.5), 10, grey.darker(0.7), getHeight());
    tg.setGradientFill(cg);
    tg.fillAll();
    g.drawImage(image, getLocalBounds().toFloat());
}

void SawAdsrComponent::resized()
{
    const auto bounds = getLocalBounds();
    const auto padding = 7;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = 80;
    const auto sliderStartX = 0;
    const auto sliderStartY = 20;
    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    // Labels
    attackLabel.attachToComponent(&attackSlider, false);
    decayLabel.attachToComponent(&decaySlider, false);
    sustainLabel.attachToComponent(&sustainSlider, false);
    releaseLabel.attachToComponent(&releaseSlider, false);

}
void SawAdsrComponent::setSliderParams(juce::Slider& slider)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 55, 25);
    addAndMakeVisible(slider);
}
