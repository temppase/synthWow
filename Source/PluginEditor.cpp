/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthWowAudioProcessorEditor::SynthWowAudioProcessorEditor (SynthWowAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), sin_adsr(audioProcessor.apvts), squ_adsr(audioProcessor.apvts), 
    saw_adsr(audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    // using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
    // oscSelAttachment1 = std::make_unique<ComboBoxAttachment>(audioProcessor.apvts, "OSC1", oscSelector);
    // oscSelAttachment2 = std::make_unique<ComboBoxAttachment>(audioProcessor.apvts, "OSC2", oscSelector);
    sinLabel.setText("Sine", juce::dontSendNotification);
    squLabel.setText("Square", juce::dontSendNotification);
    sawLabel.setText("Saw", juce::dontSendNotification);
    sinLabel.setJustificationType(juce::Justification::centred);
    squLabel.setJustificationType(juce::Justification::centred);
    sawLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(sin_adsr);
    addAndMakeVisible(squ_adsr);
    addAndMakeVisible(saw_adsr);
}

SynthWowAudioProcessorEditor::~SynthWowAudioProcessorEditor()
{
}

//==============================================================================
void SynthWowAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void SynthWowAudioProcessorEditor::resized()
{
    sinLabel.attachToComponent(&sin_adsr, false);
    squLabel.attachToComponent(&squ_adsr, false);
    sawLabel.attachToComponent(&saw_adsr, false);
    sin_adsr.setBounds(getWidth()/2-5,25,getWidth()/2,100);
    squ_adsr.setBounds(getWidth() / 2 - 5, 150, getWidth() / 2, 100);
    saw_adsr.setBounds(getWidth() / 2 - 5, 280, getWidth() / 2, 100);
}

