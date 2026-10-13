#ifndef SOUNDGENERATOR_H
#define SOUNDGENERATOR_H

#include <QObject>
#include <QString>

class QAudioFormat;
class QAudioSink;
class QBuffer;

/**
 * Platform-independent simple PCM tone generator and player.
 *
 * Use appendSound() / appendPause() to build a continuous buffer, then play().
 * The SoundGenerator instance must outlive asynchronous playback.
 *
 * For a single tone, use the static playSound() helper.
 */
class SoundGenerator : public QObject
{
    Q_OBJECT

public:
    explicit SoundGenerator(QObject *parent = nullptr,
                            int sampleRate = 8000,
                            int channelCount = 1);
    ~SoundGenerator() override;

    /**
     * Appends a sine tone to the buffer.
     *
     * \param amplitude Amplitude in [0.0, 1.0]
     * \param frequency Frequency in Hz; 0 delegates to appendPause()
     * \param msecs     Duration in milliseconds (minimum 50)
     */
    void appendSound(qreal amplitude, quint16 frequency, quint32 msecs);

    /**
     * Appends digital silence for the given duration.
     */
    void appendPause(quint32 msecs);

    /** Clears the sound buffer. */
    void clear() { soundBuffer->clear(); }

    /** Starts asynchronous playback of the current buffer. */
    void play();

    /** Plays a single tone using a shared helper instance. */
    static void playSound(qreal amplitude, quint16 frequency, quint32 msecs);

private:
    static SoundGenerator *sharedInstance();

    QByteArray *soundBuffer;
    QBuffer *outputBuffer;
    QAudioFormat *format;
    QAudioSink *output;

private slots:
    void playbackFinished();
};

#endif // SOUNDGENERATOR_H
