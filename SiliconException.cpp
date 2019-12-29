//
// Created by anvar on 27/12/19.
//

#include "SiliconException.h"

sc::SiliconException::SiliconException(const char *message, const int code) : _message(message), _code(code) {

}

const char *sc::SiliconException::what() const noexcept {
    return _message;
}

int sc::SiliconException::code() const {
    return _code;
}
