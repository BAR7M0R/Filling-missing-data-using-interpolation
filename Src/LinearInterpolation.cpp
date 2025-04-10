 //
// Created by Dell on 06/04/2025.
//

#include "LinearInterpolation.hpp"

 LinearInterpolation::LinearInterpolation(const Data Nodes, const std::size_t interpolationDensity): Data()
  , nodesIndexes_(Nodes.size(), 0ull)
  , interpolationDensity_(interpolationDensity) {
  for (std::size_t i = 1ull; i < getNumberOfNodes(); i++) {
   bool endNodeFlag = false;
   if (i == getNumberOfNodes() - 1ull) {
    endNodeFlag = true;
   }
   Linspain temp(Nodes[i-1ull], Nodes[i], interpolationDensity, endNodeFlag);
   push_back(temp);
   nodesIndexes_[i] = size() - 1ull;
  }
 }

 std::size_t LinearInterpolation::getNumberOfNodes() const {
  return nodesIndexes_.size();
 }
