#ifndef ModbusRTUSlave_h
#define ModbusRTUSlave_h

#include "Arduino.h"
#include "ModbusADU.h"
#include "ModbusSlaveLogic.h"
#include "ModbusRTUComm.h"

class ModbusRTUSlave : public ModbusSlaveLogic
{
    public:
        /// @brief creates ModbusRTUSlave instance
        /// @param serial reference to the serial object (all class based on Stream can be given)
        /// @param dePin
        /// @param rePin
        ModbusRTUSlave(Stream& serial, int8_t dePin = -1, int8_t rePin = -1);

        /// @brief initializes modbus communication
        /// @param localUnitId slave id
        /// @param baud UART communication speed
        /// @param config serial mode (default to `SERIAL_8N1`)
        void begin(uint8_t localUnitId, unsigned long baud, uint32_t config = SERIAL_8N1);

        /// @brief updates modbus communication
        /// @returns true if the PDU is read, otherwise false
        bool poll();

        /// @brief set the delay before the response
        /// @param responseDelay time in milliseconds
        /// @warning at 0 by default, blocking if greater (delay function)
        inline void setResponseDelay(unsigned long responseDelay) { _responseDelay = responseDelay; };

    private:
        ModbusRTUComm _rtuComm;
        uint8_t _localUnitId = 0;
        unsigned long _responseDelay = 0;
        using ModbusSlaveLogic::processPdu;
};

#endif