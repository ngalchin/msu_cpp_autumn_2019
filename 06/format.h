#pragma once
#include <iostream>
#include <sstream>
#include <cassert>
#include <vector>

//tranform to string
template <class T>
std::string my_str(T&& str)
{
	std::stringstream stream;
	stream << str;
	return stream.str();
}

template <class... ArgsT>
std::string format(const std::string& str, ArgsT&&... args)
{
	std::vector<std::string> arguments = {my_str(std::forward<ArgsT>(args))...};
	std::string resul = "";
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '{')
		{
			std::string tmp = "";
			i++;
			while(str[i] != '}')
			{
				if (!isdigit(str[i]) || i >= str.size())
				{
					throw std::runtime_error("Er");
				}
				tmp += str[i];
				i++;
			}
			if (tmp == "")
				throw std::runtime_error("Er");
			if (stoi(tmp) >= arguments.size())
				throw std::runtime_error("Er");
			resul += arguments[stoi(tmp)];
		}else{
			resul += str[i];
		}
	}
	return resul;
}
