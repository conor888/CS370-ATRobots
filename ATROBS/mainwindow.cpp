#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for (int i = 0; i < 6; i++) {
        fileName[i] = new QString("");
    }

    atr2 = new QProcess(parent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

std::string MainWindow::no_path(std::string fn) {
    int i, k;

    k = 0;
    for (i = fn.length() - 1; i >= 0; i--) {
        if(((fn[i] == '\\') || (fn[i] == ':') || (fn[i] == '/')) && (k < i)) {
            k = i;
        }
    }
    if (k != 0) {
        return MainWindow::rstr(fn, fn.length() - k - 1);
    } else {
        return fn;
    }
}

std::string MainWindow::rstr(std::string s1, int l) {
    if ((int)s1.length() <= 1) {
        return s1;
    } else {
        s1.erase(0, (s1.length() - l));

        return s1;
    }
}

std::string MainWindow::base_name_pad(std::string name) {
    int k;
    std::string s1;

    s1.clear();
    k = 0;
    while ((k < name.length()) && (name[k] != '.')) {
        s1 = s1 + name[k];
        k++;
    }

    while(s1.length() < 8) {
        s1 += " ";
    }

    s1 += ".AT2";

    return s1;
}

void MainWindow::on_pushButton_13_clicked() //Quit button
{
    exit(0);
}

void MainWindow::on_pushButton_clicked() //Robot 1 browse button
{
    *fileName[0] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_6->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[0]->toStdString()))));
}

void MainWindow::on_pushButton_2_clicked() //Robot 2 browse button
{
    *fileName[1] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_7->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[1]->toStdString()))));
}

void MainWindow::on_pushButton_3_clicked() //Robot 3 browse button
{
    *fileName[2] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_8->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[2]->toStdString()))));
}

void MainWindow::on_pushButton_4_clicked() //Robot 4 browse button
{
    *fileName[3] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_9->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[3]->toStdString()))));
}


void MainWindow::on_pushButton_5_clicked() //Robot 5 browse button
{
    *fileName[4] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_10->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[4]->toStdString()))));
}

void MainWindow::on_pushButton_6_clicked() //Robot 6 browse button
{
    *fileName[5] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_11->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[5]->toStdString()))));
}

void MainWindow::on_pushButton_14_clicked() //Play button
{
    std::string cla = "/Users/conor/Documents/GitHub/build-ATR2-Desktop_Qt_5_10_1_clang_64bit-Debug/ATR2.app/Contents/MacOS/ATR2 ";

    cla += "";

    for (int i = 0; i < 6; i++) {
        if (!fileName[i]->isEmpty()) {
            cla += '"' + fileName[i]->toStdString() + "\" ";
        }
    }

    cla += "-M100 -L5 -A";

    atr2->start(QString::fromStdString(cla));
}
