#include "Container.h"

Container::Container()
{
	this->height = 1;
	this->width = 1;
	this->length = 1;

	this->number = 1;
	this->color = "white";

	this->capacity = height * width * length;

	this->rightX = this->width;
	this->leftX = 0;
	this->upY = this->height;
	this->downY = 0;
	this->bottomZ = this->length;
	this->frontZ = 0;
}

Container::Container(int height, int width, int length, int number, string color) {
	this->height = height;
	this->width = width;
	this->length = length;
	
	this->number = number;
	this->color = color;

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

void Container::changeSize(int height, int width, int length) {
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

void Container::printContainer() {
	cout << "Color: " << color << "\n" << "Polozenie: " << "\n";
	cout << "leftX: " << leftX << "\n";
	cout << "rightX: " << rightX << "\n";
	cout << "downY: " << downY << "\n";
	cout << "upY: " << upY << "\n";
	cout << "frontZ: " << frontZ << "\n";
	cout << "bottomZ: " << bottomZ << "\n";
}
