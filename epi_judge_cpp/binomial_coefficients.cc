#include "test_framework/generic_test.h"
#include "vector"

using std::vector;


int ComputeBinomialCoefficientAux(int n, int k, vector<vector<int>>& cache) {
  if(n < 0  || (k > n)) {
    return 0;
  } else if( (n == 1) || (k == 0)) {
    return 1;
  } else if(cache[n][k] == -1) {
    cache[n][k] = ComputeBinomialCoefficientAux(n -1, k, cache) 
    + ComputeBinomialCoefficientAux(n - 1, k - 1, cache);
  }
  return cache[n][k];
}

int ComputeBinomialCoefficient(int n, int k) {
  // TODO - you fill in here.
  // Effectively the binomial coefficient is n choose k. 
  // We already know how to solve n choose k recursively, so lets use that solution
  vector<vector<int>> cache(n + 1, vector<int>(k + 1, -1));
  ComputeBinomialCoefficientAux(n, k, cache);

  return ComputeBinomialCoefficientAux(n, k, cache);
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"n", "k"};
  return GenericTestMain(
      args, "binomial_coefficients.cc", "binomial_coefficients.tsv",
      &ComputeBinomialCoefficient, DefaultComparator{}, param_names);
}
