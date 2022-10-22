/*
  ==============================================================================

    SynthVoice.h
    Created: 8 Aug 2022 10:49:34am
    Author:  tempp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "AdsrData.h"
#include "OscData.h"

class SynthVoice : public juce::SynthesiserVoice 
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity,juce::SynthesiserSound *sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock,int outputChannels);
    void updateSin(const float attack, const float decay, const float sustain, const float release);
    void updateSqu(const float attack, const float decay, const float sustain, const float release);
    void updateSaw(const float attack, const float decay, const float sustain, const float release);
    void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample,int numSamples) override;
    OscData& getSinOsc() { return sin; };
    OscData& getSquOsc() { return squ; };
    OscData& getSawOsc() { return saw; };
private:
    SinAdsrData sin_adsr;
    SquAdsrData squ_adsr;
    SawAdsrData saw_adsr;
    juce::AudioBuffer<float> synthBuffer;
    bool isPrepared{ false };
    OscData sin;
    OscData squ;
    OscData saw;
    //juce::dsp::Oscillator<float> sine{ [](float x) {return std::sin(x); } };
    //juce::dsp::Oscillator<float> square{ [](float x) {return x < 0.0f ? -1.0f : 1.0f; } };
    //juce::dsp::Oscillator<float> saw{ [](float x) {return x / juce::MathConstants<float>::pi; } };
    juce::dsp::Gain<float> gain;

    // sine wave = return std::sin(x);
    // saw wave = return x / juce::MathConstants<float>::pi;
    // square wave = return x < 0.0f ? -1.0f : 1.0f;

};