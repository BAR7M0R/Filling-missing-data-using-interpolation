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
#ifndef SPLINE_HPP
#define SPLINE_HPP

#include "Data.hpp"
#include "Point.hpp"

class Cubicspline final : public Data
{
public:
    Cubicspline(const Point &first,
                const double &firstDeriv,
                const Point &second,
                const double &secondDeriv,
                const std::size_t &numPointsBetween,
                bool isIncludeLastPoint = true);
private:
  data_axi A;
  data_axi B;
  data_axi C;
  data_axi D;

};

#endif //SPLINE_HPP
