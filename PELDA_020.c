#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <commctrl.h>

#define HIBA_00 TEXT("Error:Program initialisation process.")
HINSTANCE hInstGlob;
int SajatiCmdShow;
char szClassName[] = "WindowsApp";
HWND Form1; //Ablak kezelője
FILE *file1; //fájlműveletekhez
POINT MousePos; //egérkoordináták kezeléséhez
LRESULT CALLBACK WndProc0(HWND, UINT, WPARAM, LPARAM);

//felugró üzenetablakok
void ShowMessage(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo);
int QuestionBox(LPCTSTR uzenet, LPCTSTR cim, HWND kuldo);

HWND Header2;
#define OBJ_ID100 100

void SetHeaderColText(HWND obj, int colnum, TCHAR* uzenet);
void GetHeaderColText(HWND obj, int colnum, TCHAR* uzenet);
void SetHeaderColWidth(HWND obj, int colnum, int szel);
void GetHeaderColWidth(HWND obj, int colnum, int* szel);

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
        Header2 = CreateWindowEx(0, WC_HEADER, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | HDS_HORZ | HDS_BUTTONS, 50, 50, 250, 40
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        {
            TCHAR szoveg[256];
            HD_ITEM elem;
            wcscpy_s(szoveg, L"Oszlop 1");
            elem.mask = HDI_TEXT | HDI_WIDTH;
            elem.cchTextMax = 7;
            elem.fmt = HDF_LEFT;
            elem.cxy = 70;
            elem.pszText = szoveg;
            SendMessage(Header2, HDM_INSERTITEM, 0, (LPARAM)&elem);
            wcscpy_s(szoveg, L"Oszlop 2");
            elem.mask = HDI_TEXT | HDI_WIDTH;
            elem.cchTextMax = 7;
            elem.fmt = HDF_LEFT;
            elem.cxy = 170;
            elem.pszText = szoveg;
            SendMessage(Header2, HDM_INSERTITEM, 1, (LPARAM)&elem);
        }

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
        switch (((LPNMHEADER)lParam)->hdr.code)
        {
            case HDN_ITEMCLICK:
            {
                switch (((LPNMHEADER)lParam)->hdr.idFrom)
                {
                case OBJ_ID100:
                    MessageBoxA(NULL, "Kattintás.", "Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
                    break;
                }
                break;
            }
            case HDN_ENDTRACK:
            {
                switch (((LPNMHEADER)lParam)->hdr.idFrom)
                {
                case OBJ_ID100:
                    MessageBoxA(NULL, "Átméretezés.", "Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
                    break;
                }
                break;
            }
        }
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

void SetHeaderColText(HWND obj, int colnum, TCHAR* uzenet)
{
    HD_ITEM elem;
    elem.mask = HDI_TEXT;
    elem.pszText = uzenet;
    elem.cchTextMax = sizeof(uzenet);
    elem.fmt = HDF_LEFT;
    SendMessage(obj, HDM_SETITEM, colnum, (LPARAM)&elem);
}

void GetHeaderColText(HWND obj, int colnum, TCHAR* uzenet)
{
    HD_ITEM elem;
    elem.mask = HDI_TEXT;
    elem.pszText = uzenet;
    elem.cchTextMax = 256;
    SendMessage(obj, HDM_GETITEM, colnum, (LPARAM)&elem);
}

void SetHeaderColWidth(HWND obj, int colnum, int szel)
{
    HD_ITEM elem;
    elem.mask = HDI_WIDTH;
    elem.cxy = szel;
    SendMessage(obj, HDM_SETITEM, colnum, (LPARAM)&elem);
}

void GetHeaderColWidth(HWND obj, int colnum, int* szel)
{
    HD_ITEM elem;
    elem.mask = HDI_WIDTH;
    SendMessage(obj, HDM_GETITEM, colnum, (LPARAM)&elem);
    *szel = elem.cxy;
}
