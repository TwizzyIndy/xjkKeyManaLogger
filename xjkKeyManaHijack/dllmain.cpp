// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "xjkKeyManaHijack.h"
#include <Psapi.h>
#include <strsafe.h>
#include <string>
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "xjkKeyManaOriginal.lib")

extern "C"{

	HINSTANCE hXjkKeyMana = LoadLibrary(TEXT("original.dll"));
	
	HANDLE  hOut = CreateFile(L"log.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	typedef BOOL(__stdcall* original_xjkOpenKey)(IN char* cPassWord, IN char cLetter);
	typedef BOOL(__stdcall* original_xjkOpenKeyEx) (IN char* cPassWord);
	typedef BOOL(__stdcall* original_xjkCloseKey)();
	typedef BOOL(__stdcall* original_xjkReadSector)(IN char* cDataRead, IN int iSector);
	typedef BOOL(__stdcall* original_xjkReadCluster)(IN char* cDataRead, IN int iCluster);
	typedef BOOL(__stdcall* original_xjkWriteSector)(IN char* cDataWrite, IN int iSector);
	typedef BOOL(__stdcall* original_xjkWriteCluster)(IN char* cDataWrite, IN int iCluster);
	typedef BOOL(__stdcall* original_xjkChangePwd)( IN char* cOldPwd, IN char* cNewPwd);
	typedef BOOL(__stdcall* original_xjkGetSerial)( IN char* cSerial);
	typedef int(__stdcall* original_xjkGetSectors)();
	typedef int(__stdcall* original_xjkGetClusters)();

	void DumpMemory(char* location, DWORD length) {

		DWORD i, written;
		char *hexDigit = "0123456789ABCDEF";
		char *space = " ", *crlf = "\r\n";

		WriteFile(hOut, space, strlen(space), &written, NULL);
		for (i = 0; i < length; i++) {
			WriteFile(hOut, space, strlen(space), &written, NULL);
			WriteFile(hOut, (hexDigit + ((location[i] >> 4) & 0x0F)), 1, &written, NULL);
			WriteFile(hOut, (hexDigit + ((location[i] >> 0) & 0x0F)), 1, &written, NULL);
			if (((i + 1) % 26 == 0) && ((i + 1) < length)) {
				WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
				WriteFile(hOut, space, strlen(space), &written, NULL);
			}
		}

		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);

	}

	XJKKEYMANAHIJACK_API BOOL xjkOpenKey(char* cPassWord, char cLetter)
	{

		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkOpenKey openKey = (original_xjkOpenKey)GetProcAddress(hXjkKeyMana, "xjkOpenKey");
		
		//sprintf(buffer, "xjkOpenKey : \npassword : %s\nletter : %c\n", cPassWord, cLetter);
		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		result = openKey(cPassWord, cLetter);

		DumpMemory(cPassWord, 20);
		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkOpenKeyEx(char* cPassWord)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		if (hXjkKeyMana == NULL || hXjkKeyMana == 0)
		{
			MessageBoxA(0, "Load library failed", "error", MB_OK);
		}
		
		original_xjkOpenKeyEx openKeyEx = (original_xjkOpenKeyEx)GetProcAddress(hXjkKeyMana, "xjkOpenKeyEx");

		if (openKeyEx == NULL)
		{
			MessageBoxA(0, "xjkOpenKeyEx Getprocaddress error", "error", MB_OK);
		}
		sprintf(buffer, "xjkOpenKeyEx : \npassword : %s\n", cPassWord);
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		result = openKeyEx(cPassWord);

		//DumpMemory(cPassWord, 20);

		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkCloseKey()
	{
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "\n\nim in xjkCloseKey\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		BOOL result;
		original_xjkCloseKey closeKey = (original_xjkCloseKey)GetProcAddress(hXjkKeyMana, "xjkCloseKey");

		result = closeKey();

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkReadSector(char* cDataRead, int iSector)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkReadSector\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkReadSector readSector = (original_xjkReadSector)GetProcAddress(hXjkKeyMana, "xjkReadSector");

		char data[518];

		result = readSector(data, iSector);
		cDataRead = data;
		//memcpy(cDataRead, data, 512);

		//sprintf(buffer, "xjkReadSector : \ncDataRead : %s\n iSector : %i", cDataRead, iSector);

		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		//DumpMemory(cDataRead, iSector);

		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkReadCluster(char* cDataRead, int iCluster)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];
		
		sprintf(buffer, "im in xjkReadCluster\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkReadCluster readCluster = (original_xjkReadCluster)GetProcAddress(hXjkKeyMana, "xjkReadCluster");

		result = readCluster(cDataRead, iCluster);

		//sprintf(buffer, "xjkReadCluster : \ncDataRead : %s\n iCluster : %i", cDataRead, iCluster);

		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);
		DumpMemory(cDataRead, iCluster);


		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkWriteSector(char* cDataWrite, int iSector)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkWriteSector\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkWriteSector writeSector = (original_xjkWriteSector)GetProcAddress(hXjkKeyMana, "xjkWriteSector");

		result = writeSector(cDataWrite, iSector);

		//sprintf(buffer, "xjkReadCluster : \ncDataRead : %s\n iCluster : %i", cDataWrite, iSector);

		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);
		DumpMemory(cDataWrite, iSector);


		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}
	XJKKEYMANAHIJACK_API BOOL xjkWriteCluster(char* cDataWrite, int iCluster)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkWriteCluster\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkWriteCluster writeCluster = (original_xjkWriteCluster)GetProcAddress(hXjkKeyMana, "xjkWriteCluster");

		result = writeCluster(cDataWrite, iCluster);

		//(buffer, "xjkWriteCluster : \ncDataWrite : %s\n iCluster : %i", cDataWrite, iCluster);

		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);
		DumpMemory(cDataWrite, iCluster);


		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;
	}

	XJKKEYMANAHIJACK_API BOOL xjkChangePwd(char* cOldPwd, char* cNewPwd)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkChangePwd\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkChangePwd changePwd = (original_xjkChangePwd)GetProcAddress(hXjkKeyMana, "xjkChangePwd");

		//sprintf(buffer, "xjkChangePwd : \nold : %s\nnew : %c\n", cOldPwd, cNewPwd);
		//WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		result = changePwd(cOldPwd, cNewPwd);

		DumpMemory(cOldPwd, 30);
		DumpMemory(cNewPwd, 30);

		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;

	}

	XJKKEYMANAHIJACK_API BOOL xjkGetSerial(char* cSerial)
	{
		BOOL result;
		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		original_xjkGetSerial getSerial = (original_xjkGetSerial)GetProcAddress(hXjkKeyMana, "xjkGetSerial");


		result = getSerial(cSerial);

		//DumpMemory(cSerial, 20);

		sprintf(buffer, "xjkGetSerial : \nserial : %s\n", cSerial);
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		WriteFile(hOut, crlf, strlen(crlf), &written, NULL);
		sprintf(buffer, "===============================\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		return result;

	}

	XJKKEYMANAHIJACK_API int xjkGetSectors()
	{

		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkGetSectors\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		int result;
		original_xjkGetSectors getSectors = (original_xjkGetSectors)GetProcAddress(hXjkKeyMana, "xjkGetSectors");

		result = getSectors();
		return result;
	}
	XJKKEYMANAHIJACK_API int xjkGetClusters()
	{

		DWORD written;
		char *crlf = "\r\n";
		const int bufferLength = 1024;
		char buffer[bufferLength];

		sprintf(buffer, "im in xjkGetClusters\n");
		WriteFile(hOut, buffer, strlen(buffer), &written, NULL);

		int result;
		original_xjkGetClusters getClusters = (original_xjkGetClusters)GetProcAddress(hXjkKeyMana, "xjkGetClusters");

		result = getClusters();
		return result;
	}
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		if (hXjkKeyMana == 0 || hXjkKeyMana == NULL || hOut == 0 || hOut == NULL)
		{
			hXjkKeyMana = LoadLibraryA("original.dll");
			hOut = CreateFile(L"log.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		}

	case DLL_THREAD_ATTACH:
		if (hXjkKeyMana == 0 || hXjkKeyMana == NULL || hOut == 0 || hOut == NULL)
		{

			hXjkKeyMana = LoadLibraryA("original.dll");
			if (hXjkKeyMana == NULL)
			{
				MessageBoxA(0, "Load library failed", "error", MB_OK);
			}

			hOut = CreateFile(L"log.txt", GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hOut == NULL)
			{
				MessageBoxA(0, "createfile fail", "error", MB_OK);
			}
		}
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

