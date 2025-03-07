#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <utility>

int main() {
  std::string last_string;

  std::map<std::string, int> var_name_to_var_index;

  std::stack<std::map<int, int>> var_index_to_value;

  // initialize first map
  var_index_to_value.emplace();

  int last_index = 0;

  while (std::cin >> last_string) {
    if (last_string == "}") {
      var_index_to_value.pop();
      continue;
    }

    if (last_string == "{") {
      var_index_to_value.emplace(var_index_to_value.top());  // copy
      continue;
    }

    size_t equals_char_pos = last_string.find('=');

    std::string var_name = last_string.substr(0, equals_char_pos);
    std::string value_string = last_string.substr(equals_char_pos + 1);

    // emplaced
    auto inserted_pair = var_name_to_var_index.try_emplace(var_name, last_index);
    if (inserted_pair.second) {
      last_index++;
    }
    int lvalue_index = inserted_pair.first->second;

    bool is_number =
        std::all_of(value_string.begin(), value_string.end(), [](char character) -> bool {
          return character == '-' || std::isdigit(character) != 0;
        });

    int value = 0;

    if (is_number) {
      value = std::stoi(value_string);
    } else {
      auto iterator = var_name_to_var_index.find(value_string);

      if (iterator != var_name_to_var_index.end()) {
        int index = iterator->second;
        value = var_index_to_value.top()[index];
      }

      std::cout << value << '\n';
    }

    var_index_to_value.top()[lvalue_index] = value;
  }

  return 0;
}
