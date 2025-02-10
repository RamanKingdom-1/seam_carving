#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>

#include "pixel.hpp"

using namespace std;

class Image {
public:
  // REQUIRES: height and width are > 0.
  // MODIFIES: Image
  // EFFECTS: Initializes an image of height x width.
  // MP PART: 1
  Image(int height, int width);

  // REQUIRES: filename leads to a valid PPM P3 file.
  // MODIFIES: Image
  // EFFECTS: Initializes an image from a PPM file at filename.
  //          If the file cannot be opened, throw a runtime_error exception with
  //          the message "File could not be opened."
  // MP PART: 1
  Image(const std::string& filename);

  // REQUIRES:
  // MODIFIES:
  // EFFECTS: Writes the image to a PPM file named filename.
  //          The three header items in the PPM file are not followed by a space, just a 
  //          newline. Each pixel is printed in the format of "<red> <green> <blue> ". 
  //          This includes the last pixel in the row. Each row is followed by a newline. 
  // MP PART: 1
  void SaveToFile(const std::string& filename);

  // REQUIRES: data_ has at least 1 row.
  // MODIFIES:
  // EFFECTS: Returns the width of the 1st row of the image as an int.
  //          Use assert to check the REQUIRES.
  // MP PART: 1
  int Width() const;

  // REQUIRES:
  // MODIFIES:
  // EFFECTS: Returns the image height as an int.
  // MP PART: 1
  int Height() const;

  // REQUIRES: row is between [0, height), and col is between [0, width).
  // MODIFIES:
  // EFFECTS: Returns the pixel at row, col.
  //          Use assert to check the REQUIRES.
  // MP PART: 1
  Pixel GetPixel(int row, int col) const;

  // REQUIRES: row is between [0, height), col is between [0, width), and
  //           new_pixel is a valid pixel.
  // MODIFIES: Image
  // EFFECTS: Sets the pixel at row, col to new_pixel.
  //          Use assert to check the REQUIRES.
  // MP PART: 1
  void SetPixel(int row, int col, Pixel new_pixel);

  // REQUIRES: row is between [0, height), col is between [0, width). There are
  //            at least 2 pixels in row's corresponding row.
  // MODIFIES: Image
  // EFFECTS: Removes the pixel at row, col. Changing that row to have one less
  //          pixel. Use assert to check the requires.
  //          hint: Feel free to use any vector member functions
  // MP PART: 1
  void RemovePixel(int row, int col);

private:
  vector<vector<Pixel>> data_;
};

#endif
