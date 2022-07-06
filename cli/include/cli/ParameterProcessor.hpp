#ifndef CLI_PARAMETERPROCESSOR_HPP
#define CLI_PARAMETERPROCESSOR_HPP

#include <map>
#include <vector>
#include <string>

namespace cli
{

    namespace param_types
    {
        enum ArgType
        {
            INPUT_FILE = 'i',
            INPUT_POS_X = 'x',
            INPUT_POS_Y = 'y',
            INPUT_ROTATION = 'r',
            INPUT_HEIGHT = 'h',
            OUTPUT_FILE = 'o'
        };
    }

    class ParameterProcessor
    {
    public:
        ParameterProcessor(std::vector<std::string> &inputFileNames,
                           std::string &outputFileName,
                           std::map<int, float> &xOffsets,
                           std::map<int, float> &yOffsets,
                           std::map<int, float> &height,
                           std::map<int, float> &rotations);
        int process(const char *param, const char *value);

    private:
        bool file_set = false;
        bool x_set = false;
        bool y_set = false;
        bool hight_set = false;
        bool output_set = false;
        int index = 0;

        std::vector<std::string> &inputFileNames;
        std::string &outputFileName;
        std::map<int, float> &xOffsets;
        std::map<int, float> &yOffsets;
        std::map<int, float> &height;
        std::map<int, float> &rotations;

        void reset();
        bool validateRecord();

        int processInput(const char *value);
        int processX(const char *value);
        int processY(const char *value);
        int processHeight(const char *value);
        int processRotation(const char *value);
        int processOutput(const char *value);

        static bool validateNumber(const char *text, float &value);
    };
}

#endif
