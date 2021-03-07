To setup kbdflt on your system:

On Win32 environment edit the reg key:

`HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Windows`
or  
`HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows NT\CurrentVersion\Windows`
on win64

* AppInit_DLLs (REG_SZ) => put full path of kbdflt.dll;
* LoadAppInit_DLLs (REG_DWORD) => 0x00000001
* RequireSignedAppInit_DLLs (REG_DWORD) => 0x00000000

Reminder: only data from "putty.exe" are stored inside %APPDATA%\pid_putty_random.txt
