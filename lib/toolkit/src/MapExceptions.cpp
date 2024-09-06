#include "MapExceptions.hpp"

namespace vertex::exceptions
{
	MapNotFoundException::MapNotFoundException(const std::string& what_arg) : std::runtime_error(what_arg)
	{
	}

	MapParseException::MapParseException(const std::string& what_arg)
		: std::runtime_error(what_arg)
	{
	}

	UnsupportedMapTypeException::UnsupportedMapTypeException(const std::string& what_arg)
		: std::runtime_error(what_arg)
	{
	}
}
