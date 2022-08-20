// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the XJKKEYMANAHIJACK_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// XJKKEYMANAHIJACK_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

extern "C"
{


#ifdef XJKKEYMANAHIJACK_EXPORTS
#define XJKKEYMANAHIJACK_API __declspec(dllexport)
#else
#define XJKKEYMANAHIJACK_API __declspec(dllimport)
#endif

	XJKKEYMANAHIJACK_API BOOL xjkOpenKey(char* cPassWord, char cLetter);
	XJKKEYMANAHIJACK_API BOOL xjkOpenKeyEx(char* cPassWord);
	XJKKEYMANAHIJACK_API BOOL xjkCloseKey();
	XJKKEYMANAHIJACK_API BOOL xjkReadSector(char* cDataRead, int iSector);
	XJKKEYMANAHIJACK_API BOOL xjkReadCluster(char* cDataRead, int iCluster);
	XJKKEYMANAHIJACK_API BOOL xjkWriteSector(char* cDataWrite, int iSector);
	XJKKEYMANAHIJACK_API BOOL xjkWriteCluster(char* cDataWrite, int iCluster);
	XJKKEYMANAHIJACK_API BOOL xjkChangePwd(char* cOldPwd, char* cNewPwd);
	XJKKEYMANAHIJACK_API BOOL xjkGetSerial(char* cSerial);
	XJKKEYMANAHIJACK_API int xjkGetSectors();
	XJKKEYMANAHIJACK_API int xjkGetClusters();
}