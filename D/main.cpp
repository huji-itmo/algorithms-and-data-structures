#include <iostream>

int main() {
  int a_input = 0;
  int b_input = 0;
  int c_input = 0;
  int d_input = 0;
  int k_input = 0;
  int yesterday_amount = -1;
  std::cin >> a_input;
  std::cin >> b_input;
  std::cin >> c_input;
  std::cin >> d_input;
  std::cin >> k_input;

  while (k_input > 0) {
    a_input *= b_input;

    if (a_input < c_input) {
      std::cout << "0" << '\n';
      return 0;
    }

    a_input -= c_input;
    a_input = std::min(a_input, d_input);

    if (yesterday_amount == a_input) {
      break;
    }

    yesterday_amount = a_input;
    k_input--;
  }

  std::cout << a_input << '\n';
  return 0;
}
