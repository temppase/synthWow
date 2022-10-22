/*
  ==============================================================================

    OscData.h
    Created: 13 Oct 2022 3:08:18pm
    Author:  tempp

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class OscData : public juce::dsp::Oscillator<float> 
{
public:
    void prepareToPlay(juce::dsp::ProcessSpec spec);
    void setWaveTypeSin();
    void setWaveTypeSqu();
    void setWaveTypeSaw();
    void setWaveFrequency(const int midiNoteNumber);
    void getNextAudioBlock(juce::dsp::AudioBlock<float>& block);
    void setFmParam(const float depth, const float freq);
    
private:
    juce::dsp::Oscillator<float> fmOsc{ [] ( float x) {return std::sin(x); }  };
    float fmMod{ 0.0f };
    float fmDepth{ 0.0f };
    int lastMidiNote{ 0 };
};