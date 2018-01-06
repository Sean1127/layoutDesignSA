#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            plates[i][j] = new QLabel(this);
            plates[i][j]->setGeometry(IMAGE_SIZE * j, IMAGE_SIZE * i, IMAGE_SIZE, IMAGE_SIZE);
            id[i][j] = 0;
        }
    }

    run = false;
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            delete plates[i][j];
        }
    }
    delete ui;
}

QString MainWindow::fileName(int i)
{
    QString str("plate");
    str.append(QString::number(i));
    str.append(QString(".png"));
    return str;
}

void MainWindow::on_pushButton_stop_clicked()
{
    run = false;
}

void MainWindow::on_pushButton_go_clicked()
{
    run = true;

    double temperature = 300.0;
    double coolingRate = 0.95;
    int maxIteration = 500;
    Graph graph(ROWS * COLS, id);

    // main loop
    for (int i = 0; i < maxIteration; ++i) {
        // neighbor search



        // cool down
        temperature *= coolingRate;
    }

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            plates[i][j]->setPixmap(QPixmap(fileName(id[i][j])));
        }
    }
}
