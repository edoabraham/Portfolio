#ifndef _H_SAT_COLLISION
#define _H_SAT_COLLISION
#include "dependencies.h"

struct Vertex {
	Vertex();
	Vertex(double xVal, double yVal);
	double x, y;
};

class Vector2D {
public:
	Vector2D();
	Vector2D(double xVal, double yVal);
	const Vector2D & operator+(const Vector2D &operand) const;
	const Vector2D & operator-(const Vector2D &operand) const;
	const Vector2D & operator*(const int &operand) const;
	const Vector2D & operator/(const int &operand) const;
	const Vector2D & operator+=(const Vector2D &operand) const;
	const Vector2D & operator-=(const Vector2D &operand) const;
	const Vector2D & operator*=(const int &operand) const;
	const Vector2D & operator/=(const int &operand) const;
	const Vector2D & operator=(const Vector2D &right_hand) const;
	const bool & operator==(const Vector2D &operand) const;
	const bool & operator!=(const Vector2D &operand) const;
	void zero();
	void perpendicular();
	void reverse();
	const bool isZero() const;
	const Vector2D normalize() const;
	const double length() const;
	const double dot_product(const Vector2D vector2) const;
	const double cross_product(const Vector2D vector2) const;
	double x() const;
	double y() const;
private:
	double x_, y_;
};

class PolygonShape {
public:
	PolygonShape();
	~PolygonShape();
	void set_coords(const vector<Vertex> vertices);
	void set_coords(Vertex vertex, ...);
protected:
	void set_sides();
	vector<Vertex> vertex_list_;
	unsigned int vertices_;
};

class Circle {
public:
	Circle();
	~Circle();
	void set(const Vertex vertex, unsigned int radius);
	void set(int x, int y, unsigned int radius);
	const double x() const;
	const double y() const;
	int radius() const;
	Vertex vertex() const;
private:
	double x_, y_;
	unsigned radius_;
	Vertex vertex_;
};

class SAT_Collision {
public:
	SAT_Collision();
	~SAT_Collision();
private:
	Vector2D *collision_test(Circle circ1, Circle circ2);
	Vector2D *collision_test(Circle circ1, PolygonShape poly2);
	Vector2D *collision_test(PolygonShape poly1, Circle circ2);
	Vector2D *collision_test(PolygonShape poly1, PolygonShape poly2);
	double totalRadius(const Circle circ1, const Circle circ2) const;
	double distanceSquared(const Circle circ1, const Circle circ2);
};







































#endif