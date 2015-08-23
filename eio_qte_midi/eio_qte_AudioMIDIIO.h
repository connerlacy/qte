#ifndef EIO_QTE_AUDIOMIDIIO_H
#define EIO_QTE_AUDIOMIDIIO_H

#include <QObject>
#include <QDebug>
#include "JuceHeader.h"

class AudioMIDIIO : public QObject,
                    public AudioDeviceManager
{
    Q_OBJECT
public:
    explicit AudioMIDIIO(QObject *parent = 0);

    void pollDevices();

signals:

public slots:
    void slot_AddMIDIInputCallback(const String &midiInputDeviceName, MidiInputCallback *callback);
    void slot_OutputMIDIMessage(QString outputDeviceName, MidiMessage message);
};

#endif // EIO_QTE_AUDIOMIDIIO_H
