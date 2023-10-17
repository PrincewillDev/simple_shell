#include "shell.h"

int _setenv(const char *vname, const char *value, int overwrite)
{
	int result;
	if (vname == NULL)
	{
		perror("Invalid Argument");
		return -1;
	}

	if (getenv(vname) != NULL && !overwrite)
	{
		return 0;
	}

	result = setenv(vname, value, overwrite);
	if (result != 0)
	{
		fputs("Failed to set environment variable\n", stderr);
		return -1;
	}

	return 0;
}
