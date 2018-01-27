// AnalogReader.h

#ifndef _ANALOGREADER_h
#define _ANALOGREADER_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


class AnalogData {
public:
	double TempOut;
	double RHOut;
};

//BLE needs the data as uint8_t pointers to the values times 10
//encapsulate the logic in a simple class
class BLEData {
private:
	int16_t _Temperature;
	uint16_t _RelativeHumidity;
public:
	void FillData(double pTemp, double pRH) {
		//use string to avoid rounding errors (else e.g. 1.30 could become 1.29)
		String strTmp = String(pTemp*100.0);
		_Temperature = strTmp.toInt();
		strTmp = String(pRH*100.0);
		_RelativeHumidity = strTmp.toInt();
	}
	uint8_t* Temperature() { return((uint8_t*)&_Temperature); }
	uint8_t* RelativeHumidity() { return((uint8_t*)&_RelativeHumidity); }
};


class AnalogReader {
private:
	//static const uint8_t A_OUT_TEMP = A7;
	//static const uint8_t A_OUT_RH = A4;

	static const uint8_t A_OUT_TEMP = A3;
	static const uint8_t A_OUT_RH = A6;

	int aTempOut[4];
	int aRHOut[4];
	double _TempOut;
	double _RHOut;

	byte bCounter;
	/// analog values are a bit to small in low ranges
	/// use this simple math to add some value to it
	/// the smaller the value is - the more we have to add
	/// the values used come from a series of measurements simply using trail and error
	/// what we get is (simplified) for 500 we read 300 for 10000 we read 900 for 2000 we get 1990
	/// so we calculate the difference from max to the read value, multiply it with a factor and add this to the result
	double DoCalcVolts(int nVal) {
		double dBase = 4100;
		double dFactor = 0.00000004595;
		double dCalcBase = 0.000801;
		//calculate the offset to max
		double dTmp = dBase - nVal;
		//multiply with the factor to compensate the offset
		dTmp *= dFactor;
		//add the base (not used in offset calculation)
		dTmp += dCalcBase;
		return(nVal*dTmp);
	}
	void CalcOutsideData() {
		double dTempOutVolts = DoCalcVolts((aTempOut[0] + aTempOut[1] + aTempOut[2] + aTempOut[3]) / 4);
		double dRHOutVolts = DoCalcVolts((aRHOut[0] + aRHOut[1] + aRHOut[2] + aRHOut[3]) / 4);
		//offset calculation can lead to slightly over- / underflow of values 
		//use _min / _max to stay in ranges
		//outside we have 0.0 to 3.0 -- this means NO offset and a range of 3
		//temperature is -40 to 60 - a range of 100
		int nTempOut = (int)(dTempOutVolts * 1000 / 3);
		nTempOut -= 400;	//0==-400 1000==60
						//calculate with one digit rounded
		_TempOut = _min(60, _max(-40, (nTempOut + 0.5) / 10.0));
		//humidity is 0 to 100%
		_RHOut = _min(100, _max(0, (int)(dRHOutVolts * 100 / 3)));	
	}

public:
	AnalogReader() {
		aTempOut[0] = analogRead(A_OUT_TEMP);
		aRHOut[0] = analogRead(A_OUT_RH);
		//initialize the arrays
		for(int nX = 1; nX < 4; nX++) {
			aTempOut[nX] = aTempOut[0];
			aRHOut[nX] = aRHOut[0];
		}
	}
	//read all analog values to a 4 values buffer
	void ReadAnalog() {
		int nIDX = bCounter++ % 4;	//0 to 3
		aTempOut[nIDX] = analogRead(A_OUT_TEMP);
		aRHOut[nIDX] = analogRead(A_OUT_RH);
	}
	void GetData(AnalogData *pData) {
		CalcOutsideData();
		pData->TempOut = _TempOut;
		pData->RHOut = _RHOut;
	}
	void GetBLEData(BLEData *pData) {
		CalcOutsideData();
		pData->FillData(_TempOut, _RHOut);
	}
};


#endif

