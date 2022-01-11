#ifndef _WX_WXSTDSTREAM_H__
#define _WX_WXSTDSTREAM_H__
#include <ios>
#include <istream>
#include <ostream>
#include <streambuf>
#include <wx/defs.h>
#include <wx/stream.h>

class wxStdInputStreamBuffer : public std::streambuf
{
public:
	wxStdInputStreamBuffer(wxInputStream& stream);
	virtual ~wxStdInputStreamBuffer() { }

protected:
	virtual std::streambuf *setbuf(char *s, std::streamsize n);
	virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way,
		std::ios_base::openmode which =	std::ios_base::in | std::ios_base::out);
	virtual std::streampos seekpos(std::streampos sp,
		std::ios_base::openmode which =	std::ios_base::in | std::ios_base::out);
	virtual std::streamsize showmanyc();
	virtual std::streamsize xsgetn(char *s, std::streamsize n);
	virtual int underflow();
	virtual int uflow();
	virtual int pbackfail(int c = EOF);

	wxInputStream& m_stream;
	int m_lastChar;
};

class wxStdInputStream : public std::istream
{
public:
	wxStdInputStream(wxInputStream& stream);
	virtual ~wxStdInputStream() { }

protected:
	wxStdInputStreamBuffer m_streamBuffer;
};

class wxStdOutputStreamBuffer : public std::streambuf
{
public:
	wxStdOutputStreamBuffer(wxOutputStream& stream);
	virtual ~wxStdOutputStreamBuffer() { }

protected:
	virtual std::streambuf *setbuf(char *s, std::streamsize n);
	virtual std::streampos seekoff(std::streamoff off, std::ios_base::seekdir way,
		std::ios_base::openmode which =	std::ios_base::in | std::ios_base::out);
	virtual std::streampos seekpos(std::streampos sp,
		std::ios_base::openmode which =	std::ios_base::in | std::ios_base::out);
	virtual std::streamsize xsputn(const char *s, std::streamsize n);
	virtual int overflow(int c);

	wxOutputStream& m_stream;
};

class wxStdOutputStream : public std::ostream
{
public:
	wxStdOutputStream(wxOutputStream& stream);
	virtual ~wxStdOutputStream() { }

protected:
	wxStdOutputStreamBuffer m_streamBuffer;
};
#endif // _WX_WXSTDSTREAM_H__
