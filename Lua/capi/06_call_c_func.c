#include <stdio.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

static int
isquare(lua_State *L)
{
	float num = lua_tonumber(L, -1);
	printf("square(), num = %f\n", num);
	lua_pushnumber(L, num * num);
	return 1;
}

static int
icube(lua_State *L)
{
	float num = lua_tonumber(L, -1);
	printf("cube(), num = %f\n", num);
	lua_pushnumber(L, num * num * num);
	return 1;
}

static const struct luaL_Reg libs [] = {
	{"square", isquare},
	{"cube", icube},
	{NULL, NULL}
};

int
luaopen_mylib(lua_State *L)
{
	luaL_newlib(L, libs);
	return 1;
}