#ifndef RUBIKSTATE_H
#define RUBIKSTATE_H

#include "Permutation.hpp"
#include <array>
#include <cctype>
#include <functional>
#include <map>
#include <sstream>
#include <string>

class RubikState {
public:
  enum Color {
    Black,
    Yellow,
    Red,
    Green,
    White,
    Orange,
    Blue,
  };
  enum Face {
    UP,
    FRONT,
    RIGHT,
    BACK,
    LEFT,
    DOWN,
  };

private:
  using Sz = std::size_t;
  using ValueType = Color;
  using FaceSquaresType = std::array<Face, 9>;

  constexpr static Sz CORNER_COUNT = 24;
  Permutation<Color, CORNER_COUNT> m_corners;
  constexpr static Sz EDGE_COUNT = 24;
  Permutation<Color, EDGE_COUNT> m_edges;
  constexpr static Sz CENTER_COUNT = 6;
  Permutation<Color, CENTER_COUNT> m_centers;
  /*
  Up: Yellow
  0 1
  2 3
  Front: Red | Right: Green | Back: Orange | Left: Blue
  4 5 | 8 9   | 12 13 | 16 17
  6 7 | 10 11 | 14 15 | 18 19
  Down: White
  20 21
  22 23
  */
  /*
  Up: Yellow
    0
  1   2
    3
  Front: Red | Right: Green | Back: Orange | Left: Blue
    4   |   8    |   12   |   16
  5   6 | 9   10 | 13  14 | 17  18
    7   |   11   |   15   |   19
  Down: White
    20
  21  22
    23
  */
  /*
  0
  1 | 2 | 3 | 4
  5
  */
public:
  constexpr RubikState()
      : m_corners{
            Yellow, Yellow, Yellow, Yellow, Red,   Red,    Red,
            Red,    Green,  Green,  Green,  Green, Orange, Orange,
            Orange, Orange, Blue,   Blue,   Blue,  Blue,
            White,White,White,White,
        }, m_edges{{
            Yellow, Yellow, Yellow, Yellow, Red,   Red,    Red,
            Red,    Green,  Green,  Green,  Green, Orange, Orange,
            Orange, Orange, Blue,   Blue,   Blue,  Blue,
            White, White, White, White,
        }}, m_centers{Yellow, Red, Green, Orange, Blue, White,} {}

  constexpr std::array<ValueType, 9> view_face(Face f) const {
    std::array<ValueType, 9> sqs;
    sqs[0] = m_corners[f * 4];
    sqs[1] = m_edges[f * 4];
    sqs[2] = m_corners[f * 4 + 1];
    sqs[3] = m_edges[f * 4 + 1];
    sqs[4] = m_centers[f];
    sqs[5] = m_edges[f * 4 + 2];
    sqs[6] = m_corners[f * 4 + 2];
    sqs[7] = m_edges[f * 4 + 3];
    sqs[8] = m_corners[f * 4 + 3];
    return sqs;
  }
  constexpr auto edges() const {
    return m_edges;
  }
  constexpr auto corners() const {
    return m_corners;
  }
  constexpr auto centers() const {
    return m_centers;
  }

