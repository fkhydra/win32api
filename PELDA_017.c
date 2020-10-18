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

HWND TreeView1;
HWND Button1;
#define OBJ_ID100 100
#define OBJ_ID101 101

void AddTreeviewItem(HWND hwndTV, TCHAR lpszItem[], int nlevel);

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
        TreeView1 = CreateWindowEx(0, WC_TREEVIEW, (LPCWSTR)NULL, WS_CHILD | WS_VISIBLE | TVS_DISABLEDRAGDROP | TVS_HASBUTTONS | TVS_HASLINES, 50, 50, 200, 150
            , hwnd, (HMENU)(OBJ_ID100), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        TCHAR felirat[256];
        wcscpy_s(felirat,L"Főelem");
        AddTreeviewItem(TreeView1, felirat,1);
        wcscpy_s(felirat, L"Alelem 1");
        AddTreeviewItem(TreeView1, felirat, 2);
        wcscpy_s(felirat, L"Alelem 2");
        AddTreeviewItem(TreeView1, felirat, 2);
        wcscpy_s(felirat, L"Alelem 3");
        AddTreeviewItem(TreeView1, felirat, 3);
        wcscpy_s(felirat, L"Alelem 4");
        AddTreeviewItem(TreeView1, felirat, 3);
        wcscpy_s(felirat, L"Alelem 5");
        AddTreeviewItem(TreeView1, felirat, 3);
        wcscpy_s(felirat, L"Alelem 6");
        AddTreeviewItem(TreeView1, felirat, 3);

        Button1 = CreateWindow(TEXT("button"), TEXT("Nyomógomb")
            , WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_MULTILINE, 10, 200, 150, 30
            , hwnd, (HMENU)(OBJ_ID101), ((LPCREATESTRUCT)lParam)->hInstance, NULL);
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
        switch (((LPNMHDR)lParam)->code)
        {
            case NM_CLICK:
            {
                switch (((LPNMHDR)lParam)->idFrom)
                {
                case OBJ_ID100:
                    //TCHAR szoveg[256];
                    //HTREEITEM elem = NULL;
                    //TV_ITEMW listaelemadat;
                    //int sorszam;

                    //SendMessage(TreeView1, TVM_GETNEXTITEM, (WPARAM)TVGN_NEXT, (LPARAM)&elem);
                    ////TreeView_GetNextSelected(TreeView1, elem);
                    //listaelemadat.hItem = elem;
                    //listaelemadat.mask = TVIF_TEXT;
                    //listaelemadat.pszText = szoveg;
                    //listaelemadat.cchTextMax = 255;
                    //SendMessage(TreeView1, TVM_GETITEM, 0, (LPARAM)&listaelemadat);
                    //wcscpy_s(szoveg, 255,listaelemadat.pszText);
                    //MessageBoxA(NULL, (const char*)szoveg, "Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
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
        switch (LOWORD(wParam))
        {
        case OBJ_ID101:
            WCHAR szoveg[256];
            WCHAR uzenet[256];
            HTREEITEM elem;
            TV_ITEMW listaelemadat;

            elem = (HTREEITEM)SendDlgItemMessage(hwnd, OBJ_ID100, TVM_GETNEXTITEM, TVGN_CARET, (LPARAM)NULL);
            listaelemadat.hItem = elem;
            listaelemadat.mask = TVIF_TEXT;
            listaelemadat.pszText = szoveg;
            listaelemadat.cchTextMax = wcslen(szoveg);
            SendDlgItemMessage(hwnd, OBJ_ID100, TVM_GETITEM, TVGN_CARET, (LPARAM)&listaelemadat);
            
            wcscpy_s(uzenet,L"A kiválasztott elem: ");
            wcscat_s(uzenet,szoveg);
            MessageBox(NULL, uzenet, L"Felhasználói interakció", MB_OK | MB_ICONINFORMATION);
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

void AddTreeviewItem(HWND hwndTV, TCHAR lpszItem[], int nlevel)
{
    TVITEM tvi;
    TVINSERTSTRUCT tvins;
    static HTREEITEM hprev = (HTREEITEM)TVI_FIRST;
    static HTREEITEM hprevrootitem = NULL;
    static HTREEITEM hprevlev2item = NULL;
    static HTREEITEM hprevlev3item = NULL;
    static HTREEITEM hprevlev4item = NULL;
    static HTREEITEM hprevlev5item = NULL;
    static HTREEITEM hprevlev6item = NULL;
    static HTREEITEM hprevlev7item = NULL;
    static HTREEITEM hprevlev8item = NULL;
    static HTREEITEM hprevlev9item = NULL;
    static HTREEITEM hprevlev10item = NULL;

    if (nlevel < 1 || nlevel>10) { return; }
    tvi.mask = TVIF_TEXT | TVIF_PARAM;
    tvi.pszText = lpszItem;
    tvi.cchTextMax = sizeof(tvi.pszText) / sizeof(tvi.pszText[0]);
    tvi.lParam = (LPARAM)nlevel;
    tvins.item = tvi;
    tvins.hInsertAfter = hprev;
    if (nlevel == 1) { tvins.hParent = TVI_ROOT; }
    else if (nlevel == 2) { tvins.hParent = hprevrootitem; }
    else if (nlevel == 3) { tvins.hParent = hprevlev2item; }
    else if (nlevel == 4) { tvins.hParent = hprevlev3item; }
    else if (nlevel == 5) { tvins.hParent = hprevlev4item; }
    else if (nlevel == 6) { tvins.hParent = hprevlev5item; }
    else if (nlevel == 7) { tvins.hParent = hprevlev6item; }
    else if (nlevel == 8) { tvins.hParent = hprevlev7item; }
    else if (nlevel == 9) { tvins.hParent = hprevlev8item; }
    else if (nlevel == 10) { tvins.hParent = hprevlev9item; }
    else { tvins.hParent = hprevlev9item; }
    hprev = (HTREEITEM)SendMessage(hwndTV, TVM_INSERTITEM, 0, (LPARAM)(LPTVINSERTSTRUCT)&tvins);
    if (nlevel == 1) { hprevrootitem = hprev; }
    else if (nlevel == 2) { hprevlev2item = hprev; }
    else if (nlevel == 3) { hprevlev3item = hprev; }
    else if (nlevel == 4) { hprevlev4item = hprev; }
    else if (nlevel == 5) { hprevlev5item = hprev; }
    else if (nlevel == 6) { hprevlev6item = hprev; }
    else if (nlevel == 7) { hprevlev7item = hprev; }
    else if (nlevel == 8) { hprevlev8item = hprev; }
    else if (nlevel == 9) { hprevlev9item = hprev; }
    else if (nlevel == 10) { hprevlev10item = hprev; }
}
