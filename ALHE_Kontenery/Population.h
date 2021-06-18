#pragma once

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

		int mu;
		int lambda;

		vector<Subject> parents;
		vector<Subject> offsprings;

		Subject bestSubject;

	public:
		Population(vector <Container> packList, Container container, int mu, int lambda);
		void run();
		Subject getBestSubject();
};

