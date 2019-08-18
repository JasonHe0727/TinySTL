#include "Exception.hpp"

Exception::Exception() {
}

Exception::Exception(const String& message)
	:message{message} {
}
