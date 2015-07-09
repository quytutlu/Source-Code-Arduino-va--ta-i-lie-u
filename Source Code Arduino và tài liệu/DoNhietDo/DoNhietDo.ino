float NhietDo;
char charVal[7];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}
void(* resetFunc) (void) = 0;
void loop() {
    NhietDo = analogRead(0);
    NhietDo = (NhietDo * 5.0 * 1000 / 1024) / 10.0;
    dtostrf(NhietDo, 4, 3, charVal);
    charVal[5]='}';
    Serial.write(charVal);
    delay(500);
    resetFunc();
}
