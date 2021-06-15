#include "Subject.h"

Subject::Subject(vector <int> chromosome, vector <Container> packListIn, Container container) {
	this->n = packListIn.size();

	if (chromosome.empty()) this->chromosome = this->createChromosome(this->n);
	else {
		for (int i = 0; i < chromosome.size(); ++i) this->chromosome.push_back(chromosome[i]);
	} 

	this->packList = this->packListInOrder(this->chromosome, packListIn);
	this->container = container;
	//this->freeSpaceList.clear();
	this->freeSpaceList.push_back(container);
	//this->packedList.clear();
	this->value = this->calcValue();

}

vector <int> Subject::createChromosome(int n) {
	vector <int> items;
	vector <int> chromosome;

	for (int i = 0; i < n; ++i) {
		items.push_back(i);
	}

	int randNumber;

	while (items.size() > 0) {
		randNumber = rand() % items.size();
		chromosome.push_back(items[randNumber]);
		items.erase(items.begin() + randNumber);
	}

	return chromosome;
}

vector <int> Subject::mutate() {
	int chromosomeLenght = this->chromosome.size();
	int numberOfMutations = this->numberOfMutations();
	vector <int> newChromosome = this->chromosome;

	int randNumber1, randNumber2;
	int itemNumber1, itemNumber2;

	for (int i = 0; i < numberOfMutations; ++i) {
		randNumber1 = rand() % n;
		randNumber2 = rand() % n;

		while(randNumber1 == randNumber2) randNumber2 = rand() % n;

		itemNumber1 = newChromosome[randNumber1];
		itemNumber2 = newChromosome[randNumber2];
		newChromosome[randNumber1] = itemNumber2;
		newChromosome[randNumber2] = itemNumber1;
	}

	return newChromosome;
}

int Subject::numberOfMutations() {
	const int SIZE = 20;

	int mutations[SIZE] = { 1,1,1,1,1,1,1,1,1,1,2,2,2,2,3,3,3,4,4,5 };
		// P(1) = 50 %
		// P(2) = 20 %
		// P(3) = 15 %
		// P(4) = 10 %
		// P(5) = 5 %
	int randNumber = rand()%SIZE;
		// dodaæ srand
	return mutations[randNumber];
}

vector <Container> Subject::packListInOrder(vector <int> chromosome, vector <Container> packListIn) {
	vector <Container> packListInOrder;

	for (int i = 0; i < chromosome.size(); ++i) {
		packListInOrder.push_back(packListIn[i]);
	}

	return packListInOrder;
}

int Subject::calcValue() {
	int iter = 0;
	int packedSpace = 0;
	vector <Container> packs;

	this->freeSpaceList.clear();
	this->freeSpaceList.push_back(this->container);
	this->packedList.clear();

	for (int i = 0; i < this->packList.size(); ++i) {
		packs.push_back(this->packList[i]);
	}

	while (this->putContainer(packs[iter]) && iter < packs.size()) { // packs.size() - 1 ??
		++iter;
	}

	for (int i = 0; i < this->packedList.size(); ++i) {
		packedSpace += packedList[i].getWidth() * packedList[i].getHeight() * packedList[i].getLength();
	}

	return packedSpace;
}

bool Subject::putContainer(Container container) {
	bool success = false;

	for (int i = 0; i < this->freeSpaceList.size(); ++i) {
		if (!success && container.getWidth() <= freeSpaceList[i].getWidth() && container.getHeight() <= freeSpaceList[i].getHeight() && container.getLength() <= freeSpaceList[i].getLength()) {
			container.setPosition(freeSpaceList[i].getLeftX(), freeSpaceList[i].getDownY(), freeSpaceList[i].getFrontZ());
			this->packedList.push_back(container);
			success = true;

			Container newFreeSpace2(freeSpaceList[i].getWidth(), freeSpaceList[i].getHeight() - container.getHeight(), freeSpaceList[i].getLength());
			newFreeSpace2.setPosition(freeSpaceList[i].getLeftX(), freeSpaceList[i].getDownY() + container.getHeight(), freeSpaceList[i].getFrontZ());
			Container newFreeSpace1(freeSpaceList[i].getWidth() - container.getWidth(), freeSpaceList[i].getHeight(), freeSpaceList[i].getLength());
			newFreeSpace1.setPosition(freeSpaceList[i].getLeftX() + container.getWidth(), freeSpaceList[i].getDownY(), freeSpaceList[i].getFrontZ());
			Container newFreeSpace3(freeSpaceList[i].getWidth(), freeSpaceList[i].getHeight(), freeSpaceList[i].getLength() - container.getLength());
			newFreeSpace3.setPosition(freeSpaceList[i].getLeftX(), freeSpaceList[i].getDownY(), freeSpaceList[i].getFrontZ() + container.getLength());
			
			this->freeSpaceList.erase(freeSpaceList.begin() + i);
			this->freeSpaceList.push_back(newFreeSpace1);
			this->freeSpaceList.push_back(newFreeSpace2);
			this->freeSpaceList.push_back(newFreeSpace3);
		}
	}

	for (int i = 0; i < this->freeSpaceList.size(); ++i) {
		if (container.checkCollision(freeSpaceList[i])) {
			if (container.getLeftX() <= freeSpaceList[i].getLeftX() && container.getDownY() <= freeSpaceList[i].getDownY() && container.getFrontZ() <= freeSpaceList[i].getFrontZ()) {
				freeSpaceList[i].changeSize(0, 0, 0);
			}
			else if (container.getLeftX() > freeSpaceList[i].getLeftX()) {
				freeSpaceList[i].changeSize(container.getLeftX() - freeSpaceList[i].getLeftX(), freeSpaceList[i].getHeight(), freeSpaceList[i].getLength());
			}
			else if (container.getDownY() > freeSpaceList[i].getDownY()) {
				freeSpaceList[i].changeSize(freeSpaceList[i].getWidth(), container.getDownY() - freeSpaceList[i].getDownY(), freeSpaceList[i].getLength());
			}
			else if (container.getFrontZ() > freeSpaceList[i].getFrontZ()) {
				freeSpaceList[i].changeSize(freeSpaceList[i].getWidth(), freeSpaceList[i].getHeight(), container.getFrontZ() - freeSpaceList[i].getFrontZ());
			}
		}
	}

	for (int i = 0; i < this->freeSpaceList.size(); ++i) {
		if (freeSpaceList[i].getCapacity() == 0) {
			freeSpaceList.erase(freeSpaceList.begin() + i);
		}
	}

	//dodaæ sortowanie wolnych przestrzeni

	return success;
}