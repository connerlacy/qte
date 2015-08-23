#include "eio_qte_AudioMIDIIO.h"

AudioMIDIIO::AudioMIDIIO(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType<MidiMessage>("MidiMessage");

    //Enable all MIDI inputs (should poll repeatedly and enable)
    pollDevices();
}

void AudioMIDIIO::pollDevices()
{
    //Enable all midi inputs (routing handled by callback registration)
    StringArray midiInputDevices = MidiInput::getDevices();

    for(int inputs = 0; inputs < midiInputDevices.size(); inputs++)
    {
        this->setMidiInputEnabled(midiInputDevices[inputs], true);
        //qDebug() << "Input Device Enabled: " << midiInputDevices[inputs].toStdString().c_str() << this->isMidiInputEnabled(midiInputDevices[inputs]);
    }

    StringArray midiOutputDevices = MidiInput::getDevices();
    for(int outputs = 0; outputs < midiOutputDevices.size(); outputs++)
    {
        //this->setMidiInputEnabled(midiOutputDevices[outputs], true);
        //qDebug() << "Output Device: " << midiOutputDevices[outputs].toStdString().c_str();// << this->isMidiInputEnabled(midiOutputDevices[outputs]);
    }
}

void AudioMIDIIO::slot_AddMIDIInputCallback(const String &midiInputDeviceName, MidiInputCallback *callback)
{
    this->addMidiInputCallback(midiInputDeviceName, callback);
}

void AudioMIDIIO::slot_OutputMIDIMessage(QString outputDeviceName, MidiMessage message)
{
    StringRef strR = StringRef(outputDeviceName.toStdString().c_str());
    int index = MidiOutput::getDevices().indexOf(strR);

    if(index > -1)
    {
        MidiOutput *mo = MidiOutput::openDevice(index);
        mo->sendMessageNow(message);
    }

    qDebug() << "output midid message" << index;
}
