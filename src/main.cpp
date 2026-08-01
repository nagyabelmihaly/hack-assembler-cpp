#include <iostream>
#include <string_view>
#include <concepts>
static_assert(std::integral<int>);

int main()
{
    constexpr std::string_view msg = "hack assembler v0 - C++20";
    std::cout << msg << '\n';
    return 0;
}
