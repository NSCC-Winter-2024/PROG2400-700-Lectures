#include <iostream>
#include <cstring>

bool is_palindrome(const char* input, size_t len) {
    for (int i = 0; i < len / 2; ++i) {
        if (input[i] != input[len - i - 1]) {
            return false;
        }
    }
    return true;
}

bool is_palindrome_recursive(const char* input, size_t len) {
    // the recursion end state
    if (len <= 1) return true;

    // does this work for three letter words?
    if (input[0] == input[len-1]) {
        return is_palindrome_recursive(&input[1], len-2);
    }

    return false;
}

int main() {
    const int BUFFER_SIZE = 80;
    char buffer[BUFFER_SIZE];

    std::cout << "Enter a word: ";
    std::cin.getline(buffer, BUFFER_SIZE);

    if (is_palindrome(buffer, strnlen(buffer, BUFFER_SIZE))) {
        std::cout << buffer << " IS a palindrome." << std::endl;
    } else {
        std::cout << buffer << " IS NOT a palindrome." << std::endl;
    }

    if (is_palindrome_recursive(buffer, strnlen(buffer, BUFFER_SIZE))) {
        std::cout << buffer << " IS a palindrome." << std::endl;
    } else {
        std::cout << buffer << " IS NOT a palindrome." << std::endl;
    }

    return 0;
}