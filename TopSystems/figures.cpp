#include "figures.h"

void Triangle::draw()
{
    glColor3f(current_color[0], current_color[1], current_color[2]);
    glBegin(GL_POLYGON);

    for (auto p = pts.begin(); p != pts.end(); p++)
        glVertex2d(p->x, p->y);

    glEnd();
}

void Square::draw()
{
    glColor3f(current_color[0], current_color[1], current_color[2]);
    glBegin(GL_POLYGON);
    
    for(auto p = pts.begin(); p!= pts.end(); p++)
        glVertex2d(p->x, p->y);

    glEnd();
    glFlush();
}

void Circle::draw()
{
    glColor3f(current_color[0], current_color[1], current_color[2]);
    glBegin(GL_TRIANGLES);

    double px = x0;
    double py = y0;

    for (int i = 0; i <= steps; i++)
    {
        double nx = size / 2 * sin(angle * i);
        double ny = size / 2 * cos(angle * i);

        glVertex2d(x0,y0);
        glVertex2d(x0+nx, y0+ny);
        glVertex2d(x0+px * int(i!=0), y0+py * int(i!=0));

        px = nx;
        py = ny;
    }
    glEnd();
}