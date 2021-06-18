#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>

#include "Container.h"

using namespace std;

class Subject
{
	private:
		int n;
		int value;

		vector <Container> packList;
		vector <Container> freeSpaceList;
		vector <Container> packedList;
		Container container;

	public:
		vector <int> chromosome;
		vector <OrientationType> orientationChromosome;

		Subject();
		Subject(vector <int> chromosome, vector <Container> packListIn, Container container);
		Subject(vector <int> chromosome, vector <OrientationType> orientationChromosome, vector <Container> packListIn, Container container);
		vector <int> createChromosome(int n); 
		vector <OrientationType> createOrientationChromosome(int n);
		vector <int> mutate();
		vector <OrientationType> mutateOrientation();
		int numberOfMutations(); 
		vector <Container> packListInOrder(vector <int> chromosome, vector <Container> packListIn);
		int calcValue();
		bool putContainer(Container container);
		int getValue();
		vector <Container> getPackedList();
		void print();
};

