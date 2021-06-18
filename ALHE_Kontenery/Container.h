#pragma once

#include <iostream>

using namespace std;

class Container {
private:
    int height;
    int width;
    int length;
    int capacity;

    int rightX;
    int leftX;
    int upY;
    int downY;
    int bottomZ;
    int frontZ;

    int number;
public:
    enum class OrientationType {
        DEFAULT,
        ROTATE_X,
        ROTATE_Y,
        ROTATE_Z,
        ROTATE_XZ,
        ROTATE_ZX
    };
private:
    OrientationType orientation = OrientationType::DEFAULT;
public:
    Container();
    Container(int width, int height, int length);
    Container(int width, int height, int length, int number);
    void setPosition(int positionX, int positionY, int positionZ);
    void changeSize(int width, int height, int length);
    bool checkCollision(Container container);

    void setOrientation(OrientationType orientation);

    int getHeight();
    int getWidth();
    int getLength();
    int getCapacity();

    int getLeftX();
    int getRightX();
    int getDownY();
    int getUpY();
    int getFrontZ();
    int getBottomZ();

    void print();
};
