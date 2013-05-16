#ifndef IO_H_INCLUDED
#define IO_H_INCLUDED

#include <windows.h>
#include <string.h>

class EditBox
{
	HWND hEditBox;
public:
	void InitEditBox(HWND hDlg, int ctrlID)
	{
		hEditBox=GetDlgItem(hDlg, ctrlID);
	}

	char* GetText();
	bool SetText(char* buffer);
	bool AppendText(char* inputbuffer);
    bool ScrollLine();

};

class InputSignal{
    bool cmdAvail;
    char cmdStr[512];
    public:
    bool IsCmdAvail(){
    if(cmdAvail)
        return 1;
    return 0;
    }
    void SetCmd(bool v){cmdAvail=v;}
    void Reset(){cmdStr[0]=0;cmdAvail=0;}
    void GetCmdString(char* buffer){strcpy(buffer, cmdStr);}
    void SetCmdString(char* i)

    {
        strcpy(cmdStr, i);
    }
    InputSignal()
    {
        cmdAvail=0;
        cmdStr[0]=0;
    }
};
#endif // IO_H_INCLUDED
