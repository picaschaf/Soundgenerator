#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

enum DigitalNotes {
    c = 523,
    d = 587,
    e = 659,
    f = 698,
    g = 784,
    a = 880,
    a_ = 932
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static const int CDurationShort = 400;
    constexpr static qreal CAmplitude = 16383;
    const QVector<DigitalNotes> KomischesTetrisMelody{a, e, f, g, f, e, d, d, f, a, g, f, e, e, f, g, a, f, d, d,
                                                      g, g, a_, d, c, a_, a, f, a, g, f, e, f, g, a, f, d, d};

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
