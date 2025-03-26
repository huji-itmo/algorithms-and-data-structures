#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> lists_of_paper{};
  std::string last_string;
  while (std::cin >> last_string) {
    lists_of_paper.emplace_back(last_string);
  }

  std::sort(
      lists_of_paper.begin(),
      lists_of_paper.end(),
      [](const std::string& var1, const std::string& var2) { return var1 + var2 > var2 + var1; }
  );

  for (std::string& str : lists_of_paper) {
    std::cout << str;
  }
}
