//
// Created by rylan on 4/29/17.
//

#ifndef PROJECT_COMPUTEPERMUTATIONPLAUSABILITY_H
#define PROJECT_COMPUTEPERMUTATIONPLAUSABILITY_H

double permutation_plausibility(std::unordered_map<char, std::unordered_map<char, double>> frequency_matrix,
                                std::unordered_map<char, char> permutation, std::string ciphertext);

void generate_permutation(std::unordered_map<char, char> *new_permutation);

void generate_swapped_permutation(std::unordered_map<char, char> *current_permutation,
                                  std::unordered_map<char, char> *new_permutation);

#endif //PROJECT_COMPUTEPERMUTATIONPLAUSABILITY_H
