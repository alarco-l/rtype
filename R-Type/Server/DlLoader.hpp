#pragma once

#ifdef __linux__
#include <dlfcn.h>
#include <dirent.h>
#include <sys/types.h>
#define LINUX
#elif _WIN32
#include <windows.h>
#define WINDOWS
#endif

#include "IDlLoader.h"

class								DlLoader : public IDlLoader
{
public:
	DlLoader(std::string const &DLLDir);
	~DlLoader();

	void							loadDLL(std::string const &path, std::string const &name = "");
	void							loadDLLDir(std::string const &path = "");
	void							closeDLL(std::string const &name);

	template<typename T>
	T								*getInstance(std::string const &name)
	{
		T*(*dll)(void) = NULL;
		T							*instance = NULL;

#ifdef LINUX
		dll = (T*(*)(void))dlsym(_dll[name], "newInstance");
#else
		dll = (T*(*)(void))GetProcAddress(_dll[name], "newInstance");
#endif
		if (!dll)
			throw std::runtime_error("Error corrupt dll");
		instance = dll();
		return instance;
	}

	std::string const				&getDirPath() const;
	std::vector<std::string> const	&getAllDLLName() const;

	void							setDirPath(std::string const &path);
private:
#ifdef WINDOWS
	std::map<std::string, HMODULE>	_dll;
#else
	std::map<std::string, void *>	_dll;
#endif
	std::string						_path;
	std::vector<std::string>		_name;
};
