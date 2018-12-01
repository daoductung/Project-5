/*==============================
 * Chương trình điều khiển led đèn giao thông
 * Update 01/12/2018
 * Coder: Dao Duc Tung
 * Truong: SPKT Hưng Yên
 * Lop: 101153
 * Các thông tin upadae: 
  - Cập nhật chương trình điều khiển led 7 thanh(hien thi thong so)
  - Cập nhật chương trình điều khiển led yellow, red, green
================================*/
#define latchSeg  6
#define clockSeg  7
#define dataSeg  5
#define latchLed  3
#define clockLed  4
#define dataLed  2

//Khai bao chan do, xanh, vang
#define ledGreen 8
#define ledYellow 9
#define ledRed 10
#define ledGreen_2  11
#define ledYellow_2   12
#define ledRed_2  13

//Khai báo biến 
int i=0,j=0;

int dem,_start = 35,hdv,hc;
byte ledStatus, ledStatus_2, moc;
unsigned long previousMillis = 0,previous=0;
const long interval = 1000; 
//Khai báo mảng
unsigned char Display_Number[10]={0xC0,0xF9,0xA4,0xA8,0x99,0x8A,0x82,0xF8,0x80,0x88};
unsigned char Display_Led[5]={0x04,0x08,0x01,0x02,0x00};
unsigned char Display_Led_2[5]={0x08,0x04,0x02,0x01,0x00};
//Thiết lập chân
void setup() {
  pinMode(latchSeg, OUTPUT);
  pinMode(clockSeg, OUTPUT);
  pinMode(dataSeg,OUTPUT);
  pinMode(latchLed, OUTPUT);
  pinMode(clockLed, OUTPUT);
  pinMode(dataLed, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed_2, OUTPUT);
  pinMode(ledYellow_2, OUTPUT);
  pinMode(ledGreen_2, OUTPUT);
  Serial.begin(9600);
  
}
//Điều khiển led bằng ic74HC595
void display_led(int id){
    digitalWrite(latchLed, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
    shiftOut(dataLed, clockLed, MSBFIRST, Display_Led[id]);
    digitalWrite(latchLed, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
}

void HienThiSoCot13(int hc)
{
    for(int i=0;i<2;i++)
    {
    digitalWrite(latchSeg, LOW);
    switch(i)
    {
      case 0:
              ledStatus = Display_Number[hc/10];
              break;
      case 1: 
              ledStatus = Display_Number[hc%10];
              break;
    }
      shiftOut(dataSeg, clockSeg, MSBFIRST, ledStatus); 
      digitalWrite(latchSeg, HIGH);
      display_led(5);
      display_led(i);
      delay(10);
     }
  }
 void HienThiSoCot24(int hc)
{
    for(int i=2;i<4;i++)
    {
    digitalWrite(latchSeg, LOW);
    switch(i)
    {
      case 2:
              ledStatus = Display_Number[hc/10];
              break;
      case 3: 
              ledStatus = Display_Number[hc%10];
              break;
    }
      shiftOut(dataSeg, clockSeg, MSBFIRST, ledStatus); 
      digitalWrite(latchSeg, HIGH);
      display_led(5);
      display_led(i);
      delay(10);
     }
  }
void loop() {
 unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if(dem <= 0){
      dem = _start;
    }
      
    else 
      dem--;
  }
  HienThiSoCot13(dem);
  
 
}
    
