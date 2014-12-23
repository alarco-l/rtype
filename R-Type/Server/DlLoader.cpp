#include "DlLoader.hpp"

DlLoader::DlLoader(std::string const &DLLDir) : _path(DLLDir) {}

DlLoader::~DlLoader() {}

#ifdef WINDOWS
void							DlLoader::loadDLL(std::string const &path, std::string const &name)
{
	HMODULE						dll;
	char	 					dllName[256];
	std::string					tmp;
	size_t						start = 0;
	size_t						end = 0;

	dll = LoadLibrary(path.c_str());
	if (!dll)
		throw std::runtime_error(path + std::string(" : dll not found"));
	if (name == "")
	{
		GetModuleFileName(dll, dllName, 255);
		tmp = dllName;
		start = tmp.rfind("\\");
		end = tmp.find(".dll");
		if (start != std::string::npos && end != std::string::npos)
			tmp = tmp.substr(start + 1, (end + 3) - start);
		_dll[tmp] = dll;
		_name.push_back(tmp);
	}
	else
	{
		_dll[name] = dll;
		_name.push_back(name);
	}
}
#else
void							DlLoader::loadDLL(std::string const &path, std::string const &name)
{
	void						*dll = NULL;
	std::string					tmp;
	size_t						start = 0;
	size_t						end = 0;

	dll = dlopen(path.c_str(), RTLD_LAZY);
	if (!dll)
		throw std::runtime_error(path + std::string(" : .so not found"));
	if (name == "")
	{
		tmp = path;
		start = tmp.rfind("/");
		end = tmp.find(".so");
		if (start != std::string::npos && end != std::string::npos)
			tmp = tmp.substr(start + 1, (end + 3) - start);
		_dll[tmp] = dll;
		_name.push_back(tmp);
	}
	else
	{
		_dll[name] = dll;
		_name.push_back(name);
	}
}
#endif

#ifdef WINDOWS
void							DlLoader::loadDLLDir(std::string const &path)
{
	WIN32_FIND_DATA				ffd;
	HANDLE						handle = NULL;
	std::string					tmppath(_path + "/*");
	size_t						found;
	size_t						end = 0;
	std::string					tmp;
	std::string					name;

	if (path == "")
	{
		handle = FindFirstFile(tmppath.c_str(), &ffd);
		tmppath = _path + "/";
		if (!handle)
			throw std::runtime_error("Dir path is not valid");
		while (FindNextFile(handle, &ffd) != 0)
		{
			name = ffd.cFileName;
			found = name.find(".dll");
			if (found != std::string::npos)
			{
				tmp = tmppath + name;
				loadDLL(tmp);
			}
		}
	}
	else
	{
		tmppath = path + "/*";
		handle = FindFirstFile(tmppath.c_str(), &ffd);
		tmppath = path + "/";
		if (!handle)
			throw std::runtime_error("Dir path is not valid");
		while (FindNextFile(handle, &ffd) != 0)
		{
			name = ffd.cFileName;
			found = name.find(".dll");
			if (found != std::string::npos)
			{
				tmp = tmppath + name;
				loadDLL(tmp);
			}
		}
	}
}
#else
void							DlLoader::loadDLLDir(std::string const &path)
{
  DIR							*rep = NULL;
  struct dirent						*file = NULL;
  std::string						tmp;
  std::string						name;
  size_t						found = 0;
  
  if (path == "")
    {
      rep = opendir(_path.c_str());
      if (rep == NULL)
	throw std::runtime_error("Dir path is not valid");
      while ((file = readdir(rep)) != NULL)
	{
	  name = file->d_name;
	  found = name.find(".so");
	  if (found != std::string::npos)
	    {
	      tmp = _path + "/" + name;
	      loadDLL(tmp);
	    }
	}
    }
  else
    {
      rep = opendir(path.c_str());
      if (rep == NULL)
	throw std::runtime_error("Dir path is not valid");
      while ((file = readdir(rep)) != NULL)
	{
	  name = file->d_name;
	  found = name.find(".so");
	  if (found != std::string::npos)
	    {
	      tmp = path + "/" + name;
	      loadDLL(tmp);
	    }
	}
    }
  closedir(rep);
}
#endif

#ifdef WINDOWS
void							DlLoader::closeDLL(std::string const &name)
{
	FreeLibrary(_dll[name]);
}
#else
void							DlLoader::closeDLL(std::string const &name)
{
	dlclose(_dll[name]);
}
#endif

std::string const				&DlLoader::getDirPath() const { return (_path); }

void							DlLoader::setDirPath(std::string const &path) { _path = path; }

std::vector<std::string> const	&DlLoader::getAllDLLName() const { return (_name); }
