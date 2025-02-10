#include "pixel.hpp"

// Instructions: Do NOT edit.

// REQUIRES: p1 and p2 are valid pixels
// MODIFIES:
// EFFECTS: Returns the energy between two pixels
int SquaredPixelEnergy(const Pixel& p1, const Pixel& p2) {
  double dr = p2.r - p1.r;
  double dg = p2.g - p1.g;
  double db = p2.b - p1.b;
  // Divide by 100 is to avoid possible overflows later on in the algorithm.
  return (dr * dr + dg * dg + db * db) / 100;
}