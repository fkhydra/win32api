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

HWND ListView1;
#define OBJ_ID100 100

void AddLVColumn(HWND LVObject, int colnum, int colwidth, wchar_t *coltitle);
void AddLVItem(HWND LVObject, int mainitem, TCHAR* coltitle);
void AddLVSubItem(HWND LVObject, int mainitem, int subitem, TCHAR* coltitle);

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
        ListView1 = CreateWindowEx(0, WC_LISTVIEW, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_EDITLABELS, 10, 10, 500, 400
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        SendMessage(ListView1, LVM_SETEXTENDEDLISTVIEWSTYLE, 0, LVS_EX_FULLROWSELECT);
        
        AddLVColumn(ListView1, 0, 80,(wchar_t *)L"Fejléc 1");
        AddLVColumn(ListView1, 1, 80, (wchar_t*)L"Fejléc 2");
        AddLVColumn(ListView1, 2, 80, (wchar_t*)L"Fejléc 3");

        AddLVItem(ListView1,0, (wchar_t*)L"Elem1");
        AddLVItem(ListView1, 1, (wchar_t*)L"Elem2");

        AddLVSubItem(ListView1, 0, 2, (wchar_t*)L"Elem3");
        AddLVSubItem(ListView1, 1, 1, (wchar_t*)L"Elem4");
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
        switch (LOWORD(wParam))
        {
            case OBJ_ID100:
            {
                if (((LPNMHDR)lParam)->code == NM_CLICK)
                {
                    TCHAR szoveg[255];
                    int iSlected = 0;
                    LV_ITEM LvItem;
                    iSlected = SendMessage(ListView1, LVM_GETNEXTITEM, -1, LVNI_FOCUSED);
                    if (iSlected != -1)
                    {
                        memset(&LvItem, 0, sizeof(LvItem));
                        LvItem.mask = LVIF_TEXT;
                        LvItem.iSubItem = 0;
                        LvItem.pszText = szoveg;
                        LvItem.cchTextMax = 256;
                        LvItem.iItem = iSlected;
                        SendMessage(ListView1, LVM_GETITEMTEXT, iSlected, (LPARAM)&LvItem);
                        wcscpy_s(szoveg, 255, LvItem.pszText);
                        MessageBox(NULL, szoveg, L"Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
                        break;
                    }
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

void AddLVColumn(HWND LVObject, int colnum, int colwidth, wchar_t *coltitle)
{
    TCHAR szoveg[256];
    LV_COLUMN oszlop;
    memset(&oszlop, 0, sizeof(oszlop));
    wcscpy_s(szoveg, coltitle);
    oszlop.mask = LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
    oszlop.cx = colwidth;
    oszlop.pszText = szoveg;
    oszlop.cchTextMax = sizeof(szoveg);
    SendMessage(LVObject, LVM_INSERTCOLUMN, colnum, (LPARAM)&oszlop);
}

void AddLVItem(HWND LVObject, int mainitem, TCHAR* coltitle)
{
    TCHAR szoveg[256];
    LV_ITEM elem;
    memset(&elem, 0, sizeof(elem));
    wcscpy_s(szoveg, coltitle);
    elem.mask = LVIF_TEXT;
    elem.iItem = mainitem;
    elem.iSubItem = 0;
    elem.pszText = coltitle;
    elem.cchTextMax = sizeof(coltitle);
    SendMessage(LVObject, LVM_INSERTITEM, 0, (LPARAM)&elem);
}

void AddLVSubItem(HWND LVObject, int mainitem, int subitem, TCHAR* coltitle)
{
    LV_ITEM elem;
    memset(&elem, 0, sizeof(elem));
    elem.mask = LVIF_TEXT;
    elem.iItem = mainitem;
    elem.iSubItem = subitem;
    elem.pszText = coltitle;
    elem.cchTextMax = sizeof(coltitle);
    SendMessage(LVObject, LVM_SETITEM, 0, (LPARAM)&elem);
}
