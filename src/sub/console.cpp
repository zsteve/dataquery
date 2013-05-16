/***********************************
    Main Console thread file
***********************************/
#include "console.h"
#include "..\main.h"

// Global variables
CommandProcess cmdp;
char buffer[160]={0};
char *pp;
// ****************

int ProcessCmd(char* cmd)
{
    if(!strcmpi(cmd, "!quit"))
        return _QUIT;
    if(!strcmpi(cmd, "!show"))
        return _SHOW;
    if(!strcmpi(cmd, "!next"))
        return _NEXT;
    if(!strcmpi(cmd, "!prev"))
        return _PREV;
    if(!strcmpi(cmd, "!find"))
        return _FIND;
    if(!strcmpi(cmd, "!set"))
        return _SET;
    else
    return -1;
}

DWORD WINAPI cmain(LPVOID lpParameter)
{
    llist ll;
    ll.InitList(100);
    ct.Output("Initialized list of ");
    ct.Output(ll.GetElementsCount());
    ct.Output(" elements\r\n");
    for(;;)
    {
        ct.Output("Welcome to this thing\r\n");
        ct.Input(buffer,160);
        ct.Output("Your input was :");
        ct.Output(buffer);
        ct.Output("\r\n");
        if(buffer[0])
        {
            pp=cmdp.PreprocessCmd(buffer);
            cmdp.ProcessCmd(pp);
            switch(ProcessCmd(cmdp.CmdWord))
            {
                case _QUIT:
                    ct.Output("Thread will exit now");
                    return 1;
                    break;
                case _SHOW:
                    // Show contents of current element in linked list
                    {
                        le *p=ll.GetCP();
                        ct.Output("\t");
                        ct.Output(p->id);
                        ct.Output();
                        ct.Output("\t");
                        ct.Output(p->itemname);
                        ct.Output();
                        ct.Output("\t");
                        ct.Output(p->itemdescrip);
                        ct.Output();
                    }
                    break;
                case _NEXT:
                    ll.StepOne();
                    break;
                case _PREV:
                    ll.UnstepOne();
                    break;
                case _FIND:
                    {
                        char* args;
                        le **r;
                        args=cmdp.CmdArgs[0];
                        ct.Output(args);
                        ll.SearchList(args);
                    }
                    break;
                case _SET:
                    {
                        char* args;
                        args=cmdp.CmdArgs[0];
                        le *c=ll.GetCP();
                        if(!strcmpi(args, "name"))
                        {
                            char in[80];
                            ct.Output("Enter new name :");
                            ct.Input(in, 80);
                            strcpy(c->itemname, in);
                        }
                        else if(!strcmpi(args, "descrip"))
                        {
                            char in[80];
                            ct.Output("Enter new description :");
                            ct.Input(in, 80);
                            strcpy(c->itemdescrip, in);
                        }
                    }
                    break;
            }
        }
    }
    cmdp.Reset();
    return 1;
}

void ConsoleThread::Input(char *buffer, int maxlen=80)
{
    while(!isig.IsCmdAvail())
    {
        Sleep(40);
    }
    isig.GetCmdString(buffer);
    isig.Reset();
}

void ConsoleThread::Output(char* buffer)
{
    inputEdit->AppendText(buffer);
    ScrollLine();
}

void ConsoleThread::Output(int num)
{
    char cnum[64];
    sprintf(cnum, "%d", num);
    inputEdit->AppendText(cnum);
    ScrollLine();
}

void ConsoleThread::Output()
{
    inputEdit->AppendText("\r\n");
}
