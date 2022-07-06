#include <core/LayerGanerator.hpp>
#include <cli/ParameterProcessor.hpp>
#include <cli/ErrorMessages.hpp>

#include <vector>
#include <map>

using namespace cli;

int main(int argc, const char *argv[])
{
    const char *command = argv[0];

    bool expectParameter = true;
    std::vector<std::string> inputFileNames;
    std::string outputFileName;
    std::map<int, float> xOffsets;
    std::map<int, float> yOffsets;
    std::map<int, float> height;
    std::map<int, float> rotations;
    ParameterProcessor paramProcessor{inputFileNames, outputFileName, xOffsets, yOffsets, height, rotations};

    if (argc % 2 == 0)
    {
        printError(errors::PARAM_MISSING_VALUE, argv[argc - 1]);
        return errors::PARAM_MISSING_VALUE;
    }
    for (int i = 1; i < argc; i += 2)
    {
        int error = paramProcessor.process(argv[i], argv[i + 1]);
        if (error)
            return error;
    }

    return 0;
}
