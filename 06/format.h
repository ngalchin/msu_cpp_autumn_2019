#pragma once
#include <sstream>
#include <cassert>
#include <vector>

using namespace std;

//tranform to string
template <class T>
string my_str(T&& str)
{
	stringstream stream;
	stream << str;
	return stream.str();
}

template <class... ArgsT>
string format(const string& str, ArgsT&&... args)
{
	vector<string> arguments = {my_str(forward<ArgsT>(args))...};
	string str_res = str;
	for (size_t i = 0; i < str.size(); i++)
	{
		if (str[i] == '{')
		{
			string tmp = "";
			i++;
			while(str[i] != '}')
			{
				if (!isdigit(str[i]) || i >= str.size())
				{
					throw runtime_error("");
				}
				tmp += str[i];
				i++;
			}
			if (tmp == "")
				throw runtime_error("");
			if (stoi(tmp) >= arguments.size())
				throw runtime_error("");
			//while (str_res.find("{" + tmp + "}") != strng::npos)
			str_res.replace(str_res.find("{" + tmp + "}"), tmp.length() + 2, arguments[stoi(tmp)]);
		}
	}
	return str_res;
}