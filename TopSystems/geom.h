#ifndef __GEOM_H
#define __GEOM_H

#define M_PI 3.14159265358979323846

#include <math.h>

struct vec2f
{
    static double org_x;
    static double org_y;
    union
    {
        struct
        {
            double x;
            double y;
        };
    };
    vec2f(double ix = 0, double iy = 0) : x(ix), y(iy) { }
    vec2f(const vec2f& src) : x(src.x), y(src.y) { }
    double length() const { return sqrt(x * x + y * y); }
    double arg() const
    {
        double len_ = sqrt((x - org_x) * (x - org_x) + (y - org_y) * (y - org_y));
        if (len_ != 0.0)
        {
            double cos_fi = (x - org_x) / len_;
            double sin_fi = (y - org_y);
            return sin_fi >= 0 ? acos(cos_fi) : 2 * M_PI - acos(cos_fi);
        }
        else
            return 0.0;
    }
    double dist_org() const
    {
        return sqrt((x - org_x) * (y - org_y));
    }
    bool operator<(const vec2f& oth) const
    {
        return (arg() < oth.arg()) || (arg() == oth.arg() && dist_org() < oth.dist_org());
    }

    bool right_turn(const vec2f& oth) const
    {
        return x * oth.y - oth.x * y > 0.0;
    }

    vec2f operator+(const vec2f& src) const
    {
        return vec2f(x + src.x, y + src.y);
    }

    vec2f operator-(const vec2f& src) const
    {
        return vec2f(x - src.x, y - src.y);
    }

    double operator*(const vec2f& src) const
    {
        return double(x * src.x + y * src.y);
    }

    vec2f operator*(double src) const
    {
        return vec2f(x * src, y * src);
    }

    vec2f operator/(double src) const
    {
        double inv(1.0 / src);
        return vec2f(x * inv, y * inv);
    }
    bool operator==(const vec2f& src) const
    {
        return x == src.x && y == src.y;
    }
    // Angle between vectors
    double operator^(const vec2f& f) const
    {
        return acos((*this / length()) * (f / f.length()));
    }

};

#endif __GEOM_H
