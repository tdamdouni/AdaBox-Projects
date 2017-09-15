# AdaFruit Feather HUZZAH/32u4 Bluefruit Tracked Vehicle

_Captured: 2017-09-15 at 10:34 from [www.hackster.io](https://www.hackster.io/alien-energy-3/adafruit-feather-huzzah-32u4-bluefruit-tracked-vehicle-a854c3)_

![AdaFruit Feather HUZZAH/32u4 Bluefruit Tracked Vehicle](https://hackster.imgix.net/uploads/attachments/246880/20170102_073957_resized_HFm67T1r1W.jpg?auto=compress%2Cformat&w=900&h=675&fit=min)

For a year, I have been buying AdaFruit's new Feather based items thinking that at some time I would build another tracked vehicle. Now I didn't want to invest again in another platform that required special software/code to make work. I also wanted a robot controlled via my cellphone or tablet (Android/Windows vs Bluetooth BLE/Wifi).

![](https://hackster.imgix.net/uploads/attachments/246990/20170102_081049_resized_8bc7gwrcp2_79XweBkzTe.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

I had experience with RaspberryPi, Arduino, PcDuino, Particle, Photon based WiFi enabled vehicles programmed with Python or C++. Most of these vehicles were built upon similar code samples.

The hardest thing about building this project would be soldering the headers on each of the 6 Feather based boards.

This project was going to be based upon the option to utilize either the Feather HUZZAH with ESP8266 or the 32u4 Bluefruit boards as the controller with the Motor FeatherWing and the FeatherWing Doubler to drive the Tracked/Tank/Wheeled platform of your choice.

My choice of vehicles were many, since I had 2-wheeled, 4-wheeled, and tracked based platforms on hand. I chose a tracked tank platform from Sainsmart.

PLEASE DOWNLOAD and review appropriate Adafruit training documentation from their website for each component utilized. It is very informative and is helpful and required to setup access and control in used by each module.

;

;

![](https://hackster.imgix.net/uploads/attachments/247076/20170102_073949_resized_VHfbI0xFJG.jpg?auto=compress%2Cformat&w=680&h=510&fit=max)

I have listed different battery types/holders because the Adafruit Lithium Ion batteries do not have a power ON/OFF switch, but the 4x AA or 3x AA battery holder does. Its a matter of preference.

This project requires a separate battery source for the HUZZAH or Feather 32u4, the motor driver requires its own source 4.5v to 14v dc, I used 2x 18650 batteries in a holder with a 2.1mm power jack/plug.

I also used a 12vdc power pack (not listed originally from Linksprite/CuteDigi)

All assembly documentation can be downloaded from AdaFruit's website for each of the components utilized and as a basis for development of software control.
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    aREST(char* rest_remote_server, int rest_port) {
    
    
    
    
    
    
    
    
    
    
    
    
    
      client.setServer(mqtt_server, 1883);
    
    
    aREST(PubSubClient& client, char* new_mqtt_server) {
    
    
    
      client.setServer(new_mqtt_server, 1883);
    
    
    
    void subscribe(String device, String eventName) {
    
      String topic = device + "_" + eventName + "_in";
    
      topic.toCharArray(charBuf, 50);
    
      subscriptions_names[subscriptions_index] = charBuf;
    
    
    void publish(PubSubClient& client, String eventName, T data) {
    
        Serial.print("Publishing event " + eventName + " with data: ");
    
      String message = "{\"client_id\": \"" + String(id) + "\", \"event_name\": \"" + eventName + "\", \"data\": \"" + String(data) + "\"}";
    
    
      message.toCharArray(charBuf, 100);
    
      client.publish(publish_topic, charBuf);
    
    
    void setKey(char* proKey, PubSubClient& client) {
    
      client.setServer(mqtt_server, 1883);
    
    
    
      strncpy(id, randomId.c_str(), ID_SIZE);
    
      String inTopic = randomId + String(proKey) + String("_in");
      String outTopic = randomId + String(proKey) + String("_out");
    
      strcpy(in_topic, inTopic.c_str());
      strcpy(out_topic, outTopic.c_str());
    
      strcpy(client_id, clientId.c_str());
    
    
    
    
    
    
    
      if(status_led_pin != 255){
        unsigned long i = millis();
        int j = i % 4096;
        if (j > 2048) { j = 4096 - j;}
    
    
      addToBuffer(F("HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: POST, GET, PUT, OPTIONS\r\nContent-Type: application/json\r\nConnection: close\r\n\r\n"));
    
    
    
          Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
    
    
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.println(freeMemory, DEC);
    
    
    
      if (client.available()) {
    
        handle_proto(client,true,0);
    
        sendBuffer(client,32,20);
    
    
    
    
      publish_proto(client, eventName, value);
    
    
    
      if (client.available()) {
    
        handle_proto(client,false,0);
    
        sendBuffer(client,25,10);
    
    
    void publish(YunClient& client, String eventName, T value) {
    
      publish_proto(client, eventName, value);
    
    
    
      if (serial.available()) {
    
        handle_proto(serial,false,0);
    
        sendBuffer(serial,100,1);
    
    
    
    
    
    
      if (client.available()) {
    
        handle_proto(client,true,0);
    
        sendBuffer(client,50,0);
    
    
    void publish(EthernetClient& client, String eventName, T value) {
    
      publish_proto(client, eventName, value);
    
    
    
      if (client.available()) {
    
        handle_proto(client,true,0);
    
        sendBuffer(client,0,0);
    
    
    
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
    
      if (client.available()) {
    
          Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
    
        handle_proto(client,true,0);
    
          Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
    
        sendBuffer(client,0,0);
    
    
    
    
      publish_proto(client, eventName, value);
    
    
    
      if (client.available()) {
    
        if (DEBUG_MODE) {Serial.println("Request received");}
    
        handle_proto(client,true,0);
    
        sendBuffer(client,0,0);
    
    
    
      publish_proto(client, eventName, value);
    
    
    
      if (client.available()) {
    
        if (DEBUG_MODE) {Serial.println("Request received");}
    
        handle_proto(client,true,0);
    
        sendBuffer(client,50,1);
    
    
    
      publish_proto(client, eventName, value);
    
    
    void handle(usb_serial_class& serial){
    
      if (serial.available()) {
    
        handle_proto(serial,false,1);
    
        sendBuffer(serial,25,1);
    
    
    void publish(usb_serial_class& client, String eventName, T value) {
    
      publish_proto(client, eventName, value);
    
    
    
      if (serial.available()) {
    
        handle_proto(serial,false,1);
    
        sendBuffer(serial,25,1);
    
    
    void publish(Serial_& client, String eventName, T value) {
    
      publish_proto(client, eventName, value);
    
    
    
      if (serial.available()) {
    
        handle_proto(serial,false,1);
    
        sendBuffer(serial,25,1);
    
    
    void publish(HardwareSerial& client, String eventName, T value) {
    
      publish_proto(client, eventName, value);
    
    
    void handle(char * string) {
    
    
    
    void handle_proto(char * string) {
      for (int i = 0; i < strlen(string); i++){
    
        char c = string[i];
    
    
    
    
    void publish_proto(T& client, String eventName, V value) {
    
      String data = "name=" + eventName + "&data=" + String(value);
    
      Serial.println("POST /" + String(id) + "/events HTTP/1.1");
      Serial.println("Host: " + String(remote_server) + ":" + String(port));
      Serial.println(F("Content-Type: application/x-www-form-urlencoded"));
      Serial.print(F("Content-Length: "));
      Serial.println(data.length());
    
      client.println(F("POST /1/events HTTP/1.1"));
      client.println("Host: " + String(remote_server) + ":" + String(port));
      client.println(F("Content-Type: application/x-www-form-urlencoded"));
      client.print(F("Content-Length: "));
      client.println(data.length());
    
    
    void handle_proto(T& serial, bool headers, uint8_t read_delay)
    
      while (serial.available()) {
    
        char c = serial.read();
        answer = answer + c;
    
    
    
    
    
    void handle_callback(PubSubClient& client, char* topic, byte* payload, unsigned int length) {
    
      for(i = 0; i < length; i++) {
        mqtt_msg[i] = payload[i];
      mqtt_msg[i] = '\0';
    
    
        String modified_message = String(msgString) + " /";
        modified_message.toCharArray(char_message, 100);
    
    
    
          Serial.println(strlen(answer));
          Serial.println(strlen(client_id));
    
        int max_message_size = 128 - 20 - strlen(client_id);
    
        if (strlen(answer) < max_message_size) {
          client.publish(out_topic, answer);
    
          uint8_t max_iteration = (int)(strlen(answer)/max_message_size) + 1;
    
          for (uint8_t i = 0; i < max_iteration; i++) {
            memcpy(intermediate_buffer, buffer + i*max_message_size, max_message_size);
    
              Serial.println(strlen(intermediate_buffer));
    
            client.publish(out_topic, intermediate_buffer);
    
    
    
    
    
    
    
    
      if (!client.connected()) {
    
    
    void handle(PubSubClient& client){
    
      if (!client.connected()) {
    
    
    void reconnect(PubSubClient& client) {
    
      while (!client.connected()) {
        Serial.print(F("Attempting MQTT connection..."));
    
          if (client.connect(client_id)) {
            if (private_mqtt_server) {
              Serial.println(F("Connected to MQTT server"));
              Serial.println(F("Connected to aREST.io"));
    
    
            Serial.print(F("failed, rc="));
            Serial.print(client.state());
            Serial.println(F(" try again in 5 seconds"));
    
    
    
    void process(char c){
    
      if ((c == '/' || c == '\r') && state == 'u') {
    
    
          if (command == 'm' && pin_selected && state == 'u') {
    
    
    
         if (command == 'd' && pin_selected && state == 'u') {
    
           if (answer[0] == 'r') {state = 'r';}
    
           else {value = answer.toInt(); state = 'w';}
    
         if (command == 'a' && pin_selected && state == 'u') {
    
           if (answer[0] == 'r') {state = 'r';}
    
           else {value = answer.toInt(); state = 'w';}
    
         if (command != 'u' && pin_selected == false) {
    
           if (answer[0] == 'A') {
             pin = 14 + answer[1] - '0';
    
    
    
    
    
           if ((answer[1] != '/' && answer[2] != '/')
            || (answer[1] == ' ' && answer[2] == '/')
            || (answer[2] == ' ' && answer[3] == '/')) {
    
            if (command == 'd') {
    
              if (answer[0] == 'a') {state = 'a';}
    
              else {state = 'r';}
    
           if (command == 'a') {
    
             if (answer[0] == 'a') {state = 'a';}
    
    
    
         if (answer.startsWith("digital")) {command = 'd';}
    
         if (answer.startsWith("mode")) {command = 'm';}
    
         if (answer.startsWith("analog")) {
    
    
    
         if (command == 'u') {
    
           for (uint8_t i = 0; i < variables_index; i++){
             if(answer.startsWith(int_variables_names[i])) {
    
    
    
           for (uint8_t i = 0; i < float_variables_index; i++){
             if(answer.startsWith(float_variables_names[i])) {
    
    
    
           for (uint8_t i = 0; i < string_variables_index; i++){
             if(answer.startsWith(string_variables_names[i])) {
    
    
    
           for (uint8_t i = 0; i < functions_index; i++){
             if(answer.startsWith(functions_names[i])) {
    
    
    
               uint8_t header_length = strlen(functions_names[i]);
               if (answer.substring(header_length, header_length + 1) == "?") {
                 uint8_t footer_start = answer.length();
                 if (answer.endsWith(" HTTP/"))
                 arguments = answer.substring(header_length + 8, footer_start);
    
           if ( (answer[0] == 'i' && answer[1] == 'd') ){
    
    
    
           if (answer[0] == ' '){
    
    
    
    
    
    
    
    bool send_command(bool headers) {
    
    
         Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
    
         Serial.println(F("Sending command"));
         Serial.print(F("Command: "));
         Serial.print(F("State: "));
         Serial.print(F("State of buffer at the start: "));
    
       if (headers && command != 'r') {send_http_headers();}
    
       if (command == 'm'){
    
           addToBuffer(F("{\"message\": \"Pin D"));
    
         if (state == 'i'){
    
    
          if (!LIGHTWEIGHT){addToBuffer(F(" set to input\", "));}
    
         if (state == 'o'){
    
    
           if (!LIGHTWEIGHT){addToBuffer(F(" set to output\", "));}
    
    
       if (command == 'd') {
         if (state == 'r'){
    
    
           if (LIGHTWEIGHT){addToBuffer(value);}
            addToBuffer(F("{\"return_value\": "));
    
         if (state == 'a') {
           if (!LIGHTWEIGHT) {addToBuffer(F("{"));}
    
           for (uint8_t i = 0; i < NUMBER_DIGITAL_PINS; i++) {
    
    
               addToBuffer(F("\"D"));
               addToBuffer(F("\": "));
    
         if (state == 'w') {
    
    
    
            addToBuffer(F("{\"message\": \"Pin D"));
            addToBuffer(F("\", "));
    
       if (command == 'a') {
         if (state == 'r'){
    
    
           if (LIGHTWEIGHT){addToBuffer(value);}
            addToBuffer(F("{\"return_value\": "));
         if (state == 'a') {
           if (!LIGHTWEIGHT) {addToBuffer(F("{"));}
    
           for (uint8_t i = 0; i < NUMBER_ANALOG_PINS; i++) {
    
    
               addToBuffer(F("\"A"));
               addToBuffer(F("\": "));
       if (state == 'w') {
    
    
         addToBuffer(F("\", "));
    
    
      if (command == 'v') {
    
           if (LIGHTWEIGHT){addToBuffer(*int_variables[value]);}
            addToBuffer(F("{\""));
            addToBuffer(F("\": "));
            addToBuffer(*int_variables[value]);
    
      if (command == 'l') {
    
           if (LIGHTWEIGHT){addToBuffer(*float_variables[value]);}
            addToBuffer(F("{\""));
            addToBuffer(F("\": "));
            addToBuffer(*float_variables[value]);
    
      if (command == 's') {
    
           if (LIGHTWEIGHT){addToBuffer(*string_variables[value]);}
            addToBuffer(F("{\""));
            addToBuffer(F("\": \""));
            addToBuffer(*string_variables[value]);
            addToBuffer(F("\", "));
    
      if (command == 'f') {
    
        int result = functions[value](arguments);
    
         addToBuffer(F("{\"return_value\": "));
    
      if (command == 'r' || command == 'u') {
    
      if (command == 'i') {
        if (LIGHTWEIGHT) {addToBuffer(id);}
    
         addToBuffer(F("\r\n"));
    
    
         if (command != 'r' && command != 'u') {
           addToBuffer(F("\"id\": \""));
           addToBuffer(F("\", \"name\": \""));
           addToBuffer(F("\", \"hardware\": \""));
           addToBuffer(F("\", \"connected\": true}\r\n"));
    
         Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
         Serial.print(F("State of buffer at the end: "));
    
    
    
          if (command != 'u') {
            addToBuffer(F("HTTP/1.1 200 OK\r\nAccess-Control-Allow-Origin: *\r\nAccess-Control-Allow-Methods: POST, GET, PUT, OPTIONS\r\nContent-Type: application/json\r\nConnection: close\r\n\r\n"));
    
    
        addToBuffer(F("{\"variables\": {"));
    
    
        if (variables_index == 0 && string_variables_index == 0 && float_variables_index == 0){
    
    
            for (uint8_t i = 0; i < variables_index; i++){
              addToBuffer(F("\""));
              addToBuffer(F("\": "));
              addToBuffer(*int_variables[i]);
    
    
            for (uint8_t i = 0; i < string_variables_index; i++){
              addToBuffer(F("\""));
              addToBuffer(F("\": \""));
              addToBuffer(*string_variables[i]);
              addToBuffer(F("\", "));
    
    
            for (uint8_t i = 0; i < float_variables_index; i++){
              addToBuffer(F("\""));
              addToBuffer(F("\": "));
              addToBuffer(*float_variables[i]);
    
    
    
          for (uint8_t i = 0; i < variables_index-1; i++){
            addToBuffer(F("\""));
            addToBuffer(F("\": "));
            addToBuffer(*int_variables[i]);
    
          addToBuffer(F("\""));
          addToBuffer(F("\": "));
    
    
      addToBuffer(F("\"id\": \""));
      addToBuffer(F("\", \"name\": \""));
      addToBuffer(F("\", \"hardware\": \""));
    
      addToBuffer(F("\", \"connected\": true}"));
      addToBuffer(F("\", \"connected\": true}\r\n"));
    
    
    void variable(char * variable_name, int *variable){
    
      int_variables[variables_index] = variable;
      int_variables_names[variables_index] = variable_name;
    
    
    void variable(char * variable_name, float *variable){
    
      float_variables[float_variables_index] = variable;
    
    
    void variable(char * variable_name, String *variable){
    
      string_variables[string_variables_index] = variable;
    
    
    void function(char * function_name, int (*f)(String)){
    
      functions_names[functions_index] = function_name;
      functions[functions_index] = f;
    
    void set_id(char *device_id){
    
      strncpy(id, device_id, ID_SIZE);
    
    
    
      String inTopic = randomId + String(id) + String("_in");
      String outTopic = randomId + String(id) + String("_out");
    
      strcpy(in_topic, inTopic.c_str());
      strcpy(out_topic, outTopic.c_str());
    
      strcpy(client_id, clientId.c_str());
    
    
    
    
    
    
      volatile uint32_t val1, val2, val3, val4;
      volatile uint32_t *ptr1 = (volatile uint32_t *)0x0080A00C;
      volatile uint32_t *ptr = (volatile uint32_t *)0x0080A040;
    
      sprintf(buf, "%8x%8x%8x%8x", val1, val2, val3, val4);
    
    
    
    
    
        randomString = String(ESP.getChipId());
        randomString = randomString.substring(0, 6);
    
    
        randomString = randomString.substring(0, 6);
    
    
    
      int l = charset.length();
      for (int n = 0; n < length; n++) {
        key = random(0, l - 1);
        randomString += charset[key];
    
    
    
    void set_name(char *device_name){
    
      strcpy(name, device_name);
    
    
      device_name.toCharArray(name, NAME_SIZE);
    
    
    
    
    
    
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.print(F("Added to buffer as char: "));
    
      for (int i = 0; i < strlen(toAdd); i++){
        buffer[index+i] = toAdd[i];
      index = index + strlen(toAdd);
    
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.print(F("Added to buffer as String: "));
    
      for (int i = 0; i < toAdd.length(); i++){
        buffer[index+i] = toAdd[i];
      index = index + toAdd.length();
    
    
      itoa(toAdd,number,10);
    
    
    
      itoa(toAdd,number,10);
    
    
    
      dtostrf(toAdd, 5, 2, number);
    
    
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.print(F("Added to buffer as progmem: "));
    
    
    
        unsigned char c = pgm_read_byte(p++);
        if (c == 0) break;
        buffer[index + idx] = c;
      index = index + idx;
    
    void sendBuffer(T& client, uint8_t chunkSize, uint8_t wait_time) {
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.print(F("Buffer size: "));
    
      if (chunkSize == 0) {
    
    
        uint8_t max_iteration = (int)(index/chunkSize) + 1;
    
        for (uint8_t i = 0; i < max_iteration; i++) {
          memcpy(intermediate_buffer, buffer + i*chunkSize, chunkSize);
    
    
    
            Serial.print(F("Sent buffer: "));
    
        Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
        Serial.print(F("Buffer size: "));
    
    
          Serial.println(freeMemory - ESP.getFreeHeap(),DEC);
          Serial.print(F("Buffer size: "));
    
    
    
      memset(&buffer[0], 0, sizeof(buffer));
    
    
    uint8_t esp_12_pin_map(uint8_t pin) {
    
    
    
    
    
    
    char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
      sprintf(fmt, "%%%d.%df", width, prec);
      sprintf(sout, fmt, val);
    
    
    
    
    
    
    
    
    
    
    
    
      char* mqtt_server = "45.55.196.201";
    
    
    
    
    
      int (*functions[NUMBER_FUNCTIONS])(String);
    
