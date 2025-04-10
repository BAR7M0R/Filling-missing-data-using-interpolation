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
