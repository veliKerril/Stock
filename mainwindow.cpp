#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include "position.h"
#include <QFile>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    this->setWindowIcon(QIcon(":/icon/img/stockIcon.com.png"));
    this->setWindowFlags(Qt::FramelessWindowHint);

    ui->countOfPos->setMinimum(1);
    ui->countOfPos->setMaximum(999);

    ui->resultTable->setColumnCount(4);
    ui->resultTable->setRowCount(50);
    QStringList strList = {"Контейнер", "Наименование", "Количество", "Производитель"};
    ui->resultTable->setHorizontalHeaderLabels(strList);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    //ui->resultTable->verticalHeader()->hideSection(10);

    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QString line;

    QFile file("E:\\Stock\\Stock.txt");
    file.open(QIODevice::ReadOnly);

    //Position pos("PC", "Test", 12, "Test");

    // Чтение из файла
    while(!file.atEnd()) {
        line = file.readLine();
        std::replace(line.begin(), line.end(), '\n', '\0');
        std::replace(line.begin(), line.end(), '\r', '\0');
        //listPos.push_back(Position::fromStringToObject(line));
        bool flag = false;
        for (Container& e : listCont) {
            if (Position::fromStringToObject(line).getNameOfCont() == e.name) {
                e.listPos.push_back(Position::fromStringToObject(line));
                flag = true;
                break;
            }
        }
        if (flag == false) {
            Container cont(Position::fromStringToObject(line).getNameOfCont());
            cont.listPos.push_back(Position::fromStringToObject(line));
            listCont.push_back(cont);
        }
    }

    file.close();

    // Отображение для таблицы
    int count = 0;
    for (int i = 0; i < listCont.size(); i++) {
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            ui->resultTable->setItem(count, 0, new QTableWidgetItem(listCont[i].listPos[j].getNameOfCont()));
            ui->resultTable->setItem(count, 1, new QTableWidgetItem(listCont[i].listPos[j].getName()));
            ui->resultTable->setItem(count, 2, new QTableWidgetItem(QString::number(listCont[i].listPos[j].getCount())));
            ui->resultTable->setItem(count, 3, new QTableWidgetItem(listCont[i].listPos[j].getProd()));
            ui->resultTable->item(count, 0)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 1)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 2)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 3)->setTextAlignment(Qt::AlignCenter);
            count++;
        }
        count++;
    }

    // Отображение для выпадающего списка.
    for (int i = 0; i < listCont.size(); i++) {
        ui->comboBox->addItem(listCont[i].name);
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_addPos_clicked() {

    Position current;

    current.setCont(ui->lineEditAddCont->text());
    current.setCount(ui->countOfPos->text().toInt());
    current.setName(ui->lineEditAddName->text());
    current.setProd(ui->lineEditAddProd->text());

    current.setCont(ui->lineEditAddCont->text());
    current.setName(ui->lineEditAddName->text());
    current.setProd(ui->lineEditAddProd->text());

    // Если пользователь ничего не ввел
    if (ui->lineEditAddCont->text().isEmpty() || ui->lineEditAddName->text().isEmpty() || ui->lineEditAddProd->text().isEmpty()) {
        ui->infoLabel->setText("Заполните все поля для добавления.");
        return;
    }

    // Если ввел отрицательное значение
    else if (current.getCount() <= 0) {
        ui->infoLabel->setText("Напишите положительное количество.");
        ui->lineEditAddCont->clear();
        ui->lineEditAddName->clear();
        ui->lineEditAddProd->clear();
        return;
    }

    // Если пользователь что-то ввел, надо либо добавить в контейнер, либо создать новый и добавить туда
    else {
        bool flagCont = true;
        // Ищем, есть ли подходящий контейнер
        for (int i = 0; i < listCont.size(); i++) {
            bool flag = false;

            // Оп, контейнер нашли
            if (listCont[i].name == current.getNameOfCont()) {
                for (int j = 0; j < listCont[i].listPos.size(); j++) {

                    // Если это что-то уже есть на складе
                    if ((listCont[i].listPos[j].getName() == current.getName()) && (listCont[i].listPos[j].getProd().startsWith(current.getProd()))) {

                        listCont[i].listPos[j].setCount(listCont[i].listPos[j].getCount() + current.getCount());
                        ui->infoLabel->setText("Позиция \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в контейнере \"" + current.getNameOfCont()  + "\" успешно увеличена!");
                        flagCont = false;
                        flag = true;
                        break;
                    }
                }

                // Если позиции нет
                if (flag == false) {
                    flagCont = false;
                    Position newPos;
                    newPos.setCont(ui->lineEditAddCont->text());
                    newPos.setCount(ui->countOfPos->text().toInt());
                    newPos.setName(ui->lineEditAddName->text());
                    newPos.setProd(ui->lineEditAddProd->text());
                    listCont[i].listPos.push_back(newPos);
                    ui->infoLabel->setText("Позиция \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в контейнер \"" + current.getNameOfCont() + "\" успешно добавлена!");
                }
            }
        }

        // Не нашли подходящий контейнер
        if (flagCont == true) {
            Container cont(current.getNameOfCont());
            Position newPos;
            newPos.setCont(ui->lineEditAddCont->text());
            newPos.setCount(ui->countOfPos->text().toInt());
            newPos.setName(ui->lineEditAddName->text());
            newPos.setProd(ui->lineEditAddProd->text());
            cont.listPos.push_back(newPos);
            ui->infoLabel->setText("Позиция \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в новый контейнер \"" + current.getNameOfCont()  + "\" успешно добавлена!");
            listCont.push_back(cont);
        }

        ui->lineEditAddCont->clear();
        ui->lineEditAddName->clear();
        ui->lineEditAddProd->clear();
    }

    // Отображение для таблицы
    ui->resultTable->clear();

    QStringList strList = {"Контейнер", "Наименование", "Количество", "Производитель"};
    ui->resultTable->setHorizontalHeaderLabels(strList);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int count = 0;
    for (int i = 0; i < listCont.size(); i++) {
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            ui->resultTable->setItem(count, 0, new QTableWidgetItem(listCont[i].listPos[j].getNameOfCont()));
            ui->resultTable->setItem(count, 1, new QTableWidgetItem(listCont[i].listPos[j].getName()));
            ui->resultTable->setItem(count, 2, new QTableWidgetItem(QString::number(listCont[i].listPos[j].getCount())));
            ui->resultTable->setItem(count, 3, new QTableWidgetItem(listCont[i].listPos[j].getProd()));
            ui->resultTable->item(count, 0)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 1)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 2)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 3)->setTextAlignment(Qt::AlignCenter);
            count++;
        }
        count++;
    }

    // Перезапись файла
    QFile file("E:\\Stock\\Stock.txt");
    file.open(QIODevice::WriteOnly);

    QString line;

    for (Container e : listCont)
        for (Position e2 : e.listPos) {
            line = e2.fromObjectToSring();
            line.append("\r\n");
            file.write(line.toUtf8());
        }

    file.close();
}

