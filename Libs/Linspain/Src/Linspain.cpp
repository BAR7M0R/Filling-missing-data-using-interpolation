//
// Created by Dell on 05/04/2025.
//
#include "Linspain.hpp"

Linspain::Linspain(const Point& first, const Point& second, const std::size_t& numPointsBetween, const bool lastPoint=true)
    : Data(numPointsBetween+1ull, Point{0.0, 0.0}), last_point_(lastPoint) {
    operator[](0ull) = first;
    const size_t totalPoints = numPointsBetween+2ull;
    const Point delta = (second - first) / (totalPoints-1ull);

    for (std::size_t i = 1ull; i < size(); ++i)
    {
        operator[](i) = operator[](i - 1ull) + delta;
    };
    if (lastPoint)
    {
        push_back(second);
    }
}

bool Linspain::isIncludeLastPoint() const {
    return last_point_;
}
