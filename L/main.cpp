#include <climits>
#include <deque>
#include <iostream>
#include <vector>

int main() {
  size_t number_of_elements = 0;
  std::cin >> number_of_elements;

  size_t size_of_sliding_window = 0;
  std::cin >> size_of_sliding_window;

  std::vector<int> buffer(size_of_sliding_window);
  std::deque<size_t> window;

  for (size_t i = 0; i < number_of_elements; ++i) {
    size_t buffer_index = i % size_of_sliding_window;
    std::cin >> buffer[buffer_index];

    // Remove elements from the front that are out of the current window
    if (i >= size_of_sliding_window) {
      while (!window.empty() && window.front() <= i - size_of_sliding_window) {
        window.pop_front();
      }
    }

    // Remove elements from the back that are greater than the current element
    while (!window.empty() && buffer[buffer_index] <= buffer[window.back() % size_of_sliding_window]
    ) {
      window.pop_back();
    }

    window.push_back(i);

    // Output the minimum for the current window starting from the first complete window
    if (i >= size_of_sliding_window - 1) {
      std::cout << buffer[window.front() % size_of_sliding_window] << ' ';
    }
  }

  std::cout << '\n';
  return 0;
}
