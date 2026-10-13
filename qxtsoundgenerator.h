#ifndef QXTSOUNDGENERATOR_H
#define QXTSOUNDGENERATOR_H

#include <QObject>

class QAudioFormat;
class QAudioOutput;
class QBuffer;

/**
  * This class is used to do platform independant simple sound output.
  *
  * appendSound() can be used to build multiple tones in a continous sound. Pauses
  * have to be built with a frequency of 0 Hz. After you finished building up the
  * playlist, you can start playback with play(). The QxtSoundGenerator object must
  * exist until the playback finished because of the asynchronous nature of play().
  *
  * If you just want to play a single frequency you can also use the static method playSound().
  */
class QxtSoundGenerator : public QObject
{
    Q_OBJECT

public:
    explicit QxtSoundGenerator(QObject* parent = 0, int sampleRate = 8000, int channelCount = 1, int sampleSize = 16, const QString& codec = "audio/pcm");
    virtual ~QxtSoundGenerator();

    void appendSound(qreal, quint16, quint32);
    void appendPause(quint32);

    /**
      * \brief Clears the sound buffer.
      */
    void clear() { soundBuffer->clear(); }

    void play();

    static void playSound(qreal, quint16, quint32);

private:
    static QxtSoundGenerator* generatorHelper;

    QByteArray*   soundBuffer;
    QBuffer*      outputBuffer;
    QAudioFormat* format;
    QAudioOutput* output;

private slots:
    void playbackFinished();
};

#endif // QXTSOUNDGENERATOR_H
