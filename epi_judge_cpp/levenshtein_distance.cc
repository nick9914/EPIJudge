#include <string>
#include <vector>
#include <unordered_map>

#include "test_framework/generic_test.h"
using std::string;
using std::vector;

int LevenshteinDistanceAux(const string& A, const string& B, 
std::unordered_map<std::string, std::unordered_map<std::string, int> >& cache) {
  if(cache.find(A) != cache.end() && cache[A].find(B) != cache[A].end()) {
    //std::cout << "reuse cache: " << cache[A][B] << std::endl;
    return cache[A][B];
  }

  if(A.empty() || B.empty() || A == B) {
    int levDistance = 0;
    if(A == B) {
      levDistance = 0;
    } else if(A.empty()) {
      levDistance = B.size();
    } else {
      levDistance = A.size();
    }    
    cache[A][B] = levDistance;
    //return levDistance;
  } else  {

    if(A[A.size() - 1] == B[B.size() - 1]) {
      cache[A][B] = LevenshteinDistanceAux(A.substr(0, A.size() >= 1 ? A.size() - 1 : 0),
     B.substr(0, B.size() >= 1 ? B.size() - 1 : 0), cache);

    } else {
      //std::cout << "deletionAdjustment: " << A << ", " << B << std::endl;
      int deletionAdjustment = LevenshteinDistanceAux(A.substr(0, A.size() >= 1 ? A.size() - 1 : 0), B, cache);

      //std::cout << "substitutionAdjustment: " << A << ", " << B << std::endl;
      int substitutionAdjustment = LevenshteinDistanceAux(A.substr(0, A.size() >= 1 ? A.size() - 1 : 0),
        B.substr(0, B.size() >= 1 ? B.size() - 1 : 0), cache);
    
      //std::cout << "insertionAdjustment: " << A << ", " << B << std::endl;
      int insertionAdjustment = LevenshteinDistanceAux(A, B.substr(0, B.size() >= 1 ? B.size() - 1 : 0), cache);
      cache[A][B] = 1 + std::min(std::min(deletionAdjustment, substitutionAdjustment), insertionAdjustment);
    }    
  } 
  //std::cout << "result: "  << A << ", " << B << " : " <<cache[A][B] << std::endl;
  return cache[A][B];
}

int LevenshteinDistance(const string& A, const string& B) {
  //cache definition
  //TODO: look at test case and start with simpler example.
  // also googling segmentation fa
  //std::cout << "before recursion" << std::endl;
  std::unordered_map<std::string, std::unordered_map<std::string, int> > cache;
  LevenshteinDistanceAux(A, B, cache);
  //std::cout << "A and B: " << A << ", " << B << std::endl;
  return cache[A][B];
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"A", "B"};
  return GenericTestMain(args, "levenshtein_distance.cc",
                         "levenshtein_distance.tsv", &LevenshteinDistance,
                         DefaultComparator{}, param_names);
}
