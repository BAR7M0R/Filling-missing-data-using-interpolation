//
// Created by Dell on 06/04/2025.
//

#ifndef LINEARINTERPOLATION_HPP
#define LINEARINTERPOLATION_HPP

#include <cstdint>

#include "Data.hpp"
#include "Linspain.hpp"

struct LinearInterpolation final : Data
{
    LinearInterpolation(Data Nodes, std::size_t interpolationDensity);

    [[nodiscard]] std::size_t getNumberOfNodes() const;

private:
    std::vector<uint64_t> nodesIndexes_;
    std::size_t interpolationDensity_;
};
#endif //LINEARINTERPOLATION_HPP
