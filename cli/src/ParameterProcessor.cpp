#include <cli/ParameterProcessor.hpp>
#include <cli/ErrorMessages.hpp>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace cli;
using namespace cli::param_types;

ParameterProcessor::ParameterProcessor(std::vector<std::string> &inputFileNames,
                                       std::string &outputFileName,
                                       std::map<int, float> &xOffsets,
                                       std::map<int, float> &yOffsets,
                                       std::map<int, float> &height,
                                       std::map<int, float> &rotations)
    : inputFileNames(inputFileNames),
      outputFileName(outputFileName),
      xOffsets(xOffsets),
      yOffsets(yOffsets),
      height(height),
      rotations(rotations) {}

int ParameterProcessor::process(const char *param, const char *value)
{

    size_t paramLen = std::strlen(param);
    size_t valueLen = std::strlen(value);
    if (paramLen != 2 || param[0] != '-')
    {
        printError(errors::INVALID_PARAM, param);
        return errors::INVALID_PARAM;
    }

    switch (param[1])
    {
    case INPUT_FILE:
        processInput(value);
        break;
    case INPUT_POS_X:
        processX(value);
        break;
    case INPUT_POS_Y:
        processY(value);
        break;
    case INPUT_ROTATION:
        processRotation(value);
        break;
    case INPUT_HEIGHT:
        processHeight(value);
        break;
    case OUTPUT_FILE:
        processOutput(value);
        break;
    default:
        printError(errors::INVALID_PARAM, param);
        return errors::INVALID_PARAM;
    }
    return 0;
}

void ParameterProcessor::reset()
{

    file_set = false;
    x_set = false;
    y_set = false;
    hight_set = false;
}

bool ParameterProcessor::validateRecord()
{
    bool state = (x_set && y_set && hight_set);
    if (state) {
        if (rotations.count(index) == 0) {
            rotations[index] = 0;
        }
    }
    return state;
}

int ParameterProcessor::processInput(const char *value)
{
    if (!validateRecord())
    {
        std::stringstream ss;
        if (!x_set)
            ss << "x ";
        if (!y_set)
            ss << "y ";
        if (!hight_set)
            ss << "hight ";
        printError(errors::INCOMPLETE_IMAGE_DATA, ss.str().c_str());
        return errors::INCOMPLETE_IMAGE_DATA;
    }
    std::ifstream file;
    file.open(value);
    if (!file.good())
    {
        printError(errors::FILE_NOT_FOUND, value);
        return errors::FILE_NOT_FOUND;
    }
    file.close();
    inputFileNames.push_back(std::string{value});

    reset();
    index++;
    return 0;
}

int ParameterProcessor::processX(const char *value)
{
    if (!validateNumber(value, xOffsets[index]))
    {
        printError(errors::NOT_A_NUMBER, value);
        return errors::NOT_A_NUMBER;
    }
    x_set = true;
    return 0;
}

int ParameterProcessor::processY(const char *value)
{
    if (!validateNumber(value, yOffsets[index]))
    {
        printError(errors::NOT_A_NUMBER, value);
        return errors::NOT_A_NUMBER;
    }
    y_set = true;
    return 0;
}

int ParameterProcessor::processHeight(const char *value)
{
    if (!validateNumber(value, height[index]))
    {
        printError(errors::NOT_A_NUMBER, value);
        return errors::NOT_A_NUMBER;
    }
    hight_set = true;
    return 0;
}

int ParameterProcessor::processRotation(const char *value)
{
    if (!validateNumber(value, rotations[index]))
    {
        printError(errors::NOT_A_NUMBER, value);
        return errors::NOT_A_NUMBER;
    }
    return 0;
}

int ParameterProcessor::processOutput(const char *value)
{
    std::ifstream file;
    file.open(value);
    if (!file.good())
    {
        printError(errors::FILE_NOT_FOUND, value);
        return errors::FILE_NOT_FOUND;
    }
    file.close();
    outputFileName = std::string{value};

    return 0;
}

bool ParameterProcessor::validateNumber(const char *text, float &value)
{
    size_t i = 0;
    while (text[i] != 0)
    {
        if ((text[i] < '0' || text[i] > '9') && text[i] != '.')
            return false;
        i++;
    }
    value = atof(text);
    return true;
}
