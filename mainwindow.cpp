#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "soundgenerator.h"

#include <QVector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , generator(new SoundGenerator(this))
{
    ui->setupUi(this);
    setWindowTitle(tr("Soundgenerator"));

    static const QVector<Note> tetrisMelody{
        Note::A, Note::E, Note::F, Note::G, Note::F, Note::E, Note::D, Note::D,
        Note::F, Note::A, Note::G, Note::F, Note::E, Note::E, Note::F, Note::G,
        Note::A, Note::F, Note::D, Note::D, Note::G, Note::G, Note::ASharp, Note::D,
        Note::C, Note::ASharp, Note::A, Note::F, Note::A, Note::G, Note::F, Note::E,
        Note::F, Note::G, Note::A, Note::F, Note::D, Note::D
    };

    for (Note note : tetrisMelody) {
        generator->appendSound(Amplitude, static_cast<quint16>(note), DurationShortMs);
    }

    generator->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}
