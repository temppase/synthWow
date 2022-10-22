/*
  ==============================================================================

    OscData.cpp
    Created: 13 Oct 2022 3:08:18pm
    Author:  tempp

  ==============================================================================
*/

#include "OscData.h"
void OscData::prepareToPlay(juce::dsp::ProcessSpec spec)
{
    fmOsc.prepare(spec);
    prepare(spec);
}
void OscData::setWaveTypeSin()
{
	initialise([](float x) {return std::sin(x); });
}
void OscData::setWaveTypeSqu()
{
    initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
}
void OscData::setWaveTypeSaw()
{
    initialise([](float x) {return x / juce::MathConstants<float>::pi; });
}
void OscData::setWaveFrequency(const int midiNoteNumber)
{
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
    lastMidiNote = midiNoteNumber;
}
void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
    for (int ch = 0; ch < block.getNumChannels(); ch++)
    {
        for (int s = 0; s < block.getNumSamples(); s++)
        {
            fmMod = fmOsc.processSample(block.getSample(ch, s)*fmDepth);
        }
    }
    process(block);
}

void OscData::setFmParam(const float depth, const float freq)
{
    fmOsc.setFrequency(freq);
    fmDepth = depth;
    setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
}
