#pragma once

#include <stdexcept>
#include <string>
#include <map>
#include <vector>

class										IDlLoader
{
public:
	virtual									~IDlLoader() {}

	virtual	void							loadDLL(std::string const &path, std::string const &name = "") = 0;
	virtual void							loadDLLDir(std::string const &path = "") = 0;
	virtual void							closeDLL(std::string const &name) = 0;

	virtual std::string const				&getDirPath() const = 0;
	virtual std::vector<std::string> const	&getAllDLLName() const = 0;

	virtual void							setDirPath(std::string const &path) = 0;
private:
	std::string								_path;
	std::vector<std::string>				_name;
};
