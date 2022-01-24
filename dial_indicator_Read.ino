//PIN locations
int dataIn1 = 4, clockIn1 = 5;
// Variables
String data1 = "";
int sign;
long value;
long startTime;
long currentTime;
int read_timeout=5000;
void setup() {
  // Pin Set Up
  pinMode(dataIn1, INPUT);     
  pinMode(clockIn1, INPUT);  
  Serial.begin(115200);
  Serial.println("Ready");
}

void loop(){
  if(Serial.readString()=="Read")
  {
    data1 = decode(clockIn1,dataIn1);
    Serial.println(data1);
  }
}

float decode(int CLK,int DATA) {
  int i;
  float result;
  sign=1,value=0;
  for (i=0;i<23;i++)
  {
    startTime = millis();
    while (digitalRead(CLK)==HIGH) {}
    while (digitalRead(CLK)==LOW) {
      currentTime = millis();
      if ( (currentTime-startTime)> read_timeout)
      {
        Serial.println("Waiting in 2nd loop");//wait until clock returns to HIGH- the first bit is not needed
        return 99.1234567890;
      }
    }
    if (digitalRead(DATA)==LOW)
    {
      if (i<20) value|= 1<<i;
      if (i==20) sign=-1;
    }
  }
  result = (value*sign-1)/100.00;
  Serial.println(result);
  return result;
}
