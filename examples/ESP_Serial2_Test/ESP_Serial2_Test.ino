void setup() {
  Serial2.begin(9600);
  Serial2.println("Hello");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial2.available()){
   Serial2.println(Serial2.readStringUntil('\r'));
  }
}
