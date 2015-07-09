#include <IRremote.h> // thư viện hỗ trợ IR remote
const int receiverPin = 10; // chân digital 10 dùng để đọc tín hiệu
IRrecv irrecv(receiverPin); // tạo đối tượng IRrecv mới
decode_results results;// lưu giữ kết quả giải mã tín hiệu
bool s1 = true, s2 = true, s3 = true, s4 = false, s5 = false;
void setup()
{
  randomSeed(analogRead(0));
  //Serial.begin(9600);// serial baudrate 9600
  //  pinMode(9, OUTPUT);
  //  pinMode(8, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(7, OUTPUT);
  //  pinMode(5, OUTPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  digitalWrite(2, LOW);
  //digitalWrite(1, LOW);
  //  digitalWrite(7, HIGH);
  irrecv.enableIRIn(); // start the IR receiver
}
void Remote(int port, bool stt) {
  digitalWrite(port, stt);
  //  Serial.print(port);
  //  Serial.print("---");
  //  Serial.println(stt);
}
void loop()
{
  //  if (irrecv.decode(&results)) // nếu nhận được tín hiệu
  //  {
  //    Serial.println(results.value, HEX);
  //    switch (results.value)
  //    {
  //      case 0xFF30CF://1
  //      case 0xFEE817:
  //        s1 = !s1;
  //        Remote(5, s1);
  //        break;
  //      case 0xFF18E7://2
  //      case 0xFE6897:
  //        s2 = !s2;
  //        Remote(6, s2);
  //        break;
  //      case 0xFF7A85://3
  //      case 0xFEA857:
  //        s3 = !s3;
  //        Remote(7, s3);
  //        break;
  //      case 0xFF10EF://4
  //      case 0xFE28D7:
  //        s4 = !s4;
  //        Remote(8, s4);
  //        break;
  //      case 0xFF38C7://5
  //      case 0xFEC837:
  //        s5 = !s5;
  //        Remote(9, s5);
  //        break;
  //    }
  //    delay(200);
  //    irrecv.resume(); // nhận giá trị tiếp theo
  //  }
  if (digitalRead(8) == 1)
  {
    //s4 = !s4;
    Remote(2,1);
    delay(2);
    Remote(2,0);
    //Serial.println("Nhan nut 8");
    delay(200);
  }
  if (digitalRead(9) == 1)
  {
    s5 = !s5;
    //Remote(9,s5);
    Remote(7,1);
    //analogWrite(0,-1);
    delay(2);
    Remote(7,0);
    //analogWrite(0,0);
    //Serial.println("Nhan nut 9");
    delay(200);
  }
  Remote(2,0);
  Remote(7,0);
}
