#pragma once

#include <list>

#include "basictypes.h"

namespace hpl
{
	class Buffer
	{
		class RotatingBuffer
		{
		public:
			RotatingBuffer(ulint size);
			RotatingBuffer(RotatingBuffer const &copy);
			~RotatingBuffer(void);

			void	read(char *buff, ulint size) const;
			void	get(char *buff, ulint size);
			void	write(char const *buff, ulint size);

			ulint	size(void) const;
			ulint	sizeMax(void) const;

			void	clear(void);

			RotatingBuffer	&operator=(RotatingBuffer const &copy);
		private:
			void	addChar(char c);
			char	readChar(ulint it) const;
			char	getChar(void);

			ulint	_deb;
			ulint	_end;
			ulint	_size;
			ulint	_lenght;

			char	*_buff;
		};

	public:
		Buffer(void);
		Buffer(char *buff, ulint size);
		Buffer(Buffer const &copy);
		~Buffer(void);

		ulint	read(char *buff, ulint size) const;
		ulint	get(char *buff, ulint size);
		void	write(char const *buff, ulint size);
		void	write(Buffer const &);

		ulint	size(void) const;

		Buffer	&operator=(Buffer const &copy);

		void	clear(void);

	private:
		typedef std::list<RotatingBuffer>	BufferTank;

		BufferTank	_buffers;

		ulint		_size;

		static const ulint	_bufferSize;
	};
}