#include <string>
#include <vector>
#include <assert.h>
#include <fstream>


#include "ini_parser.h"

//using namespace std;

namespace qh
{
	INIParser::INIParser()
	{}

	INIParser::~INIParser()
	{
		MapPair.clear();
		ret_val.clear();
	}
	
	
	std::vector<std::string> splite(const std::string &str, const std::string &c)
	{
		std::vector<std::string> result;
		std::string::size_type pos1, pos2;
		
		pos1 = 0;
		pos2 = str.find(c);

		while(std::string::npos != pos2)
		{
			std::string sub = str.substr(pos1, pos2 - pos1);
			if (!sub.empty()) //加此判断可以过滤掉开头的分隔符
				result.push_back(str.substr(pos1, pos2 - pos1) );
			pos1 = pos2 + c.size();
			pos2 = str.find(c, pos1);
		}
		if (pos1 != str.length())
			result.push_back(str.substr(pos1));

		return result;
	}

    bool INIParser::Parse(const std::string& ini_file_path)
	{
		
		bool res = true;

		std::ifstream fin(ini_file_path.c_str(), std::ios::in);
		assert(!fin.fail());
		
		std::string str_line;
		while(getline(fin, str_line))
		{
			size_t len = str_line.length();
		//	if (!Parse(str_line.c_str(), len) //为什么这里不能调用含有两个默认参数的Parse()函数？
			if (!Parse(str_line.c_str(), len)) 
			{	
				res = false;
			//	break;
				continue;
			}
		}

		fin.close();
		return res;
	}

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator, const std::string& key_value_seperator)
	{
		bool res = true;

		typedef std::pair<std::string, std::string> value_type;

		const std::string ini_data_src(ini_data, ini_data_len);
		std::vector<std::string> to_parse_str = splite(ini_data_src, line_seperator);

		std::vector<std::string> res_pair;

		std::vector<std::string>::const_iterator iter = to_parse_str.begin();
		for ( ; iter != to_parse_str.end(); iter ++)
		{
			res_pair = splite(*iter, key_value_seperator);
			
			assert (res_pair.size() == 2);
			value_type s(res_pair[0], res_pair[1]);
			MapPair.insert(s);	
		}

		return res;
	}
	
	

    const std::string& INIParser::Get(const std::string& key, bool* found)
	{
		bool y_true  = true, n_false = false;

		found = &n_false;

		std::map<std::string, std::string>::const_iterator iter = MapPair.find(key);
		if(iter != MapPair.end())
			ret_val = iter -> second;
		else
			ret_val = "";
		
		found = &y_true;
		
		return ret_val;

	}

	const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
	{
	//	*found = false;

		size_t len = section.length();

		if (!Parse(section.c_str(), len))
			assert(false);
		
		const std::string &res = Get(key, found);
		

		return res;
	}
	
}
