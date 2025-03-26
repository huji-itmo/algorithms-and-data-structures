#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  int items_total = 0;
  int free_every_kth = 0;
  std::cin >> items_total >> free_every_kth;

  std::vector<int> item_prices(items_total);
  for (int i = 0; i < items_total; ++i) {
    std::cin >> item_prices[i];
  }
  std::sort(item_prices.begin(), item_prices.end());

  size_t total_cost = 0;
  for (int price : item_prices) {
    total_cost += price;
  }

  size_t free_discount = 0;
  int current_position = items_total - 1;  // Start from the most expensive item

  // Process groups from expensive to cheap to maximize free items
  while (current_position >= 0) {
    const int group_start = current_position - free_every_kth + 1;

    if (group_start >= 0) {
      // The cheapest item in current group becomes free
      free_discount += item_prices[group_start];
      current_position = group_start - 1;  // Move to next group
    } else {
      break;  // Not enough items left to form a full group
    }
  }

  std::cout << total_cost - free_discount << '\n';

  return 0;
}
