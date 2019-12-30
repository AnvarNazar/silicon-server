//
// Created by anvar on 27/12/19.
//

#include "SiliconException.h"

si::SiliconException::SiliconException(const char *message, const int code) : _message(message), _code(code) {

}

const char *si::SiliconException::what() const noexcept {
    return _message;
}

int si::SiliconException::code() const {
    return _code;
}
