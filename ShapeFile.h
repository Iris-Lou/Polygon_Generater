#ifndef SHAPEFILE_H
#define SHAPEFILE_H

#include "Shape.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>


class ShapeFile {
public:
	ShapeFile(ifstream &infile);
	~ShapeFile() {}  
	void Generate();
	void Print();
private:
	vector<shared_ptr<Shape>>shapes_;
	vector<shared_ptr<Shape>>compositeShapes_;
};

#endif // !SHAPEFILE_H

