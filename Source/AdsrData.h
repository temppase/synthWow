/*
  ==============================================================================

    AdsrData.h
    Created: 12 Aug 2022 12:41:22pm
    Author:  tempp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SinAdsrData : public juce::ADSR
{
public:
    void updateSinADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams;
    
};
class SquAdsrData : public juce::ADSR
{
public:
    void updateSquADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams;

};
class SawAdsrData : public juce::ADSR
{
public:
    void updateSawADSR(const float attack, const float decay, const float sustain, const float release);
private:
    juce::ADSR::Parameters adsrParams;

};