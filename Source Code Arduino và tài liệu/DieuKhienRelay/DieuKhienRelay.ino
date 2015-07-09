int p3, p4, p5, p6, p7;
//bool stt8 = true, stt9 = true, stt11 = false, stt12 = false, stt13 = true;
bool btn9 = false, btn8 = false;
bool k3 = true, k4 = true;
//int temp;
void setup()
{
  Serial.begin(9600);// serial baudrate 9600
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(10,INPUT);
  pinMode(2,INPUT);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
}
void Remote(int port, bool stt) {
  digitalWrite(port, stt);
}
void loop()
{
  p3 = digitalRead(3);
  p4 = digitalRead(4);
  p5 = digitalRead(5);
  p6 = digitalRead(6);
  p7 = digitalRead(7);
  if (btn9 == true)
  {
    if (p7 != k4)
    {
      p7 = k4;
    }
    else
    {
      btn9 = false;
    }
  }
  if (btn8 == true)
  {
    if (p6 != k3)
    {
      p6 = k3;
    }
    else
    {
      btn8 = false;
    }
  }
  //Serial.println(analogRead(0));
  //temp=analogRead(0);
  if (digitalRead(10)==1)
  {
    Serial.println("Nhan nut 9");
    btn9 = true;
    p7 = !p7;
    k4 = p7;    //luu lai trang thai hien tai cua he thong
    delay(200);
  }
  if (digitalRead(2) == 1)
  {
    Serial.println("Nhan nut 8");
    btn8 = true;
    p6 = !p6;
    k3 = p6;
    delay(200);
  }
  Remote(8, p6);
  Remote(9, p4);
  Remote(13, p5);
  Remote(11, p3);
  Remote(12, p7);
  //delay(1000);
}
