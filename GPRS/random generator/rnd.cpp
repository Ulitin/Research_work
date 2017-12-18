#include "rnd.h"
#include <math.h>
#include <bitset>
#include <vector>
#include <iostream>


//masks: 0000 0001, 0000 0010 and etc.
const unsigned char option[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

//dfinition of notation
//d = 2 4 8 16 ...
// l,w,s[i], i - log2(d)
long int l[5] = { 2, 4, 16, 256, 65536 };
long int w[5] = { 2, 8, 64, 2048, 1048576 };
long int s[5] = { w[1], w[2], w[3], w[4], 137438953472 };



//initial start sequence Danko
void start_init(std::vector<bool> &sequence, unsigned char start) {
  for (size_t i = 0; i < 8; i++)
    if(start & option[i]) 
      sequence[i] = true;
    else 
      sequence[i] = false;
}

//decomposes n into the formula n = i·(2 ·w(d)) + j · d + k
void find_ijk(std::vector<unsigned int> &ijk, int n, int d, int ptr) {
  while (n < (ijk[0] * (2 * w[ptr])             )         )  ijk[0]--;
  while (n < (ijk[0] * (2 * w[ptr]) + ijk[1] * d)         )  ijk[1]--;
  while (n < (ijk[0] * (2 * w[ptr]) + ijk[1] * d) + ijk[2])  ijk[2]--;
}

//finding the n-th bit in sequence (d - component for the expansion of n)
bool alg_danko(std::vector<bool> sequence, int n) {
  std::vector<unsigned int> ijk(3,0);
  int d, ptr = 0;

  //We shall now define the values for n satisfying s(d/2) <=  n < s(d/2)
  do {
    ptr++;
    d = 1 << ptr;
    //init array to max value
    ijk[0] = l[ptr] - 1;
    ijk[1] = 2 * l[ptr] - 1;
    ijk[2] = d - 1;
  } while (n >= s[ptr]);
    find_ijk(ijk, n, d, ptr);

  // befor_elem - pointer to befo elem in array which is it 
  int befor_elem = -1;

  if (ijk[0] == 0)
    return sequence[(l[ptr] - ijk[1] - 1)%l[ptr] * d + ijk[2]];

  if ((ijk[0] + ijk[1]) & 1)
    befor_elem = (ijk[0] - 1) * 2 * w[ptr] + ijk[1] * d + ijk[2];

  if (ijk[1] & 1)
    befor_elem = (ijk[0] - 1) * 2 * w[ptr] + ((ijk[1] + 2) 
      % (2 * l[ptr])) * d + ijk[2];
  else
    befor_elem = (ijk[0] - 1) * 2 * w[ptr] + ((ijk[1] - 2) 
      % (2 * l[ptr])) * d + ijk[2];

  return sequence[befor_elem];
}


void rand_danko(std::vector<bool> &sequence, unsigned char seed) {
  //int size = 8 > int(seed) ? 8 : int(seed);
  system("cls");
  std::cout << "malloc memory";
  sequence.resize(MAX_SIZE);
  system("cls");
  //init 8 value and n < s(d/2)
  start_init(sequence, seed);

  int progress = 0;
  int next_procent;
  for (int i = 8; i < MAX_SIZE; i++) {
    sequence[i] = alg_danko(sequence, i);
    next_procent = int((i * 10) / MAX_SIZE);
    if (progress != next_procent) {
      progress = next_procent;
       system("cls");
      std::cout << progress*10 << "%  Loading...";
    }
  }
}





//bool grey_code(int l, int i, int j) {
//  int test = 2 ^ l - 1;
//
//  if (j == l)
//    if (i > test)
//      return true;
//    else
//      return false;
//
//  int end = 2 ^ (l + 1);
//  if(i <= test) return grey_code(l - 1, i, j);
//  if ((i > test) && (i < end)) return grey_code(l - 1, end - 1 - i, j);
//  
//  throw "don't correct value";
//}
