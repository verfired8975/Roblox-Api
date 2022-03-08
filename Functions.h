namespace Functions {

	int getgenv(unsigned int RLS)
	{
		r_lua_pushvalue(RLS, -10002);
		return 1;
	}

	int getrenv(unsigned int RLS) {
		r_lua_pushvalue(RLS, -10002);
		return 1;
	}

	//getfenv already in roblox env

	//getsenv already in init script.

	//getmenv already in init script.

	//getinstances already in init script.

	//getnilinstances already in init script.

	//getscripts already in init script.

	//getmodules and getloadedmodules already in init script.

	//checkcaller already in init script.

	int getreg(unsigned int RLS) {
		r_lua_pushvalue(RLS, -10000);
		return 1;
	}

	int getthreadcontext(unsigned int RLS)
	{
		r_lua_pushnumber(RLS, *GetLevelLoc(RLS));
		return 1;
	}

	int setthreadcontext(unsigned int RLS)
	{
		r_luaL_checktype(RLS, 1, RType::TNUMBER);
		*GetLevelLoc(RLS) = r_lua_tonumber(RLS, 1);
		return 0;
	}
}

void RegisterFunction(unsigned int RLS, int Function(unsigned int), const char* Name)
{
	r_lua_pushcclosure(RLS, reinterpret_cast<int>(Function), 0, 0, 0);
	r_lua_setfield(RLS, -10002, Name);
}