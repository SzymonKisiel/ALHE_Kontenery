#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

#include "Container.h"

using namespace std;


class ContainersGenerator
{
	private:
		int maxAmountOfDivisions;

		Container container;
		vector<Container> containerListX;
		vector<Container> containerListXY;
		vector<Container> containerListFinal;
	public:
		ContainersGenerator(Container container, int maxAmountOfDivisions);
		ContainersGenerator(Container container, int maxAmountOfDivisions, unsigned int seed);
		vector <int> divide(int n, int size);
		void createContainerListX();
		void createContainerListXY();
		void createContainerListFinal();
		vector<Container> getContainerList();

};

