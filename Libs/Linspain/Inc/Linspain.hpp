//
// Created by Dell on 05/04/2025.
//

#ifndef LINSPAIN_HPP
#define LINSPAIN_HPP

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

#endif //LINSPAIN_HPP
