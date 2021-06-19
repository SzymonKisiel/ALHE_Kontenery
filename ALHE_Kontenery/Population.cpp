#include "Population.h"

Population::Population(vector <Container> packList, Container container, int mu, int lambda) {
	this->packList = packList;
	this->container = container;
	this->mu = mu;
	this->lambda = lambda;

	for (int i = 0; i < mu; ++i) {
		vector <int> emptyChromosome;
		Subject subject(emptyChromosome, vector<OrientationType>(), this->packList, this->container);
		parents.push_back(subject);
	}

}

void Population::run() {
	offsprings.clear();
		
	for (int i = 0; i < this->lambda; ++i) {
		int randIndex = rand() % parents.size();
		Subject parent = parents[randIndex];
		vector<int> newChromosome = parent.mutate();
		vector<OrientationType> newOrientationChromosome = parent.mutateOrientation();
		Subject offspring(newChromosome, newOrientationChromosome, this->packList, this->container);
		offsprings.push_back(offspring);
	}

	for (int i = 0; i < parents.size(); ++i) {
		offsprings.push_back(parents[i]);
	}

	sort(offsprings.begin(), offsprings.end());

	parents = offsprings;
	if (this->mu < this->lambda) {
		parents.erase(parents.begin() + mu , parents.end());
	}

	bestSubject = parents[0];
}

bool operator <  (Subject s1, Subject s2)
{
	return s1.getValue() > s2.getValue();
}

Subject Population::getBestSubject() {
	return this->bestSubject;
}
