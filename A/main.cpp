#include <iostream>

int main() {
  size_t input_size = 0;
  std::cin >> input_size;

  size_t max_count = 0;
  size_t max_staring_index = 1;
  size_t max_ending_index = 0;

  size_t current_repeating_count = 1;
  size_t current_max_count = 0;
  size_t last_begining_index = 1;

  int last_num = 0;

  for (size_t i = 1; i < input_size + 1; i++) {
    int new_num = 0;
    std::cin >> new_num;

    if (new_num == last_num) {
      current_repeating_count++;
    } else {
      current_repeating_count = 1;
    }

    last_num = new_num;
    if (current_repeating_count < 3) {
      current_max_count++;

      if (current_max_count > max_count) {
        max_count = current_max_count;
        max_staring_index = last_begining_index;
        max_ending_index = i;
      }
    } else {
      last_begining_index = i - 1;
      current_max_count = 2;
      current_repeating_count = 2;
    }
  }

  std::cout << max_staring_index << " " << max_ending_index << '\n';

  return 0;
}
