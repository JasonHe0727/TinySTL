#include "Exception.hpp"

Exception::Exception() {
}

Exception::Exception(String message)
	:message{message} {
}
