#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

namespace {
void RemoveFirstTwoChars(std::string& input_string, char char_to_remove) {
  int removed = 0;
  size_t current_index = 0;

  while (current_index < input_string.size() && removed < 2) {
    if (input_string[current_index] != char_to_remove) {
      current_index++;
      continue;
    }

    removed++;
    input_string.erase(current_index, 1);
  }
}
}  // namespace
int main() {
  std::string input_string;
  std::cin >> input_string;

  std::vector<std::pair<char, int>> weights;
  for (int i = 0; i < 26; ++i) {
    int weight = 0;
    std::cin >> weight;
    weights.emplace_back(static_cast<char>('a' + i), weight);
  }

  std::map<char, int> char_frequency;
  for (char c : input_string) {
    char_frequency[c]++;
  }

  std::stable_sort(
      weights.begin(),
      weights.end(),
      [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
        return a.second > b.second;
      }
  );

  std::string start_of_the_result;

  for (auto& weight : weights) {
    char current_char = weight.first;
    if (char_frequency[current_char] >= 2) {
      RemoveFirstTwoChars(input_string, current_char);

      char_frequency[current_char] -= 2;
      start_of_the_result += current_char;
    }
  }

  std::string end_of_the_result(start_of_the_result);

  std::reverse(end_of_the_result.begin(), end_of_the_result.end());

  std::cout << start_of_the_result + input_string + end_of_the_result << '\n';
  return 0;
}
