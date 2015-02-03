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

	if(luaL_loadfile(L, "call_lua_table.lua"))
		error(L, "luaL_loadfile failed.\n");

	if (lua_pcall(L, 0, 0, 0))
        error(L, "lua_pcall failed");

    printf("In C,  calling Lua->tablehandler()\n");
    lua_getglobal(L, "tablehandler");
    lua_newtable(L);					//新建一个table入栈
    lua_pushliteral(L, "firstname");	//键为"firstname"入栈，此时table位置-2
    lua_pushliteral(L, "Veinin");		//值为"Veinin"入栈，次数table位置-3
    lua_settable(L, -3);				//把key和value放入表中，操作完成后键和值都会被弹出栈

    lua_pushliteral(L, "lastname");
    lua_pushliteral(L, "Guo");
    lua_settable(L, -3);

    if(lua_pcall(L, 1, 1, 0))			//执行调用函数
    	error(L, "lua_pcall failed");

    printf("============ Back in C again, Iterating thru returned table ============\n");

    lua_pushnil(L);						//第一个键，
    const char *k, *v;
    while(lua_next(L, -2)) {			//table现在在-2位置，lua_next得到一个键-值对，分别入栈
    	v = lua_tostring(L, -1);
    	k = lua_tostring(L, -2);

    	lua_pop(L, 1);					//’值’出栈，‘键’不出栈，保留做下一次迭代

    	printf("%s = %s\n", k, v);
    }

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