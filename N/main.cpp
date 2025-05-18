
/*

количество разбитых копилок - количество висячих вершин в графе
upd: не совсем так, любая начальная точка это сломанная копилка.

а если мы ее сломали, то в любом случае можно попробовать пооткрывать ключом и другие.

еще стоит начинать разбитие копилок, с тех, которые могут открыть больше всего других.
*/

#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <iostream>
#include <queue>
#include <utility>
#include <vector>

using BankIndex = uint;

namespace {
void Bfs(
    BankIndex starting_bank,
    std::vector<bool>& visited,
    const std::vector<std::vector<BankIndex>>& adj_banks
) {
  std::queue<BankIndex> banks_to_visit;
  visited[starting_bank] = true;

  banks_to_visit.push(starting_bank);
  while (!banks_to_visit.empty()) {
    BankIndex current_bank = banks_to_visit.front();
    banks_to_visit.pop();

    for (BankIndex adj_bank : adj_banks[current_bank]) {
      if (!visited[adj_bank]) {
        banks_to_visit.push(adj_bank);
        visited[adj_bank] = true;
      }
    }
  }
}
}  // namespace

int main() {
  size_t number_of_banks = 0;
  std::cin >> number_of_banks;

  std::vector<std::vector<BankIndex>> adj_banks(number_of_banks);

  for (BankIndex current_bank = 0; current_bank < number_of_banks; current_bank++) {
    BankIndex bank_with_a_key_to_current_bank = 0;
    std::cin >> bank_with_a_key_to_current_bank;

    // zero based indexing
    bank_with_a_key_to_current_bank--;
    adj_banks[bank_with_a_key_to_current_bank].emplace_back(current_bank);
    adj_banks[current_bank].emplace_back(bank_with_a_key_to_current_bank);
  }

  std::vector<std::pair<size_t, BankIndex>> breaking_order;
  breaking_order.reserve(number_of_banks);
  for (BankIndex current_bank = 0; current_bank < number_of_banks; current_bank++) {
    breaking_order.emplace_back(adj_banks[current_bank].size(), current_bank);
  }
  std::sort(breaking_order.begin(), breaking_order.end(), std::greater<>());

  std::vector<bool> visited(number_of_banks);
  size_t broken_banks_to_get_starting_key = 0;

  for (auto starting_bank_pair : breaking_order) {
    BankIndex starting_bank = starting_bank_pair.second;
    if (visited[starting_bank]) {
      continue;
    }
    // if its not visited then we have to break it to use the key
    broken_banks_to_get_starting_key++;
    Bfs(starting_bank, visited, adj_banks);
  }

  std::cout << broken_banks_to_get_starting_key << '\n';

  return 0;
}
