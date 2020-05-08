/********************************************************************************
** Form generated from reading UI file 'stockshow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOCKSHOW_H
#define UI_STOCKSHOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_StockShow
{
public:
    QTextBrowser *resultText;
    QLabel *label;

    void setupUi(QDialog *StockShow)
    {
        if (StockShow->objectName().isEmpty())
            StockShow->setObjectName(QString::fromUtf8("StockShow"));
        StockShow->resize(800, 600);
        resultText = new QTextBrowser(StockShow);
        resultText->setObjectName(QString::fromUtf8("resultText"));
        resultText->setGeometry(QRect(130, 160, 521, 381));
        label = new QLabel(StockShow);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 50, 501, 81));
        QFont font;
        font.setPointSize(22);
        label->setFont(font);

        retranslateUi(StockShow);

        QMetaObject::connectSlotsByName(StockShow);
    } // setupUi

    void retranslateUi(QDialog *StockShow)
    {
        StockShow->setWindowTitle(QApplication::translate("StockShow", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\201\320\272\320\273\320\260\320\264\320\260", nullptr));
        label->setText(QApplication::translate("StockShow", "\320\242\320\265\320\272\321\203\321\211\320\265\320\265 \321\201\320\276\321\201\321\202\320\276\321\217\320\275\320\270\320\265 \321\201\320\272\320\273\320\260\320\264\320\260.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StockShow: public Ui_StockShow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOCKSHOW_H
