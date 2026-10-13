#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGlobal>

class SoundGenerator;

namespace Ui {
class MainWindow;
}

enum class Note : quint16 {
    C = 523,
    D = 587,
    E = 659,
    F = 698,
    G = 784,
    A = 880,
    ASharp = 932
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static constexpr int DurationShortMs = 400;
    static constexpr qreal Amplitude = 0.5;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SoundGenerator *generator;
};

#endif // MAINWINDOW_H
