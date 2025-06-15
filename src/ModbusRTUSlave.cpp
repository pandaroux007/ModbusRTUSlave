#include "ModbusRTUSlave.h"

ModbusRTUSlave::ModbusRTUSlave(Stream& serial, int8_t dePin, int8_t rePin)
: _rtuComm(serial, dePin, rePin) {}

void ModbusRTUSlave::begin(uint8_t localUnitId, unsigned long baud, uint32_t config)
{
    if (localUnitId >= 1 && localUnitId <= 247) _localUnitId = localUnitId;
    _rtuComm.begin(baud, config);
}

bool ModbusRTUSlave::poll()
{
    ModbusADU adu;
    // check slave ID first
    uint8_t unitId = adu.getUnitId();
    if (unitId != _localUnitId && unitId != 0) return false;
    // then check the CRC
    ModbusRTUCommError error = _rtuComm.readAdu(adu);
    if (error) return false;
    // all right, let's read PDU
    processPdu(adu);
    if (unitId != 0) {
        delay(_responseDelay);
        _rtuComm.writeAdu(adu);
    }
    return true;
}