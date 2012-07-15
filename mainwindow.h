#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

typedef union {
    int i;
    unsigned short us;
    short s;
    char data[4];
} header;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QByteArray reverse(const QByteArray&);
    void printRiffInformation(const QString&);
};

#endif // MAINWINDOW_H
