#include "ShapeFile.h"
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include<typeinfo>
#include<ctype.h>
#include<sstream>
#include<fstream>

using namespace std;

ShapeFile::ShapeFile(ifstream &infile) {
	string text;
	vector<string>line;
	while (getline(infile, text))
		line.push_back(text);
	for (auto p : line) {
		vector<double>numbers;
		string::size_type pos1 = p.find_first_not_of(" ():,");
		string::size_type pos2 = p.find_first_of(" ():,");
		while (pos1 != string::npos) {
			string word(p, pos1, pos2 - pos1);
			if (isdigit(word[0]))
				numbers.push_back(stod(word));
			pos1 = p.find_first_not_of(" ():,", pos2);
			pos2 = p.find_first_of(" ():,", pos1);
		}
		if (p.at(0) == 'C') {
			Point c(numbers.at(0), numbers.at(1));
			double r = numbers.at(2);
			shared_ptr<Shape> shape(new Circle(c, r));
			shapes_.push_back(shape);
		}
		else if (p.at(0) == 'P') {
			vector<Edge*>edges;
			vector<Point>points;
			for (unsigned i = 0; i < numbers.size() / 2; i++) {
				Point point(numbers.at(2 * i), numbers.at(2 * i + 1));
				points.push_back(point);
			}

			for (unsigned i = 0; i <= points.size() - 2; i++) {
				edges.push_back(new straightEdge(points.at(i), points.at(i + 1)));
			}
			edges.push_back(new straightEdge(points.at(points.size() - 1), points.at(0)));
			shared_ptr<Shape>shape(new MyPolygon(edges));
			shapes_.push_back(shape);
			points.clear();
			edges.clear();
		}
		else {
			Point c(numbers.at(0), numbers.at(1));
			Point p1(numbers.at(2), numbers.at(3));
			Point p2(numbers.at(4), numbers.at(5));
			double radius = c.distance(p1);
			ArcEdge arcedge(p1, p2, c);
			shared_ptr<Shape>shape(new Sector(c, radius, arcedge));
			shapes_.push_back(shape);
		}
	}
}

shared_ptr<Shape> operator & (shared_ptr<Shape> s1, shared_ptr<Shape> s2) {
	const type_info &t1 = typeid(*s1);
	const type_info &t2 = typeid(*s2);

	if (t1 == t2 && t1.name()[6] == 'C') {
		auto c1 = dynamic_pointer_cast<Circle>(s1);
		auto c2 = dynamic_pointer_cast<Circle>(s2);
		Point center1 = c1->center_;
		Point center2 = c2->center_;
		double r1 = c1->radius_;
		double r2 = c2->radius_;
		double dist = center1.distance(center2);
		if (dist < (r1 + r2)) {
			if (dist == fabs(r2 - r1)) {
				if (dist == 0)
					return s1;
				return nullptr;
			}

			else if (dist < fabs(r2 - r1)) {
				if (r1 > r2)
					return s2;
				else if (r1 < r2)
					return s1;
			}
			else {
				double AE = (fabs(r2 * r2 - r1 * r1) + dist * dist) / (2 * dist);
				double x0 = center1.x_ + AE / dist * (center2.x_ - center1.x_);
				double y0 = center1.y_ + AE / dist * (center2.y_ - center1.y_);
				double CE = sqrt(r1 * r1 - AE * AE);
				double K1 = (center2.y_ - center1.y_) / (center2.x_ - center1.x_);
				double K2 = -1 / K1;
				double EF = CE / sqrt(1 + K2 * K2);
				double CF = EF * K2;
				Point pointc(x0 - EF, y0 + CF);
				Point pointd(x0 + EF, y0 - CF);
				vector<Edge*>edges;
				edges.push_back(new ArcEdge(pointc, pointd, center1));
				edges.push_back(new ArcEdge(pointc, pointd, center2));
				shared_ptr<Shape> mypolygon(new MyPolygon(edges));
				return mypolygon;
			}
		}
	}
	else {
		//need an algorithm for finding the intersection of polygons 
		return nullptr;
	}
}

shared_ptr<Shape> operator | (shared_ptr<Shape>s1, shared_ptr<Shape>s2) {
	const type_info &t1 = typeid(*s1);
	const type_info &t2 = typeid(*s2);

	if (t1 == t2 && t1.name()[6] == 'C') {
		auto c1 = dynamic_pointer_cast<Circle>(s1);
		auto c2 = dynamic_pointer_cast<Circle>(s2);
		Point center1 = c1->center_;
		Point center2 = c2->center_;
		double r1 = c1->radius_;
		double r2 = c2->radius_;
		double dist = center1.distance(center2);

		if (dist >= (r1 + r2))
			return nullptr;
		else if (dist <= fabs(r2 - r1)) {
			if (r2 > r1)
				return s2;
			else
				return s1;
		}
		else
			return s1 & s2;
	}
	return nullptr;
}

void ShapeFile::Generate() {
	for (unsigned i = 0; i < shapes_.size(); i++) {
		for (unsigned j = i + 1; j < shapes_.size(); j++) {
			shared_ptr<Shape> shape1 = shapes_[i] | shapes_[j];
			if (shape1->isValid())
				compositeShapes_.push_back(shape1);
			shared_ptr<Shape> shape2 = shapes_[i] & shapes_[j];
			if (shape2->isValid())
				compositeShapes_.push_back(shape2);
		}
	}
}

void ShapeFile::Print() {
	cout << "--------------------Shapes--------------------" << endl;
	for (auto p : shapes_) {
		p->Print();
		cout << endl;
	}
	cout << "\n--------------------composite shapes--------------------" << endl;
	for (auto p : compositeShapes_) {
		p->Print();
		cout << endl;
	}
}