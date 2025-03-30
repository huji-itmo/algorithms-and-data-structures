#include <algorithm>
#include <cstddef>
#include <iostream>
#include <vector>

int main() {
  size_t a_val = 0;
  size_t b_val = 0;
  size_t c_val = 0;
  size_t d_val = 0;
  size_t k_val = 0;
  std::cin >> a_val;
  std::cin >> b_val;
  std::cin >> c_val;
  std::cin >> d_val;
  std::cin >> k_val;

  std::vector<size_t> history;
  size_t current = a_val;
  history.push_back(current);

  for (size_t day = 1; day <= k_val; ++day) {
    size_t new_val = current * b_val;
    if (new_val < c_val) {
      std::cout << 0 << '\n';
      return 0;
    }
    size_t temp = new_val - c_val;
    if (temp <= 0) {
      std::cout << 0 << '\n';
      return 0;
    }
    temp = std::min(temp, d_val);

    if (temp == current) {
      std::cout << temp << '\n';
      return 0;
    }

    auto it = std::find(history.begin(), history.end(), temp);
    if (it != history.end()) {
      size_t pos = it - history.begin();
      size_t cycle_length = day - pos;
      size_t remaining_days = k_val - day;
      size_t final_pos = pos + (remaining_days % cycle_length);
      std::cout << history[final_pos] << '\n';
      return 0;
    }

    if (history.size() > d_val + 2) {
      break;
    }

    history.push_back(temp);
    current = temp;
  }

  std::cout << current << '\n';
  return 0;
}
