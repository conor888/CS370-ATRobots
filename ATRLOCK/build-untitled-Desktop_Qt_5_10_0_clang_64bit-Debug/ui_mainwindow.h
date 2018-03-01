/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QPushButton *pushButton_3;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(752, 467);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setContextMenuPolicy(Qt::DefaultContextMenu);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(480, 330, 121, 71));
        QFont font;
        font.setPointSize(30);
        pushButton->setFont(font);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 330, 121, 71));
        pushButton_2->setFont(font);
        pushButton_2->setFlat(false);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(110, 30, 511, 101));
        label->setScaledContents(true);
        label->setAlignment(Qt::AlignCenter);
        pushButton_3 = new QPushButton(centralWidget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(250, 150, 231, 71));
        pushButton_3->setFont(font);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(160, 240, 411, 41));
        QFont font1;
        font1.setPointSize(20);
        label_2->setFont(font1);
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(20, 280, 711, 31));
        label_3->setFont(font1);
        label_3->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "ATRLock v0.1", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "Lock", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow", "Quit", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:60pt; font-weight:600;\">ATRLock</span></p></body></html>", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow", "Browse...", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Selected Robot:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "None selected", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
