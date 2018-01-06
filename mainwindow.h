#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
    ~MainWindow();

private slots:

    void on_pushButton_stop_clicked();

    void on_pushButton_go_clicked();

private:
    Ui::MainWindow *ui;
    QLabel *plates[ROWS][COLS];
    int id[ROWS][COLS];
    bool run;
};

#endif // MAINWINDOW_H
