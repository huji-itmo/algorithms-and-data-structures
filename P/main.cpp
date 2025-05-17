#include <algorithm>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <map>
#include <queue>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/*

This problem has a full graph with weighed edges

approach is to for each vertex leave the smallest weighted vertex

but then there is a chance that there will be floating vertexes left out

We need to find smallest possible subtree by sum, then take its max edge

Why tree?

Suppose that we have a loop inside a graph,
then to travel to each city of this loop we need to
consider just the max edge of this graph

we dont care about the sum, we just need the least volume fuel tank

then each loop inside a graph can be resolved to a tree,
hence the left out graph of optimal travels can't have a loop inside of it.

then graph of optimal travels is a tree, constructed from a full graph. a sub tree.

we need to use primes algorithm to create a least sum subtree inside this full graph.

нам выгодно использовать использовать такую структуру данных, чтобы быстро находить минимально
возможное ребро внутри вершины, при этом нужно учесть что мы будем хранить все использованные ребра

*/

using CityIndex = size_t;
using EdgeWeight = size_t;

using Edge = std::pair<EdgeWeight, CityIndex>;

int main() {
  size_t number_of_cities = 0;
  std::cin >> number_of_cities;

  std::vector<std::vector<CityIndex>> initial_matrix(
      number_of_cities, std::vector<CityIndex>(number_of_cities)
  );

  for (size_t i = 0; i < number_of_cities; i++) {
    for (size_t j = 0; j < number_of_cities; j++) {
      EdgeWeight current_city_weight = 0;

      std::cin >> current_city_weight;

      initial_matrix[i][j] = current_city_weight;
    }
  }

  for (CityIndex i = 0; i < number_of_cities; ++i) {
    for (CityIndex j = i + 1; j < number_of_cities; ++j) {
      EdgeWeight sym_weight = std::min(initial_matrix[i][j], initial_matrix[j][i]);
      initial_matrix[i][j] = sym_weight;
      initial_matrix[j][i] = sym_weight;
    }
  }

  // each city has n-1 edges in a full graph
  std::vector<std::vector<Edge>> city_index_to_adj(
      number_of_cities, std::vector<Edge>(number_of_cities - 1)
  );

  for (CityIndex i = 0; i < number_of_cities; ++i) {
    for (CityIndex j = 0; j < number_of_cities; ++j) {
      if (i != j && initial_matrix[i][j] != 0) {
        city_index_to_adj[i].emplace_back(initial_matrix[i][j], j);
      }
    }
  }

  std::vector<bool> in_mst(number_of_cities, false);
  std::priority_queue<Edge, std::vector<Edge>, std::greater<>> available_edges;
  available_edges.emplace(0, 0);  // Start from city 0 with weight 0
  size_t min_fuel_tank = 0;
  size_t mst_size = 0;

  while (!available_edges.empty() && mst_size < number_of_cities) {
    auto [weight, u] = available_edges.top();
    available_edges.pop();
    if (in_mst[u]) {
      continue;
    }

    in_mst[u] = true;
    mst_size++;
    min_fuel_tank = std::max(min_fuel_tank, weight);

    for (const auto& [adj_weight, v] : city_index_to_adj[u]) {
      if (!in_mst[v]) {
        available_edges.emplace(adj_weight, v);
      }
    }
  }

  std::cout << min_fuel_tank << '\n';

  return 0;
}
