#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "qxtsoundgenerator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QxtSoundGenerator* generator = new QxtSoundGenerator();

    // Komisches Tetris

    const int durationShort = 400;
    const qreal amplitude   = 16383;
    const int c = 523;
    const int d = 587;
    const int e = 659;
    const int f = 698;
    const int g = 784;
    const int a = 880;
    const int a_ = 932;

    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, e, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, e, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, e, durationShort);
    generator->appendSound(amplitude, e, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, a_, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, c, durationShort);
    generator->appendSound(amplitude, a_, durationShort);
    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, e, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, g, durationShort);
    generator->appendSound(amplitude, a, durationShort);
    generator->appendSound(amplitude, f, durationShort);
    generator->appendSound(amplitude, d, durationShort);
    generator->appendSound(amplitude, d, durationShort);

    generator->play();
}

MainWindow::~MainWindow() {
    delete ui;
}
