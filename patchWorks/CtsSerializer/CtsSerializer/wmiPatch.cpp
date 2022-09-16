#include "pch.h"
#include <comdef.h>
#include <Wbemidl.h>
#include "mhook-lib/mhook.h"
#include <atlconv.h>

//
// Typedefs.
//

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa392107%28v=vs.85%29.aspx

typedef HRESULT(WINAPI* tdExecQuery)
(
    IN DWORD dwUnknown,
    IN const BSTR strQueryLanguage,
    IN const BSTR strQuery,
    IN LONG lFlags,
    IN IWbemContext* pCtx,
    IN IEnumWbemClassObject** ppEnum
    );

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa391442%28v=vs.85%29.aspx

typedef HRESULT(WINAPI* tdQueryObjectGet)
(
    IN DWORD dwUnknown,
    IN LPCWSTR wszName,
    IN LONG lFlags,
    OUT VARIANT* pVal,
    OUT CIMTYPE* pvtType,
    OUT LONG* plFlavor
    );


//
// Globals.
//

tdExecQuery pExecQuery;
tdQueryObjectGet pQueryObjectGet;

WCHAR g_LastQuery[512] = { 0 };

//
// Functions.
//

HRESULT WINAPI _ExecQuery
(
    IN DWORD dwUnknown,
    IN const BSTR strQueryLanguage,
    IN const BSTR strQuery,
    IN LONG lFlags,
    IN IWbemContext* pCtx,
    IN IEnumWbemClassObject** ppEnum
)
{
    HRESULT hReturn = pExecQuery(dwUnknown, strQueryLanguage, strQuery, lFlags, pCtx, ppEnum);

    // Get the enumerator object...
    // IEnumWbemClassObject* pEnumerator = *ppEnum;

    wcscpy(g_LastQuery, strQuery);

    return hReturn;
}

HRESULT WINAPI _QueryObjectGet
(
    IN DWORD dwUnknown,
    IN LPCWSTR wszName,
    IN LONG lFlags,
    OUT VARIANT* pVal,
    OUT CIMTYPE* pvtType,
    OUT LONG* plFlavor
)
{
    USES_CONVERSION;

    HRESULT hReturn = pQueryObjectGet(dwUnknown, wszName, lFlags, pVal, pvtType, plFlavor);
#if 0
    if ((pVal->vt & VT_BSTR) == VT_BSTR)
    {
        if (wcsstr(g_LastQuery, L"Win32_Processor"))
        {
            // Example...
            if (!wcscmp(wszName, L"ProcessorId"))
            {
                wcscpy(pVal->bstrVal, L"UBER-KAWAII-PROCESSOR");
            }
            else
                if (!wcscmp(wszName, L"Name"))
                {

                }
        }
        else
            if (wcsstr(g_LastQuery, L"Win32_BaseBoard"))
            {
                if (!wcscmp(wszName, L"SerialNumber"))
                {
                    // Do your magic...
                }
                else
                    if (!wcscmp(wszName, L"Product"))
                    {

                    }
            }
            else
                if (wcsstr(g_LastQuery, L"Win32_BIOS"))
                {
                    if (!wcscmp(wszName, L"Name") ||
                        !wcscmp(wszName, L"Caption"))
                    {
                        // Do your magic...
                    }
                }
                else
                    if (wcsstr(g_LastQuery, L"Win32_IDEController"))
                    {
                        if (!wcscmp(wszName, L"PNPDeviceID"))
                        {

                        }
                        else
                            if (!wcscmp(wszName, L"Name"))
                            {

                            }
                    }
                    else
                        if (wcsstr(g_LastQuery, L"Win32_VideoController"))
                        {
                            if (!wcscmp(wszName, L"PnpDeviceID"))
                            {

                            }
                            else
                                if (!wcscmp(wszName, L"VideoProcessor"))
                                {

                                }
                                else
                                    if (!wcscmp(wszName, L"DeviceID"))
                                    {

                                    }
                        }
                        else
                            if (wcsstr(g_LastQuery, L"Win32_SoundDevice"))
                            {
                                if (!wcscmp(wszName, L"PnpDeviceId"))
                                {

                                }

                            }
                            else
                                if (wcsstr(g_LastQuery, L"Win32_PhysicalMemory"))
                                {
                                    if (!wcscmp(wszName, L"SerialNumber"))
                                    {
                                        // Do your magic...
                                    }
                                    else
                                        if (!wcscmp(wszName, L"PartNumber"))
                                        {
                                            // Do your magic...
                                        }

                                }
                                else
                                    if (wcsstr(g_LastQuery, L"Win32_DiskDrive"))
                                    {
                                        if (!wcscmp(wszName, L"Size"))
                                        {

                                        }
                                        else
                                            if (!wcscmp(wszName, L"Model"))
                                            {
                                                // Do your magic...
                                            }
                                            else
                                                if (!wcscmp(wszName, L"PnpDeviceID"))
                                                {

                                                }
                                    }
                                    else
                                        if (wcsstr(g_LastQuery, L"Win32_NetworkAdapter"))
                                        {
                                            if (!wcscmp(wszName, L"MACAddress"))
                                            {
                                                // Do your magic...
                                            }
                                            else
                                                if (!wcscmp(wszName, L"PnpDeviceID"))
                                                {

                                                }
                                        }
                                        else
                                            if (wcsstr(g_LastQuery, L"Win32_OperatingSystem"))
                                            {
                                                if (!wcscmp(wszName, L"SerialNumber"))
                                                {
                                                    // Do your magic...
                                                }
                                                else
                                                    if (!wcscmp(wszName, L"InstallDate"))
                                                    {
                                                        // Do your magic...
                                                    }
                                            }
    }
#else
    if ((pVal->vt & VT_BSTR) == VT_BSTR)
    {
        if (!wcscmp(wszName, L"ProcessorId"))
        {
            wcscpy(pVal->bstrVal, L"UBER-KAWAII-PROCESSOR");
        }
        //#	Time of Day	Thread	Module	API	Return Value	Error	Duration

        if (!wcscmp(wszName, L"Manufacturer"))
        {
            wcscpy(pVal->bstrVal, L"UBER-KAWAII-PROCESSOR");
        }
    }
    kgh_log("====== called =======\n");
#endif
    return hReturn;
}

