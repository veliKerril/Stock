#ifndef POSITION_H
#define POSITION_H

#include <QString>

class Position
{
public:
    Position();
    Position(QString, QString, int, QString);

    static QString fromStringToFirstString(QString);
    static QString fromStringToSecondString(QString);
    static QString fromStringToNameOfPos(QString);
    static int fromStringToCount(QString);
    static QString fromStringToProd(QString);


    static Position fromStringToObject(QString);
    static Position fromStringToObjectWithoutCount(QString);
    QString fromObjectToSring();

    QString getNameOfCont() const;
    QString getName() const;
    int getCount() const;
    QString getProd() const;

    void setCont(QString);
    void setCount(int);
    void setName(QString);
    void setProd(QString);

private:
    QString nameOfCont;
    QString name;
    int count = 1;
    QString prod;
};

#endif // POSITION_H
