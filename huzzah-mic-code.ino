// https://forums.adafruit.com/viewtopic.php?f=57&t=125480
/////////////////////mic////////////////////
#define MIC_PIN   13  // Microphone is attached to Trinket GPIO #2/Gemma D2 (A1)
#define DC_OFFSET  0  // DC offset in mic signal - if unusure, leave 0
#define NOISE     50  // Noise/hum/interference in mic signal
#define SAMPLES   60  // Length of buffer for dynamic level adjustment
#define TOP       (LongestCount +1) // Allow dot to go slightly off scale

//////////////for mic////////////////
byte
  peak      = 0,      // Used for falling dot
  dotCount  = 0,      // Frame counter for delaying dot-falling speed
  volCount  = 0;      // Frame counter for storing past volume data

int
  vol[SAMPLES],       // Collection of prior volume samples
  lvl       = 5,     // Current "dampened" audio level
  minLvlAvg = 0,      // For dynamic adjustment of graph low & high
  maxLvlAvg = 512;
////////////////////////////////////////////

////////////////////////////////////////////mic vol_m//////////////////////////////////////
char * vol_m() {
  int ii = 0;
  while(strcmp(feed_read, "18") == 0) {
    uint8_t  i;
    uint16_t minLvl, maxLvl;
    int      n, height;

    n   = analogRead(MIC_PIN);                 // Raw reading from mic
    n   = abs(n - 512 - DC_OFFSET);            // Center on zero
    n   = (n <= NOISE) ? 0 : (n - NOISE);      // Remove noise/hum
    lvl = ((lvl * 7) + n) >> 3;    // "Dampened" reading (else looks twitchy)

    // Calculate bar height based on dynamic min/max levels (fixed point):
    height = TOP * (lvl - minLvlAvg) / (long)(maxLvlAvg - minLvlAvg);

    if(height < 0L)       height = 0;      // Clip output
    else if(height > TOP) height = TOP;
    if(height > peak)     peak   = height; // Keep 'peak' dot at top

    // Color pixels based on rainbow gradient
    for(i=0; i<LongestCount; i++) {
      if(i >= height) {
         stripM.setPixelColor(i,   0,   0, 0, 0); // RGBW
         stripR.setPixelColor(i,   0,   0, 0, 0); // RGBW
         stripL.setPixelColor(i,   0,   0, 0, 0); // RGBW
      } else {
         stripM.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
         stripR.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
         stripL.setPixelColor(i,Wheel(map(i,0,LongestCount -1,30,150)));
           }
         //stripM.setPixelColor(i,Wheel(map(i,0,stripM.numPixels()-1,30,150)));//worked with rgb
      }

     stripM.show(); // Update strip
     stripR.show(); // Update strip
     stripL.show(); // Update strip

    vol[volCount] = n;                      // Save sample for dynamic leveling
    if(++volCount >= SAMPLES) volCount = 0; // Advance/rollover sample counter

    // Get volume range of prior frames
    minLvl = maxLvl = vol[0];
    for(i=1; i<SAMPLES; i++) {
      if(vol[i] < minLvl)      minLvl = vol[i];
      else if(vol[i] > maxLvl) maxLvl = vol[i];
    }

    // minLvl and maxLvl indicate the volume range over prior frames, used
    // for vertically scaling the output graph (so it looks interesting
    // regardless of volume level).  If they're too close together though
    // (e.g. at very low volume levels) the graph becomes super coarse
    // and 'jumpy'...so keep some minimum distance between them (this
    // also lets the graph go to zero when no sound is playing):
    if((maxLvl - minLvl) < TOP) maxLvl = minLvl + TOP;
    minLvlAvg = (minLvlAvg * 63 + minLvl) >> 6; // Dampen min/max levels
    maxLvlAvg = (maxLvlAvg * 63 + maxLvl) >> 6; // (fake rolling average)
    ii++;
    Serial.println(maxLvl);
    Serial.println(maxLvlAvg);
    Serial.println("end");

    if((millis() - lastUpdate) > Interval) {
      feed_read = sub_onoffbutton(responseWait_Short);
    }
    if(strcmp(feed_read, "18") != 0) {
      return feed_read;
    }
  }
      if((millis() - lastUpdate) > Interval) {
      feed_read = sub_onoffbutton(responseWait_Short);
    }
    if(strcmp(feed_read, "18") != 0) {
      return feed_read;
    }
}
