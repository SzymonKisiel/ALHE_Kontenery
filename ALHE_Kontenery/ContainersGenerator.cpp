#include "ContainersGenerator.h"

ContainersGenerator::ContainersGenerator(Container container, int maxAmountOfDivisions) {
	this->maxAmountOfDivisions = maxAmountOfDivisions;

	this->container = container;

	this->createContainerListX();
	this->createContainerListXY();
	this->createContainerListFinal();
}

vector <int> ContainersGenerator::divide(int n, int size) {
	vector <int> items;
	vector <int> division;

	for (int i = 1; i < size; ++i) {
		items.push_back(i);
	}

	int randNumber;

	division.push_back(0);
	division.push_back(size);

	while (items.size() > 0 && n > 0) {
		randNumber = rand() % items.size();
		division.push_back(items[randNumber]);
		items.erase(items.begin() + randNumber);
		--n;
	}

	sort(division.begin(), division.end());

	return division;
}

void ContainersGenerator::createContainerListX() {
	int amountOfDivision = rand() % maxAmountOfDivisions;
	vector <int> division = this->divide(amountOfDivision, container.getWidth());

	for (int i = 0; i < division.size() - 1; ++i) {
		Container newContainer(division[i+1] - division[i], container.getHeight(), container.getLength());
		containerListX.push_back(newContainer);
	}
}

void ContainersGenerator::createContainerListXY() {
	for (int i = 0; i < containerListX.size(); ++i) {
		int amountOfDivision = rand() % maxAmountOfDivisions;
		vector <int> division = this->divide(amountOfDivision, container.getHeight());

		for (int j = 0; division.size() != 0 && j < division.size() - 1; ++j) {
			Container newContainer(containerListX[i].getWidth(), division[j + 1] - division[j], container.getLength());
			containerListXY.push_back(newContainer);
		}
	}
}

void ContainersGenerator::createContainerListFinal() {
	for (int i = 0; i < containerListXY.size(); ++i) {
		int amountOfDivision = rand() % maxAmountOfDivisions;
		vector <int> division = this->divide(amountOfDivision, container.getLength());

		for (int j = 0; division.size() != 0 && j < division.size() - 1; ++j) {
			Container newContainer(containerListXY[i].getWidth(), containerListXY[i].getHeight(), division[j + 1] - division[j]);
			containerListFinal.push_back(newContainer);
		}
	}
}

vector<Container>  ContainersGenerator::getContainerList() {
	return this->containerListFinal;
}