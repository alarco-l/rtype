#include "buffer.h"
#include "utils.hpp"

namespace hpl
{
	const ulint	Buffer::_bufferSize = 256;

	Buffer::RotatingBuffer::RotatingBuffer(ulint size) : _deb(0), _end(0), _size(size), _buff(NULL)
	{
		_buff = new char[size];
	}
	Buffer::RotatingBuffer::RotatingBuffer(RotatingBuffer const &copy) : _buff(NULL)
	{
		*this = copy;
	}
	Buffer::RotatingBuffer::~RotatingBuffer(void) { if (_buff) delete[] _buff; }

	void	Buffer::RotatingBuffer::read(char *buff, ulint size) const
	{
		ulint	toRead = Operators::Min(_size, size);
		ulint	deb = 0;
		while (deb < toRead)
		{
			*buff = readChar(deb);
			++buff;
			++deb;
		}
	}
	void	Buffer::RotatingBuffer::get(char *buff, ulint size)
	{
		ulint	toRead = Operators::Min(_size, size);
		while (toRead)
		{
			*buff = getChar();
			++buff;
			--toRead;
		}
	}
	void	Buffer::RotatingBuffer::write(char const *buff, ulint size)
	{
		ulint	toWrite = Operators::Min(_size - this->size(), size);
		while (toWrite)
		{
			addChar(*buff);
			++buff;
			--toWrite;
		}
	}

	ulint	Buffer::RotatingBuffer::size(void) const
	{
		if (_end < _deb)
			return (_end - _deb + _size);
		return (_end - _deb);
	}
	ulint	Buffer::RotatingBuffer::sizeMax(void) const { return (_size); }

	void	Buffer::RotatingBuffer::addChar(char c)
	{
		_buff[_end] = c;
		_end = (_end + 1) % _size;
	}

	char	Buffer::RotatingBuffer::readChar(ulint it) const
	{
		return (_buff[(_deb + it) % _size]);
	}

	char	Buffer::RotatingBuffer::getChar(void)
	{
		char	c = _buff[_deb];
		_deb = (_deb + 1) % _size;
		return (c);
	}

	void	Buffer::RotatingBuffer::clear(void) { _deb = _end; }

	Buffer::RotatingBuffer	&Buffer::RotatingBuffer::operator=(Buffer::RotatingBuffer const &copy)
	{
		if (_buff)
			delete[] _buff;
		_size = copy._size;
		_buff = new char[_size];
		_deb = copy._deb;
		_end = copy._end;
		for (ulint it = _deb; it % _size != _end; ++it)
			_buff[it] = copy._buff[it];
		return (*this);
	}

	Buffer::Buffer(void) : _size(0) { _buffers.emplace_back(_bufferSize); }
	Buffer::Buffer(char *buff, ulint size) : _size(0)
	{
		_buffers.emplace_back(_bufferSize);
		write(buff, size);
	}
	Buffer::Buffer(Buffer const &copy) : _size(0) { *this = copy; }
	Buffer::~Buffer(void) { _buffers.clear(); }

	ulint	Buffer::read(char *buff, ulint size) const
	{
		ulint			wSize;
		auto			it = _buffers.begin();
		ulint			total = 0;

		while (size && it != _buffers.end())
		{
			wSize = Operators::Min(size, it->size());
			it->read(buff, wSize);
			size -= wSize;
			buff += wSize;
			total += wSize;
			++it;
		}
		return (total);
	}
	ulint	Buffer::get(char *buff, ulint size)
	{
		ulint			wSize;
		auto			it = _buffers.begin();
		ulint			total = 0;

		while (size && it != _buffers.end())
		{
			wSize = Operators::Min(size, it->size());
			it->get(buff, wSize);
			size -= wSize;
			buff += wSize;
			total += wSize;
			if (_buffers.size() == 1)
				++it;
			else
				it = _buffers.erase(it);
		}
		_size -= total;
		return (total);
	}
	void	Buffer::write(Buffer const &buff)
	{
		ulint			wSize;
		char			content[256];
		Buffer			tmp(buff);

		while (tmp.size())
		{
			wSize = tmp.get(content, sizeof(content));
			write(content, wSize);
		}
	}
	void	Buffer::write(char const *buff, ulint size)
	{
		ulint			wSize;
		RotatingBuffer	*current;
		_size += size;

		while (size)
		{
			current = &_buffers.back();
			wSize = Operators::Min(current->sizeMax() - current->size(), size);
			current->write(buff, wSize);
			size -= wSize;
			buff += wSize;
			if (size)
				_buffers.emplace_back(_bufferSize);
		}
	}

	ulint	Buffer::size(void) const { return (_size); }

	void	Buffer::clear(void)
	{
		for (auto it = _buffers.begin(); it != _buffers.end(); ++it)
			it->clear();
		_size = 0;
	}

	Buffer	&Buffer::operator=(Buffer const &copy)
	{
		clear();
		for (auto it = copy._buffers.begin(); it != copy._buffers.end(); ++it)
		{
			_buffers.emplace_back(_bufferSize);
			_buffers.back() = *it;
		}
		_size = copy._size;
		return (*this);
	}
}
