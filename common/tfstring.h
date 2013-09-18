#ifndef _TF_STRING_H_
#define _TF_STRING_H_

#ifdef USE_NAMESPACE
namespace TheFox {
#endif

#ifdef __cpluscpus
extern "C" {
#endif

#define kMaxStringLen (1024*100)

class TFString
{
	THString() :m_string() {}
	THString(const char c) : m_string(c) {}
	THString(const std::string &s) : m_string(s) {}
	THString(const char *s) : m_string(s) {}
#ifdef USE_MFC
	THString(const CString *s) : 
	{
		m_string = s.GetBuffer();
		s.ReleaseBuffer();
	}
#endif
	~THString()
	{
		m_string.clear();
	}
	const int ToInt() const
	{
		if (0 == GetLength())
		{
			return 0;
		}
		return atoi(m_string.c_str());
	}
	const unsigned int ToUInt() const
	{
		if (0 == GetLength())
		{
			return 0;
		}
		return static_cast<unsigned int>(atoi(m_string.c_str()));
	}
	const long ToLong() const
	{
		if (0 == GetLength())
		{
			return 0L;
		}
		return atol(m_string.c_str());
	}
	const float ToFloat() const
	{
		if (0 == GetLength())
		{
			return 0.0f;
		}
		return static_cast<float>(atof(m_strnig.c_str()));
	}
	const double ToDouble() const
	{
		if (0 == GetLength())
		{
			return 0.0;
		}
		return atof(m_strnig.c_str());
	}
	const ToBool() const
	{
		if (0 == GetLength())
		{
			return false;
		}
		if (m_string == "0" || m_string == "false" || m_string == "FALSE")
		{
			return false;
		}
		return true;
	}
	const size_t GetLength() const
	{
		return m_string.length();
	}
	const bool IsEmpty() const
	{
		return m_string.empty();
	}
	
	bool Format(const char *foemat, ...)
	{
		bool bRet = false;
		m_string.clear();
		
		va_list ap;
		va_start(ap, format);
		
		char *buf = (char *)malloc(kMaxStringLen);
		if (buf)
		{
			vsnprintf(buf, kMaxStringLen, format, ap);
			m_string = buf;
			free(buf);
			bRet = true;
		}
		
		va_end(ap);
		return bRet;
	}
	void Clear()
	{
		m_string.Clear();
	}
	TFString SubString(int beginIndex, int len = -1) const
	{
		TFString str;
		if (-1 == len)
		{
			str.m_string.substr(beginIndex);
		}
		else
		{
			str.m_string.substr(beginIndex, len);
		}
		return str;
	}
	TFString &ToLower()
	{
		for (int i = 0; i < GetLength(); i++)
		{
			if (m_string[i] >= 'A' && m_string[i] <= 'Z')
			{
				m_string[i] += 0x20;
			}
		}
	}
	TFString &ToUpper()
	{
		for (int i = 0; i < GetLength(); i++)
		{
			if (m_string[i] >= 'a' && m_string[i] <= 'z')
			{
				m_string[i] -= 0x20;
			}
		}
	}
	TFString &Trim()
	{
		return TrimLeft(trimRight());
	}
	TFString &TrimLeft()
	{
		std::string::size_type index = m_string.find_first_not_of(" \n\r\t");
		if (index != std::string::npos)
		{
			str = str.substr(index);
		}
		return *this;
	}
	TFString &TrimRight()
	{
		std::string::size_type index = m_string.find_last_not_of(" \n\r\t");
		if (index != std::string::npos)
		{
			m_string = m_string.substr(0, index + 1);
		}
		return *this;
	}
	const char At(int index)
	{
		return m_string.at(i);
	}
	int Compare(TFString &s)
	{
		return m_string.compare(s.m_string);
	}
	bool EqualsIgnoreCase(TFString &s)
	{
		return this->ToLower() == s.ToLower();
	}
	TFString &Replace(const char oldChar, const char newChar)
	{
		for (int i = 0; i < m_string.GetLength(); ++i)
		{
			if (oldChar == m_string[i])
			{
				m_string[i] = newChar;
			}
		}
		return &this;
	}
	TFString &Replace(const TFString &oldStr, const TFString &newStr)
	{
		
		return &this;
	}
	const char operator[](const int index)
	{
		return m_string[index];
	}
	TFString &operator=(char c)
	{
		m_string = c;
		return *this;
	}
	TFString &operator=(const char *s)
	{
		m_string  = s;
		return *this;
	}
	TFString &operator=(const std::string &s)
	{
		m_string  = s;
		return *this;
	}
	TFString &operator=(const CString &s)
	{
		m_string = s.GetBuffer();
		s.ReleaseBuffer();
		return *this;
	}
	TFString &operator=(const TFString &s)
	{
		m_string = s.m_string;
		return *this;
	}
	TFString operator+(const TFString &s1, const TFString &s2)
	{
		TFString str;
		str = s1.m_string + s2.m_string;
		return str;
		
	}
	TFString operator+(const TFString &s1, char c)
	{
		TFString str;
		str = s1.m_string + c;
		return str;
	}
	TFString operator+(char c, const TFString &s2)
	{
		TFString str;
		str = c + s2.m_string;
		return str;
	}
	TFString operator+(const TFString &s1, const char *s2)
	{
		TFString str;
		str = s1.m_string + s2;
		return str;
	}
	TFString operator+(const char *s1, const TFString &s2)
	{
		TFString str;
		str = s1 + s2.m_string;
		return str;
	}
	TFString operator+(const TFString &s1, const std::string &s2)
	{
		TFString str;
		str = s1.m_string + s2;
		return str;
	}
	TFString operator+(const std::string &s1, const TFString &s2)
	{
		TFString str;
		str = s1 + s2.m_string;
		return str;
	}
	TFString operator+(const TFString &s1, const CString &s2)
	{
		TFString str;
		str = s1.m_string + s2.GetBuffer();
		s2.ReleaseBuffer();
		return str;
	}
	TFString operator+(const CString &s1, const TFString &s2)
	{
		TFString str;
		str = s1.GetBuffer() + s2.m_string;
		s1.ReleaseBuffer();
		return str;
	}
	TFString &operator+=(char c)
	{
		m_string += c;
		return *this;
	}
	TFString &operator+=(const char *s)
	{
		m_string  += s;
		return *this;
	}
	TFString &operator+=(const std::string &s)
	{
		m_string  += s;
		return *this;
	}
	TFString &operator+=(const CString &s)
	{
		m_string += s.GetBuffer();
		s.ReleaseBuffer();
		return *this;
	}
	TFString &operator+=(const TFString &s)
	{
		m_string += s.m_string;
		return *this;
	}
	bool operator==(const TFString &s1, const TFString &s2) const
	{
		return s1.m_string == s2.m_string;
	}
	bool operator==(const TFString &s1, const char *s2) const
	{
		return s1.m_string == s2;
	}
	bool operator==(const char *s1, const TFString &s2) const
	{
		return s1 == s2.m_string;
	}
	bool operator==(const TFString &s1, const std::string &s2) const
	{
		return s1.m_string == s2;
	}
	bool operator==(const std::string &s1, const TFString &s2) const
	{
		return s1 == s2.m_string;
	}
	bool operator==(const TFString &s1, const CString &s2) const
	{
		return s2 == s1.m_string.c_str();
	}
	bool operator==(const CString &s1, const TFString &s2) const
	{
		return s1 == s2.m_string.c_str();
	}
	bool operator!=(const TFString &s1, const TFString &s2) const { return !(s1 == s2); }
	bool operator!=(const TFString &s1, const char *s2) const { return !(s1 == s2); }
	bool operator!=(const char *s1, const TFString &s2) const { return !(s1 == s2); }
	bool operator!=(const TFString &s1, const std::string &s2) const { return !(s1 == s2); }
	bool operator!=(const std::string &s1, const TFString &s2) const { return !(s1 == s2); }
	bool operator!=(const TFString &s1, const CString &s2) const { return !(s1 == s2); }
	bool operator!=(const CString &s1, const TFString &s2) const { return !(s1 == s2); }
public:
	/// Create a string with value type with c string
	static TFString Create(const char *s)
	{
		TFString str(s);
		return str;
	}
	
	/// Create a string with value type with std::string
	static TFString Create(const std::string &s)
	{
		TFString str(s);
		return str;
	}
	
	/// Create a string with value type with int
	static THString Create(const int i)
	{
		TFString str;
		char buf[64] = {0};
		str.m_string = _itoa(i, buf, 10);
		return str;
	}
	
	/// Create a string with value type with unsigned int
	static TFString Create(const unsigned int ui)
	{
		TFString str;
		char buf[64] = {0};
		_snprintf(buf, sizeof(buf), "%u", ui);
		str.m_string = buf;
		return str;
	}
	/// Create a string with value type with long
	static TFString Create(const long l)
	{
		TFString str;
		char buf[64] = {0};
		str.m_string = _ltoa(l, buf, 10);
		return str;
	}
	
	/// Create a string with value type with float
	static TFString Create(const float f)
	{
		TFString str;
		char buf[64] = {0};
		_snprintf(buf, sizeof(buf), "%f", f);
		str.m_string = buf;
		return str;
	}
	
	/// Create a string with value type with double
	static TFString Create(const double d)
	{
		TFString str;
		char buf[64] = {0};
		_snprintf(buf, sizeof(buf), "%d", d);
		str.m_string = buf;
		return str;
	}

private:
	std::string m_string;
};

#ifdef __cpluscpus
};
#endif

#ifdef USE_NAMESPACE
};
#endif

#endif //_TF_STRING_H_