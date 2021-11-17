
#include "ppt.h"
#include <vector>

typedef uint8_t u8;   ///<   8-bit unsigned integer.
typedef uint16_t u16; ///<  16-bit unsigned integer.
typedef uint32_t u32; ///<  32-bit unsigned integer.
typedef uint64_t u64; ///<  64-bit unsigned integer.

  uint8_t bagiterator = 7u;
class ppt {

public:
  uint32_t PPTRNG = 0u;
  uint8_t bag[7]{};
  uint32_t GetRand(uint32_t upperBound) {
    uint32_t uVar1;

    PPTRNG = PPTRNG * 0x5d588b65 + 0x269ec3;
    uVar1 = PPTRNG >> 0x10;
    if (upperBound != 0) {
      uVar1 = uVar1 * upperBound >> 0x10;
    }
    return uVar1;
  }
  uint32_t charToPiece(char piece) {
    switch (piece) { 
    case 'S':
        return 0;
    case 'Z':
      return 1;
    case 'J':
      return 2;
    case 'L':
      return 3;
    case 'T':
      return 4;
    case 'O':
      return 5;
    case 'I':
      return 6;
    }
    return 0;
  
  }
  char pieceToChar(int piece) {
    switch (piece) {
    case 0:
      return'i';
    case 1:
      return'z';
    case 2:
      return's';
    case 3:
      return'j';
    case 4:
      return'l';
    case 5:
      return'o';
    case 6:
      return't';    
    }
    return 0;
  }
  void makebag() {
    u32 buffer = 0;
    std::vector<char> pieces = {'S', 'Z', 'J', 'L', 'T', 'O', 'I'};
    uint32_t incrementer{};
    for (u8 i = 7; i > 0; i--) {
      buffer = (u32)GetRand(i % 8);
      bag[incrementer] = charToPiece(pieces[buffer]);
      incrementer++;
      pieces.erase(pieces.begin() + buffer);
    }
  }
} ppt;

// returns a piece 
uint32_t pptRand() {
  
    uint32_t temp{};
    if (bagiterator == 7) {
        //make new bag
        bagiterator = 0;
        ppt.makebag();
        temp = ppt.bag[bagiterator];
        bagiterator++;
        return temp;
    } else {
       temp = ppt.bag[bagiterator];
        bagiterator++;
       return temp;
    }
}

// make a new bag 
void forceReRollBag() {

  ppt.makebag();
}