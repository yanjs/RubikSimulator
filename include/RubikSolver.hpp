#ifndef RUBIKSOLVER_H
#define RUBIKSOLVER_H

#include "Permutation.hpp"
#include "RubikState.hpp"
#include <cstddef>
#include <deque>
#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <unordered_set>
#include <vector>

// misoriented edges
struct G1Encoding : Permutation<bool, 12> {
  /*
    0
  1   2
    3
  -----
  |  3  |  2  |  0  |  1  |
  |4   5|5   6|6   7|7   4|
  |  8  |  10 |  11 |  9  |
  -----
    8
  9   10
    11
  */
  inline explicit G1Encoding(RubikState s) {
    using C = RubikState::Color;
    auto c_v = [](C c) {
      switch (c) {
      case C::White:
      case C::Yellow:
        return 2;
      case C::Red:
      case C::Orange:
        return 1;
      case C::Blue:
      case C::Green:
        return 0;
      default:
        throw -1;
      }
    };
    auto test = [&](Sz f1i, Sz f2i, Sz c1i, Sz c2i) -> bool {
      auto f1 = c_v(s.centers()[f1i]);
      auto f2 = c_v(s.centers()[f2i]);
      auto c1 = c_v(s.edges()[c1i]);
      auto c2 = c_v(s.edges()[c2i]);
      return (f1 > f2) ? (c1 < c2) : (c1 > c2);
    };

    auto values = data();

    values[0] = test(0, 3, 0, 12);
    values[1] = test(0, 4, 1, 16);
    values[2] = test(0, 2, 2, 8);
    values[3] = test(0, 1, 3, 4);
    values[4] = test(1, 4, 5, 18);
    values[5] = test(1, 2, 6, 9);
    values[6] = test(2, 3, 10, 13);
    values[7] = test(3, 4, 14, 17);
    values[8] = test(1, 5, 7, 20);
    values[9] = test(4, 5, 19, 21);
    values[10] = test(2, 5, 11, 22);
    values[11] = test(3, 5, 15, 23);
  }
  inline size_t count() const {
    return std::accumulate(cbegin(), cend(), size_t());
  }
  using Ops = std::vector<std::string>;
  template <Sz... ids> constexpr void flips() {
    for (auto id : {ids...}) {
      (*this)[id] = !(*this)[id];
    }
  }
  constexpr void rot_U() { cycle<0, 1, 3, 2>(); }
  constexpr void rot_F() {
    cycle<3, 4, 8, 5>();
    flips<3, 4, 8, 5>();
  }
  constexpr void rot_R() { cycle<2, 5, 10, 6>(); }
  constexpr void rot_B() {
    cycle<0, 6, 11, 7>();
    flips<0, 6, 11, 7>();
  }
  constexpr void rot_L() { cycle<1, 7, 9, 4>(); }
  constexpr void rot_D() { cycle<8, 9, 11, 10>(); }

  inline Ops solve() const {
    // bfs
    if (count() == 0) {
      return {};
    }
    std::deque<std::pair<G1Encoding, Ops>> queue;
    std::unordered_set<G1Encoding, std::hash<Permutation<bool, 12>>> visited{
        *this};

    std::array<std::function<std::string(G1Encoding &)>, 12> op_table{
        [](G1Encoding &e) {
          e.rot_U();
          return "U";
        },
        [](G1Encoding &e) {
          e.rot_U();
          e.rot_U();
          e.rot_U();
          return "U'";
        },
        [](G1Encoding &e) {
          e.rot_F();
          return "F";
        },
        [](G1Encoding &e) {
          e.rot_F();
          e.rot_F();
          e.rot_F();
          return "F'";
        },
        [](G1Encoding &e) {
          e.rot_R();
          return "R";
        },
        [](G1Encoding &e) {
          e.rot_R();
          e.rot_R();
          e.rot_R();
          return "R'";
        },
        [](G1Encoding &e) {
          e.rot_B();
          return "B";
        },
        [](G1Encoding &e) {
          e.rot_B();
          e.rot_B();
          e.rot_B();
          return "B'";
        },
        [](G1Encoding &e) {
          e.rot_L();
          return "L";
        },
        [](G1Encoding &e) {
          e.rot_L();
          e.rot_L();
          e.rot_L();
          return "L'";
        },
        [](G1Encoding &e) {
          e.rot_D();
          return "D";
        },
        [](G1Encoding &e) {
          e.rot_D();
          e.rot_D();
          e.rot_D();
          return "D'";
        },
    };

    queue.push_back({*this, {}});
    size_t count{};
    while (queue.size() > 0) {
      count++;
      auto [old_enc, old_ops] = queue.front();
      for (auto op : op_table) {
        auto new_enc = old_enc;
        auto new_ops = old_ops;
        new_ops.push_back(op(new_enc));
        if (new_enc.count() == 0) {
          return new_ops;
        } else {
          auto it = visited.find(new_enc);
          // insert to visited if not visited
          if (it == visited.end()) {
            visited.insert(new_enc);
            queue.push_back({new_enc, new_ops});
          }
        }
      }
      queue.pop_front();
    }
    // unreached
    std::cerr << count << std::endl;
    throw -1;
  }
};

#endif // RUBIKSOLVER_H