#include <algorithm>
#include <cstddef>
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <vector>

int main() {
  std::string input_string;
  std::getline(std::cin, input_string);

  const int letters_in_alphabet = 26;

  std::map<char, int> character_weights;
  std::map<char, int> character_frequency;

  for (auto char_in_string : input_string) {
    character_frequency[char_in_string]++;
  }

  for (size_t i = 0; i < letters_in_alphabet; i++) {
    int input_weight = 0;
    std::cin >> input_weight;

    auto current_char = static_cast<unsigned char>('a' + i);

    character_weights.emplace(current_char, input_weight);
  }

  std::vector<char> multi_occurrence_chars;
  for (int i = 0; i < letters_in_alphabet; ++i) {
    char current_char = static_cast<char>('a' + i);

    if (character_frequency[current_char] >= 2) {
      multi_occurrence_chars.push_back(current_char);
    }
  }

  std::sort(
      multi_occurrence_chars.begin(),
      multi_occurrence_chars.end(),
      [&character_weights](char var1, char var2) {
        return character_weights[var1] > character_weights[var2];
      }
  );

  size_t left = 0;
  size_t right = input_string.length() - 1;

  std::string output_string(input_string.length(), ' ');

  for (char chr : multi_occurrence_chars) {
    if (character_frequency[chr] >= 2 && left <= right) {
      output_string[left] = chr;
      output_string[right] = chr;
      character_frequency[chr] -= 2;
      left++;
      right--;
    }
  }

  std::vector<char> single_occurrence_chars;
  for (char chr : input_string) {
    if (character_frequency[chr] > 0) {
      single_occurrence_chars.push_back(chr);
      character_frequency[chr]--;
    }
  }

  //   std::sort(
  //       single_occurrence_chars.begin(),
  //       single_occurrence_chars.end(),
  //       [&character_weights](char var1, char var2) {
  //         return character_weights[var1] < character_weights[var2];
  //       }
  //   );

  for (char chr : single_occurrence_chars) {
    if (left > right) {
      break;
    }
    output_string[left++] = chr;
  }

  std::cout << output_string << '\n';

  return 0;
}
