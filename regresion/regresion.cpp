#include <cmath>
#include <algorithm>
#include <matplot/matplot.h>

std::vector<double> linspain(double first, double second, double points);

class point
{
public:
    point(const double& x, const double& y)
        :x_(x)
        , y_(y)
    {}
    point(const point& p)
        :x_(p.x_)
        , y_(p.y_)
    {}
    point& operator=(const point& p) {
        if (this != &p) {
            x_ = p.x_;
            y_ = p.y_;
        }
        return *this;
    }
    double getX() const
    {
        return x_;
    }
    double getY() const
    {
        return y_;
    }
    void print() const
    {
        std::cout << "x: " << x_ << "y: " << y_ << "\n";
    }
private:
    double x_;
    double y_;
};
class data
{
public:
    data(const std::vector<point>& data)
        :data_(data)
    {
    }
    virtual std::vector<double> getX() const
    {
        std::vector<double> X;
        std::transform(data_.begin(), data_.end(), std::back_inserter(X), [](point data) {return data.getX(); });
        return X;
    }
    virtual std::vector<double> getY() const
    {
        std::vector<double> Y;
        std::transform(data_.begin(), data_.end(), std::back_inserter(Y), [](point data) {return data.getY(); });
        return Y;
    }
    std::vector<point> getData() const
    {
        return data_;
    }
    void printData() const
    {
        for (auto p : data_)
        {
            p.print();
        }
    }
    virtual ~data()
    {}
private:
    std::vector<point> data_;
};
class linearInterpolation : public data
{
public:
    linearInterpolation(const std::vector<point>& discrietData, const double& scaleFactor)
        :data(discrietData)
        , scaleFactor_(scaleFactor)
    {
        const std::vector<point> rawData = getData();
        point memPoint = rawData.front();
        std::vector<point> tempData;
        for (size_t pointIndex = 1; pointIndex < rawData.size(); ++pointIndex)
        {
            tempData = twoPoints(memPoint, rawData.at(pointIndex));
            interpolatedData_.insert(interpolatedData_.end(), tempData.begin(), tempData.end());
            if (pointIndex != (rawData.size() - 1))
            {
                interpolatedData_.pop_back();
            }
            memPoint = rawData.at(pointIndex);
        }
    }
    std::vector<double> getX() const override
    {
        std::vector<double> X;
        std::transform(interpolatedData_.begin(),
            interpolatedData_.end(),
            std::back_inserter(X),
            [](point data) {return data.getX(); });
        return X;
    }
    std::vector<double> getY() const override 
    {

        std::vector<double> Y;
        std::transform(interpolatedData_.begin(),
            interpolatedData_.end(),
            std::back_inserter(Y),
            [](point data) {return data.getY(); });
        return Y;
    }


private:
    std::vector<point> twoPoints(point first, point second) const
    {
        std::vector<point> out;
        double numberOfPoint = scaleFactor_; //here is made simplification 
        const std::vector<double> x = linspain(first.getX(), second.getX(), scaleFactor_);
        if ((second.getX() - first.getX()) != 0)
        {
            double slope = (second.getY() - first.getY()) / (second.getX() - first.getX());
            double offset = first.getY() - (slope * first.getX());
            std::transform(x.begin(), x.end(), std::back_inserter(out), [slope, offset](double element) {return point(element, element * slope + offset); });
        }
        else
        {
            out.push_back(first);
            double dy = (second.getY() - first.getY()) / (scaleFactor_ - 1);
            for (size_t i = 0; i < scaleFactor_ - 1; ++i)
            {
                out.push_back(point(x.at(i), out.back().getY() + dy));
            }
        }
        return out;
    }
    const double scaleFactor_;
    std::vector<point> interpolatedData_;
};
class splineInterpolation : public data
{
    splineInterpolation(std::vector<point>  interpolationKnots, double repeatabilityFactor)
        : data(interpolationKnots)
        , repeatabilityFactor_(repeatabilityFactor)
    {}
    std::vector<double> getX() const override
    {
        std::vector<double> X;
        std::transform(interpolatedData_.begin(), interpolatedData_.end(), std::back_inserter(X), [](point data) {return data.getX(); });
        return X;
    }
    std::vector<double> getY() const override
    {

        std::vector<double> Y;
        std::transform(interpolatedData_.begin(), interpolatedData_.end(), std::back_inserter(Y), [](point data) {return data.getY(); });
        return Y;
    }
private:
    const double repeatabilityFactor_;
    std::vector<point> interpolatedData_;
};
int main() {
    const linearInterpolation interpolatedLineary({ point(1,1),point(2,9),point(3,27), point(4, 81) }, 10);
    //const splineInterpolation interpolatedSpline({ point(1,1),point(2,9),point(3,27), point(4, 81) }, 10);
    matplot::scatter(interpolatedLineary.getX(), interpolatedLineary.getY());
    matplot::hold(matplot::on);
    //matplot::scatter(interpolatedSpline.getX(), interpolatedSpline.getY());
    //std::vector<double> x = matplot::linspace(0, 2 * matplot::pi);
    //std::vector<double> y = matplot::transform(x, [](auto x) { return sin(x); });

    //matplot::plot(x, y, "-o");
    //
    //matplot::plot(x, matplot::transform(y, [](auto y) { return -y; }), "--xr");
    //matplot::plot(x, matplot::transform(x, [](auto x) { return x / matplot::pi - 1.; }), "-:gs");
   // matplot::plot({ 1.0, 0.7, 0.4, 0.0, -0.4, -0.7, -1 }, "k");

    matplot::show();
    return 0;
}

std::vector<double> linspain(double first, double second, double points)
{
    std::vector<double> data({ first });
    double dData = (second - first) / (points - 1);
    for (size_t i = 0; i < points - 1; ++i)
    {
        data.push_back(data.back() + dData);
    }
    return data;
}