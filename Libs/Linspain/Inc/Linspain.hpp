//
// Created by Dell on 05/04/2025.
//

#ifndef LINSPAIN_HPP
#define LINSPAIN_HPP

#include <vector>
#include "Data.hpp"
#include "Point.hpp"

struct Linspain: Data
{
    Linspain(const Point& first, const Point& second, const std::size_t& numPointsBetween, const bool lastPoint=true);
    bool isIncludeLastPoint() const;
private:
    const bool last_point_;
};
#endif //LINSPAIN_HPP
