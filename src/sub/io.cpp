#include "io.h"

char* EditBox::GetText()
{
	char *hGet;
	int l=GetWindowTextLength(hEditBox);
	hGet=(char*)malloc(l+1);
	GetWindowText(hEditBox, hGet, l+1);
	return hGet;
}


bool EditBox::SetText(char* buffer)
{
	SetWindowText(hEditBox, buffer);
	return TRUE;
}

bool EditBox::AppendText(char* inputbuffer)
{
	char *hNew;
	int l=GetWindowTextLength(hEditBox);
	hNew= (char*) malloc(l+strlen(inputbuffer)+1);
	GetWindowText(hEditBox, hNew, l+strlen(inputbuffer)+1);
	strcat(hNew, inputbuffer);
	SetWindowText(hEditBox, hNew);
	free(hNew);
	return TRUE;
}

bool EditBox::ScrollLine()
{
    SendMessage(hEditBox, EM_SETSEL, GetWindowTextLength(hEditBox)-2, GetWindowTextLength(hEditBox));
    SendMessage(hEditBox, EM_SCROLLCARET, 0, 0);
}
