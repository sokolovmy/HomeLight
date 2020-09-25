#include <stdio.h>
#include "emCLI.h"

bool cmdHelp(const char* args) {
	printf("this help command\r\n");
	return true;
};

bool cmdList(const char* args) {
	printf("this list command\r\n");
	return true;
};

bool cmdSubCmd(const char* args) {
	printf("this subcmd command");
	return true;
};

#define EOFCOMMAND { NULL, NULL, NULL, NULL, NULL}

EMCCommand subCmds[] = {
	{
		"subcmd1",
		"sub cmd1 help",
		"",
		&cmdSubCmd,
		NULL
	}, {
		"subcmd1",
		"sub cmd1 help",
		"",
		cmdSubCmd,
		NULL
	},
	EOFCOMMAND
};

const EMCCommand cmds[] = {
	{
		"help",
		"some help descr",
		"bla bla bla",
		cmdHelp,
		NULL
	}, {
		"list",
		"list command help",
		"sadf;lksj;lkj sdf;lkj",
		cmdList,
		NULL
	}, {
		"subcmd",
		"subcmd command help",
		"sdfsdf ;lkjsdf[powe;lkjsfd",
		NULL,
		subCmds
	},
	EOFCOMMAND
};

