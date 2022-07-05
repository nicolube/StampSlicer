#include <formats/Image.hpp>
#include <formats/config/ResinConfig.hpp>
#include <formats/config/PrinterConfig.hpp>

namespace core
{
    class LayerGanerator
    {
    private:
        formats::config::PrinterConfig printerConfig;
        formats::config::ResinConfig resinConfig;
        float stempHight;
        int layerCount;
        formats::Image *imageData;

        const float px_mm;
        const int channelWidth;
        const int padding;
        const int centerLayer;
        const int channelHeight;
        const int baseHeight;

        void generateBaseLayers(int x, int y, int width, int height);
        void generateImageLayers(int x, int y, formats::Image &image);

    public:
        LayerGanerator(formats::config::PrinterConfig &printerConfig, formats::config::ResinConfig &resinConfig, float stempHight);
        ~LayerGanerator();
        void add(int x, int y, formats::Image &image);
    };
}