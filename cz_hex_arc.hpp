#ifndef CZ_HEX_ARC_HPP
#define CZ_HEX_ARC_HPP

#include <cmath>

namespace CZ {

/**
 * @brief CZ-Engine V9.0: Hex-Arc Hybrid (Behavioral Math Core)
 * Handles non-linear dynamic state transitions for ultra-high load stability.
 */
class HexArcShield {
private:
    double density;
    int hexNodes;
    int arcPoints;

public:
    HexArcShield(double initialDensity = 3.0, int initialNodes = 6, int initialArcPoints = 3)
        : density(initialDensity), hexNodes(initialNodes), arcPoints(initialArcPoints) {}

    /**
     * @brief Calculates hybrid integrity metric under exponential dynamic loads.
     * @param load Input stress magnitude (dynamic state factor).
     * @return Computed integrity score.
     */
    double calculateHybridIntegrity(double load) {
        if (load <= 0.0) return 1.0;

        double mag = std::log10(load);
        
        // Phase 1: Hexagonal Stress Distribution
        double hexStrength = (mag * std::pow(density, 2)) * std::sqrt(6.0);
        double hexPressure = (load / static_cast<double>(hexNodes)) / 1.0e15;
        double stage1Integrity = hexStrength / (hexPressure + 1.0);

        // Phase 2: Dynamic State Confinement
        double arcSqueeze = std::pow(mag, 1.8) * std::sqrt(3.0);
        double stage2Confinement = (stage1Integrity * arcSqueeze) / 
                                   ((load / static_cast<double>(arcPoints)) / 1.0e18 + 1.0);

        return stage2Confinement;
    }

    /**
     * @brief Dynamically rescales geometry nodes under critical pressure thresholds.
     */
    void evolveGeometry() {
        hexNodes += 6; 
        density += 0.75;
    }

    // Accessors for benchmarking visibility
    int getHexNodes() const { return hexNodes; }
    double getDensity() const { return density; }
};

} // namespace CZ

#endif // CZ_HEX_ARC_HPP
