#pragma once

#include "process.hpp"
#include "logger.hpp"
#include "prepros.h"
#include "exceptions.h"

#define main(...)	main(int argc, char *argv[], char *env[])\
					{\
						try\
						{\
							::hpl::Process::start(argc, argv, env);\
							return (::hpl::Process::stop());\
						}\
						catch (::hpl::exception const &e)\
						{\
							::hpl::Logger::err(e.what());\
						}\
					}\
					int	hpl_main(__VA_ARGS__) 
