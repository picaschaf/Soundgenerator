#include "qxtsoundgenerator.h"

#include <QAudioFormat>
#include <QAudioOutput>
#include <QByteArray>
#include <QtEndian>
#include <QBuffer>
#include <QDebug>
#include <qmath.h>


QxtSoundGenerator::QxtSoundGenerator(QObject* parent, int sampleRate, int channelCount, int sampleSize, const QString& codec) :
    QObject(parent)
{
    soundBuffer = new QByteArray();

    format = new QAudioFormat();
    format->setSampleRate(sampleRate);
    format->setChannelCount(channelCount);
    format->setSampleSize(sampleSize);
    format->setCodec(codec);
    format->setByteOrder(QAudioFormat::LittleEndian);
    format->setSampleType(QAudioFormat::UnSignedInt);

    output = new QAudioOutput(*format, this);
    connect(output, SIGNAL(stateChanged(QAudio::State)), this, SLOT(playbackFinished()));

    outputBuffer = new QBuffer(soundBuffer);
    if (outputBuffer->open(QIODevice::ReadOnly) == false) {
        qCritical() << "Invalid operation while opening QBuffer. audio/pcm";
        return;
    }
}

QxtSoundGenerator::~QxtSoundGenerator()
{
    delete soundBuffer;
    delete format;
    delete output;
    delete outputBuffer;
}

/**
  * Adds a specific tone to the playlist.
  *
  * @param amplitude The amplitude of this tone from 0.0 to 1.0
  * @param frequency The tone's frequency in Hz
  * @param msecs     The tone's duration. Minimum is 50 msecs, every value below that will be set to 50 msecs.
  */
void QxtSoundGenerator::appendSound(qreal amplitude, quint16 frequency, quint16 msecs)
{
    msecs = (msecs < 50) ? 50 : msecs;

    QByteArray data(static_cast<int>((msecs / 1000.0f) * format->sampleRate()) * format->channels(), '\0');
    const    int   channelBytes = format->sampleSize() / 8.0;
             int   length       = data.size();
    unsigned char* ptr          = reinterpret_cast<unsigned char*>(data.data());
             qreal phase        = 0.0;
    const    qreal d            = 2.0 * M_PI / format->frequency();
    const    qreal startFreq    = static_cast<qreal>((frequency == 0) ? 0.0 : frequency);
             qreal phaseStep    = d * startFreq;

    while (length) {
        qreal  x     = amplitude * qSin(phase);
        const qint16 value = x * 32767; // 32767 is the max PCM value

        for (int i = 0; i < format->channels(); i++) {
            qToLittleEndian<qint16>(value, ptr);
            ptr += channelBytes;
            length -= channelBytes;
        }

        phase += phaseStep;
    }

    soundBuffer->append(data);
}

/**
  * Plays the current sound buffer. Note, this method is asynchronous.
  */
void QxtSoundGenerator::play()
{
    output->start(outputBuffer);
}

/**
  * Internal, currently unused slot when the sound output's state changes, ie. Idle (stop).
  */
void QxtSoundGenerator::playbackFinished()
{
    if (output->state() == QAudio::IdleState) {
        //qDebug() << "Playback finished";
    }
}

/**
  * A static function to simply play a single tone.
  *
  * @todo Fix the memory leak
  */
void QxtSoundGenerator::playSound(qreal amplitude, quint16 frequency, quint16 msecs)
{
    QxtSoundGenerator* generator = new QxtSoundGenerator();
    generator->appendSound(amplitude, frequency, msecs);
    generator->play();
}
