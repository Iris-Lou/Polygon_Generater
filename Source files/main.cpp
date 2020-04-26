#include<fstream>
#include"ShapeFile.h"
using namespace std;

int main() {
	ifstream file("Shapes.txt");
	if (!file.is_open()) {
		cerr << "Cannot open the shape file!" << endl;
		return -1;
	}
	ShapeFile test(file);
	test.Generate();
	test.Print();
	return 0;
}
