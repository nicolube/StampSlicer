#ifndef CLI_ERRORMESSAGES_HPP
#define CLI_ERRORMESSAGES_HPP
#include <iostream>

namespace cli::errors
{
    enum ErrorType
    {
        INVALID_PARAM,
        PARAM_EXPECTED,
        FILE_NOT_FOUND,
        DATA_EXPECTED,
        INVALID_PATH,
        NOT_A_NUMBER,
        INVALID_NUMBER_ARGS_ERROR,
        INCOMPLETE_IMAGE_DATA,
        PARAM_MISSING_VALUE
    };

#define check_err_args(cLen)                   \
    if (cLen != length)                        \
    {                                          \
        printError(INVALID_NUMBER_ARGS_ERROR); \
        return;                                \
    }

    template <typename... Args>
    void printError(ErrorType type, Args... inArgs)
    {
        const char *args[]{inArgs...};
        size_t length = sizeof...(inArgs);
        switch (type)
        {
        case INVALID_NUMBER_ARGS_ERROR:
        {
            std::cout << "[ERROR]: Invalid number of aruments in error message.";
        }
        break;
            std::cout << "[ERROR]: ";
        case INVALID_PARAM:
        {
            check_err_args(1);
            std::cout << "Invalid parameter: " << args[0];
        }
        break;
        case FILE_NOT_FOUND: {
            check_err_args(1);
            std::cout << "File not found: " << args[0];
        }
        break;
        case INCOMPLETE_IMAGE_DATA:
        {
            check_err_args(1);
            std::cout << "This images missing arguments: " << args[0];
        }
        break;
        case NOT_A_NUMBER:
        {
            check_err_args(1);
            std::cout << "Not a number: " << args[0];
        }
        break;
        case PARAM_MISSING_VALUE:
        {
            check_err_args(1);
            std::cout << "The param \"" << args[0] << "\"missing a value.";
        }
        break;
        default:
            std::cout << "Error message not implemented!";
            break;
        }

        std::cout << std::endl;
    }

}

#endif
