#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            labels[i][j] = new QLabel(this);
            labels[i][j]->setGeometry(IMAGE_SIZE * (j + 1), IMAGE_SIZE * (i + 1), IMAGE_SIZE, IMAGE_SIZE);
            labels[i][j]->setPixmap(QPixmap(fileName(10)));
        }
    }
    entrance = new QLabel(this);
    entrance->setGeometry(IMAGE_SIZE * 2, IMAGE_SIZE * 3, IMAGE_SIZE, IMAGE_SIZE);
    entrance->setPixmap(QPixmap(fileName(1)));
    exit = new QLabel(this);
    exit->setGeometry(IMAGE_SIZE * 3, IMAGE_SIZE * 3, IMAGE_SIZE, IMAGE_SIZE);
    exit->setPixmap(QPixmap(fileName(1)));

    run = false;
}

MainWindow::~MainWindow()
{
    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            delete labels[i][j];
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

double MainWindow::eval(plate plates[ROWS][COLS])
{
    int total = ROWS * COLS * 36;
    int park = 0;

    for (int i = 0; i < ROWS; ++i) {
        for (int j = 0; j < COLS; ++j) {
            park += plates[i][j].space;
        }
    }
    return (double) park / total;
}

void MainWindow::copyPlate(plate *src, plate *dst, int length)
{
    for (int i = 0; i < length; ++i) {
        dst[i].id = src[i].id;
        dst[i].L = src[i].L;
        dst[i].R = src[i].R;
        dst[i].U = src[i].U;
        dst[i].D = src[i].D;
        dst[i].space = src[i].space;
    }
}

void MainWindow::on_pushButton_go_clicked()
{
    run = true;

    double temperature = ui->lineEdit_temp->text().toDouble();
    double coolingRate = ui->lineEdit_rate->text().toDouble();
    int maxIteration = ui->lineEdit_iter->text().toDouble();
    double objNew;
    double boltzmann;
    plate current[ROWS][COLS];
    plate next[ROWS][COLS];
    double obj = eval(current);

    qsrand(QTime::currentTime().second());
    // main loop
    for (int i = 0; i < maxIteration; ) {
        if (!run) {
            update();
            qApp->processEvents();
            continue;
        }

        // neighbor search
        next[qrand() % ROWS][qrand() % COLS].id = qrand() % 11;
        Graph graph(ROWS * COLS, next);
        if (!graph.DFS(ROWS * COLS)) {
            copyPlate(&current[0][0], &next[0][0], ROWS * COLS);
            continue;
        }

        objNew = eval(next);
        if (objNew >= obj) {
            obj = objNew;
            copyPlate(&next[0][0], &current[0][0], ROWS * COLS);
        } else {
            boltzmann = min(1.0, exp(-(obj - objNew) / temperature));
            if (qrand() / RAND_MAX < boltzmann) {
                obj = objNew;
                copyPlate(&next[0][0], &current[0][0], ROWS * COLS);
            }
        }

        // cool down
        temperature *= coolingRate;
        ++i;

        // display
        for (int i = 0; i < ROWS; ++i) {
            for (int j = 0; j < COLS; ++j) {
                labels[i][j]->setPixmap(QPixmap(fileName(current[i][j].id)));
            }
        }
        ui->lineEdit_temp->setText(QString::number(temperature));
        ui->lineEdit_iter->setText(QString::number(i));
        ui->lineEdit_rate->setText(QString::number(coolingRate));
        update();
        qApp->processEvents();

        cout << obj << endl;
    }
    cout << obj << endl;
}

void MainWindow::on_pushButton_pause_resume_clicked()
{
    if (run) {
        run = false;
        ui->pushButton_pause_resume->setText("resume");
    } else {
        run = true;
        ui->pushButton_pause_resume->setText("pause");
    }
}
