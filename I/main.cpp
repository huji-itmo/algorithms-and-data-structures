#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using ToyID = int;
using NextOccurrenceIndex = int;

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);
  std::cout.tie(nullptr);

  int total_unique_toys = 0;
  int cache_capacity = 0;
  int num_requests = 0;
  std::cin >> total_unique_toys >> cache_capacity >> num_requests;

  std::vector<ToyID> requests(num_requests);
  for (int i = 0; i < num_requests; ++i) {
    std::cin >> requests[i];
  }

  // Precompute next occurrence indices
  std::vector<NextOccurrenceIndex> next_occurrence(num_requests, num_requests);
  std::unordered_map<ToyID, NextOccurrenceIndex> next_position_map;

  for (int i = num_requests - 1; i >= 0; --i) {
    ToyID current_toy = requests[i];
    if (next_position_map.count(current_toy) != 0U) {
      next_occurrence[i] = next_position_map[current_toy];
    } else {
      next_occurrence[i] = num_requests;
    }
    next_position_map[current_toy] = i;
  }

  // Simulate cache using Belady's algorithm
  std::unordered_map<ToyID, NextOccurrenceIndex> cache_entries;
  std::set<std::pair<NextOccurrenceIndex, ToyID>, std::greater<>> eviction_set;

  int cache_misses = 0;

  for (int i = 0; i < num_requests; ++i) {
    ToyID current_toy = requests[i];
    auto cache_entry = cache_entries.find(current_toy);

    if (cache_entry != cache_entries.end()) {
      NextOccurrenceIndex old_next = cache_entry->second;
      eviction_set.erase({old_next, current_toy});
      NextOccurrenceIndex new_next = next_occurrence[i];
      eviction_set.insert({new_next, current_toy});
      cache_entries[current_toy] = new_next;
    } else {
      ++cache_misses;
      if (cache_entries.size() < cache_capacity) {
        NextOccurrenceIndex new_next = next_occurrence[i];
        cache_entries[current_toy] = new_next;
        eviction_set.insert({new_next, current_toy});
      } else {
        auto evict_candidate = eviction_set.begin();
        ToyID evicted_toy = evict_candidate->second;
        eviction_set.erase(evict_candidate);
        cache_entries.erase(evicted_toy);

        NextOccurrenceIndex new_next = next_occurrence[i];
        cache_entries[current_toy] = new_next;
        eviction_set.insert({new_next, current_toy});
      }
    }
  }

  std::cout << cache_misses << '\n';

  return 0;
}
