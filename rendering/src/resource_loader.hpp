#ifndef RESOURCELOADER_HPP
#define RESOURCELOADER_HPP

#include <string>

class ResourceLoader {
   public:
    static std::string readStringFromFile(std::string resource);

   private:
    ResourceLoader();
    ~ResourceLoader();
};

#endif
