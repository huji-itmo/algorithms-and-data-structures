#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

int main() {
  int N;
  std::cin >> N;

  std::unordered_map<int, std::vector<int>> children;
  int root = -1;

  for (int i = 0; i < N; ++i) {
    int id = 0;
    int parent_id = 0;
    std::cin >> id >> parent_id;

    if (parent_id == -1) {
      root = id;
    } else {
      children[parent_id].push_back(id);
    }
  }

  // Initialize in_time and out_time arrays
  const int max_nodes = 40001;
  std::vector<int> in_time(max_nodes, 0);
  std::vector<int> out_time(max_nodes, 0);
  int time = 0;

  // DFS traversal using a stack
  std::stack<std::pair<int, bool>> dfs_stack;
  dfs_stack.emplace(root, false);

  while (!dfs_stack.empty()) {
    auto current = dfs_stack.top();
    dfs_stack.pop();

    int node = current.first;
    bool visited = current.second;

    if (!visited) {
      in_time[node] = time++;
      dfs_stack.emplace(node, true);
      // Push children in reverse order to maintain correct DFS order
      for (auto it = children[node].rbegin(); it != children[node].rend(); ++it) {
        dfs_stack.emplace(*it, false);
      }
    } else {
      out_time[node] = time++;
    }
  }

  int L;
  std::cin >> L;

  std::vector<std::string> results;
  for (int i = 0; i < L; ++i) {
    int a = 0;
    int b = 0;
    std::cin >> a >> b;

    int a_in = in_time[a];
    int a_out = out_time[a];
    int b_in = in_time[b];
    int b_out = out_time[b];

    if (a_in <= b_in && a_out >= b_out) {
      results.emplace_back("1");
    } else if (b_in <= a_in && b_out >= a_out) {
      results.emplace_back("2");
    } else {
      results.emplace_back("0");
    }
  }

  // Output all results
  for (const std::string& result : results) {
    std::cout << result << '\n';
  }

  return 0;
}
