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
#include "Data_tools.hpp"

Cubicspline::Cubicspline(const Point &p0,
                const double &p0_first_deriv,
                const Point &p1,
                const double &p1_second_deriv,
                const std::size_t &numPointsBetween,
                const bool isIncludeLastPoint)
    : Data(Linspain(p0, p1, numPointsBetween, isIncludeLastPoint))
    , A(DataTools::convertDataXToAxi(*this, [&](double& p) {
            p = (p - p1.getX())/(p0.getX()-p1.getX());
          }))
    , B(DataTools::convertDataXToAxi(*this, [&](double& p) {
            p = (p - p0.getX())/(p1.getX()-p0.getX());
          }))
    , C(DataTools::convertAxiToAxi(A, [&](double &p) {
            p = ((1.0/6.0)
                       * (pow(p,3)-p)
                       * pow(p1.getX()-p0.getX(), 2));
          }))
    , D(DataTools::convertAxiToAxi(B, [&](double &p) {
            p = ((1.0/6.0)
                       * (pow(p,3)-p)
                       * pow(p1.getX()-p0.getX(), 2));
          }))
{
    for(std::size_t i = 0; i < size(); ++i)
    {
        (*this)[i] = Point((*this)[i].getX(),
                           A[i]*p0.getY()+B[i]*p1.getY()+C[i]*p0_first_deriv+D[i]*p1_second_deriv);
    }
}