void MainWindow::on_delPos_clicked() {

    int countFromSpin = ui->countOfPos->text().toInt();

    int rowToDell = -1;
    rowToDell = ui->resultTable->currentRow();

    if (rowToDell > -1) {
        // Все о текущей позиции
        if (ui->resultTable->item(rowToDell, 0) == 0) {
            ui->resultTable->clearSelection();
            ui->infoLabel->setText("Выделите строку, позицию в которой хотите уменьшить или удалить");
            return;
        }

        QString curNameOfCont = ui->resultTable->item(rowToDell, 0)->text();
        QString curNameOfPos = ui->resultTable->item(rowToDell, 1)->text();
        int curCountOfPos = ui->resultTable->item(rowToDell, 2)->text().toInt();
        QString curNameOfProd = ui->resultTable->item(rowToDell, 3)->text();

        // Если позиций на складе больше, чем ввел пользователь
        // По сути надо узнать номер контейнера и номер позиции в контейнере
        for (int i = 0; i < listCont.size(); i++) {
            for (int j = 0; j < listCont[i].listPos.size(); j++) {
                if ((curNameOfCont == listCont[i].name) && (curNameOfPos == listCont[i].listPos[j].getName()) && (curNameOfProd == listCont[i].listPos[j].getProd())) {
                    if (curCountOfPos > countFromSpin) {
                        listCont[i].listPos[j].setCount(listCont[i].listPos[j].getCount() - countFromSpin);
                        ui->infoLabel->setText("Количество позиции \"" + curNameOfPos + "\" производителя \"" + curNameOfProd + "\" в контейнере \"" + curNameOfCont + "\" успешно уменьшено!");
                        ui->resultTable->clearSelection();
                        break;
                    }

                    // Если позиций на складе меньше или равно
                    else {
                        listCont[i].listPos.removeAt(j);
                        ui->infoLabel->setText("Позиция \"" + curNameOfPos + "\" производителя \"" + curNameOfProd + "\" в контейнере \"" + curNameOfCont + "\" успешно удалена!");
                        ui->resultTable->clearSelection();

                        // Если контейнер закончился
                        if (listCont[i].listPos.size() == 0) {
                            listCont.removeAt(i);
                            ui->infoLabel->setText("Позиция \"" + curNameOfPos + "\" производителя \"" + curNameOfProd + "\" вместе с контейнером \"" + curNameOfCont + "\" успешно удалена!");
                            ui->resultTable->clearSelection();
                        }

                        break;
                    }
                }
            }
        }
    }

/*
 * // Ниже - блок, который обрабатывает все возможные варианты удаления.

mainPart:
    // Если склад пустой
    if (listCont.size() == 0) {
        ui->lineEditAddAndDell->clear();
        ui->infoLabel->setText("Склад пуст. Ничего удалить нельзя.");
        return;

    // Если пользователь ничего не ввел
    } else {
        if (newPos.isEmpty()) {


            ui->infoLabel->setText("Напишите, что Вы хотите удалить.");
            return;
        }


        // Если пользователь ввел хоть что-то
        else {
            bool flagCont = false;
            //Есть ли вообще такой контейнер???
            for (int i = 0; i < listCont.size(); i++) {
                if (listCont[i].name == current.getNameOfCont()) {

                    //Ок, контейнер есть и мы в его вошли
                    flagCont = true;

                    bool flag = 0;
                    for (int j = 0; j < listCont[i].listPos.size(); j++) {

                        // Если позиция, введенная пользователем, существует
                        if ((listCont[i].listPos[j].getName() == current.getName()) && (listCont[i].listPos[j].getProd().startsWith(current.getProd()))) {
                            flag = true;

                            // Если позиций на складе больше, чем ввел пользователь
                            if (listCont[i].listPos[j].getCount() > current.getCount()) {
                                listCont[i].listPos[j].setCount(listCont[i].listPos[j].getCount() - current.getCount());
                                ui->infoLabel->setText("Количество позиции \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в контейнере \"" + current.getNameOfCont() + "\" успешно уменьшено!");
                                ui->lineEditAddAndDell->clear();
                                break;
                            }

                            // Если позиций на складе меньше или равно
                            else {
                                listCont[i].listPos.removeAt(j);
                                ui->infoLabel->setText("Позиция \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в контейнере \"" + current.getNameOfCont() + "\" успешно удалена!");
                                ui->lineEditAddAndDell->clear();

                                // Если контейнер закончился
                                if (listCont[i].listPos.size() == 0) {
                                    listCont.removeAt(i);
                                    ui->infoLabel->setText("Позиция \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" вместе с контейнером \"" + current.getNameOfCont() + "\" успешно удалена!");
                                    ui->lineEditAddAndDell->clear();
                                }

                                break;
                            }
                        }
                    }

                    // Если такой позиции на складе не оказалось
                    if (flag == false) {
                        ui->lineEditAddAndDell->clear();
                        ui->infoLabel->setText("Позиции \"" + current.getName() + "\" производителя \"" + current.getProd() + "\" в контейнере \"" + current.getNameOfCont() + "\" не существует.");
                    }
                }
            }

            if (flagCont == false) {
                ui->lineEditAddAndDell->clear();
                ui->infoLabel->setText("Контейнера \"" + current.getNameOfCont() + "\" не существует");
            }
        }
    }
*/

    // Отображение для таблицы
    ui->resultTable->clear();

    QStringList strList = {"Контейнер", "Наименование", "Количество", "Производитель"};
    ui->resultTable->setHorizontalHeaderLabels(strList);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int count = 0;
    for (int i = 0; i < listCont.size(); i++) {
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            ui->resultTable->setItem(count, 0, new QTableWidgetItem(listCont[i].listPos[j].getNameOfCont()));
            ui->resultTable->setItem(count, 1, new QTableWidgetItem(listCont[i].listPos[j].getName()));
            ui->resultTable->setItem(count, 2, new QTableWidgetItem(QString::number(listCont[i].listPos[j].getCount())));
            ui->resultTable->setItem(count, 3, new QTableWidgetItem(listCont[i].listPos[j].getProd()));
            ui->resultTable->item(count, 0)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 1)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 2)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 3)->setTextAlignment(Qt::AlignCenter);
            count++;
        }
        count++;
    }

    // Перезапись файла
    QFile file("E:\\Stock\\Stock.txt");
    file.open(QIODevice::WriteOnly);

    QString line;

    for (Container e : listCont)
        for (Position e2 : e.listPos) {
            line = e2.fromObjectToSring();
            line.append("\r\n");
            file.write(line.toUtf8());
        }

    file.close();
    return;
}

