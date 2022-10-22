/*
  ==============================================================================

    SynthVoice.cpp
    Created: 8 Aug 2022 10:49:34am
    Author:  tempp

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    sin.setWaveFrequency(midiNoteNumber);
    squ.setWaveFrequency(midiNoteNumber);
    saw.setWaveFrequency(midiNoteNumber);
    sin_adsr.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    sin_adsr.noteOff();
    if (! allowTailOff || !sin_adsr.isActive())
    {
        clearCurrentNote();
    }
}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock,int outputChannels)
{
    sin_adsr.setSampleRate(sampleRate);
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    sin.prepare(spec);
    squ.prepare(spec);
    saw.prepare(spec);
    gain.prepare(spec);
    gain.setGainDecibels(-30.0f);
    
    
    isPrepared = true;
}
void SynthVoice::updateSin(const float attack, const float decay, const float sustain, const float release) 
{
    sin_adsr.updateSinADSR(attack,decay,sustain,release);
}
void SynthVoice::updateSqu(const float attack, const float decay, const float sustain, const float release)
{
    squ_adsr.updateSquADSR(attack, decay, sustain, release);
}
void SynthVoice::updateSaw(const float attack, const float decay, const float sustain, const float release)
{
    saw_adsr.updateSawADSR(attack, decay, sustain, release);
}
void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(isPrepared);
    if (! isVoiceActive())
    {
        return;
    }
    synthBuffer.setSize(outputBuffer.getNumChannels(),numSamples,false,false,true);
    synthBuffer.clear();
    juce::dsp::AudioBlock<float> audioBlock{ synthBuffer};
    sin.getNextAudioBlock(audioBlock);
    squ.getNextAudioBlock(audioBlock);
    saw.getNextAudioBlock(audioBlock);
    gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
    sin_adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());
    //if (startSample != 0)
    //{
    //    jassertfalse;
    //}
    for (int channel = 0; channel < outputBuffer.getNumChannels(); channel++)
    {
        outputBuffer.addFrom(channel,startSample,synthBuffer,channel,0,numSamples);
        if (! sin_adsr.isActive() && !squ_adsr.isActive())
        {
            clearCurrentNote();
        }
    }
}
