#include "script.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "assertion.h"

Script::Script() : luaState(luaL_newstate(), lua_close) {
    luaL_openlibs(luaState.get());

    int fileStatus = luaL_dofile(luaState.get(), "../resources/test.lua");

    if (fileStatus) {
        fprintf(stderr, "Error: %s\n", lua_tostring(luaState.get(), -1));
    }
}

Script::~Script() {
}

void Script::start() {
    lua_getglobal(luaState.get(), "start");

    if (lua_pcall(luaState.get(), 0, 0, 0) != 0) {
        int status = lua_error(luaState.get());

        if (status) {
            fprintf(stderr, "Error: %s\n", lua_tostring(luaState.get(), -1));
        }
    }
}

void Script::update(double delta) {
    lua_getglobal(luaState.get(), "update");

    lua_pushnumber(luaState.get(), delta);

    if (lua_pcall(luaState.get(), 1, 0, 0) != 0) {
        int status = lua_error(luaState.get());

        if (status) {
            fprintf(stderr, "Error: %s\n", lua_tostring(luaState.get(), -1));
        }
    }
}
