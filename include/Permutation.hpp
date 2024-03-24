#ifndef PERMUTATION_H
#define PERMUTATION_H

#include <array>
#include <cstddef>
#include <sstream>
#include <string>

template <class T, std::size_t N> struct Permutation : std::array<T, N> {
  using Sz = std::size_t;
  // e.g. (1 2 4)
  template <Sz... ids> constexpr void cycle() {
    auto values = this->data();
    if constexpr (sizeof...(ids) <= 1) {
      return;
    }
    Sz indices[]{ids...};
    auto temp = values[indices[0]];
    for (Sz i = 0; i < sizeof...(ids) - 1; i++) {
      values[indices[i]] = values[indices[i + 1]];
    }
    values[indices[sizeof...(ids) - 1]] = temp;
  }
  template <Sz... ids> constexpr void set(T value) {
    auto values = this->data();
    ((values[ids] = value), ...);
  }
  inline std::string to_string() const {
    std::stringstream ss;
    for (auto c : *this) {
      ss << c;
    }
    return ss.str();
  }
};

template <class T, std::size_t N> struct std::hash<Permutation<T, N>> {
  auto operator()(const Permutation<T, N> &objs) const {
    std::hash<T> ht;
    std::hash<size_t> hs;
    size_t result = 0;
    for (auto o : objs) {
      result = hs(result ^ ht(o));
    }
    return result;
  }
};

#endif // PERMUTATION_H