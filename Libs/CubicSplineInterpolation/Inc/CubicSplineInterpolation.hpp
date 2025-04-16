/******************************************************************************
 * Copyright 2025, Bartłomiej Głodek
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 ******************************************************************************/

#ifndef SPLINEINTERPOLATION_HPP
#define SPLINEINTERPOLATION_HPP

#include "Data.hpp"
#include "Cubicspline.hpp"

struct CubicSpinelInterpolation : Data {
    explicit CubicSpinelInterpolation(Data nodes);
};

//class splineInterpolation : public data
//{
//public:
//    splineInterpolation(const std::vector<point>  &interpolationKnots, const double &repeatabilityFactor)
//        : data(interpolationKnots)
//        , repeatabilityFactor_(repeatabilityFactor)
//    {
//        if (interpolationKnots.size() < 3)
//        {
//            throw std::invalid_argument("lack of Knots");
//        }
//        std::queue<point> q;
//        bool firstCalculation(true);
//        std::vector<point> tempPart;
//        for (point knot : getData())
//        {
//            if (q.size() == 3)
//            {
//
//                if(firstCalculation)
//                {
//                    tempPart = triPoint(q, 0);
//                    interpolatedData_.insert(interpolatedData_.end(), tempPart.begin(), tempPart.end());
//                }
//                tempPart = triPoint(q, 1);
//                interpolatedData_.insert(interpolatedData_.end(), tempPart.begin(), tempPart.end());
//                q.pop();
//            }
//            q.push(knot);
//        }
//    }
//    std::vector<double> getX() const override
//    {
//        std::vector<double> X;
//        std::transform(interpolatedData_.begin(),
//            interpolatedData_.end(),
//            std::back_inserter(X),
//            [](point data) {return data.getX(); });
//        return X;
//    }
//    std::vector<double> getY() const override
//    {
//
//        std::vector<double> Y;
//        std::transform(interpolatedData_.begin(),
//            interpolatedData_.end(),
//            std::back_inserter(Y),
//            [](point data) {return data.getY(); });
//        return Y;
//    }
//private:
//    std::vector<point> triPoint(const std::queue<point>& triKnot, size_t firstElement)
//    {
//        std::vector<point> out;
//        std::vector<point> knots;
//
//        knots.emplace_back(std::move(triKnot.front()));
//        linspain xSeries(knots.at(firstElement).getX(), knots.at(firstElement+1).getX(), static_cast<size_t>(repeatabilityFactor_));
//        double ySecDev = calcualteSecondDerivativeY(triKnot);
//
//        std::vector<point> tempA(A(xSeries.getX(), knots.at(firstElement), knots.at(firstElement + 1)));
//        std::vector<point> tempB(B(xSeries.getX(), knots.at(firstElement), knots.at(firstElement + 1)));
//        std::vector<point> tempC(CD(tempA, knots.at(firstElement), knots.at(firstElement + 1)));
//        std::vector<point> tempD(CD(tempB, knots.at(firstElement), knots.at(firstElement + 1)));
//        for (size_t i = 0; i < xSeries.size(); ++i)
//        {
//            out.at(i) = point(xSeries.getX(i),
//                tempA.at(i).getY() * knots.at(firstElement).getY() +
//                tempB.at(i).getY() * knots.at(1).getY() +
//                tempC.at(i).getY() * calcualteSecondDerivativeY(triKnot) * (firstElement %2) +
//                tempD.at(i).getY() * calcualteSecondDerivativeY(triKnot) * ((firstElement+1) % 2));
//        }
//        return out;
//    }
//    std::vector<point> A(const std::vector<double>& xData,
//        const point& first,
//        const point& second)
//    {
//        std::vector<point> out;
//
//        std::transform(xData.begin(),
//            xData.end(),
//            std::back_inserter(out),
//            [first, second](double x) {return point(x, (x - second.getX()) / (first.getX() - second.getX())); });
//        return out;
//    }
//    double checkCornerA(const point& corner,
//        const point& first,
//        const point& second)
//    {
//        return (corner.getX() - second.getX()) / (first.getX() - second.getX());
//    }
//    double calculateFirstDerivativeA(const point& first,
//        const point& second)
//    {
//        return (1.0 / (first.getX() - second.getX()));
//    }
//    std::vector<point> B(const std::vector<double>& xData,
//        const point& first,
//        const point& second)
//    {
//        std::vector<point> out;
//        std::transform(xData.begin(),
//            xData.end(),
//            std::back_inserter(out),
//            [first, second](double x) {return point(x, (x - first.getX()) / (second.getX() - first.getX())); });
//        return out;
//    }
//    double calculateFirstDerivativeA(const point& first,
//        const point& second)
//    {
//        return (1.0 / (second.getX() - first.getX()));
//    }
//    double checkCornerB(const point& corner,
//        const point& first,
//        const point& second)
//    {
//        return (corner.getX() - first.getX()) / (second.getX() - first.getX());
//    }
//    std::vector<point> CD(std::vector<point> data,
//        const point& first,
//        const point& second)
//    {
//        std::transform(data.begin(),
//            data.end(),
//            data.begin(),
//            [first, second](point p) {return point(p.getX(), 1 / 6 * (pow(p.getY(), 3) - p.getY()) * pow(second.getX() - first.getY(), 2)); });
//        return data;
//    }
//
//    std::vector<point> calculateFirstDerivativeC(std::vector<point> data,
//        const point& first,
//        const point& second)
//    {
//        std::transform(data.begin(),
//            data.end(),
//            data.begin(),
//            [first, second](point p)
//            {return point(p.getX(), -1 / 6 * (pow(p.getY(), 2) - 1) * (second.getX() - first.getY())); });
//        return data;
//    }
//    std::vector<point> calculateFirstDerivativeD(std::vector<point> data,
//        const point& first,
//        const point& second)
//    {
//        std::transform(data.begin(),
//            data.end(),
//            data.begin(),
//            [first, second](point p)
//            {return point(p.getX(), 1 / 6 * (pow(p.getY(), 2) - 1) * (second.getX() - first.getY())); });
//        return data;
//    }
//    double calcualteSecondDerivativeY(std::queue<point> triKnot)
//    {
//        std::vector<point> out;
//        std::vector<point> knots;
//        knots.emplace_back(std::move(triKnot.front()));
//        point first(knots.front());
//        point middle(knots.at(1));
//        point last(knots.back());
//        return 3.0 / (last.getX() - first.getX()) *
//            ((last.getY() - middle.getY()) / (last.getX() - middle.getX()) -
//                (middle.getY() - first.getY()) / (middle.getX() - first.getX()));
//    }
//    double checkCornerCD(const point& corner,
//        const point& first,
//        const point& second)
//    {
//        return (1.0 / 6.0) * (pow(corner.getY(), 3) - corner.getY()) * pow(second.getX() - first.getY(), 2);
//    }
//
//
//
//    const double repeatabilityFactor_;
//    std::vector<point> interpolatedData_;
//};



#endif //SPLINEINTERPOLATION_HPP
