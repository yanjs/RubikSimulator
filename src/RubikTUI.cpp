#include "RubikTUI.hpp"
#include "RubikState.hpp"
#include <iostream>
#include <ostream>

static void print_block(Color c) {
  const char *seq;
  if (auto s = COLOR_ESCAPE_SEQUENCES.find(c);
      s == COLOR_ESCAPE_SEQUENCES.end()) {
    seq = RUBICTUI_COLOR_ESCAPE_CLEAR;
  } else {
    seq = s->second;
  }
  std::cout << seq << "[]" << RUBICTUI_COLOR_ESCAPE_CLEAR;
}

void RubikTUI::display(const RubikState &s) const {
  auto up = s.view_face(RubikState::UP);
  auto front = s.view_face(RubikState::FRONT);
  auto right = s.view_face(RubikState::RIGHT);
  auto back = s.view_face(RubikState::BACK);
  auto left = s.view_face(RubikState::LEFT);
  auto down = s.view_face(RubikState::DOWN);
  for (size_t i = 0; i < 9; i++) {
    print_block(up[i]);
    if (i % 3 == 2) {
      std::cout << "\n";
    }
  }
  for (size_t i = 0; i < 3; i++) {
    for (size_t j = 0; j < 3; j++) {
      print_block(front[i * 3 + j]);
    }
    for (size_t j = 0; j < 3; j++) {
      print_block(right[i * 3 + j]);
    }
    for (size_t j = 0; j < 3; j++) {
      print_block(back[i * 3 + j]);
    }
    for (size_t j = 0; j < 3; j++) {
      print_block(left[i * 3 + j]);
    }
    std::cout << "\n";
  }
  for (size_t i = 0; i < 9; i++) {
    print_block(down[i]);
    if (i % 3 == 2) {
      std::cout << "\n";
    }
  }
  std::cout << RUBICTUI_COLOR_ESCAPE_CLEAR;
}