#include <iostream>

#include "Engine.hpp"
#include "utils/ConfigManager.hpp"

int main() {
    try {
        LoadConfig("config.cfg");

    } catch (const std::exception& e) {
        std::cerr << "Config error: " << e.what() << std::endl;
        return 1;
    }

    Engine engine;
    engine.run();

    return 0;
}