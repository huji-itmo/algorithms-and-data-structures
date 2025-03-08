#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>

int main() {
  std::string last_string;

  std::unordered_map<std::string, std::stack<int>> var_name_to_value_history;

  std::stack<std::unordered_set<std::string>> used_vars_inside_a_block_stack(
      {std::unordered_set<std::string>{}}
  );

  while (std::cin >> last_string) {
    if (last_string == "}") {
      for (const std::string& var_name : used_vars_inside_a_block_stack.top()) {
        auto var_history_iterator = var_name_to_value_history.find(var_name);

        bool found = var_history_iterator != var_name_to_value_history.end();

        if (found) {
          var_history_iterator->second.pop();

          if (var_history_iterator->second.empty()) {
            // in this case variable was declared inside a block and we can discard it
            var_name_to_value_history.erase(var_history_iterator->first);
          }
        }
      }

      used_vars_inside_a_block_stack.pop();
      continue;
    }

    if (last_string == "{") {
      // push an empty one
      used_vars_inside_a_block_stack.emplace();

      continue;
    }

    size_t equals_char_pos = last_string.find('=');

    std::string lvalue_name = last_string.substr(0, equals_char_pos);
    std::string rvalue_string = last_string.substr(equals_char_pos + 1);

    bool rvalue_is_number =
        std::all_of(rvalue_string.begin(), rvalue_string.end(), [](char character) -> bool {
          return character == '-' || std::isdigit(character) != 0;
        });

    int rvalue = 0;

    if (rvalue_is_number) {
      rvalue = std::stoi(rvalue_string);
    } else {
      auto iterator = var_name_to_value_history.find(rvalue_string);

      if (iterator != var_name_to_value_history.end()) {
        rvalue = iterator->second.top();
      }
      // if value is not found, the default is zero
      std::cout << rvalue << '\n';
    }

    auto emplace_result = var_name_to_value_history.emplace(lvalue_name, std::stack<int>{});
    // bool new_variable = emplace_result.second;
    // std::stack variable_history = emplace_result.first->second;

    auto is_var_emplaced = used_vars_inside_a_block_stack.top().emplace(lvalue_name).second;
    if (!is_var_emplaced) {
      // variable overwrite
      emplace_result.first->second.pop();
    }

    // push value to the stack
    emplace_result.first->second.push(rvalue);
  }

  return 0;
}

void close_code_block() {
}
