#include <climits>
#include <iostream>
#include <limits>
#include <vector>

using VertexIndex = size_t;
using EdgeWeight = int;

namespace {
bool BellmanFord(
    VertexIndex vertex_count,
    const std::vector<std::vector<std::pair<VertexIndex, EdgeWeight>>>& adj,
    VertexIndex start,
    VertexIndex end
) {
  std::vector<EdgeWeight> dist(vertex_count, std::numeric_limits<EdgeWeight>::max());
  dist[start] = 0;

  for (VertexIndex i = 1; i <= vertex_count - 1; i++) {
    for (VertexIndex u = 0; u < vertex_count; u++) {
      for (const auto& edge : adj[u]) {
        VertexIndex v = edge.first;
        EdgeWeight weight = edge.second;

        if (dist[u] != std::numeric_limits<EdgeWeight>::max() && dist[v] > dist[u] + weight) {
          dist[v] = dist[u] + weight;
        }
      }
    }
  }

  bool has_negative_cycle = false;
  for (VertexIndex u = 0; u < vertex_count; u++) {
    for (const auto& edge : adj[u]) {
      VertexIndex v = edge.first;
      EdgeWeight weight = edge.second;

      // is_visited && less then was
      if (dist[u] != std::numeric_limits<EdgeWeight>::max() && dist[v] > dist[u] + weight) {
        has_negative_cycle = true;
        break;
      }
    }
    if (has_negative_cycle) {
      break;
    }
  }

  if (has_negative_cycle) {
    std::cout << "Граф содержит цикл отрицательной стоимости." << '\n';
    return true;
  }
  std::cout << "Ответ " << dist[end] << '\n';

  return has_negative_cycle;
}
}  // namespace

int main() {
  VertexIndex vertex_count = 5;

  std::vector<std::vector<std::pair<VertexIndex, EdgeWeight>>> adj(vertex_count);

  // Adding edges (u -> v, weight)
  adj[0].emplace_back(1, -1);
  adj[1].emplace_back(2, -1);
  adj[2].emplace_back(3, -1);
  //   adj[3].emplace_back(1, -1);
  adj[3].emplace_back(4, -1);

  BellmanFord(vertex_count, adj, 0, 4);

  return 0;
}
