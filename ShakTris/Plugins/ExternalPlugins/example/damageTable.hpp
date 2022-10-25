#include <array>
#include <stdint.h>
constexpr int DAMAGETABLESIZE = 5;
const std::array<const uint8_t, DAMAGETABLESIZE> damageTable = {
	0,0,1,2,4
};