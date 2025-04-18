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

#ifndef LINEARINTERPOLATION_HPP
#define LINEARINTERPOLATION_HPP

#include <cstdint>

#include "Data.hpp"


struct LinearInterpolation final : Data
{
    LinearInterpolation(const Data& Nodes, std::size_t interpolationDensity);

    [[nodiscard]] std::size_t getNumberOfNodes() const;
#ifdef TESTS
    friend class LinearInterpolation_tests;
#endif
private:
    std::vector<uint64_t> nodesIndexes_;
    std::size_t interpolationDensity_;
};
#endif //LINEARINTERPOLATION_HPP
