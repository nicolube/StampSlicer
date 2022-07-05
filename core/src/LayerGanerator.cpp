#include <core/LayerGanerator.hpp>
#include <sstream>

using namespace core;
using namespace formats::config;
using formats::Image;

LayerGanerator::LayerGanerator(PrinterConfig &printerConfig, ResinConfig &resinConfig, float stempHight)
    : printerConfig(printerConfig),
      resinConfig(resinConfig),
      stempHight(stempHight),
      px_mm(printerConfig.getResolutionX() / printerConfig.getBedWidth()),
      channelWidth(3 * px_mm),
      padding(4 * px_mm),
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

void LayerGanerator::add(int x, int y, Image &image)
{
    generateBaseLayers(x, y, image.getWidth(), image.getHeight());
    generateImageLayers(x, y, image);
}

void stripeImage(Image &image, int width, int padding)
{
    int numX = image.getWidth() / padding - 1;
    int numY = image.getHeight() / padding - 1;
    int startX = (image.getWidth() - (numX * padding)) / 2;
    int startY = (image.getHeight() - (numY * padding)) / 2;

    for (int x = 0; x <= numX; x++)
    {
        int posX = startX + padding * x - (width / 2);
        image.fill(posX, 0, width, image.getHeight(), 0);
    }
    for (int y = 0; y <= numX; y++)
    {
        int posY = startY + padding * y - (width / 2);
        image.fill(0, posY, image.getWidth(), width, 0);
    }
}

void LayerGanerator::generateBaseLayers(int x, int y, int width, int height)
{
    Image stripedImage(width, height, 255);
    stripeImage(stripedImage, channelWidth, padding);
    imageData[centerLayer].copy(x, y, &stripedImage);

    for (int layer = 1; layer < channelHeight / 2; layer++)
    {
        // int stripeWidth = channelWidth; // Regtangle
        // int stripeWidth = channelWidth - ((float)channelWidth * layer / (channelHeight / 2-1)); // Regtangle 45 deg
        int stripeWidth = channelWidth * cos(asin((float)layer / (channelHeight / 2))); // circle
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
        int padding = (tan(deg_15) * layerOffset * resinConfig.getLayerHeight() * px_mm);
        Image image(src);
        if (padding != 0)
            image.padding(padding);
        imageData[layer].copy(x, y, &image);   
    }
}