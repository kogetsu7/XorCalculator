#include <cctype>
#include <cstdio>
#include <iostream>
#include <vector>

#include "../inc/error.hpp"

enum class Symbol { Zero, One, LParen, RParen, Caret, LineFeed };

class Reader {
   private:
    Symbol symbol;

   public:
    Reader() noexcept { read(); }

    void read() noexcept {
        int c = 0;

        do {
            c = std::getchar();

            if (c == EOF) {
                exit_with_error("Syntax error");
            }
        } while (std::isblank(c));

        if (c == '0') {
            symbol = Symbol::Zero;
        } else if (c == '1') {
            symbol = Symbol::One;
        } else if (c == '(') {
            symbol = Symbol::LParen;
        } else if (c == ')') {
            symbol = Symbol::RParen;
        } else if (c == '^') {
            symbol = Symbol::Caret;
        } else if (c == '\n') {
            symbol = Symbol::LineFeed;
        } else {
            exit_with_error("Unknown charactor");
        }

        return;
    }

    [[nodiscard]] Symbol get() const noexcept { return symbol; }
};

class Parser {
   private:
    Reader reader;
    std::vector<std::string> result;

    // <E> ::= <F> [['^' <F>]]
    void parseE() noexcept {
        parseF();

        while (reader.get() == Symbol::Caret) {
            reader.read();

            parseF();

            result.push_back("xor");
        }

        return;
    }

    // <F> ::= <N> | '(' <E> ')'
    void parseF() noexcept {
        if (reader.get() == Symbol::LParen) {
            reader.read();

            parseE();

            if (reader.get() != Symbol::RParen) {
                exit_with_error("Syntax error");
            }

            reader.read();
        } else {
            parseN();
        }

        return;
    }

    // <N> ::= <D> [[<D>]]
    void parseN() noexcept {
        result.push_back("push ");

        do {
            parseD();
        } while (reader.get() == Symbol::Zero || reader.get() == Symbol::One);

        return;
    }

    // <D> ::= '0' | '1'
    void parseD() noexcept {
        if (reader.get() == Symbol::Zero) {
            result.back() += "0";
        } else if (reader.get() == Symbol::One) {
            result.back() += "1";
        } else {
            exit_with_error("Syntax error");
        }

        reader.read();

        return;
    }

   public:
    Parser() : reader(), result() {}

    // <E'> ::= <E> '\n'
    void parse() noexcept {
        parseE();

        if (reader.get() != Symbol::LineFeed) {
            exit_with_error("Syntax error");
        }

        result.push_back("print");
        result.push_back("exit");

        return;
    }

    void print() const noexcept {
        for (const auto& s : result) {
            std::cout << s << "\n";
        }

        return;
    }
};

int main() {
    Parser parser;

    parser.parse();
    parser.print();

    return 0;
}
