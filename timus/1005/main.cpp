#include <iostream>
#include <vector>
//O(n*2^n)
int main() {
  int number_of_stones = 0;
  std::cin >> number_of_stones;
  std::vector<int> stones(number_of_stones);
  int total_sum = 0;
  for (int i = 0; i < number_of_stones; ++i) {
    std::cin >> stones[i];
    total_sum += stones[i];
  }

  int max_sum = 0;
  int target = total_sum / 2;

  for (int mask = 0; mask < (1 << number_of_stones); mask++) {
    int current = 0;
    for (int i = 0; i < number_of_stones; ++i) {
      if ((mask & (1 << i)) != 0) {
        current += stones[i];
        if (current > target) {
          break;
        }
      }
    }
    if (current > max_sum && current <= target) {
      max_sum = current;
    }
  }

  std::cout << total_sum - (2 * max_sum) << '\n';

  return 0;
}
