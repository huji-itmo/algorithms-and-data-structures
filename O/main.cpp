/*

"Требуется определить, сможет ли он разделить лкшат на две группы так,
чтобы любой обмен записками осуществлялся от лкшонка одной группы лкшонку другой группы."

то есть нужно проверить граф на двудольность.

главное условий двудольности: не должно быть ребер, которые находятся в одной доли.

можно воспользоваться bfs, причем каждый раз все вершины на одном уровне будут всегда окрашены в
один цвет если это не так, то мы знаем, что граф не двудольный.

граф может быть не связным, поэтому мы пройдемся по каждой вершине как по начальной.

*/

#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <queue>
#include <vector>

using StudentIndex = uint;

enum class Color : uint8_t { Undefined = 0, Black, Red };

namespace {
bool IsVisited(StudentIndex student, const std::vector<Color>& student_color) {
  return student_color[student] != Color::Undefined;
}
Color ChooseNextColor(Color color) {
  assert(color != Color::Undefined);

  return static_cast<Color>(3 - static_cast<uint8_t>(color));
}

bool Bfs(
    StudentIndex starting_student,
    const std::vector<std::vector<StudentIndex>>& adjacent_students,
    std::vector<Color>& student_color
) {
  // if we are here, this means that we are inside another connected component,
  // so we can color the first vertex anything we want, since it wont affect other components
  std::queue<StudentIndex> students_to_visit;
  students_to_visit.push(starting_student);
  student_color[starting_student] = Color::Black;

  while (!students_to_visit.empty()) {
    StudentIndex current_student = students_to_visit.front();
    Color current_student_color = student_color[current_student];
    students_to_visit.pop();
    Color next_color = ChooseNextColor(current_student_color);

    for (StudentIndex adj_student : adjacent_students[current_student]) {
      if (!IsVisited(adj_student, student_color)) {
        students_to_visit.push(adj_student);
        student_color[adj_student] = next_color;
      } else {
        if (student_color[adj_student] == current_student_color) {
          return false;
        }
      }
    }
  }

  return true;
}

bool IsBipartite(
    const std::vector<std::vector<StudentIndex>>& adjacent_students, size_t number_of_students
) {
  // also can be used as a visited list
  std::vector<Color> student_color(number_of_students);

  for (StudentIndex starting_student = 0; starting_student < number_of_students;
       starting_student++) {
    if (IsVisited(starting_student, student_color)) {
      continue;
    }

    if (!Bfs(starting_student, adjacent_students, student_color)) {
      return false;
    }
  }

  return true;
}

}  // namespace

int main() {
  size_t number_of_students = 0;
  std::cin >> number_of_students;

  size_t number_of_pairs = 0;
  std::cin >> number_of_pairs;

  std::vector<std::vector<StudentIndex>> adjacent_students(
      number_of_students, std::vector<StudentIndex>()
  );

  for (size_t i = 0; i < number_of_pairs; i++) {
    StudentIndex first = 0;
    StudentIndex second = 0;
    std::cin >> first >> second;

    // zero based indexing
    first--;
    second--;

    adjacent_students[first].emplace_back(second);
    adjacent_students[second].emplace_back(first);
  }

  bool res = IsBipartite(adjacent_students, number_of_students);

  if (res) {
    std::cout << "YES" << '\n';
  } else {
    std::cout << "NO" << '\n';
  }
}
