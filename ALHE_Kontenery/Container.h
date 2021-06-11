#include <iostream>

using namespace std;

class Container {
	private:
		int height;
		int width;
		int length;
		int capacity;

		int rightX;
		int leftX;
		int upY;
		int downY;
		int bottomZ;
		int frontZ;

		int number;
		string color;
	public:
		Container(int height, int width, int length, int number, string color);
		void setPosition(int positionX, int positionY, int positionZ);
		void changeSize(int height, int width, int length);
		bool checkCollision(Container container);
		void printContainer();
};