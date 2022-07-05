#include <formats/config/ResinConfig.hpp>

using namespace formats::config;

ResinConfig::ResinConfig(
    float bottomLiftDistance,
    float bottomLiftSpeed,
    float liftDistance,
    float liftSpeed,
    float retractSpeed,
    float resinMass,
    float resinCost,
    float bottomLightOffTime,
    float bottomLightOnTime,
    float lightOffTime,
    float lightOnTime,
    float bottomLayerCount,
    float layerHeight)
    : bottomLiftDistance(bottomLiftDistance),
      bottomLiftSpeed(bottomLiftSpeed),
      liftDistance(liftDistance),
      liftSpeed(liftSpeed),
      retractSpeed(retractSpeed),
      resinMass(resinMass),
      resinCost(resinCost),
      bottomLightOffTime(bottomLightOffTime),
      bottomLightOnTime(bottomLightOnTime),
      lightOffTime(lightOffTime),
      lightOnTime(lightOnTime),
      bottomLayerCount(bottomLayerCount),
      layerHeight(layerHeight)
{
}

float ResinConfig::getBottomLiftDistance()
{
    return bottomLiftDistance;
}

float ResinConfig::getBottomLiftSpeed()
{
    return bottomLiftSpeed;
}

float ResinConfig::getLiftDistance()
{
    return liftDistance;
}

float ResinConfig::getLiftSpeed()
{
    return liftSpeed;
}

float ResinConfig::getRetractSpeed()
{
    return retractSpeed;
}

float ResinConfig::getResinMass()
{
    return resinMass;
}

float ResinConfig::getResinCost()
{
    return resinCost;
}

float ResinConfig::getBottomLightOffTime()
{
    return bottomLightOffTime;
}

float ResinConfig::getBottomLightOnTime()
{
    return bottomLightOnTime;
}

float ResinConfig::getLightOffTime()
{
    return lightOffTime;
}

float ResinConfig::getLightOnTime()
{
    return lightOnTime;
}

float ResinConfig::getBottomLayerCount()
{
    return bottomLayerCount;
}

float ResinConfig::getLayerHeight()
{
    return layerHeight;
}
