#pragma once

#include <lua.hpp>
#include <memory>

class Script {
   private:
    std::unique_ptr<lua_State, void(*)(lua_State*)> luaState;
   public:
    Script();
    ~Script();
    void start();
    void update(double delta);
};
