#include "image.hpp"
using namespace std;

// Write the member functions of Image below.

// REQUIRES: height and width are > 0.
// MODIFIES: Image
// EFFECTS: Initializes an image of height x width.
// MP PART: 1

// I BELIEVE THIS WORKS
Image ::Image(int height, int width) {
  Pixel helper;
  helper.r = 0;
  helper.b = 0;
  helper.g = 0;
  vector<Pixel> helper_two;
  for (int i = 0; i < width; i++) {
    helper_two.push_back(helper);
  }
  for (int i = 0; i < height; i++) {
    data_.push_back(helper_two);
  }
}

// REQUIRES: filename leads to a valid PPM P3 file.
// MODIFIES: Image
// EFFECTS: Initializes an image from a PPM file at filename.
//          If the file cannot be opened, throw a runtime_error exception with
//          the message "File could not be opened."
// MP PART: 1
Image ::Image(const std::string& filename) {
  ifstream op(filename);
  Pixel gopher;
  vector<Pixel> getter;
  vector<Pixel> emptier;
  if (!op) {
    throw runtime_error("File could not be opened.");
  }
  string helper;
  int width = -1;
  bool the_255 = false;
  bool the_width = false;
  bool the_length = false;
  int counter = 0;
  int helper_two;

  while (op >> helper) {
    try {
      helper_two = stoi(helper);
      if (!the_width) {
        the_width = true;
        width = helper_two;
      } else if (!the_length) {
        the_length = true;
      } else if (!the_255) {
        the_255 = true;
      } else {
        if (counter % 3 == 0) {
          gopher.r = helper_two;
          counter++;
        } else if (counter % 3 == 1) {
          gopher.g = helper_two;
          counter++;
        } else if (counter % 3 == 2) {
          gopher.b = helper_two;
          getter.push_back(gopher);
          counter++;
        }

        if (getter.size() == width) {
          data_.push_back(getter);
          getter = emptier;
        }
      }
    } catch (invalid_argument) {
    }
  }
}

// REQUIRES:
// MODIFIES:
// EFFECTS: Writes the image to a PPM file named filename.
//          The three header items in the PPM file are not followed by a space,
//          just a newline. Each pixel is printed in the format of "<red>
//          <green> <blue> ". This includes the last pixel in the row. Each row
//          is followed by a newline.
// MP PART: 1

// I BELIEVE THIS IS COMPLETE
void Image ::SaveToFile(const std::string& filename) {
  ofstream op(filename);
  op << "P3" << '\n' << Width() << ' ' << Height();
  op << '\n' << 255 << '\n';

  for (int i = 0; i < data_.size(); i++) {
    for (Pixel x : data_[i]) {
      op << x.r << ' ' << x.g << ' ' << x.b << ' ';
    }
    if (i < data_.size() - 1) {
      op << '\n';
    }
  }
  op << '\n';
}
// REQUIRES: data_ has at least 1 row.
// MODIFIES:
// EFFECTS: Returns the width of the 1st row of the image as an int.
//          Use assert to check the REQUIRES.
// MP PART: 1
int Image ::Width() const { return data_[0].size(); }

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns the image height as an int.
// MP PART: 1
int Image::Height() const { return data_.size(); }

// REQUIRES: row is between [0, height), and col is between [0, width).
// MODIFIES:
// EFFECTS: Returns the pixel at row, col.
//          Use assert to check the REQUIRES.
// MP PART: 1
Pixel Image ::GetPixel(int row, int col) const {
  assert(row >= 0 && row < Height());
  assert(col >= 0 && col < data_[row].size());
  return data_[row][col];
}

// REQUIRES: row is between [0, height), col is between [0, width), and
//           new_pixel is a valid pixel.
// MODIFIES: Image
// EFFECTS: Sets the pixel at row, col to new_pixel.
//          Use assert to check the REQUIRES.
// MP PART: 1
void Image ::SetPixel(int row, int col, Pixel new_pixel) {
  assert(row >= 0 && row < Height());
  assert(col >= 0 && col < data_[row].size());
  data_[row][col] = new_pixel;
}

// REQUIRES: row is between [0, height), col is between [0, width). There are
//            at least 2 pixels in row's corresponding row.
// MODIFIES: Image
// EFFECTS: Removes the pixel at row, col. Changing that row to have one less
//          pixel. Use assert to check the requires.
//          hint: Feel free to use any vector member functions
// MP PART: 1
void Image ::RemovePixel(int row, int col) {
  assert(row >= 0 && row < Height());
  assert(col >= 0 && col < data_[row].size());
  assert(data_[row].size() >= 2);
  data_[row].erase(data_[row].begin() + col);
}
