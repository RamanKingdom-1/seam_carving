#include "image_processing.hpp"
using namespace std;
#include <algorithm>

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
void RotateLeft(Image& image_) {
  Image savior(image_.Width(), image_.Height());
  vector<Pixel> helper;
  vector<Pixel> emptier;
  for (int i = image_.Width() - 1; i >= 0; i--) {
    for (int p = 0; p < image_.Height(); p++) {
      helper.push_back(image_.GetPixel(p, i));
    }
  }

  int counter = 0;

  for (int i = 0; i < savior.Height(); i++) {
    for (int p = 0; p < savior.Width(); p++) {
      savior.SetPixel(i, p, helper[counter]);
      counter++;
    }
  }

  image_ = savior;
}

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
void RotateRight(Image& image_) {
  RotateLeft(image_);
  RotateLeft(image_);
  RotateLeft(image_);
}

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the energy matrix for image_. See spec for algorithm.
//          hint: use SquaredPixelEnergy() from pixel.hpp
//          hint: use kHighEnergy
// MP PART: 2
vector<vector<int>> CalculateEnergy(const Image& image_) {
  vector<vector<int>> main_man;
  vector<int> helper;
  vector<int> emptier;

  for (int i = 0; i < image_.Height(); i++) {
    for (int p = 0; p < image_.Width(); p++) {
      if (i == 0 || i == image_.Height() - 1 || p == 0 ||
          p == image_.Width() - 1) {
        helper.push_back(kHighEnergy);
      } else {
        int x = SquaredPixelEnergy(image_.GetPixel(i - 1, p),
                                   image_.GetPixel(i + 1, p)) +
                SquaredPixelEnergy(image_.GetPixel(i, p - 1),
                                   image_.GetPixel(i, p + 1));
        helper.push_back(x);
      }
    }
    main_man.push_back(helper);
    helper = emptier;
  }

  return main_man;
}

// REQUIRES: energy is a rectangle.
// MODIFIES:
// EFFECTS: Returns the vertical cost matrix for energy. See spec for the
// algorithm. MP PART: 2
vector<vector<int>> CalculateCostVertical(const vector<vector<int>>& energy) {
  vector<vector<int>> main_returner(energy.size(),
                                    vector<int>(energy[0].size(), 0));

  for (int i = 0; i < energy.size(); i++) {
    for (int p = 0; p < energy[i].size(); p++) {
      if (i == 0) {
        main_returner[i][p] = energy[i][p];
      } else if (p == 0) {
        main_returner[i][p] = energy[i][p] + min(main_returner[i - 1][p],
                                                 main_returner[i - 1][p + 1]);
      } else if (p == energy[i].size() - 1) {
        main_returner[i][p] = energy[i][p] + min(main_returner[i - 1][p],
                                                 main_returner[i - 1][p - 1]);
      } else {
        main_returner[i][p] =
            energy[i][p] +
            min(main_returner[i - 1][p + 1],
                min(main_returner[i - 1][p], main_returner[i - 1][p - 1]));
      }
    }
  }

  return main_returner;
}

void BackwardsFiller(vector<int>& backwards,
                     vector<vector<int>> main_man,
                     int x) {
  int y = x;
  for (int i = main_man.size() - 1; i >= 0; i--) {
    if (i != main_man.size() - 1) {
      if (y == 0) {
        if (main_man[i][y] <= main_man[i][y + 1]) {
          backwards.push_back(y);
        } else {
          backwards.push_back(y + 1);
          y = y + 1;
        }
      } else if (y == main_man[i].size() - 1) {
        if (main_man[i][y] < main_man[i][y - 1]) {
          backwards.push_back(y);
        } else {
          backwards.push_back(y - 1);
          y = y - 1;
        }
      } else {
        if (main_man[i][y] < main_man[i][y - 1] &&
                main_man[i][y] < main_man[i][y + 1] ||
            (main_man[i][y] == main_man[i][y + 1] &&
             main_man[i][y - 1] > main_man[i][y])) {
          backwards.push_back(y);
        } else if (main_man[i][y - 1] <= main_man[i][y] &&
                   main_man[i][y - 1] <= main_man[i][y + 1]) {
          backwards.push_back(y - 1);
          y = y - 1;
        } else if (main_man[i][y + 1] < main_man[i][y] &&
                   main_man[i][y + 1] < main_man[i][y - 1]) {
          backwards.push_back(y + 1);
          y = y + 1;
        }
      }
    }
  }
}

// REQUIRES: image_ is a rectangle of pixels.
// MODIFIES:
// EFFECTS: Returns the lowest energy vertical seam in the image. The returned
//          vector's size is image_ height. Each element in the vector is
//          between [0, image_ width). The value at the 0th index indicates the
//          column value of the seam at row 0 and so forth. See spec for the
//          algorithm. hint: You will need to call CalculateEnergy, and
//          CalculateCostVertical.
// MP PART: 2
vector<int> FindVerticalSeam(const Image& image_) {
  vector<vector<int>> main_man = CalculateCostVertical(CalculateEnergy(image_));
  vector<int> backwards;
  int x = main_man[main_man.size() - 1][0];
  int y = 0;
  for (int i = 0; i < main_man[main_man.size() - 1].size(); i++) {
    if (main_man[main_man.size() - 1][i] < x) {
      y = i;
      x = main_man[main_man.size() - 1][i];
    }
  }
  backwards.push_back(y);

  BackwardsFiller(backwards, main_man, y);

  vector<int> correct;
  for (int i = backwards.size() - 1; i >= 0; i--) {
    correct.push_back(backwards[i]);
  }

  return correct;
}

// REQUIRES: seam is of size image_ height and each element in seam is between
//           [0, image width). image_ is a rectangle of pixels.
// MODIFIES: image_
// EFFECTS: Removes one pixel from each row from the image per the col value
//          found in the seam.
// MP PART: 2
void RemoveVerticalSeam(Image& image_, const std::vector<int>& seam) {
  int counter = 0;
  for (int i = 0; i < seam.size(); i++) {
    image_.RemovePixel(counter, seam[i]);
    counter++;
  }
}