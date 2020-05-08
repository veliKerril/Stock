#ifndef CONTAINER_H
#define CONTAINER_H

#include "position.h"
#include <QList>



class Container {
public:
    Container();
    Container(QString);

    void containerPush(Position);

    QList<Position> listPos;
    QString name;
};

#endif // CONTAINER_H
