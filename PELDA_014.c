#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>
#include <richedit.h>

#define HIBA_00 TEXT("Error:Program initialisation process.")
HINSTANCE hInstGlob;
int SajatiCmdShow;
char szClassName[] = "WindowsApp";
HWND Form1; //Ablak kezelője
FILE* file1; //fájlműveletekhez
POINT MousePos; //egérkoordináták kezeléséhez
LRESULT CALLBACK WndProc0(HWND, UINT, WPARAM, LPARAM);

//felugró üzenetablakok
void ShowMessage(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo);
int QuestionBox(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo);

HWND RichEdit1;
#define OBJ_ID100 100

BOOL REdit_loader(HWND hwndREdit, const char *pstrFileName);

//*********************************
//A windows program belépési pontja
//*********************************
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("StdWinClassName");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass0;
    SajatiCmdShow = iCmdShow;
    hInstGlob = hInstance;
    LoadLibrary(L"COMCTL32.DLL");
    LoadLibrary(TEXT("RICHED32.DLL"));

    //*********************************
    //Ablak osztálypéldány előkészítése
    //*********************************
    wndclass0.style = CS_HREDRAW | CS_VREDRAW;
    wndclass0.lpfnWndProc = WndProc0;
    wndclass0.cbClsExtra = 0;
    wndclass0.cbWndExtra = 0;
    wndclass0.hInstance = hInstance;
    wndclass0.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndclass0.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass0.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);//LTGRAY_BRUSH
    wndclass0.lpszMenuName = NULL;
    wndclass0.lpszClassName = TEXT("WIN0");

    //*********************************
    //Ablak osztálypéldány regisztrációja
    //*********************************
    if (!RegisterClass(&wndclass0))
    {
        MessageBox(NULL, HIBA_00, TEXT("Program Start"), MB_ICONERROR); return 0;
    }

    //*********************************
    //Ablak létrehozása
    //*********************************
    Form1 = CreateWindow(TEXT("WIN0"),
        TEXT("Ablak"),
        (WS_OVERLAPPED | WS_SYSMENU | WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX),
        50,
        50,
        400,
        300,
        NULL,
        NULL,
        hInstance,
        NULL);

    //*********************************
    //Ablak megjelenítése
    //*********************************
    ShowWindow(Form1, SajatiCmdShow);
    UpdateWindow(Form1);

    //*********************************
    //Ablak üzenetkezelésének aktiválása
    //*********************************
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

//*********************************
//Az ablak callback függvénye: eseménykezelés
//*********************************
LRESULT CALLBACK WndProc0(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;

    switch (message)
    {
        //*********************************
        //Ablak létrehozásakor közvetlenül
        //*********************************
    case WM_CREATE:
        /*Init*/;
        RichEdit1 = CreateWindow(TEXT("richedit"), TEXT("")
            , WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 50, 50, 200, 100
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(RichEdit1, EM_SETBKGNDCOLOR, 0, RGB(240, 240, 240));
        REdit_loader(RichEdit1, "teszt.rtf");
        return 0;
        //*********************************
        //görgetés kezeléséhez
        //*********************************
    case WM_HSCROLL:
        switch (LOWORD(wParam))
        {
            ;
        }
        return 0;
    case WM_VSCROLL:
        switch (LOWORD(wParam))
        {
            ;
        }
        return 0;
        //*********************************
        //speciális üzenetkezelő
        //*********************************
    case WM_NOTIFY: {
        return 0; }
                  //*********************************
                  //bal egérgomb felengedve (lenyomás után)
                  //*********************************
    case WM_LBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //középső egérgomb felengedve (lenyomás után)
        //*********************************
    case WM_MBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //jobb egérgomb felengedve (lenyomás után)
        //*********************************
    case WM_RBUTTONUP:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //vezérlőelem működtetése (többnyire kattintás)
        //*********************************
    case WM_COMMAND:
        MousePos.x = LOWORD(lParam);
        MousePos.y = HIWORD(lParam);
        return 0;
        //*********************************
        //Ablak átméretezése
        //*********************************
    case WM_SIZE:
        return 0;

        //*********************************
        //Ablak kliens területének újrarajzolása
        //*********************************
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
        return 0;
        //*********************************
        //Ablak bezárása
        //*********************************
    case WM_CLOSE:
        DestroyWindow(hwnd);
        return 0;
        //*********************************
        //Ablak megsemmisítése
        //*********************************
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}

//*********************************
//Üzenetablak OK gombbal
//*********************************
void ShowMessage(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo)
{
    MessageBox(kuldo, uzenet, cim, MB_OK);
}

//*********************************
//Üzenetablak YES-NO gombbal
//*********************************
int QuestionBox(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo)
{
    return MessageBox(kuldo, uzenet, cim, MB_YESNO);
}

BOOL REdit_loader(HWND hwndREdit, const char *pstrFileName)
{
    BYTE csere;
    DWORD beolvasas_hossz;
    HANDLE hFile;
    int i, fajl_hossz, uni_ellenorzes;
    TCHAR* pBuffer, * pText, * pConv;

    // fájl megkeresése
    SetWindowText(hwndREdit, TEXT(""));
    if (INVALID_HANDLE_VALUE ==
        (hFile = CreateFileA(pstrFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL)))
    {
        return FALSE;
    }

    // fájl beolvasása
    fajl_hossz = GetFileSize(hFile, NULL);
    pBuffer = (TCHAR*)malloc(fajl_hossz + 2);
    ReadFile(hFile, pBuffer, fajl_hossz, &beolvasas_hossz, NULL);
    CloseHandle(hFile);
    pBuffer[fajl_hossz] = '\0';
    pBuffer[fajl_hossz + 1] = '\0';

    //Unicode tartalom kezelése
    uni_ellenorzes = IS_TEXT_UNICODE_SIGNATURE | IS_TEXT_UNICODE_REVERSE_SIGNATURE;

    if (IsTextUnicode(pBuffer, fajl_hossz, &uni_ellenorzes))
    {
        pText = pBuffer + 2; fajl_hossz -= 2;

        if (uni_ellenorzes & IS_TEXT_UNICODE_REVERSE_SIGNATURE)
        {
            for (i = 0; i < fajl_hossz / 2; i++)
            {
                csere = ((BYTE*)pText)[2 * i];
                ((BYTE*)pText)[2 * i] = ((BYTE*)pText)[2 * i + 1];
                ((BYTE*)pText)[2 * i + 1] = csere;
            }
        }

        pConv = (TCHAR*)malloc(fajl_hossz + 2);

#ifndef UNICODE
        WideCharToMultiByte(CP_ACP, 0, (PWSTR)pText, -1, pConv, fajl_hossz + 2, NULL, NULL);
#else
        lstrcpy((PTSTR)pConv, (PTSTR)pText);
#endif
    }
    else      // nem Unicode a tartalom
    {
        pText = pBuffer;
        pConv = (TCHAR*)malloc(2 * fajl_hossz + 2);
#ifdef UNICODE
        MultiByteToWideChar(CP_ACP, 0, (LPCCH)pText, -1, (PTSTR)pConv, fajl_hossz + 1);
#else
        lstrcpy((PTSTR)pConv, (PTSTR)pText);
#endif
    }
    SetWindowText(hwndREdit, (PTSTR)pConv);
    free(pBuffer);
    free(pConv);
    return TRUE;
}