#include "Population.h"

Population::Population(vector <Container> packList, Container container, int simulationLength, int mu, int lambda) {
	this->packList = packList;
	this->container = container;
	this->simulationLength = simulationLength;
	this->mu = mu;
	this->lambda = lambda;
	this->simulationTime = 0;

	for (int i = 0; i < mu; ++i) {
		vector <int> emptyChromosome;
		Subject subject(emptyChromosome, this->packList, this->container);
	}

}

void Population::run() {
	while (simulationTime < simulationLength) {
		offsprings.clear();
		
		for (int i = 0; i < this->lambda; ++i) {
			int randIndex = rand() % parents.size();
			Subject parent = parents[randIndex];
			vector<int> newChromosome = parent.mutate();
			Subject offspring(newChromosome, this->packList, this->container);
			offsprings.push_back(offspring);
		}

		for (int i = 0; i < parents.size(); ++i) {
			offsprings.push_back(parents[i]);
		}

		sort(offsprings.begin(), offsprings.end(), compareSubjects);

		parents = offsprings;
		if (this->mu < this->lambda) {
			parents.erase(parents.begin() + mu , parents.end());
		}

		Subject bestSubject = parents[0];

		++simulationTime;
	}
}

bool Population::compareSubjects(Subject s1, Subject s2) {
	return s1.getValue() < s2.getValue();
}