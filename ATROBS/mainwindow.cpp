#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>

MainWindow::MainWindow(QProcess *atr2in, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("ATROBS");

    for (int i = 0; i < 6; i++) {
        fileName[i] = new QString("");
    }

    atr2 = atr2in;
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

std::string MainWindow::lstr(std::string s1, int l) {
    if ((int)s1.length() <= l) {
        return s1;
    } else {
        s1.erase((unsigned int)(l), std::string::npos);
        return s1;
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
    while ((k < (int)name.length()) && (name[k] != '.')) {
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
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[0] = inputFile;
        ui->label_6->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[0]->toStdString()))));
    }
}

void MainWindow::on_pushButton_2_clicked() //Robot 2 browse button
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[1] = inputFile;
        ui->label_7->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[1]->toStdString()))));
    }
}

void MainWindow::on_pushButton_3_clicked() //Robot 3 browse button
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[2] = inputFile;
        ui->label_8->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[2]->toStdString()))));
    }
}

void MainWindow::on_pushButton_4_clicked() //Robot 4 browse button
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[3] = inputFile;
        ui->label_9->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[3]->toStdString()))));
    }
}


void MainWindow::on_pushButton_5_clicked() //Robot 5 browse button
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[4] = inputFile;
        ui->label_10->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[4]->toStdString()))));
    }
}

void MainWindow::on_pushButton_6_clicked() //Robot 6 browse button
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));

    if (!inputFile.isEmpty()) {
        *fileName[5] = inputFile;
        ui->label_11->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[5]->toStdString()))));
    }
}

void MainWindow::on_pushButton_14_clicked() //Play button
{
    //full ATR2 program path
//    std::string cla = "/Users/conor/Documents/GitHub/build-ATR2-Desktop_Qt_5_10_1_clang_64bit-Debug/ATR2.app";
    //QString current_dir = QDir::currentPath();
    // /ATROBS.app/Contents/MacOS
    QString current_dir = QCoreApplication::applicationDirPath();
    std::string cla;

    if (QSysInfo::productType() == "windows") {
        cla = current_dir.toStdString() + "/ATR2.exe";
    } else if (QSysInfo::productType() == "osx") {
        std::cout << "rstr 26 = " << MainWindow::rstr(current_dir.toStdString(), 26) << std::endl;
        if (MainWindow::rstr(current_dir.toStdString(), 26) == "/ATROBS.app/Contents/MacOS") {
            current_dir = QString::fromStdString(MainWindow::lstr(current_dir.toStdString(), current_dir.toStdString().length() - 26));
            std::cout << "lstr 27 = " << current_dir.toStdString() << std::endl;
        }
        cla = current_dir.toStdString() + "/ATR2.app";
    } else {
        cla = current_dir.toStdString() + "/ATR2";
    }


    //show robot source
    if (!ui->checkBox_2->isChecked()) {
        cla += " -S";
    }

    //add up to 6 robots
    for (int i = 0; i < 6; i++) {
        if (!fileName[i]->isEmpty()) {
            cla += " \"" + fileName[i]->toStdString() + "\"";
        }
    }

    //matches
    QString numMatchesStr = ui->spinBox->cleanText();
    cla += " -M" + numMatchesStr.toStdString();

    //game delay
    QString numDelayStr = ui->spinBox_2->cleanText();
    cla += " -D" + numDelayStr.toStdString();

    //game limit
    QString numLimitStr = ui->spinBox_3->cleanText();
    cla += " -L" + numLimitStr.toStdString();

    //show scan arcs
    if (ui->checkBox->isChecked()) {
        cla += " -A";
    }

    //disable graphics
    if (ui->checkBox_3->isChecked()) {
        cla += " -G";
    }

    std::cout << cla << std::endl;

    atr2->start(QString::fromStdString(cla));
}

void MainWindow::on_pushButton_7_clicked() //Robot 1 remove
{
    MainWindow::remove_robot(0);
}

void MainWindow::on_pushButton_8_clicked() //Robot 2 remove
{
    MainWindow::remove_robot(1);
}

void MainWindow::on_pushButton_9_clicked() //Robot 3 remove
{
    MainWindow::remove_robot(2);
}

void MainWindow::on_pushButton_10_clicked() //Robot 4 remove
{
    MainWindow::remove_robot(3);
}

void MainWindow::on_pushButton_11_clicked() //Robot 5 remove
{
    MainWindow::remove_robot(4);
}

void MainWindow::on_pushButton_12_clicked() //Robot 6 remove
{
    MainWindow::remove_robot(5);
}

void MainWindow::remove_robot(int robot) {
    //*fileName[robot] = "";

    for (int i = robot + 1; i < 6; i++) {
        *fileName[i - 1] = *fileName[i];
    }

    *fileName[5] = "";

    if (fileName[0]->isEmpty()) {
        ui->label_6->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_6->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[0]->toStdString()))));
    }

    if (fileName[1]->isEmpty()) {
        ui->label_7->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_7->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[1]->toStdString()))));
    }

    if (fileName[2]->isEmpty()) {
        ui->label_8->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_8->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[2]->toStdString()))));
    }

    if (fileName[3]->isEmpty()) {
        ui->label_9->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_9->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[3]->toStdString()))));
    }

    if (fileName[4]->isEmpty()) {
        ui->label_10->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_10->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[4]->toStdString()))));
    }

    if (fileName[5]->isEmpty()) {
        ui->label_11->setText(QString::fromStdString("        .   "));
    } else {
        ui->label_11->setText(QString::fromStdString(MainWindow::base_name_pad(MainWindow::no_path(fileName[5]->toStdString()))));
    }


}
