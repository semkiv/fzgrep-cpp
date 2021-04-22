#include <cstdlib>
#include <iostream>
#include <thread>

auto main([[maybe_unused]] int const argc, [[maybe_unused]] char const * const argv[]) -> int {
    auto greeter = std::jthread{[] { std::cout << "Hello, world!" << std::endl; }};

    return EXIT_SUCCESS;
}