typedef int (*pFn_WideCharToMultiByte)(
    UINT                               CodePage,
    DWORD                              dwFlags,
    LPCWCH lpWideCharStr,
    int                                cchWideChar,
    LPSTR                              lpMultiByteStr,
    int                                cbMultiByte,
    LPCCH                              lpDefaultChar,
    LPBOOL                             lpUsedDefaultChar
); 
pFn_WideCharToMultiByte g_ori_fn_WideCharToMultiByte;

int myWideCharToMultiByte(
    UINT                               CodePage,
    DWORD                              dwFlags,
    LPCWCH                              lpWideCharStr,
    int                                cchWideChar,
    LPSTR                              lpMultiByteStr,
    int                                cbMultiByte,
    LPCCH                              lpDefaultChar,
    LPBOOL                             lpUsedDefaultChar
)
{

    if (lpWideCharStr && lpMultiByteStr)
    {
        if (wcscmp(lpWideCharStr, L"BFEBFBFF000306C3") == 0)
        {
            strcpy(lpMultiByteStr, "FFEBFBFFF03306CF");
            kgh_log("====== patched myWideCharToMultiByte : %s , %d =======\n", lpMultiByteStr, 17);
            return 17;
        }
    }
    int nres = g_ori_fn_WideCharToMultiByte(CodePage, dwFlags, lpWideCharStr, cchWideChar, lpMultiByteStr, cbMultiByte, lpDefaultChar, lpUsedDefaultChar);

#if 0
    if(nres && lpMultiByteStr != NULL && cbMultiByte > 0)
        kgh_log("====== myWideCharToMultiByte : %s , %d =======\n", lpMultiByteStr, cbMultiByte);
#endif

#if 0
    if (nres && lpMultiByteStr != NULL && cbMultiByte > 0)
    {
        if (strcmp(lpMultiByteStr, "GenuineIntel") == 0)
        {

        }
        if (strcmp(lpMultiByteStr, "BFEBFBFF000306C3") == 0)
        {
            strcpy(lpMultiByteStr, "FFEBFBFFF03306CF");
            kgh_log("====== patched myWideCharToMultiByte : %s , %d =======\n", lpMultiByteStr, nres);
        }
    }
#endif
    return nres;
}

void wmi_install_patch()
{
    //pExecQuery = (tdExecQuery)Get_IWbemServices_ExecQuery_funcAddress();
    //pQueryObjectGet = (tdQueryObjectGet)Get_IWbemClassObject_Get_funcAddress();

    //Mhook_SetHook((PVOID*)&pQueryObjectGet, _QueryObjectGet);
    //kgh_log("PatchInfo: pExecQuery=0x%llx, pGet=0x%llx\n", pExecQuery, pQueryObjectGet);
    //Sleep(1000);
#if 1
    HMODULE hmod = GetModuleHandle("kernel32.dll");
    g_ori_fn_WideCharToMultiByte = (pFn_WideCharToMultiByte)GetProcAddress(hmod, "WideCharToMultiByte");
    //Mhook_SetHook((PVOID*)&g_ori_fn_WideCharToMultiByte, myWideCharToMultiByte);
    kgh_log("PatchInfo: kernel32 WideCharToMultiByte=0x%llx\n", g_ori_fn_WideCharToMultiByte);
#endif

    HMODULE hLibFnp = LoadLibrary("AppMaintainer_libFNP.dll");
    void* g_impaddr_widechar = *(void**)((__int64)hLibFnp + 0x1805A59C0 - 0x180000000);

    kgh_log("g_impaddr_widechar=0x%llx\n", g_impaddr_widechar);

}