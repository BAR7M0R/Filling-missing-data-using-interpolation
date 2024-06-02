#include <cmath>
#include <algorithm>
#include <queue>
#include <matplot/matplot.h>

class point
{
public:
    point(const double& x, const double& y)
        : x_(x)
        , y_(y)
    {}
    point(const point& p)
        : x_(p.x_)
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
    data()
    {}
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
protected:
    void setData(const std::vector<point>& data)
    {
        data_ = data;
    }
private:
    std::vector<point> data_;
};
class linspain
{
public:
    linspain(const double& first, const double& second, const size_t& numberOfPoints)
        : first_(first)
        , second_(second)
        , numberOfPoints_(numberOfPoints)
        , x_({ first })
    {
        double deltaX = (second_ - first_) / (numberOfPoints_ - 1);
        for (size_t i = 0; i < numberOfPoints_ - 1; ++i)
        {
            x_.push_back(x_.back() + deltaX);
        }
        std::transform(x_.begin(), x_.end(), data_.begin(), [](double p) {return point(p, 0); });
    }
    std::vector<point> getPoints() const
    {
        return data_;
    }
    point getPoint(size_t pos) const
    {
        return data_.at(pos);
    }
    std::vector<double> getX() const
    {
        return x_;
    }
    double getX(size_t pos) const
    {
        return x_.at(pos);
    }
    size_t size() const
    {
        return numberOfPoints_;
    }
private:
    const size_t numberOfPoints_;
    const double first_;
    const double second_;
    std::vector<point> data_;
    std::vector<double> x_;
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
        size_t numberOfPoint = static_cast<size_t>(scaleFactor_); //here is made simplification

        const std::vector<double> x = linspain(first.getX(), second.getX(), numberOfPoint).getX();
        if ((second.getX() - first.getX()) != 0)
        {
            double slope = (second.getY() - first.getY()) / (second.getX() - first.getX());
            double offset = first.getY() - (slope * first.getX());
            std::transform(x.begin(), x.end(), std::back_inserter(out), [slope, offset](double element) {return point(element, element * slope + offset); });
        }
        else
        {
            out.push_back(first);
            double dy = (second.getY() - first.getY()) / (numberOfPoint - 1);
            for (size_t i = 0; i < numberOfPoint - 1; ++i)
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
public:
    splineInterpolation(const std::vector<point>  &interpolationKnots, const double &repeatabilityFactor)
        : data(interpolationKnots)
        , repeatabilityFactor_(repeatabilityFactor)
    {
        if (interpolationKnots.size() < 3)
        {
            throw std::invalid_argument("lack of Knots");
        }
        std::queue<point> q;
        bool firstCalculation(true);
        std::vector<point> tempPart;
        for (point knot : getData())
        {
            if (q.size() == 3)
            {

                if(firstCalculation)
                {
                    tempPart = triPoint(q, 0);
                    interpolatedData_.insert(interpolatedData_.end(), tempPart.begin(), tempPart.end());
                }
                tempPart = triPoint(q, 1);
                interpolatedData_.insert(interpolatedData_.end(), tempPart.begin(), tempPart.end());
                q.pop();
            }
            q.push(knot);
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
    std::vector<point> triPoint(const std::queue<point>& triKnot, size_t firstElement)
    {
        std::vector<point> out;
        std::vector<point> knots;

        knots.emplace_back(std::move(triKnot.front()));
        linspain xSeries(knots.at(firstElement).getX(), knots.at(firstElement+1).getX(), static_cast<size_t>(repeatabilityFactor_));
        double ySecDev = calcualteSecondDerivativeY(triKnot);

        std::vector<point> tempA(A(xSeries.getX(), knots.at(firstElement), knots.at(firstElement + 1)));
        std::vector<point> tempB(B(xSeries.getX(), knots.at(firstElement), knots.at(firstElement + 1)));
        std::vector<point> tempC(CD(tempA, knots.at(firstElement), knots.at(firstElement + 1)));
        std::vector<point> tempD(CD(tempB, knots.at(firstElement), knots.at(firstElement + 1)));
        for (size_t i = 0; i < xSeries.size(); ++i)
        {
            out.at(i) = point(xSeries.getX(i),
                tempA.at(i).getY() * knots.at(firstElement).getY() +
                tempB.at(i).getY() * knots.at(1).getY() +
                tempC.at(i).getY() * calcualteSecondDerivativeY(triKnot) * (firstElement %2) +
                tempD.at(i).getY() * calcualteSecondDerivativeY(triKnot) * ((firstElement+1) % 2));
        }
        return out;
    }
    std::vector<point> A(const std::vector<double>& xData,
        const point& first,
        const point& second)
    {
        std::vector<point> out;

        std::transform(xData.begin(),
            xData.end(),
            std::back_inserter(out),
            [first, second](double x) {return point(x, (x - second.getX()) / (first.getX() - second.getX())); });
        return out;
    }
    double checkCornerA(const point& corner,
        const point& first,
        const point& second)
    {
        return (corner.getX() - second.getX()) / (first.getX() - second.getX());
    }
    double calculateFirstDerivativeA(const point& first,
        const point& second)
    {
        return (1.0 / (first.getX() - second.getX()));
    }
    std::vector<point> B(const std::vector<double>& xData,
        const point& first,
        const point& second)
    {
        std::vector<point> out;
        std::transform(xData.begin(),
            xData.end(),
            std::back_inserter(out),
            [first, second](double x) {return point(x, (x - first.getX()) / (second.getX() - first.getX())); });
        return out;
    }
    double calculateFirstDerivativeA(const point& first,
        const point& second)
    {
        return (1.0 / (second.getX() - first.getX()));
    }
    double checkCornerB(const point& corner,
        const point& first,
        const point& second)
    {
        return (corner.getX() - first.getX()) / (second.getX() - first.getX());
    }
    std::vector<point> CD(std::vector<point> data,
        const point& first,
        const point& second)
    {
        std::transform(data.begin(),
            data.end(),
            data.begin(),
            [first, second](point p) {return point(p.getX(), 1 / 6 * (pow(p.getY(), 3) - p.getY()) * pow(second.getX() - first.getY(), 2)); });
        return data;
    }

    std::vector<point> calculateFirstDerivativeC(std::vector<point> data,
        const point& first,
        const point& second)
    {
        std::transform(data.begin(),
            data.end(),
            data.begin(),
            [first, second](point p)
            {return point(p.getX(), -1 / 6 * (pow(p.getY(), 2) - 1) * (second.getX() - first.getY())); });
        return data;
    }
    std::vector<point> calculateFirstDerivativeD(std::vector<point> data,
        const point& first,
        const point& second)
    {
        std::transform(data.begin(),
            data.end(),
            data.begin(),
            [first, second](point p)
            {return point(p.getX(), 1 / 6 * (pow(p.getY(), 2) - 1) * (second.getX() - first.getY())); });
        return data;
    }
    double calcualteSecondDerivativeY(std::queue<point> triKnot)
    {
        std::vector<point> out;
        std::vector<point> knots;
        knots.emplace_back(std::move(triKnot.front()));
        point first(knots.front());
        point middle(knots.at(1));
        point last(knots.back());
        return 3.0 / (last.getX() - first.getX()) *
            ((last.getY() - middle.getY()) / (last.getX() - middle.getX()) -
                (middle.getY() - first.getY()) / (middle.getX() - first.getX()));
    }
    double checkCornerCD(const point& corner,
        const point& first,
        const point& second)
    {
        return (1.0 / 6.0) * (pow(corner.getY(), 3) - corner.getY()) * pow(second.getX() - first.getY(), 2);
    }



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


