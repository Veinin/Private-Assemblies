#include <stdio.h>
#include <stdlib.h>

#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"

void error(lua_State *L, const char *fmt, ...);

int
main()
{
	lua_State *L = luaL_newstate();
	luaL_openlibs(L);

	if(luaL_loadfile(L, "call_lua.lua"))
		error(L, "luaL_loadfile failed.\n");

	printf("In C, calling Lua\n");

	if(lua_pcall(L, 0, 0, 0))
		error(L, "lua_pcall() failed.", lua_tostring(L, -1));

	printf("Back in C again\n");

	lua_close(L);

	return 0;
}

void 
error(lua_State *L, const char *fmt, ...) 
{
	va_list argp;
	va_start(argp, fmt);
	vfprintf(stderr, fmt, argp);
	va_end(argp);
	lua_close(L);
	exit(EXIT_FAILURE);
}