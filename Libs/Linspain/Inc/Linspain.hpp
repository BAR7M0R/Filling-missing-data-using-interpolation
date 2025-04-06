//
// Created by Dell on 05/04/2025.
//

#ifndef LINSPAIN_HPP
#define LINSPAIN_HPP

#include <vector>
#include "Data.hpp"
#include "Point.hpp"


struct Linspain final : Data
{
    Linspain(const Point& first, const Point& second, const size_t& numPoints)
        : Data(numPoints, Point{0.0, 0.0})
    {
        Data::operator[](0ull) = first;
        Data::operator[](Data::size() - 1ull) = second;
        const Point delta = (second - first) / (numPoints - 1ull);
        for (std::size_t i = 1ull; i < Data::size() - 1ull; ++i)
        {
            Data::operator[](i) = Data::operator[](i - 1ull) + delta;
        };
    }
};
#endif //LINSPAIN_HPP
