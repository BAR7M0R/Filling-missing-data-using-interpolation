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
#include <catch2/catch_test_macros.hpp>
#include "Data.hpp"
#include "LagrangePolynomialInterpolation.hpp"
TEST_CASE("dummy test")
{
    Data test1({{-3.0,4.0},{-1.0,-5.0},{1.0,-3.0},{1.5,4.0}});
    LagrangePolynomialInterpolation csi(test1);
    auto x = csi.getX();
    auto y = csi.getY();
    REQUIRE(true == true);
}