#include "ConvexHull.hpp"
Point2D::Point2D(double x, double y) : x{x}, y{y}
{
}

const double& Point2D::X() const
{
    return x;
}

const double& Point2D::Y() const
{
    return y;
}

int Counterclockwise(const Point2D& a, const Point2D& b, const Point2D& c)
{
    double area2 =
        (b.X() - a.X()) * (c.Y() - a.Y()) - (b.Y() - a.Y()) * (c.X() - a.X());
    if (area2 < 0)
    {
        return -1;
    }
    else if (area2 > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
