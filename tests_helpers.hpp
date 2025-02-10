#include <string>
#include <vector>

#include "image.hpp"

using namespace std;

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true if pixel a has the same member variables as pixel b
bool ComparePixels(Pixel a, Pixel b);

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true img is the same as ground_truth
bool CompareImages(const Image& img, const vector<vector<Pixel>>& ground_truth);

// REQUIRES:
// MODIFIES:
// EFFECTS: Returns true img1 is the same as img2
bool CompareImages(const Image& img1, const Image& img2);

bool CompareIntVectors(const vector<vector<int>>& b,
                       const vector<vector<int>>& a);