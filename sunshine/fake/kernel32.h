#pragma once
#include "hookinfo.h"

namespace fake {
	namespace kernel32 {
		const hook::Module eModule = hook::Kernel32_dll;
		namespace func {
			enum Function {
				CreateFileA,

				MaxFunctionNumber
			};
		}

		inline CNktHookLib::HOOK_INFO* SetHookInfo(func::Function enumFunction, void* lpProcToHook, void* lpNewProcAddr) {
			if (func::MaxFunctionNumber != hook::GetCount(eModule)) {
				hook::CreateHookInfo(eModule, func::MaxFunctionNumber);
			}

			CNktHookLib::HOOK_INFO* pHookInfo = hook::GetInfo(eModule, enumFunction);

			if (pHookInfo) {
				pHookInfo->nHookId = 0;
				pHookInfo->lpCallOriginal = NULL;

				pHookInfo->lpProcToHook = lpProcToHook;
				pHookInfo->lpNewProcAddr = lpNewProcAddr;
			}

			return pHookInfo;
		}

		typedef HANDLE (WINAPI* __pfnCreateFileA)(__in LPCSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile);

		HANDLE WINAPI CreateFileA(__in LPCSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile);
	}
}