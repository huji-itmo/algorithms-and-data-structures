#include <iostream>
#include <string>

int main() {
  size_t input_size = 0;
  std::cin >> input_size;

  for (size_t i = 0; i < input_size; i++) {
    std::string new_string;
    std::cin >> new_string;

    size_t len = new_string.length();

    if (len % 2 != 0) {
      std::cout << "NO" << '\n';
      continue;
    }

    std::string left_part = new_string.substr(0, len / 2);
    std::string right_part = new_string.substr(len / 2, len);

    if (left_part == right_part) {
      std::cout << "YES" << '\n';
    } else {
      std::cout << "NO" << '\n';
    }
  }

  return 0;
}
