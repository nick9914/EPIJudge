#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistanceAux(const string& A, const string& B, int AIdx, int BIdx,
vector<vector<int>>& cache) {

  if(AIdx < 0 || BIdx < 0) {
    return AIdx < 0 ? BIdx + 1 : AIdx + 1;    
  }

  if(cache[AIdx][BIdx] == -1) {
    if(A[AIdx] == B[BIdx]) {
      cache[AIdx][BIdx] = LevenshteinDistanceAux(A,B, AIdx - 1, BIdx -1 , cache);
    } else {      
      int deletionAdjustment = LevenshteinDistanceAux(A, B, AIdx -1, BIdx, cache);

      int substitutionAdjustment = LevenshteinDistanceAux(A, B, AIdx - 1, BIdx - 1, cache);
    
      int insertionAdjustment = LevenshteinDistanceAux(A, B, AIdx, BIdx -1, cache);
    
      cache[AIdx][BIdx] = 1 + std::min({deletionAdjustment, substitutionAdjustment, 
        insertionAdjustment});
    }    
  }
  return cache[AIdx][BIdx];
}

int LevenshteinDistance(const string& A, const string& B) {
  //cache definition
  vector<vector<int>> cache(A.size(), vector<int>(B.size(), -1));
  LevenshteinDistanceAux(A, B, A.size() -1 , B.size() - 1, cache);
  //std::cout << "A and B: " << A << ", " << B << std::endl;
  return cache[A.size() -1 ][B.size() - 1];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
