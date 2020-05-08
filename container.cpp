#include "container.h"

Container::Container() {

}

Container::Container(QString name) {
    this->name = name;
}

void Container::containerPush(Position pos) {
    listPos.push_back(pos);
}
