int MY_PIN = 8;

void setup() {
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(MY_PIN, INPUT);
   Serial.begin(9600);
   Serial.println("Running!");  
 }
 void loop() {
   boolean my_pin_state = digitalRead(MY_PIN);
   digitalWrite(LED_BUILTIN, my_pin_state);
}
