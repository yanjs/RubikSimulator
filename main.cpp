#include "RubikState.hpp"
#include "RubikTUI.hpp"
#include <iostream>

int main() {
  RubikState s;
  RubikTUI d;
  s.rot_M();
  s.rot_B();
  d.display(s);
  std::cout<<s.to_string()<<std::endl;
  return 0;
}