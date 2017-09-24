#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>   // Special version for ESP8266, apparently
#include "Telnet.h"
#include "C:\Leif\GitHub\ESP8266\Common\ssids.h"

//how many clients should be able to telnet to this ESP8266
#define MAX_SRV_CLIENTS 1

#define BLUE_LED 2
#define RED_LED  0

//WiFiServer server(23);
//WiFiClient serverClients[MAX_SRV_CLIENTS];

SoftwareSerial softSerial(4, 5); // RX, TX

void setup() 
{  
  Serial.begin(115200);
  softSerial.begin(9600);

  // LEDs
  pinMode(BLUE_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(BLUE_LED, HIGH);  // HIGH=Off
  digitalWrite(RED_LED, HIGH);

  softSerial.println();
  softSerial.println();
  AnsiClearScreen(softSerial);
  softSerial.print("Connecting to ");
  softSerial.print(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    softSerial.print(".");
  }

  softSerial.println("WiFi connected!");
  softSerial.print("IP address: ");
  softSerial.println(WiFi.localIP());
 
  // Start the server 
  //server.begin();
  //server.setNoDelay(true);   

  // Init message
  softSerial.println();
  softSerial.println("READY.");
  //softSerial.print("Ready! Use 'telnet ");
  //softSerial.print(WiFi.localIP());
  //softSerial.println(" 23' to connect");
}


void loop()
{
  digitalWrite(BLUE_LED, HIGH);  // HIGH=Off
  digitalWrite(RED_LED, HIGH);

  DoTelnet();
}

void TerminalMode(WiFiClient client)
{
  int i = 0;
  char buffer[10];
  int buffer_index = 0;
  int buffer_bytes = 0;
  bool isFirstChar = true;
  bool isTelnet = false;
  bool telnetBinaryMode = false;

  while (client.connected())
  {
    digitalWrite(BLUE_LED, HIGH);  // HIGH=Off
    digitalWrite(RED_LED, HIGH);

    // Get data from the telnet client and push it to the UART client
    if (client.available() > 0)
    {
      digitalWrite(BLUE_LED, LOW);  // Low=On

      int data = client.read();

      // If first character back from remote side is NVT_IAC, we have a telnet connection.
      if (isFirstChar)
      {
        if (data == NVT_IAC)
        {
          isTelnet = true;
          CheckTelnet(isFirstChar, telnetBinaryMode, client);
        }
        else
        {
          isTelnet = false;
        }
        isFirstChar = false;
      }
      else  // Connection already established, but may be more telnet control characters
      {
        if ((data == NVT_IAC) && isTelnet)
        {
          if (CheckTelnet(isFirstChar, telnetBinaryMode, client))
          {
            softSerial.write(NVT_IAC);
          }
        }
        else   //  Finally regular data - just pass the data along.
        {
          softSerial.write(data);
        }
      }
    }

    //check UART for data
    if (softSerial.available())
    {
      digitalWrite(RED_LED, LOW);  // Low=On

      size_t len = softSerial.available();
      uint8_t sbuf[len];
      softSerial.readBytes(sbuf, len);
      client.write(sbuf, len);
      delay(1);  // needed?
    }
  } // while (client.connected())
}

// ----------------------------------------------------------
// User Input Handling

boolean IsBackSpace(char c)
{
  if ((c == 8) || (c == 20) || (c == 127))
  {
    return true;
  }
  else
  {
    return false;
  }
}

String GetInput()
{
  String temp = GetInput_Raw();
  temp.trim();
  return temp;
}

String GetInput_Raw()
{
  char temp[80];

  int max_length = sizeof(temp);

  int i = 0; // Input buffer pointer
  char key;

  while (true)
  {
    key = ReadByte(softSerial);  // Read in one character

    if (!IsBackSpace(key))  // Handle character, if not backspace
    {
      temp[i] = key;
      softSerial.write(key);    // Echo key press back to the user

      if (((int)key == 13) || (i >= (max_length - 1)))   // The 13 represents enter key.
      {
        temp[i] = 0; // Terminate the string with 0.
        return String(temp);
      }
      i++;
    }
    else     // Backspace
    {
      if (i > 0)
      {
        softSerial.write(key);
        i--;
      }
    }

    // Make sure didn't go negative
    if (i < 0) i = 0;
  }
}


// ----------------------------------------------------------
// Helper functions for read/peek

int ReadByte(Stream& in)
{
  while (in.available() == 0) 
  {
    yield();
  }
  return in.read();
}


// EOF