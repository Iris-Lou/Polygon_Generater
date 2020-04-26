#ifndef EDGE_H
#define EDGE_H

#include<string>
#include<memory>
#include<vector>
#include<cmath>
#include<iostream>
using namespace std;

class Point {
public:
	Point() {}
	Point(double x, double y) :x_(x), y_(y) {}
	void Print()const { 
		cout << '(' << x_ << ',' << y_ << ')'; 
	}
	double distance(const Point & p2) const {
		return sqrt((x_ - p2.x_) * (x_ - p2.x_) + (y_ - p2.y_) * (y_ - p2.y_));
	}
	~Point() {}
	friend bool operator ==  (const Point&p1, const Point&p2);
	double x_ = 0.0;
	double y_ = 0.0;
};

class Edge {
public:
	Edge(Point point1, Point point2) :point1_(point1), point2_(point2) {}
	virtual double Length()const = 0;
	virtual void Print()const = 0;
	virtual Point getCenter()const = 0;
	Point point1_;
	Point point2_;
};

class straightEdge :public Edge {
public:
	virtual double Length()const override {
		return point1_.distance(point2_);
	}
	virtual void Print()const override;
	virtual Point getCenter()const override { 
		Point p(0, 0); 
		return p; 
	}
	straightEdge(Point point1, Point point2) :Edge(point1, point2) {}
	~straightEdge() {}
};


class ArcEdge :public Edge {
public:
	ArcEdge(Point point1, Point point2, Point c) :Edge(point1, point2), centre_of_circle(c),radius_(point1.distance(c)) {}
	virtual double Length()const override {
		double len_AB = point1_.distance(point2_);
		double radius = point1_.distance(centre_of_circle);
		double length = 2 * radius * asin(len_AB / radius / 2);
		return length;
	}
	virtual void Print()const override;
	virtual Point getCenter()const override { return centre_of_circle; }
	~ArcEdge() {}
	Point centre_of_circle;
	double radius_;
};

#endif
