#pragma once
#include "hookinfo.h"

namespace fake {
	namespace kernel32 {
		const hook::Module eModule = hook::Kernel32_dll;
		namespace func {
			enum Function {
				CreateFileA,
				LoadLibraryW,
				LoadLibraryExW,
				CreateProcessW,
				CreateProcessInternalW,

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
	}

	HMODULE WINAPI LoadLibraryW(__in LPCWSTR lpLibFileName);
	typedef HMODULE (WINAPI* __pfnLoadLibraryW)(__in LPCWSTR lpLibFileName);

	HMODULE WINAPI LoadLibraryExW(__in       LPCWSTR lpLibFileName, __reserved HANDLE hFile, __in       DWORD dwFlags);
	typedef HMODULE (WINAPI* __pfnLoadLibraryExW)(__in       LPCWSTR lpLibFileName, __reserved HANDLE hFile, __in       DWORD dwFlags);

	HANDLE WINAPI CreateFileA(__in LPCSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile);
	typedef HANDLE(WINAPI* __pfnCreateFileA)(__in LPCSTR lpFileName, __in DWORD dwDesiredAccess, __in DWORD dwShareMode, __in_opt LPSECURITY_ATTRIBUTES lpSecurityAttributes, __in DWORD dwCreationDisposition, __in DWORD dwFlagsAndAttributes, __in_opt HANDLE hTemplateFile);
	
	BOOL WINAPI CreateProcessW(_In_opt_ LPCWSTR lpApplicationName, _Inout_opt_ LPWSTR lpCommandLine, _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes, _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ BOOL bInheritHandles, _In_ DWORD dwCreationFlags, _In_opt_ LPVOID lpEnvironment, _In_opt_ LPCWSTR lpCurrentDirectory, _In_ LPSTARTUPINFOW lpStartupInfo, _Out_ LPPROCESS_INFORMATION lpProcessInformation);
	typedef BOOL(WINAPI* __pfnCreateProcessW)(_In_opt_ LPCWSTR lpApplicationName, _Inout_opt_ LPWSTR lpCommandLine, _In_opt_ LPSECURITY_ATTRIBUTES lpProcessAttributes, _In_opt_ LPSECURITY_ATTRIBUTES lpThreadAttributes, _In_ BOOL bInheritHandles, _In_ DWORD dwCreationFlags, _In_opt_ LPVOID lpEnvironment, _In_opt_ LPCWSTR lpCurrentDirectory, _In_ LPSTARTUPINFOW lpStartupInfo, _Out_ LPPROCESS_INFORMATION lpProcessInformation);

	BOOL WINAPI CreateProcessInternalW(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES	lpProcessAttributes, LPSECURITY_ATTRIBUTES	lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation, PHANDLE hNewToken);
	typedef BOOL(WINAPI* __pfnCreateProcessInternalW)(HANDLE hToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine, LPSECURITY_ATTRIBUTES	lpProcessAttributes, LPSECURITY_ATTRIBUTES	lpThreadAttributes, BOOL bInheritHandles, DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo, LPPROCESS_INFORMATION lpProcessInformation, PHANDLE hNewToken);

}