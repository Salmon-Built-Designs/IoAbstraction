/*
 * Copyright (c) 2018 https://www.thecoderscorner.com (Nutricherry LTD).
 * This product is licensed under an Apache license, see the LICENSE file in the top-level directory.
 */

#ifndef _IOABSTRACTION_IOABSTRACTIONWIRE_H_
#define _IOABSTRACTION_IOABSTRACTIONWIRE_H_

#include <IoAbstraction.h>
#include <Wire.h>

/**
 *  An implementation of BasicIoFacilties that supports the PCF8574 i2c IO chip.
 */
class PCF8574IoAbstraction : public BasicIoAbstraction {
private:
	uint8_t address;
	uint8_t lastRead;
	uint8_t toWrite;
	bool needsWrite;
	uint8_t interruptPin;
public:
	/** Construct a 8574 expander on i2c address and with interrupts connected to a given pin (0xff no interrupts) */
	PCF8574IoAbstraction(uint8_t addr, uint8_t interruptPin);
	virtual ~PCF8574IoAbstraction() { }
	/** 
	 * sets the pin direction on the device, notice that on this device input is achieved by setting the port to high 
	 * so it is always set as INPUT_PULLUP, even if INPUT is chosen 
	 */
	virtual void pinDirection(uint8_t pin, uint8_t mode);
	/** 
	 * writes a new value to the device after a runLoop is called. 
	 */
	virtual void writeValue(uint8_t pin, uint8_t value);
	/**
	 * reads a value from the last cached state  - updated each runLoop 
	 */
	virtual uint8_t readValue(uint8_t pin);
	/** 
	 * attaches an interrupt handler for this device. Notice for this device, all pin changes will be notified
	 * on any pin of the port, it is not configurable 
	 */
	virtual void attachInterrupt(uint8_t pin, RawIntHandler intHandler, uint8_t mode);
	/** 
	 * updates settings on the board after changes 
	 */
	virtual void runLoop();
private:
	void writeData();
	uint8_t readData();
};

/*
 * performs digital read and write function using an 8574 IO expander chip
 */
IoAbstractionRef ioFrom8754(uint8_t addr, uint8_t interruptPin = 0xff);

#endif /* _IOABSTRACTION_IOABSTRACTIONWIRE_H_ */