#include <cctype>
#include <iostream>
#include <map>
#include <stack>
#include <string>

int main() {
  std::string input_string;
  std::cin >> input_string;

  std::stack<char> brackets;
  std::map<int, int> trap_index_to_animal_index;

  std::stack<int> animal_index_stack;
  std::stack<int> trap_index_stack;

  int last_animal_index = 1;
  int last_trap_index = 1;

  for (char character : input_string) {
    if (std::islower(character) != 0) {
      animal_index_stack.push(last_animal_index++);
    } else {
      trap_index_stack.push(last_trap_index++);
    }

    if (brackets.empty()) {
      brackets.push(character);
      continue;
    }

    const char last_char = brackets.top();
    if (std::tolower(character) == std::tolower(last_char) && (character != last_char)) {
      trap_index_to_animal_index[trap_index_stack.top()] = animal_index_stack.top();
      animal_index_stack.pop();
      trap_index_stack.pop();

      brackets.pop();
    } else {
      brackets.push(character);
    }
  }

  if (!brackets.empty()) {
    std::cout << "Impossible" << '\n';
    return 0;
  }

  std::cout << "Possible" << '\n';
  for (auto& pair : trap_index_to_animal_index) {
    std::cout << pair.second << '\n';
  }

  return 0;
}
