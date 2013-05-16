/*****************************************
DataQuery - Data Querying Application in C++
Code (C) Stephen Zhang - http://0x4c.phatcode.net
------------------------------------------
Descrip : This is the main cpp file
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
// non-standard include files
#include "sub\global.h"
#include "sub\io.h"g
InputSignal isig;
#include "rsrc\resource.h"
#include "sub\console.h"
#include "main.h"
#include "sub\cmd.h"

#define ERRICON MB_ICONERROR

using namespace std;

HINSTANCE hInstance;

EditBox gEdit;
EditBox gCmd;
ConsoleThread ct(&gEdit, &gCmd);

BOOL CALLBACK DlgProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	CommandProcess cmd;
	int wid,len;
	switch(Message)
	{
	case WM_INITDIALOG:
		gEdit.InitEditBox(hWnd, IDC_MAINEDIT);
		gCmd.InitEditBox(hWnd, IDC_CMD);
		{
            union sdim{
			unsigned long big;
			struct{
				unsigned short hi;
				unsigned short lo;
			}smll;
            }screen_dimensions;
            screen_dimensions.smll.hi=640  ;
            screen_dimensions.smll.lo=480;
            SendMessage(hWnd, WM_SIZE, 0, screen_dimensions.big);
            MoveWindow(hWnd, 200, 200, screen_dimensions.smll.hi, screen_dimensions.smll.lo, TRUE);
		}
        if(!ct.Create(8192, 0, cmain))
            MessageBox(NULL, "Error : Failed to init secondary thread", "error", ERRICON);
        SetTimer(hWnd, 1, 100, 0);
		return TRUE;
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
			case IDC_ENTERCMD:
                isig.SetCmd(TRUE);
                isig.SetCmdString(gCmd.GetText());
                gEdit.AppendText(gCmd.GetText());
                gEdit.AppendText("\r\n");
				gCmd.SetText("");
				break;
		}
        break;
    case WM_TIMER:
        switch(LOWORD(wParam))
        {
            case 1:
                if(GetAsyncKeyState(VK_RETURN)!=0)
                {
                    if(GetFocus()==GetDlgItem(hWnd, IDC_CMD))
                        SendMessage(hWnd, WM_COMMAND, IDC_ENTERCMD, 0);
                }
                break;
        }
        break;
	case WM_SIZE:
		// adjust size of IDC_MAINEDIT
			wid=LOWORD(lParam);
			len=HIWORD(lParam);
			MoveWindow(GetDlgItem(hWnd, IDC_MAINEDIT), 2,2, wid, len-24, 1);
			MoveWindow(GetDlgItem(hWnd, IDC_CMD), 2, len-22, wid-64, 20, 1);
			MoveWindow(GetDlgItem(hWnd, IDC_ENTERCMD),wid-64, len-22, 64, 20, 1);
			break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR pszCmdLine, int iCmdShow)
{
	hInstance = GetModuleHandle(NULL);
	DialogBox (hInst, MAKEINTRESOURCE(IDD_MAIN), 0, DlgProc);
	return 0;
}
