#include "RubikSolver.hpp"
#include "RubikState.hpp"
#include "RubikTUI.hpp"
#include <iostream>

int main() {
  RubikState s;
  RubikTUI d;
  s.move_command("UFDFBU'RL");
  G1Encoding g1{s};
  auto soln = g1.solve();

  d.display(s);
  s.moves(soln);
  d.display(s);
  for (auto v : soln) {
    std::cout << v;
  }
  std::cout << std::endl;
  return 0;
}