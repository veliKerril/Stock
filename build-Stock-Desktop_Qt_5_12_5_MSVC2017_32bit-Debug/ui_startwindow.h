/********************************************************************************
** Form generated from reading UI file 'startwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTWINDOW_H
#define UI_STARTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_StartWindow
{
public:
    QLabel *label;
    QPushButton *pushButton;

    void setupUi(QDialog *StartWindow)
    {
        if (StartWindow->objectName().isEmpty())
            StartWindow->setObjectName(QString::fromUtf8("StartWindow"));
        StartWindow->resize(800, 600);
        label = new QLabel(StartWindow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 100, 381, 91));
        QFont font;
        font.setPointSize(30);
        label->setFont(font);
        pushButton = new QPushButton(StartWindow);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(190, 380, 351, 91));
        QFont font1;
        font1.setPointSize(17);
        pushButton->setFont(font1);

        retranslateUi(StartWindow);

        QMetaObject::connectSlotsByName(StartWindow);
    } // setupUi

    void retranslateUi(QDialog *StartWindow)
    {
        StartWindow->setWindowTitle(QApplication::translate("StartWindow", "Dialog", nullptr));
        label->setText(QApplication::translate("StartWindow", "\320\241\320\272\320\273\320\260\320\264\321\201\320\272\320\276\320\271 \321\203\321\207\320\265\321\202.", nullptr));
        pushButton->setText(QApplication::translate("StartWindow", "\320\235\320\260\321\207\320\260\321\202\321\214 \321\203\321\207\320\270\321\202\321\213\320\262\320\260\321\202\321\214 \321\201\320\272\320\273\320\260\320\264!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartWindow: public Ui_StartWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTWINDOW_H
