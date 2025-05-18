
/*

Мы должны использовать алгоритм Дейкстры для поиска кратчайшего пути

легче всего получать инцидентные вершины прямо с матрицы, не создавая
вектор инцидентных вершин.


*/

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <utility>
#include <vector>

using Coordinates = std::pair<size_t, size_t>;
enum VertexType : int8_t { Uninitialized = 0, Field = 1, Forest = 2, Water = -1 };
using MapPoint = std::pair<VertexType, Coordinates>;

using Distance = size_t;
#define DISTANCE_MAX SIZE_MAX
using PathNode = std::pair<Distance, Coordinates>;

namespace {
VertexType CharToVertexType(char chr) {
  switch (chr) {
    case '.':
      return VertexType::Field;
    case 'W':
      return VertexType::Forest;
    case '#':
      return VertexType::Water;
    default:
      assert(false);
  }
}

Distance VertexTypeToDistance(VertexType vertex) {
  return static_cast<Distance>(vertex);
}

std::vector<MapPoint> GetAdjVertices(
    const Coordinates& pos, const std::vector<std::vector<VertexType>>& map
) {
  std::vector<MapPoint> res;

  // get left
  if (pos.first != 0) {
    VertexType type = map[pos.second][pos.first - 1];
    if (type != VertexType::Water) {
      res.emplace_back(type, std::make_pair(pos.first - 1, pos.second));
    }
  }

  // get up
  if (pos.second != 0) {
    VertexType type = map[pos.second - 1][pos.first];
    if (type != VertexType::Water) {
      res.emplace_back(type, std::make_pair(pos.first, pos.second - 1));
    }
  }

  // get right
  if (pos.first != map[0].size() - 1) {
    VertexType type = map[pos.second][pos.first + 1];
    if (type != VertexType::Water) {
      res.emplace_back(type, std::make_pair(pos.first + 1, pos.second));
    }
  }

  // get down
  if (pos.second != map.size() - 1) {
    VertexType type = map[pos.second + 1][pos.first];
    if (type != VertexType::Water) {
      res.emplace_back(type, std::make_pair(pos.first, pos.second + 1));
    }
  }

  return res;
}
Distance Dijkstra(
    const Coordinates& starting_pos,
    const std::vector<std::vector<VertexType>>& map,
    const Coordinates& destination
) {
  std::vector<std::vector<Distance>> distances_matrix(
      map.size(), std::vector<Distance>(map[0].size(), DISTANCE_MAX)
  );

  distances_matrix[starting_pos.second][starting_pos.first] = 0;
  std::priority_queue<PathNode, std::vector<PathNode>, std::greater<>> paths_to_go;
  paths_to_go.emplace(0, starting_pos);

  while (!paths_to_go.empty()) {
    PathNode current_path_node = paths_to_go.top();
    paths_to_go.pop();
    Coordinates current_vertex_pos = current_path_node.second;

    Distance distance_to_current_node =
        distances_matrix[current_vertex_pos.second][current_vertex_pos.first];

    if (current_vertex_pos == destination) {
      // its lowest since we use priority_queue
      return distance_to_current_node;
    }

    for (auto adj : GetAdjVertices(current_path_node.second, map)) {
      Coordinates adj_coords = adj.second;
      Distance distance_to_adj_from_current = distances_matrix[adj_coords.second][adj_coords.first];
      Distance calculated_distance = distance_to_current_node + VertexTypeToDistance(adj.first);

      if (distance_to_adj_from_current > calculated_distance) {
        distances_matrix[adj_coords.second][adj_coords.first] = calculated_distance;
        paths_to_go.emplace(calculated_distance, adj_coords);
      }
    }
  }

  return DISTANCE_MAX;
}

}  // namespace

int main() {
  Coordinates map_size;
  std::cin >> map_size.first >> map_size.second;

  Coordinates starting_pos;
  std::cin >> starting_pos.first >> starting_pos.second;

  // zero_based_indexing
  starting_pos.first--;
  starting_pos.second--;

  Coordinates destination;
  std::cin >> destination.first >> destination.second;

  // zero_based_indexing
  destination.first--;
  destination.second--;

  std::vector<std::vector<VertexType>> map(
      map_size.first, std::vector<VertexType>(map_size.second)
  );

  // skip one line
  {
    std::string _;
    std::getline(std::cin, _);
  }

  for (size_t i = 0; i < map_size.first; i++) {
    std::string map_line_str;
    std::getline(std::cin, map_line_str);
    for (size_t char_index = 0; char_index < map_size.second; char_index++) {
      char current_char = map_line_str[char_index];
      map[i][char_index] = CharToVertexType(current_char);
    }
  }

  Distance distance = Dijkstra(starting_pos, map, destination);

  if (distance == DISTANCE_MAX) {
    std::cout << -1 << '\n';
  } else {
    std::cout << distance << '\n';
  }

  return 0;
}
