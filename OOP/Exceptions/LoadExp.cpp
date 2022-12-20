#include "LoadExp.h"

std::string  LoadExp::what() {
    return "Error restore state because of:\n" + message;
}