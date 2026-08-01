# Project Goal

The goal of this project is to implement an assembler for the hack assembly language.

The specification of the hack assembly language, hack machine language and other useful information is available at https://www.nand2tetris.org/.

# C++ Coding Conventions

Style guide for this project. Consistency matters more than any individual rule — when in doubt, match the surrounding code.

## Brace style: Allman

Opening brace always on its own line, at the same indentation as the statement that introduces it. Applies to functions, classes, namespaces, and all control flow.

```cpp
class Lexer
{
public:
    Token nextToken()
    {
        if (isAtEnd())
        {
            return Token{TokenType::EndOfFile, "", line_};
        }
        else
        {
            return makeToken(advance());
        }
    }
};
```

No exceptions for short bodies — even a one-line `if` gets its own brace block on the next line, not squeezed onto one line.

## Indentation

- 4 spaces, no tabs.
- Braces align with the construct they open, contents indented one level from that.

## Naming

| Element | Convention | Example |
|---|---|---|
| Class / struct / enum | `PascalCase` | `class TokenStream`, `struct SourceLocation` |
| Enum values (`enum class`) | `PascalCase` | `TokenType::Identifier` |
| Function / method | `camelCase` | `nextToken()`, `isWhitespace()` |
| Namespace | `camelCase`, short | `namespace hasm` |
| Local variable / parameter | `camelCase` | `int operandCount`, `std::string_view mnemonic` |
| Private member variable | `camelCase_` (trailing underscore) | `source_`, `pos_`, `line_` |
| Constant / `constexpr` | `PascalCase` prefixed with `k` | `kMaxOperands`, `kVersion` |
| File name | matches the primary class/type it defines, `PascalCase` | `Lexer.hpp`, `Lexer.cpp` |
| Template parameter | `PascalCase`, single letter or descriptive | `template <typename T>`, `template <typename TokenT>` |

The `k` + `PascalCase` constant convention (Google-style) keeps constants visually distinct from both types and functions at a glance.

## Files

- Header: `.hpp`. Source: `.cpp`.
- One primary class per file pair, file name matches the class: `class Parser` lives in `Parser.hpp` / `Parser.cpp`.
- Use `#pragma once` as the header guard — simpler than `#ifndef` guards and supported by all major compilers.

```cpp
#pragma once

#include <string_view>

namespace hasm
{

class Lexer
{
public:
    explicit Lexer(std::string_view source);

    Token nextToken();

private:
    std::string_view source_;
    size_t pos_ = 0;
    int line_ = 1;

    char peek() const;
    char advance();
};

}  // namespace hasm
```

## Enums

Always `enum class`, never a plain `enum` — avoids namespace pollution and implicit int conversion.

```cpp
enum class TokenType
{
    Identifier,
    Number,
    Mnemonic,
    Register,
    Comma,
    Newline,
    EndOfFile
};
```

## Other conventions

- **`const` correctness**: mark methods `const` when they don't mutate state; take parameters by `const&` when not modifying them.
- **`explicit`** on every single-argument constructor, to block accidental implicit conversions.
- **One declaration per line** — avoid `int x, y, *p;`.
- **Braces required** on every `if` / `for` / `while` body, even single statements — no brace-less one-liners.
- Prefer `std::string_view` / `std::span` for non-owning parameters over raw pointers or unnecessary copies.

## Formatting enforcement

This project uses `clang-format` with the following `.clang-format`:

```yaml
BasedOnStyle: Microsoft
BreakBeforeBraces: Allman
IndentWidth: 4
ColumnLimit: 100
```

`Microsoft` is Allman-based by default; `BreakBeforeBraces: Allman` makes it explicit. Enable "Format on Save" in your editor to apply this automatically.
