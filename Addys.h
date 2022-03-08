enum RType
{
	TNIL = 0,
	TBOOLEAN = 1,
	TNUMBER = 4,
	TSTRING = 5,
	TFUNCTION = 8,
	TUSERDATA = 6,
	TTABLE = 7
};

int Identity1 = 24;
int Identity2 = 108;

int OFFSET_namecall = 100;

unsigned int ADDRESS_RetcheckJMP = 0x2AF57B0;
unsigned int ADDRESS_Index2Adr = 0x1459FA0;
unsigned int ADDRESS_CreateEventA = 8014903;

unsigned int ADDRESS_deserialize = 0x1465A50;
unsigned int ADDRESS_lua_type = 0x145C3E0;
unsigned int ADDRESS_lua_tonumber = 0x145C060;
unsigned int ADDRESS_lua_newthread = 0x145AA70;
unsigned int ADDRESS_lua_pushcclosure = 0x145ADF0;
unsigned int ADDRESS_lua_getfield = 0x145A570;
unsigned int ADDRESS_lua_setfield = 0x145BA20;
unsigned int ADDRESS_lua_pushstring = 0x145B100;
unsigned int ADDRESS_lua_pcall = 0x145ACE0;
unsigned int ADDRESS_lua_pushvalue = 0x145B2B0;
unsigned int ADDRESS_lua_pushnumber = 0x145B0A0;
unsigned int ADDRESS_luaL_checktype = 0x145C900;

#define CC_deserialize __cdecl
#define CC_lua_type __cdecl
#define CC_lua_tonumber __cdecl
#define CC_lua_newthread __cdecl
#define CC_lua_pushcclosure __stdcall
#define CC_lua_getfield __fastcall
#define CC_lua_setfield __stdcall
#define CC_lua_pushstring __stdcall
#define CC_lua_pcall __cdecl
#define CC_lua_pushvalue __stdcall
#define CC_lua_pushnumber __thiscall
#define CC_luaL_checktype __cdecl


typedef int(CC_deserialize* DEF_r_deserialize)(unsigned int RState, const char* Name, const char* Bytecode, int Size);

typedef RType(CC_lua_type* DEF_r_lua_type)(unsigned int RState, int Index);

typedef double(CC_lua_tonumber* DEF_r_lua_tonumber)(unsigned int RState, int Index);

typedef unsigned int(CC_lua_newthread* DEF_r_lua_newthread)(unsigned int RState);

typedef void(CC_luaL_checktype* DEF_r_luaL_checktype)(unsigned int RState, int Index, RType Type);
typedef void(CC_lua_pushcclosure* DEF_r_lua_pushcclosure)(unsigned int RState, unsigned int Address, int a3, int Upvalues, int a5);
typedef void(CC_lua_getfield* DEF_r_lua_getfield)(unsigned int RState, int Index, const char* Name);
typedef void(CC_lua_setfield* DEF_r_lua_setfield)(unsigned int RState, int Index, const char* Name);
typedef void(CC_lua_pushstring* DEF_r_lua_pushstring)(unsigned int RState, const char* String);
typedef void(CC_lua_pcall* DEF_r_lua_pcall)(unsigned int RState, int a1, int a2, int a3);
typedef void(CC_lua_pushvalue* DEF_r_lua_pushvalue)(unsigned int RState, int Index);
typedef void(CC_lua_pushnumber* DEF_r_lua_pushnumber)(unsigned int RState, int Number);

DEF_r_lua_pushnumber r_lua_pushnumber;
DEF_r_deserialize r_deserialize;
DEF_r_lua_type r_lua_type;
DEF_r_lua_tonumber r_lua_tonumber;
DEF_r_lua_newthread r_lua_newthread;
DEF_r_lua_pushcclosure r_lua_pushcclosure;
DEF_r_luaL_checktype r_luaL_checktype;
DEF_r_lua_getfield r_lua_getfield;
DEF_r_lua_setfield r_lua_setfield;
DEF_r_lua_pushstring r_lua_pushstring;
DEF_r_lua_pcall r_lua_pcall;
DEF_r_lua_pushvalue r_lua_pushvalue;

void r_spawn(unsigned int RLS) {
	r_lua_getfield(RLS, -10002, "spawn");
	r_lua_pushvalue(RLS, -2);
	r_lua_pcall(RLS, 1, 0, 0);
}

unsigned int Rebase(unsigned int Address)
{
	return (Address - 0x400000 + reinterpret_cast<unsigned int>(GetModuleHandleA(0)));
}

unsigned int* GetLevelLoc(unsigned int RState)
{
	return reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(RState + Identity2) + Identity1);
}

unsigned int GetRState()
{
	return EyeStep::util::debug_r32(Rebase(ADDRESS_Index2Adr) + 3, EyeStep::R32_EBP, 8, 1)[0];
}

bool SetupAddys()
{
	r_deserialize = reinterpret_cast<DEF_r_deserialize>(Rebase(ADDRESS_deserialize));
	r_lua_type = reinterpret_cast<DEF_r_lua_type>(Rebase(ADDRESS_lua_type));
	r_lua_tonumber = reinterpret_cast<DEF_r_lua_tonumber>(Rebase(ADDRESS_lua_tonumber));
	r_lua_newthread = reinterpret_cast<DEF_r_lua_newthread>(Rebase(ADDRESS_lua_newthread));
	r_lua_pushcclosure = reinterpret_cast<DEF_r_lua_pushcclosure>(Rebase(ADDRESS_lua_pushcclosure));
	r_luaL_checktype = reinterpret_cast<DEF_r_luaL_checktype>(Rebase(ADDRESS_luaL_checktype));
	r_lua_getfield = reinterpret_cast<DEF_r_lua_getfield>(Rebase(ADDRESS_lua_getfield));
	r_lua_setfield = reinterpret_cast<DEF_r_lua_setfield>(Rebase(ADDRESS_lua_setfield));
	r_lua_pushstring = reinterpret_cast<DEF_r_lua_pushstring>(Rebase(ADDRESS_lua_getfield));
	r_lua_pcall = reinterpret_cast<DEF_r_lua_pcall>(Rebase(ADDRESS_lua_pcall));
	r_lua_pushvalue = reinterpret_cast<DEF_r_lua_pushvalue>(Rebase(ADDRESS_lua_pushvalue));
	r_lua_pushnumber = reinterpret_cast<DEF_r_lua_pushnumber>(Rebase(ADDRESS_lua_pushnumber));
	return true;
}