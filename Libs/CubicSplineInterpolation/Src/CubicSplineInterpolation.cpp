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
#include "CubicSplineInterpolation.hpp"

CubicSpinelInterpolation::CubicSpinelInterpolation(Data nodes): Data() {
    auto secondDerivY1 = [](const Point p0, const Point p1, const Point p2, double dy0, double dy2) -> double {
        const double t1 = (p2.getY()-p1.getY())/(p2.getX()-p1.getX());
        const double t2 = (p1.getY()-p0.getY())/(p1.getX()-p0.getX());
        const double t3 = 1.0/6.0*(p1.getX()-p0.getX());
        const double t4 = 1.0/6.0*(p2.getX()-p1.getX());
        const double t5 = 1.0/3.0*(p2.getX()-p0.getX());
        return (t1-t2-t3*dy0-t4*dy2)/t5;
    };
    double sd = secondDerivY1(nodes[0], nodes[1], nodes[2], 0.0, 0.0);
    Cubicspline a(nodes[0], 0.0, nodes[1], sd, 10ull, false);
    push_back(a);
    for (std::size_t nodeIn = 2ull; nodeIn < nodes.size()-1; nodeIn++)
    {
        double prsd = sd;
        sd = secondDerivY1(nodes[nodeIn-1ull], nodes[nodeIn], nodes[nodeIn+1ull], prsd, 0.0);
        a = Cubicspline(nodes[nodeIn-1ull], prsd, nodes[nodeIn], sd, 10ull, false);
        push_back(a);
    }
    a = Cubicspline(nodes[nodes.size()-2ull], sd, nodes[nodes.size()-1ull], 0.0, 10ull, true);
    push_back(a);
}