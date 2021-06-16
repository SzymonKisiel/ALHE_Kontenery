#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "Subject.h"

class Population
{
	private:
		vector <Container> packList;
		Container container;

		int simulationLength;
		int simulationTime;
		int mu;
		int lambda;

		vector<Subject> parents;
		vector<Subject> offsprings;

		bool compareSubjects(Subject s1, Subject s2);

	public:
		Population(vector <Container> packList, Container container, int simulationLength, int mu, int lambda);
		void run();
};

