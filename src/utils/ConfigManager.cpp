#include "utils/ConfigManager.hpp"
#include "utils/Debug.hpp"

Config config;

void LoadConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open config file: " + filename);
    }

    std::string line, model, texture;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        std::istringstream iss(line);
        std::string key;
        iss >> key;

        if (key == "width") iss >> config.width;
        else if (key == "height") iss >> config.height;
        else if (key == "frameRate") iss >> config.frameRate;

        else if (key == "fNear") iss >> config.fNear;
        else if (key == "fFar") iss >> config.fFar;
        else if (key == "fFov") iss >> config.fFov;

        else if (key == "textureVisible") iss >> std::boolalpha >> config.textureVisible;
        else if (key == "faceVisible") iss >> std::boolalpha >> config.faceVisible;
        else if (key == "backFaceVisible") iss >> std::boolalpha >> config.backFaceVisible;
        else if (key == "edgeVisible") iss >> std::boolalpha >> config.edgeVisible;
        else if (key == "liteRender") iss >> std::boolalpha >> config.liteRender;

        else if (key == "model") iss >> model;
        else if (key == "texture") iss >> texture;
    }

    config.modelPath = "resources/models/" + model;
    if (texture != "-") {
        config.texturePath = "resources/textures/" + texture;
    } else {
        config.texturePath = "-";
    }
}