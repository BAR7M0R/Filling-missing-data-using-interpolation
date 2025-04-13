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

#include <vector>
#include "Cubicspline.hpp"

struct Cubicspline_tests {
    static data_axi get_private_A(const Cubicspline& obj) {
        return obj.A;
    }
    static data_axi get_private_B(const Cubicspline& obj) {
        return obj.B;
    }
    static data_axi get_private_C(const Cubicspline& obj) {
        return obj.C;
    }
    static data_axi get_private_D(const Cubicspline& obj) {
        return obj.D;
    }
};

TEST_CASE("dummy test") {
    Cubicspline cspl(Point(1.0, 1.0), 0.0 , Point(4.0, 2.0), 1.0, 8, true);
    auto A = Cubicspline_tests::get_private_A(cspl);
    auto B = Cubicspline_tests::get_private_B(cspl);
    auto C = Cubicspline_tests::get_private_C(cspl);
    auto D = Cubicspline_tests::get_private_D(cspl);
    auto out = cspl.get();
    REQUIRE(cspl.size() == 10);
}
