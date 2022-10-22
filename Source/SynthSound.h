/*
  ==============================================================================

    SynthSound.h
    Created: 8 Aug 2022 10:51:01am
    Author:  tempp

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound 
{
public:
    bool appliesToNote(int midiNoteNumber) override { return true; };
    bool appliesToChannel(int midiChannel) override { return true; };

};