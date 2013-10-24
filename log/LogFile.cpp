#include <log/LogFile.h>
#include <base/noncopyable.h>
#include <base/ProcessInfo.h>

using namespace thefox;

// not thread safe
class LogFile::File : noncopyable
{
public:
	explicit File(const String& filename)
		: _fp(::fopen(filename.data(), "a"))
		, _writtenBytes(0)
	{
		//assert(_fp);
		::setvbuf(_fp, _buffer, _IOFBF, sizeof(_buffer));
	}

	~File()
	{
		::fclose(_fp);
	}

	void append(const char* logline, const size_t len)
	{
		size_t n = write(logline, len);
		size_t remain = len - n;
		while (remain > 0)
		{
			size_t x = write(logline + n, remain);
			if (x == 0)
			{
				int err = ferror(_fp);
				if (err)
				{
					//TRACE("LogFile::File::append() failed \r\n");
				}
				break;
			}
			n += x;
			remain = len - n;
		}

		_writtenBytes += len;
	}

	void flush()
	{
		::fflush(_fp);
	}

	size_t writtenBytes() const { return _writtenBytes; }

private:
	size_t write(const char* logline, size_t len)
	{
		return ::fwrite(logline, 1, len, _fp);
	}

  FILE* _fp;
  char _buffer[64*1024];
  size_t _writtenBytes;
};


LogFile::LogFile(const String& basename, size_t rollSize, bool threadSafe, int flushInterval)
	: _basename(basename)
	, _rollSize(rollSize)
	, _flushInterval(flushInterval)
	, _count(0)
	, _mutex(threadSafe ? new MutexLock : NULL)
	, _startOfPeriod(0)
	, _lastRoll(0)
	, _lastFlush(0)
{
	//assert(basename.find('/') == string::npos);
	rollFile();
	//append("Log begin", sizeof("Log begin"));
}

LogFile::~LogFile()
{
}

void LogFile::append(const char* logline, int len)
{
	if (_mutex)
	{
		MutexLockGuard lock(*_mutex);
		append_unlocked(logline, len);
	}
	else
	{
		append_unlocked(logline, len);
	}
}

void LogFile::flush()
{
	if (_mutex)
	{
		MutexLockGuard lock(*_mutex);
		_file->flush();
	}
	else
	{
		_file->flush();
	}
}

void LogFile::append_unlocked(const char* logline, int len)
{
	_file->append(logline, len);

	if (_file->writtenBytes() > _rollSize)
	{
		rollFile();
	}
	else
	{
		if (_count > _kCheckTimeRoll)
		{
			_count = 0;
			time_t now = ::time(NULL);
			time_t _thisPeriod = now / _kRollPerSeconds * _kRollPerSeconds;
			if (_thisPeriod != _startOfPeriod)
			{
				rollFile();
			}
			else if (now - _lastFlush > _flushInterval)
			{
				_lastFlush = now;
				_file->flush();
			}
		}
		else
		{
			++_count;
		}
	}
}

void LogFile::rollFile()
{
	time_t now = 0;
	String filename = getLogFileName(_basename, &now);
	time_t start = now / _kRollPerSeconds * _kRollPerSeconds;

	if (now > _lastRoll)
	{
		_lastRoll = now;
		_lastFlush = now;
		_startOfPeriod = start;
		_file.reset(new File(filename));
	}
}

String LogFile::getLogFileName(const String& basename, time_t *now)
{
  String filename;
  filename.reserve(basename.size() + 64);
  filename = basename;

  char timebuf[32];
  char pidbuf[32];
  
  *now = time(NULL);
  tm *tm_time = localtime(now);
  strftime(timebuf, sizeof timebuf, ".%Y%m%d-%H%M%S", tm_time);
  filename += timebuf;
  _snprintf(pidbuf, sizeof pidbuf, ".%d", ProcessInfo::pid());
  filename += pidbuf;
  filename += ".log";

  return filename;
}

