#include "cmd.h"

char* CommandProcess::PreprocessCmd(char *h)
{
    Reset();
	char* c=h;
	char* start=0;
    for(; *c; c++)
    {
        if(*c==' ')
        {
            // space - skip leading spaces
            continue;
        }
        else if(!start)
            start=c;
        if(isupper(*c))
            *c-=32; // convert to lowercase
    }
	return start;
}

char* CommandProcess::ProcessCmd(char *preprocessed)
{
    char* p=preprocessed;
    char *cw;
    char *ca;
    for(cw=&CmdWord[0]; (*p!=' ') && (*p); p++, cw++)
        *cw=*p; // copy cmd word
    // get command args
    int i=0;
    for(ca=&CmdArgs[0][0], p++; *p; p++, ca=&CmdArgs[i][0])
    {
        for(; (*p!=' ') && (*p!=0); ca++, p++)
        {
            *ca=*p;
        }
        i++;
    }
}

void CommandProcess::clear(char *buffer, int len)
{
    for(int i=0; i<len; i++)
        *(buffer+i)=0;
}

void CommandProcess::Reset()
{
    clear((char*)CmdWord, 32);
    clear((char*)CmdArgs, 32*32);
    hCmd=0;
}
