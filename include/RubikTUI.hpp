#ifndef RUBICTUI_H
#define RUBICTUI_H
#include "RubikState.hpp"
#include <map>
#define RUBICTUI_COLOR_ESCAPE_BEGIN "\033[48;2;"
constexpr static auto RUBICTUI_COLOR_ESCAPE_CLEAR = "\033[0m";

using Color = RubikState::Color;

const static std::map<Color, const char *> COLOR_ESCAPE_SEQUENCES{
    {Color::Black, RUBICTUI_COLOR_ESCAPE_BEGIN "0;0;0m"},
    {Color::Red, RUBICTUI_COLOR_ESCAPE_BEGIN "255;0;0m"},
    {Color::Green, RUBICTUI_COLOR_ESCAPE_BEGIN "0;255;0m"},
    {Color::Blue, RUBICTUI_COLOR_ESCAPE_BEGIN "0;0;255m"},
    {Color::Orange, RUBICTUI_COLOR_ESCAPE_BEGIN "255;127;0m"},
    {Color::Yellow, RUBICTUI_COLOR_ESCAPE_BEGIN "255;255;0m"},
    {Color::White, RUBICTUI_COLOR_ESCAPE_BEGIN "255;255;255m"},
};

class RubikTUI {
private:
public:
  void display(const RubikState &s) const;
};

#endif // RUBICTUI_H