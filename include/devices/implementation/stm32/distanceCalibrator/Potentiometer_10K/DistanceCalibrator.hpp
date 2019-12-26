#pragma once
#include <Arduino.h>

#include "../../../../abstract/DistanceCalibrator.hpp"

#include "Configuration.hpp"

namespace Devices::DistanceCalibrator::Implementation::Stm32::Potentiometer_10K {
    class Potentiometer_10K_DistanceCalibrator: public Abstract::IDistanceCalibrator {
        private:
            const Potentiometer_10K_Configuration &config;
        public:
            Potentiometer_10K_DistanceCalibrator(const Potentiometer_10K_Configuration &_configuration):
                config(_configuration) {
                    pinMode(config.potentiometerDataInputPin, INPUT_ANALOG);
                }

            const DistanceCalibrationValue& getValue() override {
                const unsigned short value = analogRead(config.potentiometerDataInputPin);
                const unsigned short result = map(
                    value,
                    0, 4096,
                    0, config.maximumAdditionValueOfPotentiometer
                );
                
                return {
                    .value = result,
                    .error = 0
                };
            }
    };
}