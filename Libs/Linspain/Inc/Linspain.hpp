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
