#include <regex>
#include <iostream>

int main() {
    std::regex reg("[a-z]");
    std::smatch match;
    std::string input;

    std::cin >> input;

    if (std::regex_match(input, match, reg)) {
        std::cout << "SUCCESS" << std::endl;
    } else {
        std::cout << "FAILURE" << std::endl;
    }

    return 0;
}