/********************************************************************************
** Form generated from reading UI file 'mainwindow2.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW2_H
#define UI_MAINWINDOW2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow2
{
public:
    QLabel *label;
    QPushButton *pushButton_3;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *addPos;
    QPushButton *pushButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *delPos;
    QPushButton *pushButton_2;

    void setupUi(QDialog *MainWindow2)
    {
        if (MainWindow2->objectName().isEmpty())
            MainWindow2->setObjectName(QString::fromUtf8("MainWindow2"));
        MainWindow2->resize(800, 600);
        label = new QLabel(MainWindow2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 60, 321, 101));
        QFont font;
        font.setPointSize(27);
        label->setFont(font);
        pushButton_3 = new QPushButton(MainWindow2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(240, 460, 291, 61));
        QFont font1;
        font1.setPointSize(13);
        pushButton_3->setFont(font1);
        verticalLayoutWidget = new QWidget(MainWindow2);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(90, 290, 202, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        addPos = new QLineEdit(verticalLayoutWidget);
        addPos->setObjectName(QString::fromUtf8("addPos"));

        verticalLayout->addWidget(addPos);

        pushButton = new QPushButton(verticalLayoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setFont(font1);

        verticalLayout->addWidget(pushButton);

        verticalLayoutWidget_2 = new QWidget(MainWindow2);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(480, 280, 211, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        delPos = new QLineEdit(verticalLayoutWidget_2);
        delPos->setObjectName(QString::fromUtf8("delPos"));

        verticalLayout_2->addWidget(delPos);

        pushButton_2 = new QPushButton(verticalLayoutWidget_2);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setFont(font1);

        verticalLayout_2->addWidget(pushButton_2);


        retranslateUi(MainWindow2);

        QMetaObject::connectSlotsByName(MainWindow2);
    } // setupUi

    void retranslateUi(QDialog *MainWindow2)
    {
        MainWindow2->setWindowTitle(QApplication::translate("MainWindow2", "\320\240\320\265\320\264\320\260\320\272\321\202\320\276\321\200", nullptr));
        label->setText(QApplication::translate("MainWindow2", "\320\236\321\201\320\275\320\276\320\262\320\275\320\276\320\265 \320\276\320\272\320\275\320\276", nullptr));
        pushButton_3->setText(QApplication::translate("MainWindow2", "\320\237\320\276\320\272\320\260\320\267\320\260\321\202\321\214 \321\201\320\272\320\273\320\260\320\264", nullptr));
        pushButton->setText(QApplication::translate("MainWindow2", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
        pushButton_2->setText(QApplication::translate("MainWindow2", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\277\320\276\320\267\320\270\321\206\320\270\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow2: public Ui_MainWindow2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW2_H
