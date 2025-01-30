#include <algorithm>
#include <iostream>
#include <stack>
#include <string>

#include "../inc/error.hpp"

class Machine {
   private:
    std::stack<unsigned long long> memory;

    void executePush() noexcept {
        std::string n;
        std::cin >> n;

        if (!std::all_of(n.begin(), n.end(),
                         [](const char c) -> bool { return c == '0' || c == '1'; })) {
            exitWithError("Input is not binary");
        }

        memory.push(std::stoull(n, nullptr, 2));

        return;
    }

    void executeXor() noexcept {
        if (int(memory.size()) < 2) {
            exitWithError("Stack size is less than 2");
        }

        const auto a = memory.top();
        memory.pop();

        const auto b = memory.top();
        memory.pop();

        memory.push(a ^ b);

        return;
    }

    void executePrint() const noexcept {
        if (memory.empty()) {
            exitWithError("Stack is empty");
        }

        std::string s;
        auto a = memory.top();

        if (a == 0) {
            s = "0";
        } else {
            while (0 < a) {
                s.push_back(char((a & 1) + '0'));
                a >>= 1;
            }
        }

        std::reverse(s.begin(), s.end());

        std::cout << s << "\n";

        return;
    }

   public:
    Machine() noexcept : memory() {}

    bool execute() noexcept {
        std::string inst;
        std::cin >> inst;

        if (inst == "push") {
            executePush();
        } else if (inst == "xor") {
            executeXor();
        } else if (inst == "print") {
            executePrint();
        } else if (inst == "exit") {
            return false;
        } else {
            exitWithError("Invalid input");
        }

        return true;
    }
};

int main() {
    Machine machine;

    while (machine.execute())
        ;

    return 0;
}
