//
// Created by rylan on 4/29/17.
//

#include <algorithm>
#include <iostream>
#include <math.h>
#include <unordered_map>
#include <unordered_set>

#include "PermutationFunctions.h"

using namespace std;

double permutation_plausibility(unordered_map<char, unordered_map<char, double>> frequency_matrix,
                                unordered_map<char, char> permutation, const string ciphertext){

  double frequency, log_plausibility;

  for (int i = 0; i < ciphertext.length(); i++){

    // print the current deciphered character
    if (ispunct(ciphertext[i]) || isspace(ciphertext[i])){
      cout << ciphertext[i];
    } else {
      cout << permutation[ciphertext[i]];
    }

    if (i < ciphertext.length() - 1 && !ispunct(ciphertext[i]) && !ispunct(ciphertext[i+1])){
      // calculate the log probability of the current pair of characters
      frequency = frequency_matrix[permutation[ciphertext[i]]][permutation[ciphertext[i+1]]];

      if (frequency == 0){
        frequency = 1.0 / 3000000.0;
      }

      log_plausibility += log(frequency);
    }
  }

  cout << endl;

  return log_plausibility;

};


void generate_permutation(unordered_map<char, char> *new_permutation) {

  unordered_set<char> characters = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q',
                                    'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  char temp;

  for (char i = 'a'; i <= 'z'; i++){
    temp = *next(begin(characters), rand() % characters.size());
    characters.erase(temp);
    new_permutation->insert(make_pair(i, temp));
  }

};


void generate_swapped_permutation(unordered_map<char, char> *current_permutation,
                                  unordered_map<char, char> *new_permutation) {

  for (auto it = current_permutation->begin(); it != current_permutation->end(); it++){
    (*new_permutation)[it->first] = it->second;
  }

  auto it1 = next(new_permutation->begin(), rand() % new_permutation->size());
  char key1 = it1->first, value1 = it1->second;

  auto it2 = next(new_permutation->begin(), rand() % new_permutation->size());
  char key2 = it2->first, value2 = it2->second;

  (*new_permutation)[key1] = value2;
  (*new_permutation)[key2] = value1;

};