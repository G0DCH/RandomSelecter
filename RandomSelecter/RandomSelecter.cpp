#include<iostream>
#include<io.h>
#include<vector>
#include<string>
#include<Windows.h>
#include<ctime>

using namespace std;

//Open file of path
void OpenExp(string path)
{
	ShellExecute(NULL, "open", path.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

int main()
{
	char path[MAX_PATH];
	char fullMyFilePath[MAX_PATH];
	char fileName[MAX_PATH];

	//file names which exists in directory
	vector<string> fileNames;

	string filePath;

	struct _finddata_t fd;
	intptr_t handle;

	srand((unsigned int)time(0));

	GetCurrentDirectory(MAX_PATH, path);

	GetModuleFileName(NULL, fullMyFilePath, MAX_PATH);
	GetFileTitle(fullMyFilePath, fileName, MAX_PATH);

	if ((handle = _findfirst("*.*", &fd)) == -1L)
	{
		cout << "No file in directory!" << endl;
		exit(1);
	}		

	//Find and add file names in directory
	do
	{
		if (strcmp(fd.name, "..") == 0)
			continue;
		if (strcmp(fd.name, ".") == 0)
			continue;
		if (strcmp(fd.name, fileName) == 0)
			continue;

		fileNames.push_back(fd.name);
	} while (_findnext(handle, &fd) == 0);

	_findclose(handle);

	filePath = path;

	filePath = filePath + "\\" + fileNames.at(rand() % fileNames.size());

	OpenExp(filePath);

	return 0;
}