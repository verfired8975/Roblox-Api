#include <Windows.h>
#include <iostream>
#include <string>

extern "C"
{
#include "Libs/Lua/lua.h"
#include "Libs/Lua/lapi.h"
#include "Libs/Lua/lualib.h"
#include "Libs/Lua/lauxlib.h"
}

#include "Libs/MinHook/MinHook.h"

#include "Libs/EyeStep/eyestep.h"
#include "Libs/EyeStep/eyestep_utility.h"

#include "Addys.h"
#include "Bypass.h"
#include "Functions.h"
#include "Console.h"

unsigned int RLS;

unsigned long __stdcall Thread(void*)
{
	Bypass::Console("VIVA V1 | LSI");

	if (!Bypass::Retcheck())
	{
		VIVA::print("Failed to bypass retcheck.");
		return 0;
	}
	if (!Bypass::CallCheck::StartUpCallCheck())
	{
		VIVA::print("Failed to bypass callcheck.");
		return 0;
	}

	EyeStep::open(GetCurrentProcess());

	SetupAddys();
	RLS = GetRState();

	//*GetLevelLoc(RLS) = 7;
	r_lua_pushcclosure(RLS, (int)Functions::getgenv, 0, 0, 0);
	std::cout << r_lua_type(RLS, -1) << "\n";
	//RegisterFunction(RLS, Functions::getgenv,"getgenv_test");

	//for (;;)
	//{
	//	std::getline(std::cin, script);
	//	script = Compile(script);
	//	unsigned int Thread = r_lua_newthread(RLS);
	//	r_deserialize(Thread, "VIVA", script.c_str(), script.length());
	//	r_spawn(Thread);
	//}

	return 1;
}

int __stdcall DllMain(HMODULE module, unsigned int call, void*)
{
	if (call == 1)
	{
		DisableThreadLibraryCalls(module);
		CreateThread(0, 0, Thread, 0, 0, 0);
	}
	return 1;
}