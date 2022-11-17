#include <iostream>
int main () {
  int* arr = new int[5]{};
  for (int i = 0; i < 3; ++i) {
    delete (arr + i);
  }
  for (int i = 3; i < 5; ++i) {
    std::cout << arr[i] << ' ';
  }
  for (int i = 0; i < 5; ++i) {
    std::cout << arr[i] << ' ';
  }
}