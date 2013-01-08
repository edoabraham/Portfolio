#include "SAT Collision.h"


/*	Vertex	*/

Vertex::Vertex() {
	x = 0.0;
	y = 0.0;
}

Vertex::Vertex(double xVal, double yVal) {
	x = xVal; y = yVal;
}

Vector2D::Vector2D() {
	x_ = 0;
	y_ = 0;
}

Vector2D::Vector2D(double xVal, double yVal) {
	x_ = xVal;
	y_ = yVal;
}

double Vector2D::x() const {
	return x_;
}

double Vector2D::y() const {
	return y_;
}

const Vector2D & Vector2D::operator+(const Vector2D &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() + operand.x(), current.y() + operand.y()));
}

const Vector2D & Vector2D::operator-(const Vector2D &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() - operand.x(), current.y() - operand.y()));
}

const Vector2D & Vector2D::operator*(const int &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() / operand, current.y() / operand));
}

const Vector2D & Vector2D::operator/(const int &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() * operand, current.y() * operand));
}

const Vector2D & Vector2D::operator+=(const Vector2D &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() + operand.x(), current.y() + operand.y()));
}

const Vector2D & Vector2D::operator-=(const Vector2D &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() - operand.x(), current.y() - operand.y()));
}

const Vector2D & Vector2D::operator*=(const int &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() / operand, current.y() / operand));
}

const Vector2D & Vector2D::operator/=(const int &operand) const {
	Vector2D current = *this;
	return *(new Vector2D(current.x() * operand, current.y() * operand));
}

const Vector2D & Vector2D::operator=(const Vector2D &right_hand) const {
	return *this;
}

const bool & Vector2D::operator==(const Vector2D &operand) const {
	Vector2D current = *this;
	bool *result = false;
	if(current.x() == operand.x() && current.y() == operand.y()) *result = true;
	else *result = false;
	return *result;
}

const bool & Vector2D::operator!=(const Vector2D &operand) const {
	Vector2D current = *this;
	bool *result = false;
	if(current.x() == operand.x() && current.y() == operand.y()) *result = false;
	else *result = true;
	return *result;
}

void Vector2D::zero() {
	x_ = 0.0;	y_ = 0.0;
}

const bool Vector2D::isZero() const {
	if(x_ == 0 && y_ == 0) return true;
	return false;
}

void Vector2D::perpendicular() {
	double temp = x_;
	x_ = -y_;
	y_ = x_;
}

void Vector2D::reverse() {
	x_ = -x_;
	y_ = -y_;
}

const double Vector2D::length() const {
	return sqrt(x_ * x_ + y_ * y_);
}

const Vector2D Vector2D::normalize() const {
	double len = length();
	if(len == 0) {
		return Vector2D(1, 0);
	}
	return Vector2D(x_ / len, y_ / len);
}

const double Vector2D::dot_product(const Vector2D vector2) const {
	return x_ * vector2.x() + y_ * vector2.y();
}

const double Vector2D::cross_product(const Vector2D vector2) const {
	return x_ * vector2.y() - y_ * vector2.x();
}

/*	Polygon	*/

PolygonShape::PolygonShape() {
	vertices_ = 0;
}

PolygonShape::~PolygonShape() {
	for(unsigned int i = vertex_list_.size(); i > 0 ; i--) {
		vertex_list_.pop_back();
	}
}

void PolygonShape::set_coords(Vertex vertex, ...) {
	va_list arguments;

	va_start(arguments, vertex);
	while(&vertex != NULL) {
		vertices_++;
		vertex_list_.push_back(vertex);
		vertex = va_arg(arguments, Vertex);
	}
	va_end(arguments);
}

void PolygonShape::set_coords(const vector<Vertex> vertices) {
	vertices_ = vertices.size();
	for(unsigned int i = 0; i < vertices_; i++) {
		vertex_list_[i] = vertices[i];
	}
}

/*	Circle	 */

Circle::Circle() {
	x_ = 0;
	y_ = 0;
	radius_ = 0;
	vertex_ = Vertex(0, 0);
}

Circle::~Circle() {

}

void Circle::set(const Vertex vertex, unsigned int radius) {
	x_ = vertex.x;	y_ = vertex.y;	radius_ = radius;
	vertex_ = Vertex(x_, y_);
}

void Circle::set(int x, int y, unsigned int radius) {
	x_ = x;	y_ = y;	radius_ = radius;
	vertex_ = Vertex(x_, y_);
}

const double Circle::x() const {
	return x_;
}

const double Circle::y() const {
	return y_;
}

int Circle::radius() const {
	return radius_;
}

Vertex Circle::vertex() const {
	return vertex_;
}


/*	SAT_Collision	*/

SAT_Collision::SAT_Collision() {

}

SAT_Collision::~SAT_Collision() {

}

double SAT_Collision::totalRadius(const Circle circ1, const Circle circ2) const {
	return circ1.radius() + circ2.radius();
}

double SAT_Collision::distanceSquared(const Circle circ1, const Circle circ2) {
	return (circ1.x() - circ2.x()) * (circ1.x() - circ2.x()) + (circ1.y() - circ2.y()) * (circ1.y() - circ2.y());
}

Vector2D *SAT_Collision::collision_test(Circle circ1, Circle circ2) {
	if(distanceSquared(circ1, circ2) < (totalRadius(circ1, circ2) * totalRadius(circ1, circ2))) {
		unsigned int difference = unsigned(totalRadius(circ1, circ2) - sqrt((double) distanceSquared(circ1, circ2)));
		return new Vector2D((circ2.x() - circ1.x()) * difference, (circ2.y() - circ1.y()) * difference);
	}
	return NULL;
}

//Vector2D *SAT_Collision::collision_test(PolygonShape poly1, PolygonShape poly2) {
//	int test1(0), test2(0);
//	int testNum(0);
//	int min1(0), max1(0), min2(0), max2(0);
//	Vector2D axis;
//	int offset(0);
//	
//}



