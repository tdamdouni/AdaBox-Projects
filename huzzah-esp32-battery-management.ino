// https://forums.adafruit.com/viewtopic.php?f=57&t=125767

analogReadResolution(11);
analogSetAttenuation(ADC_6db);

float measuredvbat = analogRead(BATTERYPIN);
measuredvbat *= 2;    // we divided by 2, so multiply back
measuredvbat *= 1.1; // Multiply by 1.1V, our reference voltage
measuredvbat /= 1024; // voltage

return min(map(measuredvbat * 10, BATTERY_MIN * 10, BATTERY_MAX * 10, 0, 100), 100); // Calculate Battery Level (Percent)
