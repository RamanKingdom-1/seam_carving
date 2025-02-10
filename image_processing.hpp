#ifndef IMAGE_PROCESSING_HPP
#define IMAGE_PROCESSING_HPP

#include "image.hpp"

using namespace std;

constexpr int kHighEnergy = 9999;

// REQUIRES:
// MODIFIES: image_
// EFFECTS: Rotates the image 90 degrees counterclockwise.
/*
image_ 
A B C D
E F G H
I J K L

would become
D H L
C G K
B F J 
A E I
*/
// MP PART: 1
void RotateLeft(Image& image_);

// REQUIRES:
// MODIFIES: image_
// EFFECTS: Rotates the image 90 degrees clockwise.
//          hint: You can use other image_processing functions
/*
image_ 
D H L
C G K
B F J
A E I

would become
A B C D
E F G H
I J K L
*/
// MP PART: 1
void RotateRight(Image& image_);

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the energy matrix for image_. See spec for algorithm.
//          hint: use SquaredPixelEnergy() from pixel.hpp
//          hint: use kHighEnergy
// MP PART: 2
vector<vector<int>> CalculateEnergy(const Image& image_);

// REQUIRES: energy is a rectangle.
// MODIFIES:
// EFFECTS: Returns the vertical cost matrix for energy. See spec for the algorithm.
// MP PART: 2
vector<vector<int>> CalculateCostVertical(const vector<vector<int>>& energy);

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the lowest energy vertical seam in the image. The returned
//          vector's size is image_ height. Each element in the vector is
//          between [0, image_ width). The value at the 0th index indicates the
//          column value of the seam at row 0 and so forth. See spec for the
//          algorithm. hint: You will need to call CalculateEnergy, and
//          CalculateCostVertical.
// MP PART: 2
vector<int> FindVerticalSeam(const Image& image_);

// REQUIRES: seam is of size image_ height and each element in seam is between
//           [0, image width). image_ is a rectangle of pixels.
// MODIFIES: image_
// EFFECTS: Removes one pixel from each row from the image per the col value
//          found in the seam.
// MP PART: 2
void RemoveVerticalSeam(Image& image_, const std::vector<int>& seam);

#endif
