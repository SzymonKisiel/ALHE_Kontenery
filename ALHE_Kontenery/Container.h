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
		Container();
		Container(int width, int height, int length);
		Container(int width, int height, int length, int number, string color);
		void setPosition(int positionX, int positionY, int positionZ);
		void changeSize(int width, int height, int length);
		bool checkCollision(Container container);

		int getHeight();
		int getWidth();
		int getLength();
		int getCapacity();
		string getColor();

		int getLeftX();
		int getDownY();
		int getFrontZ();

		void printContainer();
};
