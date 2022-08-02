#include <vector>
#include <unordered_set>
#include <tuple>


#include "test_framework/generic_test.h"
using std::vector;
using std::unordered_set;
using std::tuple;
using std::hash;
using std::get; //TODO: what is this? 

struct HashTuple {
  size_t operator()(const tuple<int, int, int>& t) const {
    return hash<int>()(get<0>(t) ^ get<1>(t) * 1021 ^ get<2>(t) * 1048573);
  }
};

bool isPatternContainedInGridAux(int patternIdx, const vector<int>& pattern, 
int gridXIdx, int gridYIdx, 
const vector<vector<int>>& grid, 
unordered_set<tuple<int, int, int>, HashTuple>& cache) {

  if(patternIdx >= pattern.size()) {
    //Went through the whole pattern
    return true;
  }
     
  for(vector<int> adjacentCoord : vector<vector<int>> {
    vector<int> {gridXIdx + 1, gridYIdx}, // right
    vector<int> {gridXIdx, gridYIdx + 1}, //down
    vector<int> {gridXIdx - 1, gridYIdx}, // left
    vector<int> {gridXIdx, gridYIdx - 1} //up
    }) {
      if(adjacentCoord[0] < grid.size() && adjacentCoord[1] < grid[0].size()) {
        //valid coordinate
        if(cache.find(tuple<int, int, int> {patternIdx, adjacentCoord[0], adjacentCoord[1]}) == cache.end()) {
          if(pattern[patternIdx] == grid[adjacentCoord[0]][adjacentCoord[1]]          
          && isPatternContainedInGridAux(patternIdx + 1, pattern, adjacentCoord[0], adjacentCoord[1], grid, cache)) {
            // matched pattern
            return true;              
          } else {
            cache.insert(tuple<int, int, int>{patternIdx, adjacentCoord[0], adjacentCoord[1]});
          }        
        } else {
          //Cache Used
        }        
      }
  } // end of adjacent node for loop      
  return false;
}

bool IsPatternContainedInGrid(const vector<vector<int>>& grid,
                              const vector<int>& pattern) {
    //Index 0: patternIdx, Index 1: x coordiante, Index 2: y coordiante
    unordered_set<tuple<int, int, int>, HashTuple> cache;
    for(int x = 0; x < grid.size(); x++) {
      for(int y = 0; y < grid[0].size(); y++) {
        if(pattern[0] == grid[x][y] && isPatternContainedInGridAux(1, pattern, x, y, grid, cache)) {
          return true;
        }
      }
    }
    return false;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"grid", "pattern"};
  return GenericTestMain(args, "is_string_in_matrix.cc",
                         "is_string_in_matrix.tsv", &IsPatternContainedInGrid,
                         DefaultComparator{}, param_names);
}
