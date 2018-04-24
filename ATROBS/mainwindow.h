#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QFont>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QProcess *atr2in, QWidget *parent = 0);
    ~MainWindow();
    std::string no_path(std::string fn);
    std::string lstr(std::string s1, int l);
    std::string rstr(std::string s1, int l);
    std::string base_name_pad(std::string name);
    std::string ucase(std::string s);
    void remove_robot(int robot);

    QProcess *atr2;

private slots:
    void on_pushButton_13_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_12_clicked();

private:
    Ui::MainWindow *ui;

    QFont *P2;

    //QString *fileName[6];
    QString **fileName = new QString*[6];
};

#endif // MAINWINDOW_H
