#include "position.h"

Position::Position() {

}

Position::Position(QString nameOfCont, QString name, int count, QString prod) {
    this->nameOfCont = nameOfCont;
    this->name = name;
    this->count = count;
    this->prod = prod;
}

Position Position::fromStringToObject(QString str) {
    QString nameOfCont = "";
    QString name = "";
    QString countStr = "";
    int count = 0;
    QString prod = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") nameOfCont += str[i];
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") name += str[i];
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") countStr += str[i];
    }
    count = countStr.toInt(0, 10);

    for (int i = c + 1; i < str.length(); i++) {
        if (str[i] != " ") prod += str[i];
    }

    count = count == 0 ? 1 : count;
    prod = prod == "" ? "---" : prod;
    return (Position(nameOfCont, name, count, prod));
}

Position Position::fromStringToObjectWithoutCount(QString str) {
    QString nameOfCont = "";
    QString name = "";
    QString countStr = "";
    int count = 0;
    QString prod = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") nameOfCont += str[i];
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") name += str[i];
    }

    for (int i = c + 1; i < str.length(); i++) {
        if (str[i] != " ") prod += str[i];
    }

    prod = prod == "" ? "---" : prod;
    return (Position(nameOfCont, name, count, prod));
}

QString Position::fromStringToFirstString(QString str) {
    QString name = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") name += str[i];
    }

    return name;
}

QString Position::fromStringToSecondString(QString str) {
    QString name = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") name += str[i];
    }

    return name;
}

QString Position::fromStringToNameOfPos(QString str) {
    QString name = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") name += str[i];
    }

    return name;
}

int Position::fromStringToCount(QString str) {
    QString countStr = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
        if (str[i] != " ") countStr += str[i];
    }

    int count = countStr.toInt(0, 10);

    count = count == 0 ? 1 : count;

    return count;
}

QString Position::fromStringToProd(QString str) {
    QString prod = "";

    int c = 0;
    for (int i = 0; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    int k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    k = c;
    for (int i = k + 1; i < str.length(); i++) {
        c = i;
        if (str[i] == "|") break;
    }

    for (int i = c + 1; i < str.length(); i++) {
        if (str[i] != " ") prod += str[i];
    }

    prod = prod == "" ? "---" : prod;

    return prod;
}

QString Position::fromObjectToSring() {
    return (nameOfCont + " | " + name + " | " + QString::number(count) + " | " + prod);
}

QString Position::getName() const{
    return name;
}

int Position::getCount() const{
    return count;
}

QString Position::getProd() const{
    return prod;
}

QString Position::getNameOfCont() const {
    return nameOfCont;
}

void Position::setCont(QString nameOfCont) {
    this->nameOfCont = nameOfCont;
}

void Position::setCount(int count) {
    this->count = count;
}

void Position::setName(QString name) {
    this->name = name;
}

void Position::setProd(QString prod) {
    this->prod = prod;
}
