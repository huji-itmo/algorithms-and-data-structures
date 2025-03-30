#include <cstddef>
#include <iostream>
#include <vector>

namespace {

bool CanPlace(const std::vector<int>& stalls, size_t cows, int min_dist) {
  size_t count = 1;
  int last_cow_coord = stalls[0];
  for (size_t i = 1; i < stalls.size(); ++i) {
    if (stalls[i] - last_cow_coord >= min_dist) {
      count++;
      last_cow_coord = stalls[i];
      if (count >= cows) {
        return true;
      }
    }
  }
  return count >= cows;
}

}  // namespace

int main() {
  size_t number_of_stalls = 0;
  size_t number_of_cows = 0;

  std::cin >> number_of_stalls >> number_of_cows;

  std::vector<int> stalls(number_of_stalls);

  for (size_t i = 0; i < number_of_stalls; ++i) {
    std::cin >> stalls[i];
  }

  int left = 1;
  int right = stalls.back() - stalls.front();
  int answer = 0;

  while (left <= right) {
    int mid = left + ((right - left) / 2);

    if (CanPlace(stalls, number_of_cows, mid)) {
      answer = mid;
      left = mid + 1;
    } else {
      right = mid - 1;
    }
  }

  std::cout << answer << '\n';
  return 0;
}