void MainWindow::on_swapPos_clicked() {

    int rowToDell = -1;
    rowToDell = ui->resultTable->currentRow();

    if (rowToDell > -1) {
        // Все о текущей позиции
        if (ui->resultTable->item(rowToDell, 0) == 0) {
            ui->resultTable->clearSelection();
            ui->infoLabel->setText("Выделите строку, позицию в которой вы хотите переместить");
            return;
        }

        // Засплитил выделенную строку
        QString firstCont = ui->resultTable->item(rowToDell, 0)->text();
        QString secondCont = ui->comboBox->currentText();
        QString namePos = ui->resultTable->item(rowToDell, 1)->text();
        int countPos = ui->countOfPos->text().toInt();
        QString prodPos = ui->resultTable->item(rowToDell, 3)->text();

        // Имеется ли позиция во втором.
        bool nameOfSecond = false;
        for (Container e : listCont)
            for (Position e2 : e.listPos)
                if ((e2.getName() == namePos) && (e.name == secondCont) && (e2.getProd().startsWith(prodPos))) nameOfSecond = true;

        // Если во втором нет позиции, то создаем ее.
        if (nameOfSecond == false)
            for (Container& e : listCont)
                if ((e.name == secondCont)) {
                    e.listPos.push_back(Position(secondCont, namePos, 0, prodPos));
                    break;
                }

        // Мы знаем, что все контейнеры существуют, а в первом и втором такая позиция есть.
        // Теперь считаем разницу в переменную, удаляем либо минусуем ее.
        int dif = 0;
        for (int i = 0; i < listCont.size(); i++) {
            bool flag = false;
            for (int j = 0; j < listCont[i].listPos.size(); j++) {
                if ((listCont[i].name == firstCont) && (listCont[i].listPos[j].getName() == namePos) && (listCont[i].listPos[j].getProd().startsWith(prodPos))) {
                    dif = listCont[i].listPos[j].getCount() - countPos;

                    // Удаляем позицию
                    if (dif <= 0) {
                        dif = listCont[i].listPos[j].getCount();
                        listCont[i].listPos.removeAt(j);

                        //А что, если контейнер закончился?
                        if (listCont[i].listPos.size() == 0) {
                            listCont.removeAt(i);
                            flag = true;
                        }
                    }
                    // Минусуем позицию
                    else {
                        dif = countPos;
                        listCont[i].listPos[j].setCount(listCont[i].listPos[j].getCount() - countPos);
                    }
                }
                if (flag == true) break;
            }
        }

        // Непосредственно арифметика - все что надо было добавить или убрать, сделано выше.
        for (Container& e : listCont)
            for (Position& e2 : e.listPos)
                if ((e.name == secondCont) && (e2.getName() == namePos) && (e2.getProd().startsWith(prodPos))) {
                    e2.setCount(e2.getCount() + dif);
                    ui->infoLabel->setText("Позиция \"" + namePos + "\" из контейнера \"" + firstCont + "\" в контейнер \"" + secondCont + "\" успешно перенесена.");
                }
    }

/*    // Засплитил выделенную строку
    QString firstCont = ui->resultTable->item(rowToDell, 0)->text();
    QString secondCont = ui->comboBox->currentText();
    QString namePos = ui->resultTable->item(rowToDell, 1)->text();
    int countPos = ui->resultTable->item(rowToDell, 2)->text().toInt();
    QString prodPos = ui->resultTable->item(rowToDell, 3)->text();

    // Имеются ли первый, второй контейнер, а также позиция в первом и во втором.
    bool first = false;
    bool second = false;
    bool nameOfFirst = false;
    bool nameOfSecond = false;

    // Флаг, создавали ли мы второй контейнер
    bool secondIsNew = false;

    for (Container e : listCont) {
        if (e.name == firstCont) first = true;
        if (e.name == secondCont) second = true;
        for (Position e2 : e.listPos) {
            if ((e2.getName() == namePos) && (e.name == firstCont) && (e2.getProd().startsWith(prodPos))) nameOfFirst = true;
        }
        for (Position e2 : e.listPos) {
            if ((e2.getName() == namePos) && (e.name == secondCont) && (e2.getProd().startsWith(prodPos))) nameOfSecond = true;
        }
    }

    // Если написали не положительное число, то выкидываем
    if (countPos <= 0) {
        ui->lineEditSwap->clear();
        ui->infoLabel->setText("Введите положительное количество позиции.");
        return;
    }


    // Обрабатываем случаи, когда ничего делать не надо.
    if (newPos == "") {
        ui->infoLabel->setText("Напишите, что вы хотите сделать.");
        return;
    }
    if (first == false && second == false) {
        ui->lineEditSwap->clear();
        ui->infoLabel->setText("Контейнера \"" + firstCont + "\" и контейнера \"" + secondCont + "\" не существует.");
        return;
    } else if (first == false) {
        ui->lineEditSwap->clear();
        ui->infoLabel->setText("Контейнера \"" + firstCont + "\" не существует.");
        return;
    } else if (second == false) {
        // Создаем контейнер под нужды трудящихся
        ui->lineEditSwap->clear();
        secondIsNew = true;
        Container cont(secondCont);
        listCont.push_back(cont);
    }

    // Если в первом нет позиции, то нечего и переносить.
    if (nameOfFirst == false) {
        ui->lineEditSwap->clear();
        ui->infoLabel->setText("В контейнере \"" + firstCont + "\" нет позиции \"" + namePos + "\" производителя \"" + prodPos + "\".");
        return;
    }

    // Если во втором нет позиции, то создаем ее.
    if (nameOfSecond == false)
        for (Container& e : listCont)
            if ((e.name == secondCont)) {
                e.listPos.push_back(Position(secondCont, namePos, 0, prodPos));
                break;
            }

    // Мы знаем, что все контейнеры существуют, а в первом и втором такая позиция есть.
    // Теперь считаем разницу в переменную, удаляем либо минусуем ее.
    int dif = 0;
    for (int i = 0; i < listCont.size(); i++) {
        bool flag = false;
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            if ((listCont[i].name == firstCont) && (listCont[i].listPos[j].getName() == namePos) && (listCont[i].listPos[j].getProd().startsWith(prodPos))) {
                dif = listCont[i].listPos[j].getCount() - countPos;

                // Удаляем позицию
                if (dif <= 0) {
                    dif = listCont[i].listPos[j].getCount();
                    listCont[i].listPos.removeAt(j);

                    //А что, если контейнер закончился?
                    if (listCont[i].listPos.size() == 0) {
                        listCont.removeAt(i);
                        flag = true;
                    }
                }
                // Минусуем позицию
                else {
                    dif = countPos;
                    listCont[i].listPos[j].setCount(listCont[i].listPos[j].getCount() - countPos);
                }
            }
            if (flag == true) break;
        }
    }

    //int dif = 0;
    //for (Container& e : listCont)
    //    for (int i = 0; i < e.listPos.size(); i++)
    //        if ((e.name == firstCont) && (e.listPos[i].getName() == namePos) && (e.listPos[i].getProd().startsWith(prodPos))) {
    //            dif = e.listPos[i].getCount() - countPos;
    //
    //            // Удаляем позицию
    //            if (dif <= 0) {
    //                dif = e.listPos[i].getCount();
    //                e.listPos.removeAt(i);
    //
    //                //А что, если контейнер закончился?
    //            }
    //            // Минусуем позицию
    //            else {
    //                dif = countPos;
    //                e.listPos[i].setCount(e.listPos[i].getCount() - countPos);
    //            }
    //        }

    // Непосредственно арифметика - все что надо было добавить или убрать, сделано выше.
    for (Container& e : listCont)
        for (Position& e2 : e.listPos)
            if ((e.name == secondCont) && (e2.getName() == namePos) && (e2.getProd().startsWith(prodPos))) {
                e2.setCount(e2.getCount() + dif);
                ui->lineEditSwap->clear();
                ui->infoLabel->setText("Позиция \"" + namePos + "\" из контейнера \"" + firstCont + "\" в контейнер \"" + secondCont + "\" успешно перенесена.");
            }
*/

    // Отображение для таблицы
    ui->resultTable->clear();

    QStringList strList = {"Контейнер", "Наименование", "Количество", "Производитель"};
    ui->resultTable->setHorizontalHeaderLabels(strList);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int count = 0;
    for (int i = 0; i < listCont.size(); i++) {
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            ui->resultTable->setItem(count, 0, new QTableWidgetItem(listCont[i].listPos[j].getNameOfCont()));
            ui->resultTable->setItem(count, 1, new QTableWidgetItem(listCont[i].listPos[j].getName()));
            ui->resultTable->setItem(count, 2, new QTableWidgetItem(QString::number(listCont[i].listPos[j].getCount())));
            ui->resultTable->setItem(count, 3, new QTableWidgetItem(listCont[i].listPos[j].getProd()));
            ui->resultTable->item(count, 0)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 1)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 2)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 3)->setTextAlignment(Qt::AlignCenter);
            count++;
        }
        count++;
    }

    // Перезапись файла
    QFile file("E:\\Stock\\Stock.txt");
    file.open(QIODevice::WriteOnly);

    QString line;

    for (Container e : listCont)
        for (Position e2 : e.listPos) {
            line = e2.fromObjectToSring();
            line.append("\r\n");
            file.write(line.toUtf8());
        }

    file.close();
}

void MainWindow::on_pushButton_clicked() {
    this->close();
}

void MainWindow::on_setChanges_clicked() {


    // Отображение для таблицы
    ui->resultTable->clear();

    QStringList strList = {"Контейнер", "Наименование", "Количество", "Производитель"};
    ui->resultTable->setHorizontalHeaderLabels(strList);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->resultTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);

    ui->resultTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    int count = 0;
    for (int i = 0; i < listCont.size(); i++) {
        for (int j = 0; j < listCont[i].listPos.size(); j++) {
            ui->resultTable->setItem(count, 0, new QTableWidgetItem(listCont[i].listPos[j].getNameOfCont()));
            ui->resultTable->setItem(count, 1, new QTableWidgetItem(listCont[i].listPos[j].getName()));
            ui->resultTable->setItem(count, 2, new QTableWidgetItem(QString::number(listCont[i].listPos[j].getCount())));
            ui->resultTable->setItem(count, 3, new QTableWidgetItem(listCont[i].listPos[j].getProd()));
            ui->resultTable->item(count, 0)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 1)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 2)->setTextAlignment(Qt::AlignCenter);
            ui->resultTable->item(count, 3)->setTextAlignment(Qt::AlignCenter);
            count++;
        }
        count++;
    }
}
