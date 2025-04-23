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
#include "LagrangePolynomialInterpolation.hpp"
#include "Linspain.hpp"
LagrangePolynomialInterpolation::LagrangePolynomialInterpolation(Data &nodes) {
    namespace ranges = std::ranges;
    for (std::size_t n = 1ull; n < nodes.size()-1ull; ++n)
    {
        push_back(Linspain(nodes[n-1ull],nodes[n],10ull, false));
    }
    push_back(Linspain(nodes[nodes.size()-2ull],nodes[nodes.size()-1ull],10ull, true));
    for (auto& p : *this)
    {
        p.getY_ref() = std::transform_reduce(nodes.begin(), nodes.end(),
                                             0.0, std::plus<double>{},[&](const Point& node)
                                             {
                                                 double t = std::transform_reduce(nodes.x_begin(), nodes.x_end(),
                                                                                  1.0, std::multiplies<double>{},[&](const double& xj)
                                                                                  {
                                                                                      if (&node.getX_ref() == &xj) return 1.0;
                                                                                      return (p.getX() - xj) / (node.getX() - xj);
                                                                                  });
                                                 return node.getY() * t;
                                             });
    }


}
