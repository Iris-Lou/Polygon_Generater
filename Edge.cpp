#include"Edge.h"

bool operator ==  (const Point&p1, const Point&p2) {
	if (p1.x_ == p2.x_ && p1.y_ == p2.y_)
		return true;
	return false;
}

void straightEdge::Print()const {
	cout << "Straight Edge:\tp1=";
	point1_.Print();
	cout << "\tp2= ";
	point2_.Print();
	cout << endl;
}

void ArcEdge::Print()const {
	cout << "Arc Edge:\tp1= ";
	point1_.Print();
	cout << "\tp2= ";
	point2_.Print();
	cout << "\tCenterOfCircle£º";
	centre_of_circle.Print();
	cout << "\tlength: " << Length() << endl;
}