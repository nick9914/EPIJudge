#include "test_framework/generic_test.h"


int NumberOfWaysAux(int x, int y, std::vector<std::vector<int>>& cache) {
 if(x == 0 || y == 0) {
   return 1;
 }
 
 if(!cache[x][y]) {
   int numberOfWaysLeft = NumberOfWaysAux(x - 1, y, cache);
   int numberOfWaysUp = NumberOfWaysAux(x, y - 1, cache);
   cache[x][y] = numberOfWaysLeft + numberOfWaysUp;   
 }
 return cache[x][y]; 
}
 
int NumberOfWays(int n, int m) {
 std::vector<std::vector<int>> cache (n, std::vector<int>(m, 0));
 return NumberOfWaysAux(n - 1, m - 1, cache);
}


int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "m"};
  return GenericTestMain(args, "number_of_traversals_matrix.cc",
                         "number_of_traversals_matrix.tsv", &NumberOfWays,
                         DefaultComparator{}, param_names);
}
