#include <windows.h>
#include <tchar.h>
#include <psapi.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	TCHAR fichier[5000];
	DWORD pids[500];
	DWORD returned;
	unsigned int i;
	int t;
	EnumProcesses(pids, 500, &returned);
	HANDLE h;


	for (i = 0; i < returned / sizeof(DWORD); i++)
	{
		h = OpenProcess(READ_CONTROL | PROCESS_QUERY_INFORMATION, 0, pids[i]);

		printf("PID = %d  ", pids[i]);
		if (h == NULL)
		{
			DWORD err = GetLastError();
			printf("ECHEC HANDLE : Code %d\n", err);
			continue;
		}
		t = GetProcessImageFileName(h, fichier, 5000);
		if (t == 0)
		{
			DWORD err = GetLastError();
			printf("ECHEC RECUP NOM : Code %d\n", err);
			continue;
		}
		_tprintf(_T("  %s\n"), fichier);
		CloseHandle(h);
	}
	return 0;
}