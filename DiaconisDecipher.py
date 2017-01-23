# author: Rylan Schaeffer
# Python 2, not 3!

import math
import os
import pickle
import random
import requests
import string

# if frequency matrix was already computed, load it
if os.path.isfile('bigramfrequencies.pkl'):
    file = open('bigramfrequencies.pkl', 'rb')
    M = pickle.load(file)

# if frequency matrix isn't already computed, compute it and store it for future use
else:

    # import War and Peace from given url
    warandpeace = str(requests.get('http://web.cs.ucdavis.edu/~rogaway/classes/127/spring16/war-and-peace.txt').text)

    # replace newline characters with spaces
    warandpeace = warandpeace.replace('\n', ' ')

    # replace double spaces with single spaces
    warandpeace = warandpeace.replace('  ', ' ')

    # create frequency matrix
    M = {}
    chars = string.ascii_lowercase + ' '
    for curchar in chars:
        M[curchar] = {}
        for nextchar in chars:
            M[curchar][nextchar] = 0

    # populate frequency matrix with bigram occurrences
    count = 0
    for pos in range(0, len(warandpeace) - 1):

        # if current char or next char is a digit, skip
        if warandpeace[pos] in string.digits or warandpeace[pos+1] in string.digits:
            continue

        # if current char or next char is punctuation, skip
        if warandpeace[pos] in string.punctuation or warandpeace[pos+1] in string.punctuation:
            continue

        # otherwise, increase count and update matrix
        count += 1
        M[warandpeace[pos]][warandpeace[pos+1]] += 1


    # convert bigram occurrences to bigram frequencies
    for curchar in chars:
        for nextchar in chars:
            M[curchar][nextchar] = 1.0 * M[curchar][nextchar] / count

    # save frequency matrix to file for future use
    file = open('bigramfrequencies.pkl', 'wb')
    pickle.dump(M, file)


ciphertext = 'qkne l knixw tkn onixenw iytxrerjnx, qkne tkn uxrray, tkn almbxny, qnxn xiemnw le crobjey hnarxn jn, ' \
    'qkne l qiy ykrqe tkn ckixty iew wlimxijy, tr iww, wlvlwn, iew jniybxn tknj, ' \
    'qkne l ylttlem knixw tkn iytxrerjnx qknxn kn onctbxnw qltk jbck iuuoibyn le tkn onctbxn xrrj, ' \
    'krq yrre beiccrbetihon l hncijn tlxnw iew ylcd, tloo xlylem iew molwlem rbt l qiewnxnw raa hz jzynoa, ' \
    'le tkn jzytlcio jrlyt elmkt ilx, iew axrj tljn tr tljn, orrdnw bu le unxanct ylonecn it tkn ytixy.'


# initial guess will be a random permutation
# bad initial guess! much better guess would be to count single character frequencies and start from there
f = {}
for char in (string.ascii_lowercase + ' '):
    f[char] = char

# randomly shuffle
keys = f.keys()
random.shuffle(keys)
f = dict(zip(keys, f.values()))



# function to calculate plausability of a permutation for a given ciphertext and frequency matrix
def calc_plaus(c, perm, M):

    logPlaus = 0

    for pos in range(0, len(c) - 1):

        # if one of the two characters is punctuation,
        if c[pos] in string.punctuation or c[pos+1] in string.punctuation:

            # if the first character is punctuation, print it
            if c[pos] in string.punctuation:
                print c[pos],

            # otherwise, print the deciphered character
            else:
                print perm[c[pos]],
            # move to next bigram
            continue

        # if first character is a space, don't apply the permutation to the space
        if c[pos] == ' ':
            print ' ',
            value = M[' '][perm[c[pos+1]]]
        # if the second character is a space, don't apply the permutation to the space
        elif c[pos+1] == ' ':
            print perm[c[pos]],
            value = M[perm[c[pos]]][' ']
        else:
            print perm[c[pos]],
            value = M[perm[c[pos]]][perm[c[pos+1]]]

        if value == 0:
            value = 1.0 / 3000000

        logPlaus += math.log(value)

    print '\n'
    return logPlaus



# function to swap two random mappings in a given permutation
def swap_two(f):

    # randomly select two keys
    tobeswapped = random.sample(f.keys(), 2)

    # swap the key's values
    f[tobeswapped[0]], f[tobeswapped[1]] = f[tobeswapped[1]], f[tobeswapped[0]]



count = 0
# begin Diaconis's random walk
while True:

    count += 1

    print 'Iteration: ' + str(count)

    # compute plausability of f
    plF = calc_plaus(ciphertext, f, M)

    # generate F* by switching two random values in f
    fstar = {}
    for key in f.keys():
        fstar[key] = f[key]
    swap_two(fstar)

    # compute plausability of f*
    plFstar = calc_plaus(ciphertext, fstar, M)

    # if Pl(f*) > Pl(f), f* replaces f
    if plFstar > plF:
        f = fstar

    # if Pl(f*) >= Pl(f),
    else:
        # flip a random coin with probability Pl(f*) / Pl(f)
        p = math.exp(plFstar - plF)

        # if coin comes up heads, f* replaces f
        if random.random() < p:
            # print 'plFstar is chosen with probability: ' + str(p)
            f = fstar
