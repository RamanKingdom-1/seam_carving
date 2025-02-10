#ifndef PIXEL_HPP
#define PIXEL_HPP

// Invariant: a Pixel has values between [0, 255].
struct Pixel {
  int r = 0;
  int g = 0;
  int b = 0;
};

// REQUIRES: p1 and p2 are valid pixels
// MODIFIES:
// EFFECTS: Returns the energy between two pixels
int SquaredPixelEnergy(const Pixel& p1, const Pixel& p2);

#endif