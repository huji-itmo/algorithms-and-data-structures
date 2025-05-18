#include <array>
#include <iostream>
const int GridSize = 512;

void placeTiles(
    int size,
    int x,
    int y,
    int hole_x,
    int hole_y,
    int& tile_counter,
    std::array<std::array<int, GridSize>, GridSize>& grid
) {
  // base case
  if (size == 2) {
    // Fill 2x2 grid around the hole
    for (int dx = 0; dx < 2; ++dx) {
      for (int dy = 0; dy < 2; ++dy) {
        if (x + dx != hole_x || y + dy != hole_y) {
          grid[x + dx][y + dy] = tile_counter++ / 3;
        }
      }
    }
    return;
  }

  int half = size / 2;
  // Place central trominoes in three quadrants without the hole
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      int quad_x = x + (i * half);
      int quad_y = y + (j * half);
      if (quad_x > hole_x || hole_x >= quad_x + half || quad_y > hole_y ||
          hole_y >= quad_y + half) {
        grid[x + half - 1 + i][y + half - 1 + j] = tile_counter++ / 3;
      }
    }
  }

  // Process each quadrant
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      int quad_x = x + (i * half);
      int quad_y = y + (j * half);
      if (quad_x <= hole_x && hole_x < quad_x + half && quad_y <= hole_y &&
          hole_y < quad_y + half) {
        placeTiles(half, quad_x, quad_y, hole_x, hole_y, tile_counter, grid);
      } else {
        int new_hole_x = x + half - 1 + i;
        int new_hole_y = y + half - 1 + j;
        placeTiles(half, quad_x, quad_y, new_hole_x, new_hole_y, tile_counter, grid);
      }
    }
  }
}

int main() {
  int tile_counter = 3;
  std::array<std::array<int, GridSize>, GridSize> grid{};

  int n = 0;
  int hole_row = 0;
  int hole_col = 0;

  std::cin >> n;
  std::cin >> hole_row;
  std::cin >> hole_col;

  int grid_size = 1 << n;  // Compute 2^n
  placeTiles(grid_size, 0, 0, hole_row - 1, hole_col - 1, tile_counter, grid);

  for (int i = 0; i < grid_size; ++i) {
    for (int j = 0; j < grid_size; ++j) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << '\n';
  }
  return 0;
}
