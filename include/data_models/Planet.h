#ifndef PLANET_H
#define PLANET_H

#include <string>
#include <vector>

#include "../../include/utils/Vector2D.h"

class Planet {
  public:
    // Constructor
    Planet(const std::string& name, double distanceFrom, double gravity);
    ~Planet();

    // Getters
    std::string getName() const;
    double getSize() const;
    double getDistanceFrom() const;
    double getGravity() const;
    Vector2D getPosition() const;
    std::vector<std::string> getMoons() const;
    double getDayNightCycleLength() const;
    double getOrbitalPeriod() const;
    double getAxialTilt() const;
    std::string getSeasons();
    double getHabitabilityIndex() const;

    // Setters
    void setName(const std::string& name);
    void setSize(double size);
    void setDistanceFrom(double distanceFrom);
    void setGravity(double gravity);
    void setPosition(const Vector2D& position);
    void setMoons(const std::vector<std::string>& moons);
    void setDayNightCycleLength(double dayNightCycleLength);
    void setOrbitalPeriod(double orbitalPeriod);
    void setAxialTilt(double axialTilt);
    void setSeasons(const std::string& seasons);
    void setHabitabilityIndex(double habitabilityIndex);

    // Other methods
    bool isHabitable() const;
    bool isInHabitableZone() const;
    bool hasResourcesAvailable() const;
    bool hasBeenVisited() const;
    bool hasBeenDiscovered() const;
    std::string getAtmosphereComposition() const;
    double getTemperatureVariation() const;
    double getDistanceFromPlayer() const;

  private:
    Vector2D position;
    double size;
    std::string m_name;
    double m_distanceFrom;
    double m_gravity;
    std::vector<std::string> moons;
    double dayNightCycleLength;
    double orbitalPeriod;
    double axialTilt;
    std::string seasons;
    double habitabilityIndex;
    int resourceCount;
    bool visited;
    bool discovered;
    std::string atmosphereComposition;
    double temperatureVariation;
    double distanceFromPlayer;
};

#endif  // PLANET_H
