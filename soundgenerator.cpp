#include "soundgenerator.h"

#include <QAudioFormat>
#include <QAudioSink>
#include <QBuffer>
#include <QByteArray>
#include <QDebug>
#include <QMediaDevices>
#include <QtEndian>
#include <QtMath>

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

SoundGenerator::SoundGenerator(QObject *parent, int sampleRate, int channelCount)
    : QObject(parent)
{
    soundBuffer = new QByteArray();

    format = new QAudioFormat();
    format->setSampleRate(sampleRate);
    format->setChannelCount(channelCount);
    format->setSampleFormat(QAudioFormat::Int16);

    output = new QAudioSink(QMediaDevices::defaultAudioOutput(), *format, this);
    connect(output, &QAudioSink::stateChanged, this, &SoundGenerator::playbackFinished);

    outputBuffer = new QBuffer(soundBuffer);
    if (!outputBuffer->open(QIODevice::ReadOnly)) {
        qCritical() << "Failed to open QBuffer for audio playback";
    }
}

SoundGenerator::~SoundGenerator()
{
    if (output) {
        output->stop();
    }

    delete outputBuffer;
    delete soundBuffer;
    delete format;
    // output is parented to this and deleted by QObject
}

void SoundGenerator::appendSound(qreal amplitude, quint16 frequency, quint32 msecs)
{
    if (frequency == 0) {
        appendPause(msecs);
        return;
    }

    amplitude = qBound(0.0, amplitude, 1.0);
    msecs = qMax(msecs, 50u);

    const qreal singleWaveTime = 1.0 / frequency;
    const qreal samplesPerWave = qCeil(format->sampleRate() * singleWaveTime);
    const quint32 waveCount = qCeil(msecs / (singleWaveTime * 1000.0));
    const int bytesPerSample = format->bytesPerSample();
    const qreal peak = amplitude * 32767.0;

    QByteArray data(static_cast<int>(waveCount * samplesPerWave * bytesPerSample * format->channelCount()),
                    '\0');
    unsigned char *dataPointer = reinterpret_cast<unsigned char *>(data.data());

    for (quint32 currentWave = 0; currentWave < waveCount; ++currentWave) {
        for (int currentSample = 0; currentSample < samplesPerWave; ++currentSample) {
            const double nextRadStep =
                (currentSample / static_cast<double>(samplesPerWave)) * (2.0 * M_PI);
            const qint16 sampleValue = static_cast<qint16>(qSin(nextRadStep) * peak);

            for (int channel = 0; channel < format->channelCount(); ++channel) {
                qToLittleEndian(sampleValue, dataPointer);
                dataPointer += bytesPerSample;
            }
        }
    }

    soundBuffer->append(data);
}

void SoundGenerator::appendPause(quint32 msecs)
{
    const int byteCount = static_cast<int>(format->sampleRate() * (msecs / 1000.0)
                                           * format->channelCount() * format->bytesPerSample());
    soundBuffer->append(QByteArray(byteCount, '\0'));
}

void SoundGenerator::play()
{
    outputBuffer->seek(0);
    output->start(outputBuffer);
}

void SoundGenerator::playbackFinished()
{
    if (output->state() == QAudio::IdleState) {
        // Playback finished; hook reserved for future use.
    }
}

SoundGenerator *SoundGenerator::sharedInstance()
{
    static SoundGenerator instance;
    return &instance;
}

void SoundGenerator::playSound(qreal amplitude, quint16 frequency, quint32 msecs)
{
    SoundGenerator *helper = sharedInstance();
    helper->clear();
    helper->appendSound(amplitude, frequency, msecs);
    helper->play();
}
