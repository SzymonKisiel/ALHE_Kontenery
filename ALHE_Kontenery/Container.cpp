#include "Container.h"

Container::Container()
{
    this->height = 1;
    this->width = 1;
    this->length = 1;

    this->number = -1;

    this->capacity = height * width * length;

    this->rightX = this->width;
    this->leftX = 0;
    this->upY = this->height;
    this->downY = 0;
    this->bottomZ = this->length;
    this->frontZ = 0;
}

Container::Container(int width, int height, int length) {
    this->height = height;
    this->width = width;
    this->length = length;

    this->number = -1;

    this->capacity = height * width * length;

    this->rightX = this->width;
    this->leftX = 0;
    this->upY = this->height;
    this->downY = 0;
    this->bottomZ = this->length;
    this->frontZ = 0;
}

Container::Container(int width, int height, int length, int number) {
    this->height = height;
    this->width = width;
    this->length = length;

    this->number = number;

    this->capacity = height * width * length;

    this->rightX = this->width;
    this->leftX = 0;
    this->upY = this->height;
    this->downY = 0;
    this->bottomZ = this->length;
    this->frontZ = 0;
}

void Container::setPosition(int positionX, int positionY, int positionZ) {
    this->rightX = this->width + positionX;
    this->leftX = positionX;
    this->upY = this->height + positionY;
    this->downY = positionY;
    this->bottomZ = this->length + positionZ;
    this->frontZ = positionZ;
}

void Container::changeSize(int width, int height, int length) {
    this->height = height;
    this->width = width;
    this->length = length;

    this->capacity = this->height * this->width * this->length;

    this->rightX = this->leftX + this->width;
    this->upY = this->downY + this->height;
    this->bottomZ = this->frontZ + this->length;
}

bool Container::checkCollision(Container container) {
    bool collisionX = this->rightX > container.leftX && this->leftX < container.rightX;
    bool collisionY = this->upY > container.downY && this->downY < container.upY;
    bool collisionZ = this->bottomZ > container.frontZ && this->frontZ < container.bottomZ;

    if (collisionX && collisionY && collisionZ)
        return true;
    else return false;
}

void Container::setOrientation(OrientationType orientation) {
    this->orientation = orientation;
}

int Container::getHeight() {
    switch (orientation) {
    case OrientationType::DEFAULT:
    case OrientationType::ROTATE_Y:
        return this->height;
    case OrientationType::ROTATE_X:
    case OrientationType::ROTATE_XZ:
        return this->length;
    case OrientationType::ROTATE_Z:
    case OrientationType::ROTATE_ZX:
        return this->width;
    }
}

int Container::getWidth() {
    switch (orientation) {
    case OrientationType::DEFAULT:
    case OrientationType::ROTATE_X:
        return this->width;
    case OrientationType::ROTATE_Z:
    case OrientationType::ROTATE_XZ:
        return this->height;
    case OrientationType::ROTATE_Y:
    case OrientationType::ROTATE_ZX:
        return this->length;
    }
}

int Container::getLength() {
    switch (orientation) {
    case OrientationType::DEFAULT:
    case OrientationType::ROTATE_Z:
        return this->length;
    case OrientationType::ROTATE_X:
    case OrientationType::ROTATE_ZX:
        return this->height;
    case OrientationType::ROTATE_XZ:
    case OrientationType::ROTATE_Y:
        return this->width;
    }
}

int Container::getCapacity() {
    return this->capacity;
}

int Container::getLeftX() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->leftX;
    case OrientationType::ROTATE_X:
        return this->leftX;
    case OrientationType::ROTATE_Y:
        return this->frontZ;
    case OrientationType::ROTATE_Z:
        return this->downY;
    case OrientationType::ROTATE_XZ:
        return this->downY;
    case OrientationType::ROTATE_ZX:
        return this->frontZ;
    }
}

int Container::getRightX() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->rightX;
    case OrientationType::ROTATE_X:
        return this->rightX;
    case OrientationType::ROTATE_Y:
        return this->bottomZ;
    case OrientationType::ROTATE_Z:
        return this->upY;
    case OrientationType::ROTATE_XZ:
        return this->upY;
    case OrientationType::ROTATE_ZX:
        return this->bottomZ;
    }
}

int Container::getDownY() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->downY;
    case OrientationType::ROTATE_X:
        return this->frontZ;
    case OrientationType::ROTATE_Y:
        return this->downY;
    case OrientationType::ROTATE_Z:
        return this->leftX;
    case OrientationType::ROTATE_XZ:
        return this->frontZ;
    case OrientationType::ROTATE_ZX:
        return this->leftX;
    }
}

int Container::getUpY() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->upY;
    case OrientationType::ROTATE_X:
        return this->bottomZ;
    case OrientationType::ROTATE_Y:
        return this->upY;
    case OrientationType::ROTATE_Z:
        return this->rightX;
    case OrientationType::ROTATE_XZ:
        return this->bottomZ;
    case OrientationType::ROTATE_ZX:
        return this->rightX;
    }
}

int Container::getFrontZ() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->frontZ;
    case OrientationType::ROTATE_X:
        return this->downY;
    case OrientationType::ROTATE_Y:
        return this->leftX;
    case OrientationType::ROTATE_Z:
        return this->frontZ;
    case OrientationType::ROTATE_XZ:
        return this->leftX;
    case OrientationType::ROTATE_ZX:
        return this->downY;
    }
}

int Container::getBottomZ() {
    switch (orientation) {
    case OrientationType::DEFAULT:
        return this->bottomZ;
    case OrientationType::ROTATE_X:
        return this->upY;
    case OrientationType::ROTATE_Y:
        return this->rightX;
    case OrientationType::ROTATE_Z:
        return this->bottomZ;
    case OrientationType::ROTATE_XZ:
        return this->rightX;
    case OrientationType::ROTATE_ZX:
        return this->upY;
    }
}

void Container::print() {
    cout << "Container {\n";
    cout << '\t' << "leftX:  \t" << getLeftX() << '\n';
    cout << '\t' << "rightX: \t" << getRightX() << '\n';
    cout << '\t' << "downY:  \t" << getDownY() << '\n';
    cout << '\t' << "upY:    \t" << getUpY() << '\n';
    cout << '\t' << "frontZ: \t" << getFrontZ() << '\n';
    cout << '\t' << "bottomZ:\t" << getBottomZ() << '\n';
    cout << '\n';
    cout << '\t' << "width:\t" << getWidth() << '\n';
    cout << '\t' << "height:\t" << getHeight() << '\n';
    cout << '\t' << "length:\t" << getLength() << '\n';
}
