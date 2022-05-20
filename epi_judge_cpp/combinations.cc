#include <vector>
#include <memory>

#include "test_framework/generic_test.h"
using std::vector;

void CombinationsAux(int n, int k, int offset, vector<int>& partialResult, vector<vector<int>>& result) {
 if(partialResult.size() == k) {
   result.emplace_back(partialResult);
   return;
 }
 for(int i = offset; i <= n && partialResult.size() < k + 1; i++) {
   partialResult.emplace_back(i);
   CombinationsAux(n, k, i + 1, partialResult, result);
   partialResult.pop_back();
 }
}
 
vector<vector<int>> Combinations(int n, int k) {
 vector<vector<int>> result;
 vector<int> partialResult; //TODO, since we don't really need this variable look up how we can use make_shared or any other ideas
 CombinationsAux(n, k, 1, partialResult, result);
 return result;
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(args, "combinations.cc", "combinations.tsv",
                         &Combinations, UnorderedComparator{}, param_names);
}
