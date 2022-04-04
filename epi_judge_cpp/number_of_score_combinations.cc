#include <vector>
#include <unordered_map>
#include <unordered_set>

#include "test_framework/generic_test.h"
using std::vector;

int NumCombinationsForFinalScore(int final_score,
                                 const vector<int>& individual_play_scores) {
  // TODO - you fill in here.
  /* cache[i][j]: Number of socre combinations that result in a total of j using
  individual play scores up to i */
  std::vector<vector<int>> cache; //TODO: is there a way to instantiate this?   
  for(int playIdx = 0; playIdx < individual_play_scores.size(); playIdx++) {
    std::vector<int> currentPlayCache(final_score + 1);
    cache.emplace_back(currentPlayCache); 
    cache[playIdx][0] = 1;
    for(int score = 1; score <= final_score; score++) {

      int withScore = (score - individual_play_scores[playIdx]) >= 0 ? 
      cache[playIdx][score] = cache[playIdx][score - individual_play_scores[playIdx]]
      : 0;

      int withoutsocre = playIdx > 0 ? cache[playIdx - 1][score] : 0;

      cache[playIdx][score] = withScore + withoutsocre;      
    }
    //// DEBUG
    // std::cout << "cache for playIdx: " << playIdx << std::endl;
    // for(int cahceValue : cache[playIdx]) {
    //   std::cout << cahceValue << ' ';
    // }
    // std::cout << std::endl;
    //// DEBUG

  } 
  return cache.back().back();   
}

int main(int argc, char* argv[]) {
  std::vector<std::string> args{argv + 1, argv + argc};
  std::vector<std::string> param_names{"final_score", "individual_play_scores"};
  return GenericTestMain(args, "number_of_score_combinations.cc",
                         "number_of_score_combinations.tsv",
                         &NumCombinationsForFinalScore, DefaultComparator{},
                         param_names);
}
