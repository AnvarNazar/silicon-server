//
// Created by anvar on 27/12/19.
//

#ifndef SILICON_SILICONEXCEPTION_H
#define SILICON_SILICONEXCEPTION_H

#include <exception>
#include <stdint-gcc.h>

namespace si {
    class SiliconException: std::exception {
    private:
        const char *_message;
        const int _code;

    public:
        SiliconException(const char *message, int code);

        const char *what() const noexcept override;

        int code() const;
    };
}


#endif //SILICON_SILICONEXCEPTION_H
