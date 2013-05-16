#ifndef CONSOLE_H_INCLUDED
#define CONSOLE_H_INCLUDED

#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "cmd.h"
#include "list.h"
#include "global.h"

enum {_QUIT, _SHOW, _NEXT, _PREV, _FIND, _SET};

DWORD WINAPI cmain(LPVOID lpParameter);

class ConsoleThread{
    bool init;
    SECURITY_ATTRIBUTES tSec;
    int stLen;
    DWORD tId;
    EditBox* inputEdit;
    EditBox* outputEdit;
    public:
    ConsoleThread(EditBox* in, EditBox* out)
    {
        inputEdit=in;
        outputEdit=out;
    }
    bool Create(int stacksize, void *tParam, LPTHREAD_START_ROUTINE startproc)
    {
        if(init)
            return 0;
        return CreateThread(&tSec, stLen, startproc, tParam, 0, &tId);
    }
    void Input(char* buffer, int maxlen);
    void Output(char* buffer);
    void Output(int num);
    void Output();
    void ScrollLine()
    {
        inputEdit->ScrollLine();
    }
};

#endif // CONSOLE_H_INCLUDED
