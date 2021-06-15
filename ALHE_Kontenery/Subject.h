#include <iostream>
#include <vector>
#include <cstdlib>

#include "container.h"

using namespace std;

class Subject
{
	private:
		int n;
		int value;

		vector <int> chromosome;
		vector <Container> packList;
		vector <Container> freeSpaceList;
		vector <Container> packedList;
		Container container;

	public:
		Subject(vector <int> chromosome, vector <Container> packListIn, Container container);
		vector <int> createChromosome(int n);
		vector <int> mutate();
		int numberOfMutations();
		vector <Container> packListInOrder(vector <int> chromosome, vector <Container> packListIn);
		int calcValue();
		bool putContainer(Container container);

};

