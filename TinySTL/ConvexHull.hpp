#ifndef CONVEXHULL_H
#define CONVEXHULL_H
class Point2D
{
public:
    Point2D(double x, double y);
    const double& X() const;
    const double& Y() const;

private:
    double x;
    double y;
};

int Counterclockwise(const Point2D& a, const Point2D& b, const Point2D& c);
#endif // CONVEXHULL_H
