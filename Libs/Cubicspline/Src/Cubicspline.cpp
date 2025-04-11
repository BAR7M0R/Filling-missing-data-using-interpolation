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
#include "Cubicspline.hpp"
#include "Linspain.hpp"
#include <cmath>
#include <algorithm>
#include <ranges>
#include "Data_tools.hpp"

Cubicspline::Cubicspline(const Point &first,
                const double &firstDeriv,
                const Point &second,
                const double &secondDeriv,
                const std::size_t &numPointsBetween,
                const bool isIncludeLastPoint)
    : Data(Linspain(first, second, numPointsBetween, isIncludeLastPoint))
    , A(DataTools::convertDataXToAxi(*this, [&](const double& p) -> double {
            return (p - second.getX())/(first.getX()-second.getX());
          }))
    , B(DataTools::convertDataXToAxi(*this, [&](const double& p) -> double {
            return (p - first.getX())/(first.getX()-second.getX());
          }))
    , C(DataTools::convertAxiToAxi(A, [&](const double &p) -> double {
            return ((1.0/6.0)
                       * (pow(p,3)-p)
                       * pow(second.getX()-first.getX(), 2));
          }))
    , D(DataTools::convertAxiToAxi(B, [&](const double &p) -> double {
            return ((1.0/6.0)
                       * (pow(p,3)-p)
                       * pow(second.getX()-first.getX(), 2));
          }))
{
    for(std::size_t i = 0; i < size(); ++i)
    {
        (*this)[i] = Point((*this)[i].getX(),
                           A[i]*first.getY()+B[i]*second.getY()+C[i]*firstDeriv+D[i]*secondDeriv);
    }
}
