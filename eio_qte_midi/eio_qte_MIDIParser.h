#ifndef EIO_QTE_MIDISENSORPARSER_H
#define EIO_QTE_MIDISENSORPARSER_H

#include <QObject>
#include <QDebug>
#include <JuceHeader.h>

class MIDIParser;

class MIDIParserDriver : public QObject, public AudioProcessor
{
    Q_OBJECT
public:
    explicit MIDIParserDriver(QObject *parent = 0);

    MIDIParser *parser;

    //================ Audio Processor Pure Virtual Functions =================

    //-------------------- Initialization / Processing ------------------------
    void prepareToPlay(double sampleRate, int estimatedSamplesPerBlock);
    void releaseResources();
    void processBlock(AudioSampleBuffer &buffer, MidiBuffer &midiMessages);

    //------------------------- Processor Properties --------------------------
    const String getName() const;
    const String getInputChannelName (int channelIndex) const;
    const String getOutputChannelName (int channelIndex) const;
    bool isInputChannelStereoPair (int index) const;
    bool isOutputChannelStereoPair (int index) const;
    bool silenceInProducesSilenceOut() const;
    double getTailLengthSeconds() const;
    bool acceptsMidi() const;
    bool producesMidi() const;

    //------------------------ Audio Processor Editor -------------------------
    AudioProcessorEditor* createEditor();
    bool hasEditor() const;

    //-------------------------- Presets (Programs) ---------------------------
    int	getNumPrograms ();
    int	getCurrentProgram ();
    void setCurrentProgram (int index);
    const String getProgramName (int index);
    void changeProgramName (int index, const String &newName);
    void getStateInformation (MemoryBlock &destData);
    void setStateInformation (const void *data, int sizeInBytes);
signals:

public slots:

};

//==============================================================================
//============================ MIDI Sensor Parser ==============================
//==============================================================================
class MIDIParser : public QObject, public AudioProcessorPlayer
{
    Q_OBJECT
public:
    explicit MIDIParser(QObject *parent = 0);
    ~MIDIParser();

    MIDIParserDriver *midiProcessDriver; //Processes the audio blocks
    //RecorderDriverParameter recordingParam;

    virtual void parseMidi(MidiMessage& midiMessage)=0;

public slots:

};

#endif // EIO_QTE_MIDISENSORPARSER_H
