#include <iterator>
#include <fstream>
#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include "rnd.h"

//#define _CRT_SECURE_NO_WARNINGS

//masks: 0000 0001, 0000 0010 and etc.
const unsigned char option[8] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };

void main(int argc, char* argv[]) {
  int seed[] = { 170, 85, 240, 15, 204, 51, 227, 28, 1, 2, 4, 8, 16, 32, 64, 128, 212 };
  //if (argc > 0) {
  //  seed = atoi(*argv);
  //  std::cout << *argv;
  //  std::cout << seed;
  //}
  std::vector<bool> mas;
  char* ss = new char[3];
  for (int s = 0; s <= 255; s++) {
    rand_danko(mas, s);
    std::ofstream txt;
    std::string str = itoa(s, ss, 10);
    //txt.open("random" + str +".txt");
    txt.open(str);
    unsigned char symbol[MAX_SIZE / 8] = { 0 };
    for (int i = 0; i < (MAX_SIZE / 8); i++)
      for (int j = 0; j < 8; j++)
        symbol[i] += mas[i * 8 + j] * option[8 - j];
    //std::copy(symbol, symbol + MAX_SIZE / 8, std::ostream_iterator<unsigned char>(txt));
    std::copy(mas.begin(), mas.end(), std::ostream_iterator<bool>(txt));
    txt.close();
    mas.clear();
  }

  //for (size_t i = 0; i < 64; i++)
  //  if(mas[i]) std::cout << '1';
  //  else std::cout << '0';
}