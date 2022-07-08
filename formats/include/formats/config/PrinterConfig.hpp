#ifndef INCLUDE_formats_PRINERCONFIG_HPP
#define INCLUDE_formats_PRINERCONFIG_HPP

namespace formats
{
    namespace config
    {
        class PrinterConfig
        {
        private:
            int resolutionX;
            int resolutionY;
            float bedWidth;
            float bedLength;
            float bedHeight;

        public:
            PrinterConfig(int resolutionX, int resolutionY, float bedWidth, float bedLength, float bedHeight);
            int getResolutionX();
            int getResolutionY();
            float getBedWidth();
            float getBedLength();
            float getBedHeight();
        };

    }
}
#endif