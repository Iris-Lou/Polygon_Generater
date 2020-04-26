#ifndef SHAPE_H
#define SHAPE_H

#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include "Edge.h"

using namespace std;

const double PI = 3.141592653589793;

class Shape {
public:
	Shape(){}
	virtual double Length()const = 0;
	virtual double Area()const = 0;
	virtual void Print()const = 0;
	bool isValid()const {
		if (this != nullptr)
			return true;
		//still need more check here
		return false;
	}
};

class Circle :public Shape {
public:
	Circle(Point center, double radius) :center_(center), radius_(radius) {}
	virtual double Length()const override {
		return 2 * PI * radius_;
	}
	virtual double Area()const override {
		return PI * radius_ * radius_;
	}
	virtual void Print()const override;
	~Circle() {}
	friend shared_ptr<Shape> operator & (shared_ptr<Shape> s1, shared_ptr<Shape> s2);
	Point center_;
	double radius_;
};

class Sector :public Circle {
public:
	Sector(Point center, double radius, ArcEdge arcEdge) :Circle(center, radius), arcEdge_(arcEdge) {}
	virtual double Length()const override {
		return (arcEdge_.Length() + 2 * radius_);
	}
	virtual double Area()const override {
		return (Circle::Area() * arcEdge_.Length() / Circle::Length());
	}
	void Print()const override;
	~Sector() {}
	ArcEdge arcEdge_;
};

class MyPolygon :public Shape {
public:
	MyPolygon(){}
	vector<Edge*>edges_;
	MyPolygon(vector<Edge*>edge) {
		for (auto p : edge)
			edges_.push_back(p);
	}
	virtual double Length()const override {
		double length = 0;
		for (auto p : edges_) {
			length += p->Length();
		}
		return length;
	}
	virtual double Area()const override;
	virtual void Print()const override;
	static const int UnknownValue;
	~MyPolygon() {}
};

#endif // !SHAPE_H

