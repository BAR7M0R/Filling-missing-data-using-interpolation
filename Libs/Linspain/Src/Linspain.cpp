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