  constexpr void rot_U() {
    m_corners.cycle<0, 2, 3, 1>();
    m_corners.cycle<4, 8, 12, 16>();
    m_corners.cycle<5, 9, 13, 17>();
    m_edges.cycle<0, 1, 3, 2>();
    m_edges.cycle<4, 8, 12, 16>();
  }
  constexpr void rot_F() {
    m_corners.cycle<4, 6, 7, 5>();
    m_corners.cycle<2, 19, 21, 8>();
    m_corners.cycle<3, 17, 20, 10>();
    m_edges.cycle<4, 5, 7, 6>();
    m_edges.cycle<3, 18, 20, 9>();
  }
  constexpr void rot_R() {
    m_corners.cycle<8, 10, 11, 9>();
    m_corners.cycle<1, 5, 21, 14>();
    m_corners.cycle<3, 7, 23, 12>();
    m_edges.cycle<8, 9, 11, 10>();
    m_edges.cycle<2, 6, 22, 13>();
  }
  constexpr void rot_B() {
    m_corners.cycle<12, 14, 15, 13>();
    m_corners.cycle<0, 9, 23, 18>();
    m_corners.cycle<1, 11, 22, 16>();
    m_edges.cycle<12, 13, 15, 14>();
    m_edges.cycle<0, 10, 23, 17>();
  }
  constexpr void rot_L() {
    m_corners.cycle<16, 18, 19, 17>();
    m_corners.cycle<0, 15, 20, 4>();
    m_corners.cycle<2, 13, 22, 6>();
    m_edges.cycle<16, 17, 19, 18>();
    m_edges.cycle<1, 14, 21, 5>();
  }
  constexpr void rot_D() {
    m_corners.cycle<20, 22, 23, 21>();
    m_corners.cycle<6, 18, 14, 10>();
    m_corners.cycle<7, 19, 15, 11>();
    m_edges.cycle<20, 21, 23, 22>();
    m_edges.cycle<7, 19, 15, 11>();
  }
  constexpr void rot_E() {
    m_centers.cycle<1, 4, 3, 2>();
    m_edges.cycle<5, 17, 13, 9>();
    m_edges.cycle<6, 18, 14, 10>();
  }
  constexpr void rot_M() {
    m_centers.cycle<0, 3, 5, 1>();
    m_edges.cycle<0, 15, 20, 4>();
    m_edges.cycle<3, 12, 23, 7>();
  }
  constexpr void rot_S() {
    m_centers.cycle<0, 4, 5, 2>();
    m_edges.cycle<1, 19, 22, 8>();
    m_edges.cycle<2, 16, 21, 11>();
  }
  inline void move(std::string op) {
    std::map<std::string, std::function<void()>> op_table{
        {"U", [&]() { rot_U(); }},
        {"U2",
         [&]() {
           rot_U();
           rot_U();
         }},
        {"U'",
         [&]() {
           rot_U();
           rot_U();
           rot_U();
         }},
        {"F", [&]() { rot_F(); }},
        {"F2",
         [&]() {
           rot_F();
           rot_F();
         }},
        {"F'",
         [&]() {
           rot_F();
           rot_F();
           rot_F();
         }},
        {"R", [&]() { rot_R(); }},
        {"R2",
         [&]() {
           rot_R();
           rot_R();
         }},
        {"R'",
         [&]() {
           rot_R();
           rot_R();
           rot_R();
         }},
        {"B", [&]() { rot_B(); }},
        {"B2",
         [&]() {
           rot_B();
           rot_B();
         }},
        {"B'",
         [&]() {
           rot_B();
           rot_B();
           rot_B();
         }},
        {"L", [&]() { rot_L(); }},
        {"L2",
         [&]() {
           rot_L();
           rot_L();
         }},
        {"L'",
         [&]() {
           rot_L();
           rot_L();
           rot_L();
         }},
        {"D", [&]() { rot_D(); }},
        {"D2",
         [&]() {
           rot_D();
           rot_D();
         }},
        {"D'",
         [&]() {
           rot_D();
           rot_D();
           rot_D();
         }},
        {"E", [&]() { rot_E(); }},
        {"E2",
         [&]() {
           rot_E();
           rot_E();
         }},
        {"E'",
         [&]() {
           rot_E();
           rot_E();
           rot_E();
         }},
        {"M", [&]() { rot_M(); }},
        {"M2",
         [&]() {
           rot_M();
           rot_M();
         }},
        {"M'",
         [&]() {
           rot_M();
           rot_M();
           rot_M();
         }},
        {"S", [&]() { rot_S(); }},
        {"S2",
         [&]() {
           rot_S();
           rot_S();
         }},
        {"S'",
         [&]() {
           rot_S();
           rot_S();
           rot_S();
         }},
        {"x",
         [&]() {
           rot_R();
           move("L'");
           move("M'");
         }},
        {"x2",
         [&]() {
           move("x");
           move("x");
         }},
        {"x'",
         [&]() {
           move("x");
           move("x");
           move("x");
         }},
        {"y",
         [&]() {
           rot_U();
           move("E'");
           move("D'");
         }},
        {"y2",
         [&]() {
           move("y");
           move("y");
         }},
        {"y'",
         [&]() {
           move("y");
           move("y");
           move("y");
         }},
        {"z",
         [&]() {
           rot_F();
           rot_S();
           move("B'");
         }},
        {"z2",
         [&]() {
           move("z");
           move("z");
         }},
        {"z'",
         [&]() {
           move("z");
           move("z");
           move("z");
         }},
    };

    if (auto operation = op_table.find(op); operation != op_table.end()) {
      operation->second();
    }
  }

  inline void moves(std::vector<std::string> ops) {
    for (auto op : ops) {
      move(op);
    }
  }
  inline static std::vector<std::string> parse_command(std::string str) {
    if (str.length() == 0)
      return {};
    std::vector<std::string> ops;
    auto itb = str.cbegin();
    for (auto it = str.cbegin() + 1; it != str.cend(); it++) {
      if (std::isalpha(*it)) {
        ops.push_back({itb, it});
        itb = it;
      }
    }
    ops.push_back({itb, str.cend()});
    return ops;
  }
  inline void move_command(std::string str) { moves(parse_command(str)); }

  std::string to_string() const {
    std::stringstream ss;
    ss << m_edges.to_string() << m_corners.to_string() << m_centers.to_string();
    return ss.str();
  }
};

#endif // RUBIKSTATE_H