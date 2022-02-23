
#include "ppt.h"
#include <array>
#include<algorithm>

typedef uint_fast8_t u8;   ///<   8-bit unsigned integer.
typedef uint_fast16_t u16; ///<  16-bit unsigned integer.
typedef uint_fast32_t u32; ///<  32-bit unsigned integer.
typedef uint_fast64_t u64; ///<  64-bit unsigned integer.

uint8_t bagiterator{};
class ppt {

public:
    ppt() {
        makebag();
    }
    u32 PPTRNG{};
    u8 bag[7]{};
    u32 GetRand(u32 upperBound) {
        u32 uVar1;

        PPTRNG = PPTRNG * 0x5d588b65 + 0x269ec3;
        uVar1 = PPTRNG >> 0x10;
        if (upperBound != 0) {
            uVar1 = uVar1 * upperBound >> 0x10;
        }
        return uVar1;
    }
    u32 charToPiece(char piece) {
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
    void makebag() {
        bagiterator = 0;
        u8 buffer = 0;
        std::array<char, 7> pieces = { 'S', 'Z', 'J', 'L', 'T', 'O', 'I' };
        for (int_fast8_t i = 6; i >= 0; i--) {
            buffer = (u32)GetRand(i+1);
            bag[i] = charToPiece(pieces[buffer]);
            std::swap(pieces[buffer], pieces[i]);
        }
    }
} s_ppt;

// returns a piece 
uint_fast32_t pptRand() {
    u32 next = s_ppt.bag[bagiterator];

    if (bagiterator == 6)
        s_ppt.makebag();
    else
        bagiterator++;

    return next;
}

// make a new bag 
void forceReRollBag() {
    s_ppt.makebag();
}