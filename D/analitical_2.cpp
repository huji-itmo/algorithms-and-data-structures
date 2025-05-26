#include <algorithm>
#include <iostream>

int main() {
  // Input values
  int64_t initial_bacteria = 0;
  int64_t multiplier = 0;
  int64_t removed_per_day = 0;
  int64_t max_capacity = 0;
  int64_t days = 0;

  // Read input
  std::cin >> initial_bacteria >> multiplier >> removed_per_day >> max_capacity >> days;

  // Special case: if bacteria don't multiply (multiplier = 1)
  if (multiplier == 1) {
    if (removed_per_day == 0) {
      // Bacteria count remains constant, just cap at max_capacity
      std::cout << std::min(initial_bacteria, max_capacity);
      return 0;
    }

    // If initial bacteria are not enough for the first day
    if (initial_bacteria < removed_per_day) {
      std::cout << 0;
      return 0;
    }

    // Calculate how many full days the bacteria can survive
    int64_t max_full_days = initial_bacteria / removed_per_day;

    if (days <= max_full_days) {
      // Bacteria still exist after 'days' days
      int64_t remaining = initial_bacteria - (days * removed_per_day);
      std::cout << std::min(remaining, max_capacity);
    } else {
      // All bacteria are gone before the end of 'days'
      std::cout << 0;
    }
    return 0;
  }

  int64_t current_bacteria = initial_bacteria;
  bool has_stabilized = false;

  for (int64_t day = 0; day < days && !has_stabilized; ++day) {
    // Multiply bacteria and remove the used ones
    int64_t multiplied = current_bacteria * multiplier;
    int64_t after_removal = multiplied - removed_per_day;

    // If bacteria count drops below zero, experiment ends
    if (after_removal < 0) {
      std::cout << 0;
      return 0;
    }

    // Cap at max capacity
    int64_t next_bacteria = std::min(after_removal, max_capacity);

    // If no change occurs, further iterations won't change anything
    if (next_bacteria == current_bacteria) {
      break;
    }

    current_bacteria = next_bacteria;

    // Check if we've reached max capacity and the population is stable
    // This happens when d * (b - 1) >= c
    if (current_bacteria == max_capacity && max_capacity * (multiplier - 1) >= removed_per_day) {
      has_stabilized = true;
    }
  }

  // Output the final bacteria count after k days
  std::cout << current_bacteria;
  return 0;
}
