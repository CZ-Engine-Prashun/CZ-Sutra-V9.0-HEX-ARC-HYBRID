#include <Arduino.h>
#include "cz_hex_arc.hpp"

CZ::HexArcShield core;
double stressVal = 1e12; // Starting Tera-load threshold

void setup() {
    Serial.begin(115200);
    delay(1000);
    Serial.println("=================================================");
    Serial.println("   CZ-ENGINE V9.0: HEX-ARC HYBRID EVALUATION     ");
    Serial.println("=================================================");
}

void loop() {
    if (stressVal <= 1e24) { 
        unsigned long startMicros = micros();
        double integrity = core.calculateHybridIntegrity(stressVal);
        unsigned long elapsedMicros = micros() - startMicros;

        Serial.print("\n[INPUT LOAD]: "); 
        Serial.println(stressVal, 0);
        
        // Dynamic re-alignment trigger
        if (integrity < 5.0) {
            Serial.println(">>> [STRESS THRESHOLD DETECTED] Triggering Hex-Arc Re-alignment...");
            core.evolveGeometry();
            integrity = core.calculateHybridIntegrity(stressVal);
        }

        Serial.print("INTEGRITY METRIC : "); Serial.println(integrity, 6);
        Serial.print("LATENCY (micros) : "); Serial.println(elapsedMicros);
        Serial.print("STATUS           : ");
        if (integrity > 50.0) {
            Serial.println("OPTIMAL STABILITY");
        } else {
            Serial.println("BALANCED");
        }

        stressVal *= 1000.0; // Dynamic Load Scaling
        delay(1500);
    } else {
        Serial.println("\n-------------------------------------------------");
        Serial.println("HEX-ARC STABILITY MATRIX EVALUATION COMPLETE.");
        Serial.println("-------------------------------------------------");
        while(1); 
    }
}
