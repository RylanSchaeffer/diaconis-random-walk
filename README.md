# Breaking Substitution Ciphers with Random Walks on Markov Chains

In ECS127 (Cryptography), Professor Rogaway introduced us to a particularly clever method of deciphering ciphertexts 
encrypted using simple substitution ciphers. The method is well-described in 
[a paper by Persi Diaconis](https://math.uchicago.edu/~shmuel/Network-course-readings/MCMCRev.pdf), with an excellent
example. To summarize, assuming the substitution cipher is a permutation of the English alphabet, 26! possible permutations exist. 
While a brute force solution might work for a Ceasar Cipher, brute forcing a permutation of the English alphabet is 
computationally expensive, if not infeasible.

Instead, if one knows the probability distribution of characters from the plaintext's alphabet, one can
construct a Markov chain in which each state represents a particular substitution cipher i.e. a possible permutation of 
the English alphabet. States are connected if the two permutations are identical except for two input-output
pairs, and those outputs are swapped e.g. Permutation 1 maps a->b and b->q, and Permutation 2 maps a->q and b->a. We 
choose a random state (a random permutation) and compute the "plausability" that this permutation could be the 
true substitution cipher using the aforementioned alphabet probability distribution. We then randomly choose an adjacent
state, and similarly compute the plausability of that permutation. If the plausability of the adjacent permutation is 
greater than the plausability of the current permutation, then we walk to the adjacent state. If not, we flip a biased 
coin and if the coin comes up heads, we walk to the adjacent state regardless.

After about 1500 to 2000 steps, this algorithm (usually) finds an excellent candidate substitution cipher. To me, the 
beautiful part isn't just that this algorithm works or works so much more quickly than brute force, but that it shows
seemingly different fields (cryptography's substitution ciphers and statistics' Markov Chain Monte Carlo methods) can be
used to complement one another.