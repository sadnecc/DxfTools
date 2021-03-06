#include "stdafx.h"
#include "MuMa.h"
#include "GameManager.h"




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 头文件
#include <Windows.h>
#include "Shlwapi.h"
#pragma comment( lib, "Shlwapi.lib")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 宏定义
#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)

#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall
#define ALCDECL EXTERNC NAKED void __cdecl
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Hook 命名空间
namespace Hook
{
	HHOOK m_hHook;			// HOOK 句柄


	// HOOK 函数
	LRESULT CALLBACK HookProc(INT iCode, WPARAM wParam, LPARAM lParam)
	{
		if (iCode > 0)
		{
			;
		}

		return CallNextHookEx(m_hHook, iCode, wParam, lParam);
	}

	// Hook
	inline BOOL WINAPI Hook(INT iHookId = WH_CALLWNDPROC)
	{
		m_hHook = SetWindowsHookEx(iHookId, HookProc, NULL, GetCurrentThreadId());
		return (m_hHook != NULL);
	}

	// Unhook
	inline VOID WINAPI Unhook()
	{
		if (m_hHook)
		{
			UnhookWindowsHookEx(m_hHook);
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// AheadLib 命名空间
namespace AheadLib
{
	HMODULE m_hModule = NULL;		// 原始模块句柄
	DWORD m_dwReturn[35] = { 0 };		// 原始函数返回地址


	// 加载原始模块
	inline BOOL WINAPI Load()
	{
		TCHAR tzPath[MAX_PATH];
		TCHAR tzTemp[MAX_PATH * 2];

		GetSystemDirectory(tzPath, MAX_PATH);
		lstrcat(tzPath, TEXT("\\samcli.dll"));
		m_hModule = LoadLibrary(tzPath);
		if (m_hModule == NULL)
		{
			wsprintf(tzTemp, TEXT("无法加载 %s，程序无法正常运行。"), tzPath);
			MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
		}

		return (m_hModule != NULL);
	}

	// 释放原始模块
	inline VOID WINAPI Free()
	{
		if (m_hModule)
		{
			FreeLibrary(m_hModule);
		}
	}

	// 获取原始函数地址
	FARPROC WINAPI GetAddress(PCSTR pszProcName)
	{
		FARPROC fpAddress;
		CHAR szProcName[64];
		TCHAR tzTemp[MAX_PATH];

		fpAddress = GetProcAddress(m_hModule, pszProcName);
		if (fpAddress == NULL)
		{
			if (HIWORD(pszProcName) == 0)
			{
				wsprintfA(szProcName, "%d", pszProcName);
				pszProcName = szProcName;
			}

			wsprintf(tzTemp, TEXT("无法找到函数 %hs，程序无法正常运行。"), pszProcName);
			MessageBox(NULL, tzTemp, TEXT("AheadLib"), MB_ICONSTOP);
			ExitProcess(-2);
		}

		return fpAddress;
	}
}
using namespace AheadLib;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 入口函数
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
#pragma comment(linker, "/EXPORT:NetGetDisplayInformationIndex=_AheadLib_NetGetDisplayInformationIndex,@1")
#pragma comment(linker, "/EXPORT:NetGroupAdd=_AheadLib_NetGroupAdd,@2")
#pragma comment(linker, "/EXPORT:NetGroupAddUser=_AheadLib_NetGroupAddUser,@3")
#pragma comment(linker, "/EXPORT:NetGroupDel=_AheadLib_NetGroupDel,@4")
#pragma comment(linker, "/EXPORT:NetGroupDelUser=_AheadLib_NetGroupDelUser,@5")
#pragma comment(linker, "/EXPORT:NetGroupEnum=_AheadLib_NetGroupEnum,@6")
#pragma comment(linker, "/EXPORT:NetGroupGetInfo=_AheadLib_NetGroupGetInfo,@7")
#pragma comment(linker, "/EXPORT:NetGroupGetUsers=_AheadLib_NetGroupGetUsers,@8")
#pragma comment(linker, "/EXPORT:NetGroupSetInfo=_AheadLib_NetGroupSetInfo,@9")
#pragma comment(linker, "/EXPORT:NetGroupSetUsers=_AheadLib_NetGroupSetUsers,@10")
#pragma comment(linker, "/EXPORT:NetLocalGroupAdd=_AheadLib_NetLocalGroupAdd,@11")
#pragma comment(linker, "/EXPORT:NetLocalGroupAddMember=_AheadLib_NetLocalGroupAddMember,@12")
#pragma comment(linker, "/EXPORT:NetLocalGroupAddMembers=_AheadLib_NetLocalGroupAddMembers,@13")
#pragma comment(linker, "/EXPORT:NetLocalGroupDel=_AheadLib_NetLocalGroupDel,@14")
#pragma comment(linker, "/EXPORT:NetLocalGroupDelMember=_AheadLib_NetLocalGroupDelMember,@15")
#pragma comment(linker, "/EXPORT:NetLocalGroupDelMembers=_AheadLib_NetLocalGroupDelMembers,@16")
#pragma comment(linker, "/EXPORT:NetLocalGroupEnum=_AheadLib_NetLocalGroupEnum,@17")
#pragma comment(linker, "/EXPORT:NetLocalGroupGetInfo=_AheadLib_NetLocalGroupGetInfo,@18")
#pragma comment(linker, "/EXPORT:NetLocalGroupGetMembers=_AheadLib_NetLocalGroupGetMembers,@19")
#pragma comment(linker, "/EXPORT:NetLocalGroupSetInfo=_AheadLib_NetLocalGroupSetInfo,@20")
#pragma comment(linker, "/EXPORT:NetLocalGroupSetMembers=_AheadLib_NetLocalGroupSetMembers,@21")
#pragma comment(linker, "/EXPORT:NetQueryDisplayInformation=_AheadLib_NetQueryDisplayInformation,@22")
#pragma comment(linker, "/EXPORT:NetUserAdd=_AheadLib_NetUserAdd,@23")
#pragma comment(linker, "/EXPORT:NetUserChangePassword=_AheadLib_NetUserChangePassword,@24")
#pragma comment(linker, "/EXPORT:NetUserDel=_AheadLib_NetUserDel,@25")
#pragma comment(linker, "/EXPORT:NetUserEnum=_AheadLib_NetUserEnum,@26")
#pragma comment(linker, "/EXPORT:NetUserGetGroups=_AheadLib_NetUserGetGroups,@27")
#pragma comment(linker, "/EXPORT:NetUserGetInfo=_AheadLib_NetUserGetInfo,@28")
#pragma comment(linker, "/EXPORT:NetUserGetLocalGroups=_AheadLib_NetUserGetLocalGroups,@29")
#pragma comment(linker, "/EXPORT:NetUserModalsGet=_AheadLib_NetUserModalsGet,@30")
#pragma comment(linker, "/EXPORT:NetUserModalsSet=_AheadLib_NetUserModalsSet,@31")
#pragma comment(linker, "/EXPORT:NetUserSetGroups=_AheadLib_NetUserSetGroups,@32")
#pragma comment(linker, "/EXPORT:NetUserSetInfo=_AheadLib_NetUserSetInfo,@33")
#pragma comment(linker, "/EXPORT:NetValidatePasswordPolicy=_AheadLib_NetValidatePasswordPolicy,@34")
#pragma comment(linker, "/EXPORT:NetValidatePasswordPolicyFree=_AheadLib_NetValidatePasswordPolicyFree,@35")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGetDisplayInformationIndex(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[0 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGetDisplayInformationIndex")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[0 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupAdd(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[1 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupAdd")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[1 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupAddUser(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[2 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupAddUser")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[2 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupDel(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[3 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupDel")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[3 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupDelUser(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[4 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupDelUser")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[4 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupEnum(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[5 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupEnum")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[5 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupGetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[6 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupGetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[6 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupGetUsers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[7 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupGetUsers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[7 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupSetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[8 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupSetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[8 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetGroupSetUsers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[9 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetGroupSetUsers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[9 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupAdd(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[10 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupAdd")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[10 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupAddMember(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[11 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupAddMember")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[11 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupAddMembers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[12 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupAddMembers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[12 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupDel(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[13 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupDel")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[13 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupDelMember(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[14 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupDelMember")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[14 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupDelMembers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[15 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupDelMembers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[15 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupEnum(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[16 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupEnum")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[16 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupGetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[17 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupGetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[17 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupGetMembers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[18 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupGetMembers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[18 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupSetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[19 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupSetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[19 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetLocalGroupSetMembers(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[20 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetLocalGroupSetMembers")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[20 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetQueryDisplayInformation(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[21 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetQueryDisplayInformation")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[21 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserAdd(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[22 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserAdd")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[22 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserChangePassword(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[23 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserChangePassword")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[23 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserDel(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[24 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserDel")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[24 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserEnum(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[25 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserEnum")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[25 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserGetGroups(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[26 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserGetGroups")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[26 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserGetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[27 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserGetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[27 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserGetLocalGroups(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[28 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserGetLocalGroups")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[28 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserModalsGet(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[29 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserModalsGet")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[29 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserModalsSet(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[30 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserModalsSet")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[30 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserSetGroups(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[31 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserSetGroups")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[31 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetUserSetInfo(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[32 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetUserSetInfo")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[32 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetValidatePasswordPolicy(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[33 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetValidatePasswordPolicy")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[33 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL AheadLib_NetValidatePasswordPolicyFree(void)
{
	// 保存返回地址到 TLS
	__asm PUSH m_dwReturn[34 * TYPE long];
	__asm CALL DWORD PTR[TlsSetValue];

	// 调用原始函数
	GetAddress("NetValidatePasswordPolicyFree")();

	// 获取返回地址并返回
	__asm PUSH EAX;
	__asm PUSH m_dwReturn[34 * TYPE long];
	__asm CALL DWORD PTR[TlsGetValue];
	__asm XCHG EAX, [ESP];
	__asm RET;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 入口函数
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);
		HideModuleByHandle(hModule);
		GameManager::GetInstance()->Init();
		return Load();
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		Free();
	}

	return TRUE;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

