#ifndef __FIGURES_H
#define __FIGURES_H
#include <iostream>
#include <stdlib.h>
#include "include/glut.h"
#include "geom.h"
#include <vector>

class Figure {
	
public:
	double x0;
	double y0;
	double size;
	std::vector < double > current_color;
	std::vector < vec2f > pts;
	Figure() { 
		std::cout << "empty constructor" << std::endl; }
	Figure(double x, double y, double s, std::vector < double > cc) : x0(x), y0(y), size(s), current_color(cc) {}

	virtual void draw() {
		std::cout << "default drawing" << std::endl;
	};
};

/*
class Star : public Figure
{
public:
	Star() : Figure() {}
	Star(vec2f InitPoint, double size) : Figure(InitPoint.x, InitPoint.y, size) {
		pts.push_back(vec2f(InitPoint.x - size / 2, InitPoint.y - size / 8));
		pts.push_back(vec2f(InitPoint.x - size / 8, InitPoint.y - size / 8));
		pts.push_back(vec2f(InitPoint.x + size / 2, InitPoint.y));
		pts.push_back(vec2f(InitPoint.x + size / 8, InitPoint.y - size / 8));
		pts.push_back(vec2f(InitPoint.x + size / 2, InitPoint.y - size / 8));
		
		//pts.push_back(vec2f(InitPoint.x + size / 4, InitPoint.y - size / 8));
		//pts.push_back(vec2f(InitPoint.x - size / 2, InitPoint.y + size * (3/8)));
		//pts.push_back(vec2f(InitPoint.x - size / 4, InitPoint.y));
		//pts.push_back(vec2f(InitPoint.x - size / 2, InitPoint.y - size * (3/8)));
		//pts.push_back(vec2f(InitPoint.x - size / 4, InitPoint.y - size / 8));
	}

	virtual void draw(std::vector<double> current_color);
};*/

class Square : public Figure
{
public:
	Square() : Figure() {}
	Square(vec2f InitPoint, double size, std::vector < double > cc) : Figure(InitPoint.x, InitPoint.y, size, cc) {
		pts.push_back(vec2f(InitPoint.x - size / 2, InitPoint.y - size / 2));
		pts.push_back(vec2f(InitPoint.x - size / 2, InitPoint.y + size / 2));
		pts.push_back(vec2f(InitPoint.x + size / 2, InitPoint.y + size / 2));
		pts.push_back(vec2f(InitPoint.x + size / 2, InitPoint.y - size / 2));
	}

	virtual void draw();
};

class Triangle : public Figure
{
public:
	Triangle() : Figure() {}
	Triangle(vec2f InitPoint, double size, std::vector < double > cc) : Figure(InitPoint.x, InitPoint.y, size, cc) {
		pts.push_back(vec2f(InitPoint.x - size/2, InitPoint.y - (size * tan(M_PI / 6) / 2)));
		pts.push_back(vec2f(InitPoint.x, InitPoint.y + size / (2 * cos(M_PI / 6))));
		pts.push_back(vec2f(InitPoint.x + size / 2, InitPoint.y - (size * tan(M_PI / 6) / 2)));
	}

	virtual void draw();

};

class Circle : public Figure {
	int steps;
	double angle;
public:
	Circle() : Figure() {}
	Circle(vec2f InitPoint, double size, int step, std::vector < double > cc) : Figure(InitPoint.x, InitPoint.y, size, cc) {
		steps = step; 
		angle = 2.0 * M_PI / steps;
	}

	virtual void draw();
};
 
#endif // !__FIGURES_H
