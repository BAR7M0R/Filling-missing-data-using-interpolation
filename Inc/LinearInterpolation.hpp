//
// Created by Dell on 06/04/2025.
//

#ifndef LINEARINTERPOLATION_HPP
#define LINEARINTERPOLATION_HPP

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

#endif //LINEARINTERPOLATION_HPP
