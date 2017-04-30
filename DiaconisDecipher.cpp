//
// Created by rylan on 4/29/17.
//

#include <fstream>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <unordered_map>
#include <vector>

#include "BigramFrequencies.h"
#include "PermutationFunctions.h"

using namespace std;


int main () {

  ifstream bigfile("war-and-peace.txt", ios::in | ios::binary | ios::ate);
  string bigfile_contents;
  unordered_map<char, unordered_map<char, double>> frequency_matrix;
  unordered_map<char, char> current_permutation, potential_permutation;
  long double current_log_plausibility, potential_log_plausibility;

  string ciphertext = "qkne l knixw tkn onixenw iytxrerjnx, qkne tkn uxrray, tkn almbxny, qnxn xiemnw le crobjey "
          "hnarxn jn, qkne l qiy ykrqe tkn ckixty iew wlimxijy, tr iww, wlvlwn, iew jniybxn tknj, qkne l ylttlem knixw"
          " tkn iytxrerjnx qknxn kn onctbxnw qltk jbck iuuoibyn le tkn onctbxn xrrj, krq yrre beiccrbetihon l hncijn "
          "tlxnw iew ylcd, tloo xlylem iew molwlem rbt l qiewnxnw raa hz jzynoa, le tkn jzytlcio jrlyt elmkt ilx, iew "
          "axrj tljn tr tljn, orrdnw bu le unxanct ylonecn it tkn ytixy.";

  // print ciphertext
  cout << ciphertext << endl;

  // read file contents into string
  ifstream::pos_type fileSize = bigfile.tellg();
  bigfile.seekg(0, ios::beg);
  vector<char> bytes(fileSize);
  bigfile.read(&bytes[0], fileSize);
  bigfile_contents = string(&bytes[0], fileSize);
  bigfile.close();

  // initialize frequency matrix
  frequency_matrix = parse_text(bigfile_contents);

  // generate a random initial current_permutation
  generate_permutation(&current_permutation);

  int i = 1;
  long double p;

  while (i < 50000) {
    cout << "Iteration: " << i++ << endl;

    cout << "Current best guess: " << endl;
    current_log_plausibility = permutation_plausibility(frequency_matrix, current_permutation, ciphertext);

    generate_swapped_permutation(&current_permutation, &potential_permutation);

    cout << "Potential better guess: " << endl;
    potential_log_plausibility = permutation_plausibility(frequency_matrix, potential_permutation, ciphertext);



    if ((potential_log_plausibility > current_log_plausibility)) {
      current_permutation = potential_permutation;
    } else {

      p = exp(potential_log_plausibility - current_log_plausibility);

      if ((double) rand() / RAND_MAX < p) {
        current_permutation = potential_permutation;
      }
    }

    cout << endl << endl << endl;

    // sleep to show progress
    usleep(2500000);
  }

  return 0;

}
