#include <core/LayerGanerator.hpp>
#include <core/SvgConverter.hpp>
#include <formats/cbddlp/FormatCbddlp.hpp>
#include <cli/ParameterProcessor.hpp>
#include <cli/ErrorMessages.hpp>
#include <filesystem>
#include <vector>
#include <map>

using namespace cli;
using namespace formats;
namespace fs = std::filesystem;

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

    if (outputFileName.size() == 0)
    {
        std::stringstream ss;
        for (size_t i = 0; i < inputFileNames.size(); i++)
        {
            std::string str = fs::path(inputFileNames[i]).filename().u8string();
            ss << str.substr(0, str.size() - 4) << '_';
        }
        outputFileName = ss.str();
        outputFileName.pop_back();
    }

    if (inputFileNames.size() == 0) return 0;

    config::PrinterConfig printerConfig{1440, 2560, 68.04, 120.96, 150};
    config::ResinConfig resinConfig{10 , 10, 15, 50, 150, 1.0, 1.0, 0, 90, 0, 16, 5, 0.05};

    formats::cbddlp::FormatCbddlp packager{};
    core::LayerGanerator layerGenerator{printerConfig, resinConfig, 2};

    for (size_t i = 0; i < inputFileNames.size(); i++)
    {
        std::cout << "Render image: " << inputFileNames[i] << std::endl;
        core::SvgConverter svgConverter{printerConfig, inputFileNames[i]};
        svgConverter.setHight(height[i]);
        Image baseImage = svgConverter.toImage();
        layerGenerator.add(xOffsets[i], yOffsets[i], baseImage);
    }
    layerGenerator.save(packager, outputFileName.c_str());
    return 0;
}
