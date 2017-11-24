#ifndef _DUPLICATE_EXCEP
#define _DUPLICATE_EXCEP

#include <stdexcept>
#include <string>

using namespace std;

class DuplicateException : public logic_error
{
public:
	DuplicateException(const string& message = "") : logic_error("Duplicate Item" + message) {}
}; // end NotFoundExcep

#endif
