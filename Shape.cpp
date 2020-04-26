#include"Shape.h"

const int MyPolygon::UnknownValue = -1;

void Circle::Print()const {
	cout << "Circle:\t" << endl;
	cout << "center of the circle: " ;
	center_.Print();
	cout << "\tradius = " << radius_ << '\t';
	cout << "perimeter = " << Length() << '\t';
	cout << "area = " << Area() << endl;
}

void Sector::Print()const {
	cout << "Sector:" << endl;
	Circle::Print();
	arcEdge_.Print();
	cout << "perimeter = " << Length();
	cout << "\tarea = " << Area() << endl;
}

void MyPolygon::Print()const {
	cout << "MyPolygon:" << endl;
	for (auto p : edges_) {
		p->Print();
	}
	cout << "perimeter = " << Length() << '\t' << "area = " << Area() << endl;
}

double compute_area(Edge* p1, Edge* p2) {
	Point c0 = p1->getCenter();
	double r = distance(&c0, &(p1->point1_));
	double B = p2->point2_.x_ - p2->point1_.x_;
	double A = p2->point1_.y_ - p2->point2_.y_;
	double C = p2->point1_.x_ * p2->point2_.y_ - p2->point2_.y_ * p2->point1_.y_;
	double frac = fabs(A * c0.x_ + B * c0.y_ + C);
	double dist = frac / sqrt(pow(A, 2) + pow(B, 2));
	double theta = acos(dist / r) * 2;
	double s_sec = 0.5 * theta * pow(r, 2);
	double s_triangle = 0.5 * theta * pow(r, 2);
	double area = s_sec - s_triangle;
	return area;
}

double MyPolygon::Area()const {
	double area = 0;
	auto n = edges_.size();
	const type_info &t1 = typeid(*(edges_.at(1)));
	const type_info &t0 = typeid(*(edges_.at(0)));
	if (n == 2) {
		if (t0.name()[6] == 'A' && t1.name()[6] == 'A') {  //Both edges are "ArcEdge"
			Point c0 = edges_.at(0)->getCenter();
			Point c1 = edges_.at(1)->getCenter();
			double dis = c0.distance(c1);
			double c1_r = c1.distance(edges_.at(1)->point1_);
			double c0_r = c0.distance(edges_.at(0)->point1_);
			double angle0 = acos((c0_r * c0_r + dis * dis - c1_r * c1_r) / (2 * dis * c0_r));
			double angle1 = acos((c1_r * c1_r + dis * dis - c0_r * c0_r) / (2 * dis * c1_r));
			area = c0_r * c0_r * angle0 + c1_r * c1_r * angle1 - sin(angle0) * c1_r * dis;
		}
		else if (t0.name()[6] == 'A' && t1.name()[6] == 's')  //ArcEdge and straightEdge
			area = compute_area(edges_.at(0), edges_.at(1));
		else if (t1.name()[6] == 'A' && t0.name()[6] == 's')  //ArcEdge and straightEdge
			area = compute_area(edges_.at(1), edges_.at(0));
	}
	else if (n >= 3) {    //Polygon
		vector<Point>points;
		vector<Point>::iterator it;
		for (auto t : edges_) {
			if (points.empty()) {
				points.push_back(t->point1_);
				points.push_back(t->point2_);
			}
			else {
				it = find(points.begin(), points.end(), t->point1_);
				if (it != points.end())
					points.push_back(t->point2_);
				else
					points.push_back(t->point1_);
			}
		}
		
		for (it = points.begin(); it != points.end() - 1; it++) 
			area += it->x_ * (it + 1)->y_ - (it + 1)->x_ * it->y_;
		area = fabs(area) / 2;
	}
	else
		area = UnknownValue;
	return area;
}
