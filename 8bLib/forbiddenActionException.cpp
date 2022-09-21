#include "forbiddenActionException.h"

EmulatorLib::ForbiddenActionException::ForbiddenActionException(char const* const msg) : std::exception(msg)
{

}
