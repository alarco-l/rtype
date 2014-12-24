//
// Convert.hh for vm in /home/payan_a/Documents/system unix/Abstract-vm/cpp_abstractvm
// 
// Made by Axel PAYAN
// Login   <payan_a@epitech.net>
// 
// Started on  Fri Feb 28 14:26:13 2014 Axel PAYAN
// Last update Fri Feb 28 14:40:05 2014 Axel PAYAN
//

#pragma once

#include <sstream>

class Convert
{
public:
  template <typename _To, typename _From> static _To byStringStream(_From const &value)
  {
    std::stringstream	ss;
    _To			ret;

    ss << value;
    ss >> ret;
    return (ret);
  }
};
