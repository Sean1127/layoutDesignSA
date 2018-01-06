#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QTime>

#include "graph.h"

#define IMAGE_SIZE 241

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString fileName(int i);
    double eval(plate plates[ROWS][COLS]);
    void copyPlate(plate *src, plate *dst, int length);
    void loop();
    ~MainWindow();

private slots:

    void on_pushButton_go_clicked();

    void on_pushButton_pause_resume_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *labels[ROWS][COLS];
    bool run;
};

#endif // MAINWINDOW_H
