
/*

Мы должны использовать алгоритм Дейкстры для поиска кратчайшего пути

легче всего получать инцидентные вершины прямо с матрицы, не создавая
вектор инцидентных вершин.


*/

#include <algorithm>
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
      return VertexType::Uninitialized;
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
void Dijkstra(
    const Coordinates& start_pos,
    const std::vector<std::vector<VertexType>>& map,
    const Coordinates& destination,
    std::vector<std::vector<Distance>>& distances,
    std::vector<std::vector<Coordinates>>& predecessors
) {
  size_t rows = map.size();
  size_t cols = map[0].size();

  // Initialize distances to infinity and predecessors to (-1,-1)
  distances.assign(rows, std::vector<Distance>(cols, DISTANCE_MAX));
  predecessors.assign(rows, std::vector<Coordinates>(cols, Coordinates{-1, -1}));

  // Get start row and column
  distances[start_pos.second][start_pos.first] = 0;
  std::priority_queue<PathNode, std::vector<PathNode>, std::greater<>> paths_to_go;
  paths_to_go.emplace(0, start_pos);

  while (!paths_to_go.empty()) {
    PathNode current_path_node = paths_to_go.top();
    paths_to_go.pop();
    Coordinates current_pos = current_path_node.second;

    Distance distance_to_current_node = distances[current_pos.second][current_pos.first];

    if (current_pos == destination) {
      // early exit
      return;
    }

    for (auto adj : GetAdjVertices(current_path_node.second, map)) {
      Coordinates adj_coords = adj.second;
      Distance distance_to_adj_from_current = distances[adj_coords.second][adj_coords.first];
      Distance new_distance = distance_to_current_node + VertexTypeToDistance(adj.first);

      if (distance_to_adj_from_current > new_distance) {
        distances[adj_coords.second][adj_coords.first] = new_distance;
        predecessors[adj_coords.second][adj_coords.first] = current_pos;
        paths_to_go.emplace(new_distance, adj_coords);
      }
    }
  }
}

}  // namespace

int main() {
  Coordinates map_size;
  std::cin >> map_size.first >> map_size.second;

  Coordinates start_pos;
  std::cin >> start_pos.second >> start_pos.first;

  Coordinates destination;
  std::cin >> destination.second >> destination.first;

  // zero_based_indexing
  destination.first--;
  destination.second--;

  // zero_based_indexing
  start_pos.first--;
  start_pos.second--;

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

  // Initialize distances and predecessors
  std::vector<std::vector<Distance>> distances;
  std::vector<std::vector<Coordinates>> predecessors;

  Dijkstra(start_pos, map, destination, distances, predecessors);

  Distance min_time = distances[destination.second][destination.first];

  if (min_time == DISTANCE_MAX) {
    std::cout << -1 << '\n';
    return 0;
  }

  std::cout << min_time << '\n';

  // Reconstruct path
  std::vector<char> path;
  Coordinates current = destination;

  while (current != start_pos) {
    // Get predecessor for current
    Coordinates pred = predecessors[current.second][current.first];
    if (pred.first == static_cast<size_t>(-1)) {
      break;  // invalid
    }

    int diff_col = (int)current.first - (int)pred.first;
    int diff_row = (int)current.second - (int)pred.second;

    if (diff_col > 0) {
      path.push_back('E');
    } else if (diff_col < 0) {
      path.push_back('W');
    } else if (diff_row > 0) {
      path.push_back('S');
    } else if (diff_row < 0) {
      path.push_back('N');
    }

    current = pred;
  }

  // Reverse path to get start to end
  std::reverse(path.begin(), path.end());

  // Output the directions
  for (char c : path) {
    std::cout << c;
  }
  std::cout << '\n';

  return 0;
}
