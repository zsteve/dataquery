#ifndef CMD_H_INCLUDED
#define CMD_H_INCLUDED

#include <ctype.h>

class CommandProcess{
	// command processing
	char *hCmd;
public:
    char CmdWord[32];
	char CmdArgs[32][256];
	char* PreprocessCmd(char *h);
	char* ProcessCmd(char *preprocessed);
	void clear(char* buffer, int len);
    void Reset();
	CommandProcess()
	{
	    clear((char*)CmdWord, 32);
	    clear((char*)CmdArgs, 32*32);
	}
};


#endif // CMD_H_INCLUDED
