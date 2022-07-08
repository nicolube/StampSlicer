#include <core/LayerGanerator.hpp>
#include <sstream>

using namespace core;
using namespace formats::config;
using formats::Image;
using formats::Image;

LayerGanerator::LayerGanerator(PrinterConfig &printerConfig, ResinConfig &resinConfig, float stempHight)
    : printerConfig(printerConfig),
      resinConfig(resinConfig),
      stempHight(stempHight),
      px_mmX(printerConfig.getResolutionX() / printerConfig.getBedWidth()),
      px_mmY(printerConfig.getResolutionY() / printerConfig.getBedLength()),
      channelWidth(3),
      padding(4.5),
      centerLayer(2 / resinConfig.getLayerHeight()),
      channelHeight(3 / resinConfig.getLayerHeight()),
      baseHeight(4 / resinConfig.getLayerHeight())
{
    layerCount = (4 + stempHight) / resinConfig.getLayerHeight();
    int padding = 15;
    imageData = (Image *)malloc(sizeof(Image) * layerCount);
    for (size_t i = 0; i < layerCount; i++)
    {
        imageData[i] = Image(printerConfig.getResolutionX(), printerConfig.getResolutionY());
    }
}

LayerGanerator::~LayerGanerator()
{
    free(imageData);
}

void LayerGanerator::add(float x, float y, Image &image)
{
    x *= px_mmX;
    y *= px_mmY;
    generateBaseLayers((int)x, (int)y, image.getWidth(), image.getHeight());
    generateImageLayers((int)x, (int)y, image);
}

void LayerGanerator::stripeImage(Image &image, float inWidth, float inPadding)
{
    int paddingX = inPadding * px_mmX;
    int paddingY = inPadding * px_mmY;
    int widthX = inWidth * px_mmX;
    int widthY = inWidth * px_mmY;
    int numX = image.getWidth() / paddingX - 1;
    int numY = image.getHeight() / paddingY - 1;
    int startX = (image.getWidth() - (numX * paddingX)) / 2;
    int startY = (image.getHeight() - (numY * paddingY)) / 2;
    for (int x = 0; x <= numX; x++)
    {
        int posX = startX + paddingX * x - (widthX / 2);
        image.fill(posX, 0, widthX, image.getHeight(), 0);
    }
    for (int y = 0; y <= numY; y++)
    {
        int posY = startY + paddingY * y - (widthY / 2);
        image.fill(0, posY, image.getWidth(), widthY , 0);
    }
}

void LayerGanerator::generateBaseLayers(int x, int y, int width, int height)
{
    Image stripedImage(width, height, 255);
    stripeImage(stripedImage, channelWidth, padding);
    imageData[centerLayer].copy(x, y, &stripedImage);

    for (int layer = 1; layer < channelHeight / 2; layer++)
    {
        // float stripeWidth = channelWidth; // Regtangle
        // float stripeWidth = channelWidth - ((float)channelWidth * layer / (channelHeight / 2-1)); // Regtangle 45 deg
        float stripeWidth = channelWidth * cos(asin((float)layer / (channelHeight / 2))); // circle
        stripedImage.fill(0, 0, width, height, 255);
        stripeImage(stripedImage, stripeWidth, padding);
        imageData[centerLayer + layer].copy(x, y, &stripedImage);
        imageData[centerLayer - layer].copy(x, y, &stripedImage);
    }

    for (int layer = 0; layer < baseHeight; layer++)
    {
        int channelStart = centerLayer - channelHeight / 2;

        if (layer > channelStart && layer < channelStart + channelHeight)
            continue;

        imageData[layer].fill(x, y, width, height, 255);
    }
}

void LayerGanerator::generateImageLayers(int x, int y, Image &src)
{
    const float deg_15 = 15 * M_PI / 188;

    for (int layerOffset = 0; layerOffset < layerCount - baseHeight; layerOffset++)
    {
        int layer = layerCount - layerOffset - 1;
        int paddingX = (tan(deg_15) * layerOffset * resinConfig.getLayerHeight() * px_mmX);
        int paddingY = (tan(deg_15) * layerOffset * resinConfig.getLayerHeight() * px_mmY);
        Image image(src);
        if (paddingX != 0 || paddingY != 0 )
            image.padding(paddingX);
        imageData[layer].copy(x, y, &image);   
    }
}


const unsigned char *LayerGanerator::package(formats::Packager &packager, size_t &size) {
    return packager.package(printerConfig, resinConfig, imageData, layerCount, &size);
}

void LayerGanerator::save(formats::Packager &packager, const char *name) {
    size_t size;
    std::cout << "Packange files..." << std::endl;
    const unsigned char *data =  packager.package(printerConfig, resinConfig, imageData, layerCount, &size);
    std::stringstream ss;
    ss << name << packager.getFileExtension();
    std::string fileName = ss.str();
    std::cout << "Save file to: " << fileName << std::endl;
    std::ofstream outFile(fileName);
    outFile.write((char *)data, size);
    outFile.flush();
    outFile.close();

}