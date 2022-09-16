// ReadXml.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#define KGH_DUMP_FILE_PATH "D:\\works\\offline_id_file_test_ver9\\412019-E9GG97005E6LQY2R_fullKey\\offline_createid\\9.8-2\\1\\AppMaintainer.exe.dmp"

int isEdiusXml(char* pchFileName)
{
	FILE* fp = fopen(pchFileName, "rb");

	if (!fp)
		return 0;

	int nfilesize = 0;
	fseek(fp, 0, 2);
	nfilesize = ftell(fp);

	fseek(fp, 0, 0);

	char* pchBuf = new char[nfilesize];

	fread(pchBuf, nfilesize, 1, fp);

	int res = 0;
	if (strstr(pchBuf, "FLEXnet"))
		res = 1;

	delete[] pchBuf;
	fclose(fp);

	return res;
}

void dumpXml(char* pchBuf, int nfilesize)
{
	int pos = 0;
	while (pos < nfilesize)
	{
		char* pchStart = pchBuf + pos;

		int nMode = 0;
		if (strncmp(pchStart, "<?xml", 5) == 0)
		{
			nMode = 1;
		}
		if (strncmp(pchStart, "encoding=", 9) == 0)
		{
			nMode = 2;
		}
		if (nMode)
		{
			static int xmlCount = 1;
			char pchFileName[1024] = { 0 };
			sprintf(pchFileName, "d:\\dump_%d.xml", xmlCount);

			FILE* fp = fopen(pchFileName,"wb");
			
			while (1)
			{
				char curChar = *pchStart;
				if (!curChar)
					break;
				fwrite(&curChar, 1, 1, fp);
				pchStart++;
				pos++;
			}

			fclose(fp);

			if (!isEdiusXml(pchFileName))
				DeleteFileA(pchFileName);


			xmlCount++;
		}
		else
		{
			pos++;
		}
	}
}



int main()
{

	FILE* fp = fopen(KGH_DUMP_FILE_PATH, "rb");

	if (!fp)
		return 0;


	int nfilesize = 0;
	fseek(fp, 0, 2);
	nfilesize = ftell(fp);

	fseek(fp,0, 0);

	char* pchBuf = new char[nfilesize];

	fread(pchBuf, nfilesize, 1, fp);

	fclose(fp);

	dumpXml(pchBuf, nfilesize);

	delete pchBuf;
	return 0;
}
