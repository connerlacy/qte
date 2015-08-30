#include "eio_qte_MIDIParser.h"

MIDIParserDriver::MIDIParserDriver(QObject *parent) :
    QObject(parent)
{
    parser = (MIDIParser *)parent;
}

//================== Audio Processor Pure Virtual Functions ====================

//----------------------- Initialization / Processing --------------------------

void MIDIParserDriver::prepareToPlay(double sampleRate, int estimatedSamplesPerBlock)
{

}

void MIDIParserDriver::releaseResources()
{

}

void MIDIParserDriver::processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages)
{
    //Clear audio buffer
    buffer.clear();

    MidiMessage message; int samplePosition;
    MidiBuffer::Iterator i(midiMessages);

    while(i.getNextEvent(message, samplePosition))
    {
        parser->parseMidi(message);
    }

    midiMessages.clear();
}


//-------------------------- Processor Properties ------------------------------

const String MIDIParserDriver::getName() const
{
    return "";
}

const String MIDIParserDriver::getInputChannelName (int channelIndex) const
{
    return "";
}

const String MIDIParserDriver::getOutputChannelName (int channelIndex) const
{
    return String("");
}

bool MIDIParserDriver::isInputChannelStereoPair (int index) const
{
    true;
}

bool MIDIParserDriver::isOutputChannelStereoPair (int index) const
{
    true;
}

bool MIDIParserDriver::silenceInProducesSilenceOut() const
{
    true;
}

double MIDIParserDriver::getTailLengthSeconds() const
{
    return 0.0;
}

bool MIDIParserDriver::acceptsMidi() const
{
    return true;
}

bool MIDIParserDriver::producesMidi() const
{
    return true;
}


//----------------------- Audio Processor Editor -------------------------------

AudioProcessorEditor* MIDIParserDriver::createEditor()
{

}

bool MIDIParserDriver::hasEditor() const
{
    return true;
}


//------------------------- Presets (Programs) ---------------------------------

int	MIDIParserDriver::getNumPrograms ()
{

}

int	MIDIParserDriver::getCurrentProgram ()
{

}

void MIDIParserDriver::setCurrentProgram (int index)
{

}

const String MIDIParserDriver::getProgramName (int index)
{

}

void MIDIParserDriver::changeProgramName (int index, const String &newName)
{

}

void MIDIParserDriver::getStateInformation (juce::MemoryBlock &destData)
{

}

void MIDIParserDriver::setStateInformation (const void *data, int sizeInBytes)
{

}


//==============================================================================
//============================ MIDI Sensor Parser ==============================
//==============================================================================
MIDIParser::MIDIParser(QObject *parent) :
    QObject(parent)
{
    midiProcessDriver = new MIDIParserDriver(this);
    setProcessor(midiProcessDriver);
}

MIDIParser::~MIDIParser()
{
    setProcessor(nullptr);
}
