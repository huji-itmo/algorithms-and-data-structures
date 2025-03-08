// #include <algorithm>
// #include <cctype>
// #include <cstdlib>
// #include <iostream>
// #include <map>
// #include <stack>
// #include <string>

// int main() {
//   std::string last_string;

//   std::stack<std::map<std::string, int>> var_to_value;

//   // initialize first map
//   var_to_value.emplace();

//   while (std::cin >> last_string) {
//     if (last_string == "}") {
//       var_to_value.pop();
//       continue;
//     }

//     if (last_string == "{") {
//       var_to_value.emplace(var_to_value.top());  // copy
//       continue;
//     }

//     size_t equals_char_pos = last_string.find('=');

//     std::string var_name = last_string.substr(0, equals_char_pos);
//     std::string value_string = last_string.substr(equals_char_pos + 1);

//     // emplaced

//     bool is_number =
//         std::all_of(value_string.begin(), value_string.end(), [](char character) -> bool {
//           return character == '-' || std::isdigit(character) != 0;
//         });

//     int value = 0;

//     if (is_number) {
//       value = std::stoi(value_string);
//     } else {
//       value = var_to_value.top()[value_string];
//       std::cout << value << '\n';
//     }

//     // var_index_to_value.top()[lvalue_index] = value;
//     var_to_value.top()[var_name] = value;
//   }

//   return 0;
// }
