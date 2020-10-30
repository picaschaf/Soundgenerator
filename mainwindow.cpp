#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#include "qxtsoundgenerator.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    QxtSoundGenerator* generator = new QxtSoundGenerator();

    for(auto note: KomischesTetrisMelody) {
        generator->appendSound(CAmplitude, note, CDurationShort);
    }

    generator->play();
}

MainWindow::~MainWindow() {
    delete ui;
}
