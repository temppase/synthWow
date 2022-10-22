/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SynthWowAudioProcessor::SynthWowAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),apvts(*this,nullptr,"Params",createParams())
#endif
{
    synth.addSound(new SynthSound());
    synth.addVoice(new SynthVoice());
    // in the processor constructor after the parameters are added:
    //aSin = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("A_SIN"));
    //dSin = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("D_SIN"));
    //sSin = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("S_SIN"));
    //rSin = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("R_SIN"));
    //aSqu = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("A_SQU"));
    //dSqu = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("D_SQU"));
    //sSqu = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("S_SQU"));
    //rSqu = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("R_SQU"));
    //aSaw = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("A_SAW"));
    //dSaw = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("D_SAW"));
    //sSaw = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("S_SAW"));
    //rSaw = dynamic_cast<juce::AudioParameterFloat*>(apvts.getParameter("R_SAW"));
    //jassert(aSin, dSin, sSin, rSin, aSqu, dSqu, sSqu, rSqu, aSaw, dSaw, sSaw, rSaw);
    //auto& foo = aSin->get();
}

SynthWowAudioProcessor::~SynthWowAudioProcessor()
{
}

//==============================================================================
const juce::String SynthWowAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SynthWowAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SynthWowAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SynthWowAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SynthWowAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SynthWowAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SynthWowAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SynthWowAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SynthWowAudioProcessor::getProgramName (int index)
{
    return {};
}

void SynthWowAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SynthWowAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    synth.setCurrentPlaybackSampleRate(sampleRate);
    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i))) 
        {
            voice->prepareToPlay(sampleRate,samplesPerBlock,getTotalNumOutputChannels());
        }
    }
}

void SynthWowAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SynthWowAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void SynthWowAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int i = 0; i < synth.getNumVoices(); i++)
    {
        if (auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
        {

            // osc control, ADSR, LFO...
			auto& a_sin = *apvts.getRawParameterValue("A_SIN");
		    auto& d_sin = *apvts.getRawParameterValue("D_SIN");
		    auto& s_sin = *apvts.getRawParameterValue("S_SIN");
		    auto& r_sin = *apvts.getRawParameterValue("R_SIN");
		    auto& a_squ = *apvts.getRawParameterValue("A_SQU");
		    auto& d_squ = *apvts.getRawParameterValue("D_SQU");
		    auto& s_squ = *apvts.getRawParameterValue("S_SQU");
		    auto& r_squ = *apvts.getRawParameterValue("R_SQU");
		    auto& a_saw = *apvts.getRawParameterValue("A_SAW");
		    auto& d_saw = *apvts.getRawParameterValue("D_SAW");
		    auto& s_saw = *apvts.getRawParameterValue("S_SAW");
		    auto& r_saw = *apvts.getRawParameterValue("R_SAW");
            auto& fmDepth = *apvts.getRawParameterValue("FMDEPTH");
            auto& fmFreq = *apvts.getRawParameterValue("FMFREQ");
            voice->getSinOsc().setWaveTypeSin();
            voice->getSquOsc().setWaveTypeSqu();
            voice->getSawOsc().setWaveTypeSaw();
            voice->getSinOsc().setFmParam(fmDepth,fmFreq);
		    voice->updateSin(a_sin.load(), d_sin.load(), s_sin.load(), r_sin.load());
		    voice->updateSqu(a_squ.load(), d_squ.load(), s_squ.load(), r_squ.load());
		    voice->updateSaw(a_saw.load(), d_saw.load(), s_saw.load(), r_saw.load());
            
        }
    }
    /*for (const juce::MidiMessageMetadata metadata : midiMessages)
        if (metadata.numBytes == 3)
            juce::Logger::writeToLog("TimeStamp: " + juce::String(metadata.getMessage().getTimeStamp()));*/
    synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool SynthWowAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SynthWowAudioProcessor::createEditor()
{
    return new SynthWowAudioProcessorEditor (*this);
}

//==============================================================================
void SynthWowAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SynthWowAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SynthWowAudioProcessor();
}
juce::AudioProcessorValueTreeState::ParameterLayout SynthWowAudioProcessor::createParams() 
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // OSC
    // params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC1", "Oscillator1", juce::StringArray{ "Sine","Saw","Square" }, 0));
    // params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC2", "Oscillator2", juce::StringArray{ "Sine","Saw","Square" }, 0));
    // FM

    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMFREQ", "FmFreq", juce::NormalisableRange<float>{0.0f, max}, 0.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("FMDEPTH", "FmDepth", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    // Sin ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("A_SIN", "A_sin", juce::NormalisableRange<float>{0.1f, 1.0f},0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("D_SIN", "D_sin", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("S_SIN", "S_sin", juce::NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("R_SIN", "R_sin", juce::NormalisableRange<float>{0.1f, 3.0f}, 0.1f));
    // Squ ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("A_SQU", "A_squ", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("D_SQU", "D_squ", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("S_SQU", "S_squ", juce::NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("R_SQU", "R_squ", juce::NormalisableRange<float>{0.1f, 3.0f}, 0.1f));
    // Saw ADSR
    params.push_back(std::make_unique<juce::AudioParameterFloat>("A_SAW", "A_saw", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("D_SAW", "D_saw", juce::NormalisableRange<float>{0.1f, 1.0f}, 0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("S_SAW", "S_saw", juce::NormalisableRange<float>{0.1f, 1.0f}, 1.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("R_SAW", "R_saw", juce::NormalisableRange<float>{0.1f, 3.0f}, 0.1f));

    return { params.begin(),params.end() };
}