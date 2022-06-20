#include<iostream>
#include <string.h>
#define XOR(dest, src, size) for(int i = 0; i < size; i++) dest[i] ^= src[i];

using namespace std;

char boxes[8][4][1<<4] = {
  {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
  },
  {
    {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
    {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
    {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
    {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
  },
  {
    {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
    {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
    {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
    {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
  },
  {
    {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
    {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
  },
  {
    {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
    {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
    {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
    {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
  },
  {
    {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
  },
  {
    {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
    {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
    {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
    {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
  },
  {
    {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
    {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
    {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
    {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
  }
};

class DES {
  public:
    char *plain;
    char *key;
    char *cipher;
    char *shifted_key;
    DES(char *key, char *plain);
    char* encrypt();
      void initPerm();
      char* round();
        void expPerm(char *res, char *r);
        void sboxSub(char *res, char *inp);//48->32
        void rPerm(char *res, char *inp);//32->48
      void gen_subkey(char *res);
        void pc1();
        void lshift();
        void pc2(char *subkey);
      void lrSwap();
      void invInitPerm();

    void perm(char *res, char *org, char *box, int N);
    void sub(char* res, char *org, char *box, int N);
    
    //char boxes[8][4][1<<4];//8 sboxes
    //char **boxes[8];//8 sboxes
    /*
    boxes[0] = {
      {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
      {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
      {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
      {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    };
    boxes[1] = {
      {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
      {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
      {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
      {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    };
    boxes[2] = {
      {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
      {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
      {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
      {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    };
    boxes[3] = {
      {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
      {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
      {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
      {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    };
    boxes[4] = {
      {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
      {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
      {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
      {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    };
    boxes[5] = {
      {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
      {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
      {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
      {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    };
    boxes[6] = {
      {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
      {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
      {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
      {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    };
    boxes[7] = {
      {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
      {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
      {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
      {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}
    };
    */
};

DES::DES(char *key, char *plain) {
  this->key = new char[8];
  this->plain = new char[8];
  this->cipher = new char[8];
  this->shifted_key = new char[7];
  this -> pc1();
  strncpy(this->key, key, 64);
  strncpy(this->plain, plain, 64);
}


char* DES::encrypt() {
  this -> initPerm();
  for (int i = 0; i < 16; i++)
    this -> round();
  this -> lrSwap();
  return this->cipher;
}

void DES::initPerm() {
  char iniTable[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
  };
  this -> perm(this->cipher, this->plain, iniTable, 64);
}

char* DES::round() {
  char l[4];
  char r[4];
  strncpy(l, this->cipher, 4);
  strncpy(r, this->cipher+4, 4);
  char res[6];
  this -> expPerm(res, r);
  char subkey[6];
  this -> gen_subkey(subkey);
  fgets(plain, 8, stdin);
  XOR(res, subkey, 6);

  char *res2 = new char[4];
  this -> sboxSub(res2, res);
  char tmp[4];
  strncpy(tmp, res2, 4);
  this -> rPerm(res2, tmp);
  XOR(res2, l, 4);
  strncpy(this->cipher, r, 4);
  strncpy(this->cipher+4, res2, 4);
  return this->cipher;
}

void DES::expPerm(char *res, char *r) {
  char eTable[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8 ,9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
  };
  this -> perm(res, r, eTable, 48);
}

void DES::sboxSub(char *res, char *inp) {
 //48 -> 32
 //8 boxs
  char box_inps[8] = {0};
  for (int i = 0; i < 48; i++) {
    box_inps[i/6] <<= 1;
    box_inps[i/6] |= ( inp[i/6] & (1 << (6 - i%6)) );
  }

  for (int i = 0; i < 8; i++) {
    int row = ((box_inps[i] & 0b100000) >> 4) + box_inps[i] & 1;
    int col = (box_inps[i] & 0b011110) >> 1;
    res[i/2] <<= 4;
    res[i/2] |= boxes[i][row][col];
  }
}

void DES::rPerm(char *res, char *org) {
  char pmat[32] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
  };
  this -> perm(res, org, pmat, 32);
}

void DES::gen_subkey(char *res) {
  lshift();
  pc2(res);
}

void DES::pc1() {
  char pcmat[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 43, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,

    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
  };
  this -> perm(this->shifted_key, this->key, pcmat, 56);
}

void DES::lshift() {
  static int round = 0;
  char rotates[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};
  char last_bit;
  char tmp;
  for (int i = 0; i < rotates[round]; i++) {
    last_bit = this->shifted_key[0] & 1;
    for (int j = 0, cnt = 3 ; j < 3; j++) {
      this->shifted_key[j] <<= 1;
      this->shifted_key[j] |= (shifted_key[j+1] & 0b10000000) > 0 ? 1 : 0;
    }
    // 0-23 bit are shifted
    // let's shift 24-26 bits
    tmp = this->shifted_key[3] & (0b01110000);
    tmp <<= 1;
    this->shifted_key[3] &= (0b00001111);
    this->shifted_key[3] |= tmp;
    // put 27 bit on it
    this->shifted_key[3] |= (last_bit << 4);

    last_bit = shifted_key[3] & 0b1000 > 0 ? 1 : 0;
    tmp = shifted_key[3] & 0b0111;
    tmp <<= 1;
    this->shifted_key[3] &= (0b11110000);
    this->shifted_key[3] |= tmp;
    this->shifted_key[3] &= (shifted_key[4] & 0b10000000) > 0 ? 1 : 0;
    for (int j = 4; j < 7; j++) {
      this->shifted_key[j] <<= 1;
      if (j != 6)
        this->shifted_key[j] |= (shifted_key[j+1] & 0b10000000) > 0 ? 1 : 0;
      else
        this->shifted_key[j] |= last_bit;
    }
  }
  round = (round+1) % 16;
}

void DES::pc2(char *subkey) {
  char pmat[48] = {
    14, 17, 11, 24, 1, 5, 3, 28,
    15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56,
    34, 53, 46, 42, 50, 36, 29, 32
  };
  this -> perm(subkey, this->shifted_key, pmat, 48);
}

void DES::lrSwap() {
  char l[4];
  char r[4];
  strncpy(this->cipher, l, 4);
  strncpy(this->cipher+4, r, 4);
  strncpy(this->cipher+4, l, 4);
  strncpy(this->cipher, r, 4);
}
class DES;

void DES::invInitPerm() {
  char pmat[64] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
  };
  char org[8];
  strncpy(org, this->cipher, 8);
  this -> perm(this->cipher, org, pmat, 64);
}

void DES::perm(char *res, char *org, char *box, int N) {
  memset(res, 0, N);
  int res_ind, org_ind;
  for (int i = 0; i < N; i++) {
    res_ind = i / 8;
    org_ind = box[i] / 8;

    res[res_ind] |= ( (1 << (i % 8)) & org[org_ind] ); //mask and value
  }
}

char *read_eight(char *inp) {
  while(cin.peek() == '\n' || cin.peek() == ' ') cin.get();
  for(int i = 0; i < 8; i++)
    inp[i] = cin.get();
  return inp;
}

int main(void){
  char *plain = new char[9];
  char *key = new char[9];
  //char *cipher = new char[8];
  //cin >> key >> plain;
  read_eight(key);
  read_eight(plain);
  cout << key << " " << plain << '\n';
  DES des(key, plain);
  char* cipher = des.encrypt();
  //cout << hex << int(key[0]);
  for (int i = 0; i < 8; i++){
    cout << hex << int(cipher[i]);
  }
  cout << '\n';
  return 0;
}
