namespace Bypass
{
	bool Console(const char* Title)
	{
		if (!VirtualProtect(FreeConsole, 1, PAGE_EXECUTE_READWRITE, new unsigned long))
			return false;
		*reinterpret_cast<unsigned int*>(FreeConsole) = 0xC3;
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONIN$", "r", stdin);
		SetWindowPos(GetConsoleWindow(), HWND_TOPMOST, 50, 20, 0, 0, SWP_DRAWFRAME | SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
		ShowWindow(GetConsoleWindow(), 1);
		SetConsoleTitleA(Title);
		return true;
	}

	bool Retcheck()
	{
		unsigned long Old = 0;
		void* Retcheck = reinterpret_cast<void*>(Rebase(ADDRESS_RetcheckJMP));

		if (!VirtualProtect(Retcheck, 8, PAGE_EXECUTE_READWRITE, &Old))
			return false;
		*reinterpret_cast<unsigned long long*>(Retcheck) = 0xC35D00000028C481;
		if (!VirtualProtect(Retcheck, 8, Old, &Old))
			return false;
		return true;
	}

	namespace CallCheck
	{
		typedef HANDLE(WINAPI* _CreateEventA)(LPSECURITY_ATTRIBUTES lp_event_attributes, BOOL b_banual_reset, BOOL b_initial_state, LPCTSTR lp_name);

		unsigned int original;
		int ClosurePlacement(uintptr_t RL);
		unsigned int closureplacement = reinterpret_cast<uintptr_t>(&ClosurePlacement);
		_CreateEventA CreateEventAOriginal = NULL;
		unsigned int CreateEventA = NULL;
		unsigned int HookLocation = Rebase(ADDRESS_CreateEventA);
		unsigned int Comparison = HookLocation + 6;
		unsigned int CallCheckAddr;

		__declspec(naked) void CreateEventAHook()
		{
			__asm
			{
				mov eax, [esp]
				cmp eax, Comparison
				jne normal_case
				add esp, 4
				push[esp + 4]
				call[closureplacement]
				add esp, 4
				retn
				normal_case :
				jmp[original]
			}
		}

		int ClosurePlacement(uintptr_t RL)
		{
			uintptr_t Address = 0;
			for (int i = 1; i <= MAX_INT; i++)
			{
				uintptr_t Type = r_lua_type(RL, lua_upvalueindex(i));
				if (Type == (-1))
					break;
				else if (Type == 2)
					Address = r_lua_tonumber(RL, lua_upvalueindex(i));
			}
			return ((int(*)(uintptr_t))Address)(RL);
		}

		bool StartUpCallCheck()
		{
			HMODULE Kernel32 = GetModuleHandleA("Kernel32.dll");
			if (!Kernel32) return false;
			CreateEventA = (uintptr_t)GetProcAddress(Kernel32, "CreateEventA");//".Client.crashevent" if you know yano
			if (!CreateEventA) return false;//MH_ERROR_ALREADY_INITIALIZED
			MH_STATUS Re = MH_Initialize();
			if (Re != MH_ERROR_ALREADY_INITIALIZED && Re != MH_OK) return false;//Needed temp until Drawing Lib is added
			if (MH_CreateHook((void*)CreateEventA, &CreateEventAHook, reinterpret_cast<LPVOID*>(&CreateEventAOriginal)) != MH_OK) return false;
			if (MH_EnableHook((void*)CreateEventA) != MH_OK) return false;
			original = (uintptr_t)CreateEventAOriginal;
			return true;
		}
	}
}