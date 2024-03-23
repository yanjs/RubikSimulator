#include "RubikState.hpp"
#include <cassert>
#include <string>

using namespace std::string_literals;

static void test_rot() {
  RubikState s;
  s.rot_U();
  s.rot_F();
  s.rot_R();
  s.rot_B();
  s.rot_L();
  s.rot_D();
  s.rot_E();
  s.rot_M();
  s.rot_S();
  // Up
  {
    auto got = s.view(s.UP);
    decltype(got) expected{
        s.Blue,   s.Green, s.Orange, s.Orange, s.Orange,
        s.Yellow, s.Red,   s.Yellow, s.Green,
    };
    assert(got == expected);
  }

  // Front
  {
    auto got = s.view(s.FRONT);
    decltype(got) expected{
        s.Yellow, s.Orange, s.Orange, s.Blue,  s.Yellow,
        s.Red,    s.White,  s.Blue,   s.White,
    };
    assert(got == expected);
  }
  // Right
  {
    auto got = s.view(s.RIGHT);
    decltype(got) expected{
        s.Yellow, s.Blue, s.Blue,  s.Yellow, s.Green,
        s.White,  s.Blue, s.Green, s.White,
    };
    assert(got == expected);
  }
  // Back
  {
    auto got = s.view(s.BACK);
    decltype(got) expected{
        s.Yellow, s.Orange, s.Red, s.Green, s.White,
        s.White,  s.Green,  s.Red, s.White,
    };
    assert(got == expected);
  }
  // Left
  {
    auto got = s.view(s.LEFT);
    decltype(got) expected{
        s.Yellow, s.Blue,   s.Green, s.Orange, s.Blue,
        s.White,  s.Orange, s.Green, s.Green,
    };
    assert(got == expected);
  }
  // Down
  {
    auto got = s.view(s.DOWN);
    decltype(got) expected{
        s.Red, s.Red, s.Red, s.Red, s.Red, s.Yellow, s.Blue, s.White, s.Orange,
    };
    assert(got == expected);
  }
}

static void test_to_string() {
  {
    RubikState s;
    s.rot_M();
    s.rot_B();
    auto got = s.to_string();
    auto expected = "311512213323544565662446331122223434555516164466513462"s;
    assert(got == expected);
  }
}

static void test_parse_command() {
  RubikState s{};
  {
    std::string test{"UFRBLDEMS"};
    auto got = s.parse_command(test);
    decltype(got) expected{
        "U", "F", "R", "B", "L", "D", "E", "M", "S",
    };
    assert(got == expected);
  }
  {
    std::string test{"U'F2RB2L'"};
    auto got = s.parse_command(test);
    decltype(got) expected{
        "U'", "F2", "R", "B2", "L'",
    };
    assert(got == expected);
  }
  {
    std::string test{""};
    auto got = s.parse_command(test);
    decltype(got) expected{};
    assert(got == expected);
  }
  {
    std::string test{"B"};
    auto got = s.parse_command(test);
    decltype(got) expected{
        "B",
    };
    assert(got == expected);
  }
  {
    std::string test{"B'"};
    auto got = s.parse_command(test);
    decltype(got) expected{
        "B'",
    };
    assert(got == expected);
  }
}

static void test_move_command() {
  {
    RubikState s{};
    s.move_command("UFRBLDEMSU'F'R'B'L'D'E'M'S'");
    auto got = s.to_string();
    auto expected = "241265123634153532164564311123235555616426264434426531"s;
    assert(got == expected);
  }
  {
    RubikState s{};
    s.move_command("UFRBLDEMSU'F'R'B'L'D'E'M'S'U2F2R2B2L2D2E2M2S2");
    auto got = s.to_string();
    auto expected = "214213153616655233244654331466335256412225651414426531"s;
    assert(got == expected);
  }
  {
    RubikState s{};
    s.move_command("UxFyRzBx2Ly2Dz2Ex'My'Sz'");
    auto got = s.to_string();
    auto expected = "215423156234643562163451555462236146335144316221162354"s;
    assert(got == expected);
  }
}

int main() {
  test_rot();
  test_to_string();
  test_parse_command();
  test_move_command();
  return 0;
}