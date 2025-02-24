#include "resource_loader.hpp"

#include "assertion.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

std::string ResourceLoader::readStringFromFile(std::string resource) {
    std::ifstream resourceStream(resource);

    ASSERT_MSG(!resourceStream.fail(), "Failed to open shader file");

    std::stringstream resourceBuffer;

    resourceBuffer << resourceStream.rdbuf();

    std::string output = resourceBuffer.str();

    resourceStream.close();

    return output;
}

ResourceLoader::ResourceLoader() {
}

ResourceLoader::~ResourceLoader()
{

}
