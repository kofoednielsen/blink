void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
   Serial.begin(9600);
   Serial.println("Running!");  
 }
 void loop() {
   if (Serial.available() > 0) {
     Serial.println("I am still running..!");  
   }
   digitalWrite(LED_BUILTIN, HIGH);
   delay(100);
   digitalWrite(LED_BUILTIN, LOW);
   delay(100);
}
