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

void MainWindow::on_pushButton_13_clicked() //Quit button
{
    exit(0);
}

void MainWindow::on_pushButton_clicked() //Robot 1 browse button
{
    *fileName[0] = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_6->setText(QString::fromStdString(MainWindow::no_path(fileName[0]->toStdString())));
}
