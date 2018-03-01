#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>

using namespace std;

#define lock_type 3

void write_line(string, string, ofstream &, int, char []);
bool file_exists(string);
bool endsWith(string, string);
string replaceExt(string, string);
string ucase(string);
string prepare(string, string);
string encode(string, char [], int);

QString fileName;
int lock_dat, lock_pos;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_3_clicked()
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("ATRobot File (*.AT2)"));
    ui->label_3->setText(fileName);
}

void MainWindow::on_pushButton_clicked()
{
    string fn1, fn2, s, s1, s2;
    int i, k, lock_pos, this_dat, argc;
    ifstream f1;
    ofstream f2;
    time_t now = time(0);
    tm *ltm = localtime(&now);

    fn1 = fileName.toUtf8().constData();
    argc = 2;

    lock_pos = 0;
    lock_dat = 0;

    fn2 = replaceExt(fn1, ".ATL");

    //Check here to see if file 1/input file exists
    if (!file_exists(fn1)) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File could not be opened.");
        messageBox.setFixedSize(500,200);
        return;
    }

    //Check to see if file 2's name is valid ?
    //For now, instead check to see if file creation was successful after opening stream, later on

    //Check to make sure input and output filenames are not the same
    if( fn1.compare(fn2) == 0 ) {
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Filenames of input and output cannot be the same!");
        messageBox.setFixedSize(500,200);
        return;
    }

    //Filenames have been fully checked, open files.
    f1.open(fn1, std::ofstream::binary);
    f2.open(fn2, std::ofstream::binary);

    //Check here to see if output file creation was successful
    if (!file_exists(fn2)) {
        cout<<"Output robot file \"" + fn2 + "\" could not be created.";
        exit(0);
    }

    //Copy comment header
    f2 << ";------------------------------------------------------------------------------\r\n";
    s = "";
    while (s.compare("") == 0) {
        //Read line of f1 to s
        getline(f1, s);

        //Run "btrim(s)"
        //If first character of s is ;, then write s to f2, and set s to ""
        if ( s[0] == ';' ) {
            f2 << s + "\n";
            s = "";
        }
    }

    //Randomize = rand.time null
    srand (time(NULL));

    //LOCK HEADER
    //f2 << endl;
    f2 <<";------------------------------------------------------------------------------\r\n";
    //Try to remove .AT2 ext in the future
    f2 << "; " << fn1 << " Locked on " << (1900 + ltm->tm_year) << "/" << (1 + ltm->tm_mon) <<
       "/" << (ltm->tm_mday) << "\r\n";
    f2 <<";------------------------------------------------------------------------------\r\n";

    //k:=random(21)+20;
    k = rand() % 21 + 20;
    char *lock_code = new char[k];

    //cout << "k is " << k << endl;

    //Generate lock code to char array
    for (i = 0; i < k; i++) {
        lock_code[i] = (char)(rand() % 32 + 65);
    }

    //Print lock code info
    f2 << "#LOCK" << lock_type << " ";
    for (i = 0; i < k; i++) {
        f2 << lock_code[i];
    }
    f2 << "\r\n";

    //DECODE lock_code
    for (i = 0; i < k; i++){
        lock_code[i] = (char)((int)(lock_code[i]) - 65);
    }

    cout << "Encoding " << fn1 << "..." << endl;

    //ENCODE ROBOT
    //s = //btrim(s);

    //if length(s)>0 then
    if (s.length() > 0) {
        write_line("", ucase(s), f2, k, lock_code);
    }

    // while not eof(f1) do
    //readln(f1,s1); s:='';
    //s1:=btrim(ucase(s1));

    while (getline(f1, s1)) {
        //Read line of f1 to s1, done in while cond. When it reaches EOF, while loop ends.

        s = "";
        s1 = ucase(s1);

        write_line(s, s1, f2, k, lock_code);
    }

    cout << "Done. Used LOCK Format #" << lock_type << "." << endl;
    cout << "Only ATR2 v2.08 or later can decode." << endl;
    cout << "LOCKed robot saved as " << fn2 << "." << endl;

    QMessageBox messageBox;
    std::string successmsg = "Robot file " + fn1 + " has been successfully locked.\n\nLocked file saved to " + fn2;
    messageBox.information(0,"Success",QString::fromStdString(successmsg));
    messageBox.setFixedSize(500,200);

    f1.close();
    f2.close();
}

void write_line(string s, string s1, ofstream &f2, int k, char lock_code[]) {
    s = prepare(s, s1);

    //write line
    if (s1.length() > 0) {
        s = encode(s, lock_code, k);
        f2 << s << "\r\n";
    }
}

bool file_exists(string filename)
{
    ifstream testopen(filename);
    return testopen.good();
}

bool endsWith(string one, string two) {
    //Compare end of first string with the second string.
    int str_i, endlen;

    endlen = two.length();
    str_i = one.length() - endlen;

    if( one.compare(str_i, endlen, two) == 0 ) {
        return true;
    } else {
        return false;
    }

}

string replaceExt(string one, string two) {
    //Replace ending of string one with string two.
    int str_i, extlen;
    string three;

    extlen = two.length();
    str_i = one.length() - extlen;

    three = one.replace(str_i, extlen, two);

    return three;
}

string ucase(string str) {
    int i;
    for (i = 0; i < (int)str.length(); i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}

string prepare(string s, string s1){

    int i;

    //int n = s1.length();
    //char c[n + 1];

    //for(i = 0; i < (n); i++) {
    //    c[i] = ' ';
    //}
    //strcpy(c, s1.c_str());


    //{--remove comments--}
    /*if ((s1.length() == 0) || (s1[0]=';')){
        s1 = "";
    } else {
        k = 0;
        for (i = 0; i < s1.length(); i++)
        {
            if (s1[i]==';'){
                k = i;
            }
            if (k > 0){
                //Figure out how lstr works
                //s1=lstr(s1,k-1);
            }
        }
    }*/

    //{--remove excess spaces, newlines--}
    for (i = 0; i < s1.length(); i++) {

            if ( (s1.compare(i, 1, "\b") == 0) || (s1.compare(i, 1, "\t") == 0) ||
                    (s1.compare(i, 1, "\n") == 0) || (s1.compare(i, 1, ",") == 0) || (s1.compare(i, 1, "\r") == 0) ) {
                s1.erase(i, 1);
                i--;
            }

        }

    return s1;
}

string encode(string s, char lock_code[], int k) {
    int i, this_dat;

        int n = s.length();
        char c[n+1];
        strcpy(c, s.c_str());

        if(strlen(lock_code) != 0) {
            for (i = 0; i < s.length(); i++) {

                if (lock_pos > (k - 1)) {
                    lock_pos = 0;
                }

                //If character is outside normal alphabet/symbols in ASCII range, change it to a space
                if (((int)(c[i]) <= 31) || ((int)(c[i]) >= 128)) {
                    c[i] = ' ';
                }

                this_dat = (int)(c[i]) & 15;
                c[i] = (char)((((int)(c[i]) ^ (int)(lock_code[lock_pos])) ^ lock_dat) + 1);
                lock_dat = this_dat;
                lock_pos++;
            }
            s = c;
            return s;
        }
        return "";
}
