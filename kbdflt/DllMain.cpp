#include <Windows.h>

BOOL WINAPI DllMain(_In_ HINSTANCE hInstance, _In_ DWORD fdwReason, _In_ LPVOID lpvReserved)
{
	
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls((HMODULE)hInstance);
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	default:
		break;
	}

	return TRUE;
}
