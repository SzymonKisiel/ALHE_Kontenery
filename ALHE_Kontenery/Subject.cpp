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

void Subject::mutate() {

}

int Subject::number_of_mutations() {
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
	return 0;
}

void Subject::putContainer() {

}