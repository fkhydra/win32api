#include <windows.h>
#include <stdio.h>
#include <commctrl.h>
#include <wchar.h>

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

HWND Button1, Button2;
HWND Edit1;
#define OBJ_ID100 100
#define OBJ_ID101 101
#define OBJ_ID102 102

HGLOBAL hMem;

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
        Button1 = CreateWindow(TEXT("button"), TEXT("Másol")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 50, 150, 120, 30
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        Button2 = CreateWindow(TEXT("button"), TEXT("Beilleszt")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 200, 150, 120, 30
            , hwnd, (HMENU)(OBJ_ID101), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        Edit1 = CreateWindow(TEXT("edit"), TEXT("Beviteli mező")
            , WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | WS_HSCROLL | WS_VSCROLL, 50, 50, 300, 60
            , hwnd, (HMENU)(OBJ_ID102), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
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
        int len;
        char szoveg[256];

        switch (LOWORD(wParam))
        {
         case OBJ_ID100:
            GetWindowTextA(Edit1, szoveg, GetWindowTextLength(Edit1) + 1);
            len = strlen(szoveg) + 1;
            hMem = GlobalAlloc(GMEM_MOVEABLE, len);
            memcpy_s((char *)GlobalLock(hMem), len, szoveg, len);
            GlobalUnlock(hMem);
            OpenClipboard(hwnd);
            EmptyClipboard();
            SetClipboardData(CF_TEXT, hMem);
            CloseClipboard();
            MessageBoxA(NULL, "A szöveg kimásolva a vágólapra!", "Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
            break;
         case OBJ_ID101:
             OpenClipboard(hwnd);
             if (hMem = GetClipboardData(CF_TEXT))
             {
                 //szoveg = (LPSTR)GlobalLock(hMem);
                 memcpy_s(szoveg, GlobalSize(hMem), (char*)GlobalLock(hMem), GlobalSize(hMem));
                 GlobalUnlock(hMem);
             }
             CloseClipboard();

             MessageBoxA(NULL, "Szöveg beolvasva a vágólapról!", "Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
             SetWindowTextA(Edit1,szoveg);
             break;
        }
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
