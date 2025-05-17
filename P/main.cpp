#include <algorithm>
#include <climits>
#include <cstddef>
#include <iostream>
#include <queue>
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

алгоритм Прима не сработал, потому что матрица не симметрична.

будем делать бин поиск по ответу

dfs оказался слишком медленным, попробую bfs

- спросить почему uint16_t и uint32_t не поместились а обычные инты поместились

*/

using CityIndex = uint;
using EdgeWeight = int;

namespace {

bool BfsAllVerticesWithEdgesLowerThan(
    EdgeWeight upper_bound, const std::vector<std::vector<EdgeWeight>>& matrix, bool transpose
) {
  auto vertices_count = static_cast<CityIndex>(matrix.size());

  std::vector<bool> visited(vertices_count, false);
  std::queue<CityIndex> vertices_to_visit;
  vertices_to_visit.push(0);
  visited[0] = true;
  size_t visited_count = 1;

  while (!vertices_to_visit.empty()) {
    CityIndex current_city = vertices_to_visit.front();
    vertices_to_visit.pop();

    for (CityIndex adj_city = 0; adj_city < vertices_count; adj_city++) {
      if (visited[adj_city] || adj_city == current_city) {
        continue;
      }
      EdgeWeight weight =
          transpose ? matrix[current_city][adj_city] : matrix[adj_city][current_city];

      if (weight > upper_bound) {
        continue;
      }

      visited[adj_city] = true;
      visited_count++;
      vertices_to_visit.push(adj_city);
      if (vertices_count == visited_count) {
        return true;
      }
    }
  }
  return visited_count == vertices_count;
}

bool IsStronglyConnected(
    EdgeWeight upper_bound, const std::vector<std::vector<EdgeWeight>>& matrix
) {
  return BfsAllVerticesWithEdgesLowerThan(upper_bound, matrix, false) &&
         BfsAllVerticesWithEdgesLowerThan(upper_bound, matrix, true);
}
}  // namespace

int main() {
  CityIndex number_of_cities = 0;
  std::cin >> number_of_cities;

  std::vector<std::vector<EdgeWeight>> matrix(
      number_of_cities, std::vector<EdgeWeight>(number_of_cities)
  );

  EdgeWeight max_weight = 0;
  for (CityIndex i = 0; i < number_of_cities; ++i) {
    for (CityIndex j = 0; j < number_of_cities; ++j) {
      std::cin >> matrix[i][j];
      if (i != j) {
        max_weight = std::max(max_weight, matrix[i][j]);
      }
    }
  }

  EdgeWeight high = max_weight;
  EdgeWeight low = 0;

  EdgeWeight answer = 0;

  while (low <= high) {
    EdgeWeight mid = (high + low) / 2;
    if (IsStronglyConnected(mid, matrix)) {
      answer = mid;
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  std::cout << answer << '\n';

  return 0;
}
