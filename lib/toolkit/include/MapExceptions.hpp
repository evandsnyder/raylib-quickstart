#ifndef VERTEX_MAP_EXCEPTIONS_HPP
#define VERTEX_MAP_EXCEPTIONS_HPP

#include <stdexcept>

namespace vertex::exceptions {
	class MapNotFoundException : public std::runtime_error {
	public:
		MapNotFoundException(const std::string& what_arg);
	};

	class MapParseException : public std::runtime_error
	{
	public:
		MapParseException(const std::string& what_arg);
	};

	class UnsupportedMapTypeException : public std::runtime_error
	{
	public:
		UnsupportedMapTypeException(const std::string& what_arg);
	};
}

#endif
