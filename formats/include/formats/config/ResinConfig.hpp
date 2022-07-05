#ifndef INCLUDE_FORMATS_RESINCONFIG_HPP
#define INCLUDE_FORMATS_RESINCONFIG_HPP

namespace formats::config
{

    class ResinConfig
    {
    private:
        float bottomLiftDistance;
        float bottomLiftSpeed;
        float liftDistance;
        float liftSpeed;
        float retractSpeed;
        float resinMass;
        float resinCost;
        float bottomLightOffTime;
        float lightOffTime;
        float bottomLayerCount;
        float layerHeight;

    public:
        ResinConfig(
            float bottomLiftDistance,
            float bottomLiftSpeed,
            float liftDistance,
            float liftSpeed,
            float retractSpeed,
            float resinMass,
            float resinCost,
            float bottomLightOffTime,
            float lightOffTime,
            float bottomLayerCount,
            float layerHeight);
        float getBottomLiftDistance();
        float getBottomLiftSpeed();
        float getLiftDistance();
        float getLiftSpeed();
        float getRetractSpeed();
        float getResinMass();
        float getResinCost();
        float getBottomLightOffTime();
        float getLightOffTime();
        float getBottomLayerCount();
        float getLayerHeight();
    };

}

#endif