//
// Created by rylan on 4/29/17.
//

#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>

#include "BigramFrequencies.h"

using namespace std;

unordered_map<char, unordered_map<char, double>> parse_text(string text){

  unordered_map<char, unordered_map<char, double>> frequency_matrix;
  double count;

  // replace newline characters with spaces
  replace(text.begin(), text.end(), '\n', ' ');

  for (int i = 0; i < text.length() - 1; i++){
    // skip double spaces
    if (text[i] == ' ' && text[i+1] == ' ') continue;

    // skip punctuation
    if (ispunct(text[i]) || ispunct(text[i+1])) continue;

    // skip digits
    if (isdigit(text[i]) || isdigit(text[i+1])) continue;

    frequency_matrix[text[i]][text[i+1]]++;
    count++;
  }

  // convert bigram counts to bigram frequencies
  for (auto it1 = frequency_matrix.begin(); it1 != frequency_matrix.end(); it1++) {
    for (auto it2 = it1->second.begin(); it2 != it1->second.end(); it2++) {
      frequency_matrix[it1->first][it2->first] /= count;
    }
  }

  return frequency_matrix;

};