#include <iostream>
#include "src/GameBoy.hpp"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <rom.gb>" << std::endl;
        return 1;
    }

    GameBoy gb;
    if (!gb.load(argv[1]))
        return 1;

    gb.run();
    return 0;
}
