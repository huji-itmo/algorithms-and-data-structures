#include <algorithm>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using VertexIndex = int;
using EdgeWeight = int;

namespace {

// Computes a topological ordering of the graph using Kahn's algorithm
std::vector<VertexIndex> ComputeTopologicalOrdering(
    VertexIndex total_nodes,
    const std::vector<std::vector<std::pair<VertexIndex, EdgeWeight>>>& adjacency_list,
    const std::vector<int>& in_degree_count
) {
  std::vector<int> in_degree_copy = in_degree_count;

  std::queue<VertexIndex> queue;
  std::vector<VertexIndex> topological_ordering;

  for (VertexIndex node = 0; node < total_nodes; ++node) {
    if (in_degree_copy[node] == 0) {
      queue.push(node);
    }
  }

  while (!queue.empty()) {
    VertexIndex current_node = queue.front();
    queue.pop();
    topological_ordering.push_back(current_node);

    for (const auto& edge : adjacency_list[current_node]) {
      VertexIndex neighbor_node = edge.first;
      in_degree_copy[neighbor_node]--;
      if (in_degree_copy[neighbor_node] == 0) {
        queue.push(neighbor_node);
      }
    }
  }

  return topological_ordering;
}

}  // namespace

int main() {
  VertexIndex total_nodes = 0;
  VertexIndex total_edges = 0;
  std::cin >> total_nodes >> total_edges;

  std::vector<std::vector<std::pair<VertexIndex, EdgeWeight>>> adjacency_list(total_nodes);
  std::vector<int> in_degree_count(total_nodes, 0);

  // Read and add edges to the graph
  for (VertexIndex i = 0; i < total_edges; ++i) {
    VertexIndex start_node = 0;
    VertexIndex end_node = 0;
    EdgeWeight edge_weight = 0;
    std::cin >> start_node >> end_node >> edge_weight;

    // Convert to 0-based indexing
    start_node -= 1;
    end_node -= 1;

    adjacency_list[start_node].emplace_back(end_node, edge_weight);
    in_degree_count[end_node]++;
  }

  VertexIndex source_node = 0;
  VertexIndex destination_node = 0;
  std::cin >> source_node >> destination_node;

  // Convert to 0-based indexing
  source_node -= 1;
  destination_node -= 1;

  std::vector<VertexIndex> topological_ordering =
      ComputeTopologicalOrdering(total_nodes, adjacency_list, in_degree_count);

  // Initialize the longest path distances with negative infinity
  const EdgeWeight unreachable = std::numeric_limits<EdgeWeight>::min();
  std::vector<EdgeWeight> longest_path_distances(total_nodes, unreachable);
  longest_path_distances[source_node] = 0;

  for (VertexIndex current_node : topological_ordering) {
    if (longest_path_distances[current_node] == unreachable) {
      continue;
    }

    for (const auto& edge : adjacency_list[current_node]) {
      VertexIndex neighbor_node = edge.first;
      EdgeWeight edge_weight = edge.second;

      longest_path_distances[neighbor_node] = std::max(
          longest_path_distances[neighbor_node], longest_path_distances[current_node] + edge_weight
      );
    }
  }

  if (longest_path_distances[destination_node] == unreachable) {
    std::cout << "No solution" << '\n';
  } else {
    std::cout << longest_path_distances[destination_node] << '\n';
  }

  return 0;
}
