#include "image.hpp"
#include "image_processing.hpp"
using namespace std;

void Remover(Image& x, int size) {
  cout << "hi";
  bool helper = true;
  while (helper) {
    if (x.Width() != size) {
      vector<int> the_helped = FindVerticalSeam(x);
      RemoveVerticalSeam(x, the_helped);
    } else {
      helper = false;
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc == 4) {
    try {
      string photo_name = argv[1];
      Image savior(photo_name);
      int width = stoi(argv[2]);
      int height = stoi(argv[3]);

      if (savior.Width() < width) {
        cout << "Width is too big. We cannot currently grow the image." << endl;
        return 0;
      }

      if (savior.Height() < height) {
        cout << "Height is too big. We cannot currently grow the image."
             << endl;
        return 0;
      }

      Remover(savior, width);
      RotateLeft(savior);
      Remover(savior, height);
      RotateRight(savior);

      string full_name = photo_name.substr(0, photo_name.size() - 4) +
                         to_string(width) + "x" + to_string(height) +
                         "_actual.ppm";
      savior.SaveToFile(full_name);

    } catch (...) {
      cout << "File could not be opened." << endl;
      return 0;
    }
  } else {
    cout << "The format is, <image_name> <new_width> <new_height>" << endl;
    return 0;
  }
}