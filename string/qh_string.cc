#include "qh_string.h"

#include <string.h>

namespace qh
{
    // TODO 将在这里写实现代码

    string::string()
        : data_(NULL), len_(0)
    {
    }

    string::string( const char* s )
	{
		if (s == NULL)
		{
			data_ = new char[1];
			*data_ = '\0';

			len_ = 0;
		}
		else
		{
			data_ = new char[strlen(s) + 1];
			strcpy(data_, s);

			len_ = strlen(s);
		}
    }

    string::string( const char* s, size_t len )
    {
		if (s == NULL || len == 0)
		{
			data_ = new char[1];
			*data_ = '\0';
			
			len_ = 0;
		}
		/*
		else if (len < 0)
		{	
			data_ = new char[1 - len];
			char *temp = s; //不能转化的
			temp += strlen(s) + len;

			strncpy(data_, s, -len);
			data_[-len] = '\0';
			
			len_ = -len;
		}
		*/
		else
		{
			data_ = new char[len + 1];
			strncpy(data_, s, len);
			data_[len] = '\0';

			len_ = len;
		}
    }

    string::string( const string& rhs )
    {
		if (!rhs.data_)
		{
			data_ = new char[1];
			*data_ = '\0';
			len_ = 0;
		}
		else
		{
			data_ = new char[rhs.len_ + 1];
			strcpy(data_, rhs.data_);

			len_ = rhs.len_;
		}
    }

    string& string::operator=( const string& rhs )
    {
		if (this == &rhs)
	        return *this;

		delete []data_;
		data_ = NULL;

		if (rhs.data_ == NULL)
		{
			data_ = new	char[1];
			*data_ = '\0';

			len_ = 0;
		}
		else
		{
			data_ = new char[rhs.len_ + 1];
			strcpy(data_, rhs.data_);

			len_ = rhs.len_;
		}

		return *this;
    }

	bool string::operator==(const string& rhs)
	{
		if(rhs.len_ != len_)
			return false;
		else
			return strcmp(rhs.data_, data_) ? false : true;
	}

    string::~string()
    {
		delete []data_;
		data_ =  NULL;
		len_ = 0;
    }

    size_t string::size() const
    {
        return len_;
    }

    const char* string::data() const
    {
        return data_;;
    }

    const char* string::c_str() const
    {
		
        return data_;
    }

    char* string::operator[]( size_t index )
    {
//		assert(index >=0 && index < len_);
		if (index < 0 || index >= len_)
			return NULL;

		return data_ + index;
    }
}
