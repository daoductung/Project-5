/*==============================
 * Chương trình điều khiển led đèn giao thông
 * Update 05/12/2018
 * Coder: Dao Duc Tung
 * Truong: SPKT Hưng Yên
 * Lop: 101153
 * Các thông tin upadae: 
  - Cập nhật chương trình điều khiển led 7 thanh(hien thi thong so)
  - Cập nhật chương trình điều khiển led yellow, red, green
  - Xử lý được trạng thái đèn giao thông yellow, red, green
================================*/
#define latchSeg  6
#define clockSeg  5
#define dataSeg  7


#define latchLed  3
#define clockLed  2
#define dataLed  4

//Khai bao chan do, xanh, vang
#define ledGreen 8
#define ledYellow 9
#define ledRed 10


#define ledGreen_2  11
#define ledYellow_2   12
#define ledRed_2  13
#define test_led 1
//Khai báo biến 
int i=0,j=0;
bool state=true;
int dem,hdv,hc, thoi_gian, thoi_gian_2;

int _start = 30, time_red, time_green, time_yellow = 5;
byte ledStatus, ledStatus_2, moc;
unsigned long previousMillis = 0,previous=0;
const long interval = 1000; 
//Khai báo mảng
unsigned char Display_Number[10]={0xC0,0xF9,0xA4,0xA8,0x99,0x8A,0x82,0xF8,0x80,0x88};
unsigned char Display_Led[9]={0x40,0x80,0x01,0x02, 0x10,0x20,0x04,0x08,0x00};
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
  pinMode(test_led,OUTPUT);


  Serial.begin(9600);
  
}
//Tạo độ trễ
void Delay(float delayTime){
    unsigned long endTime = millis() + delayTime;
    while(millis() < endTime)
    {
    }
}
void printSerial(int data){
  }
//Điều khiển led bằng ic74HC595
void display_led(int id){
    digitalWrite(latchLed, LOW); //các đèn LED sẽ không sáng khi bạn digital LOW
    shiftOut(dataLed, clockLed, MSBFIRST, Display_Led[id]);
    digitalWrite(latchLed, HIGH);//các đèn LED sẽ sáng với trạng thái vừa được cập nhập
}

void HienThiSoCot13(int cot_1)
{
    for(int i=0;i<4;i++)
    {
    digitalWrite(latchSeg, LOW);
    switch(i)
    {
      case 0:
              ledStatus = Display_Number[cot_1/10];
              break;
      case 1: 
              ledStatus = Display_Number[cot_1%10];
              break;
      case 2:
              ledStatus = Display_Number[cot_1/10];
              break;
      case 3: 
              ledStatus = Display_Number[cot_1%10];
              break;
    }
      shiftOut(dataSeg, clockSeg, MSBFIRST, ledStatus); 
      
      digitalWrite(latchSeg, HIGH);
      display_led(8);
      display_led(i);
      Delay(3);
     }
  }
 void HienThiSoCot24(int cot_2)
{
    for(int i=4;i<8;i++)
    {
    digitalWrite(latchSeg, LOW);
    switch(i)
    {
      case 4:
              ledStatus = Display_Number[cot_2/10];
              break;
      case 5: 
              ledStatus = Display_Number[cot_2%10];
              break;
      case 6:
              ledStatus = Display_Number[cot_2/10];
              break;
      case 7: 
              ledStatus = Display_Number[cot_2%10];
              break;
    }
      shiftOut(dataSeg, clockSeg, MSBFIRST, ledStatus); 
      digitalWrite(latchSeg, HIGH);
      display_led(8);
      display_led(i);
      Delay(3);
     }
  }
void DieuKhienLed13(int data_red, int data_green){
  digitalWrite(ledRed,LOW);
  digitalWrite(ledRed_2,LOW);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledYellow_2,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledGreen_2,LOW);
    
    
    if(data_red>time_yellow){
    digitalWrite(ledRed,HIGH);
    digitalWrite(ledGreen_2,HIGH);
    Serial.println("+COT1+RED+"+String(data_red)+"+COT2+GREEN+"+String(data_green)+"+");
    }else if(data_red<time_yellow && data_red>0){
      digitalWrite(ledRed,HIGH);
      digitalWrite(ledYellow_2,HIGH);
      digitalWrite(ledGreen_2,LOW);
      
      Serial.println("+COT1+RED+"+String(data_red)+"+COT2+YELLOW+"+String(data_green)+"+");
      }else if(data_red == 0 ){
        digitalWrite(ledYellow,HIGH);
        digitalWrite(ledYellow_2,HIGH);
        Serial.println("+COT1+YELLOW+"+String(data_red)+"+COT2+YELLOW+"+String(data_green)+"+");
        }
    
    

  }
void DieuKhienLed24(int data_red, int data_green){
  digitalWrite(ledRed,LOW);
  digitalWrite(ledRed_2,LOW);
  digitalWrite(ledYellow,LOW);
  digitalWrite(ledYellow_2,LOW);
  digitalWrite(ledGreen,LOW);
  digitalWrite(ledGreen_2,LOW);
    
  if(data_red>time_yellow){
    digitalWrite(ledRed_2,HIGH);
    digitalWrite(ledGreen,HIGH);
    Serial.println("COT1+GREEN+"+String(data_green)+"+COT2+RED+"+String(data_red)+"+");
    }else if(data_red < time_yellow && data_red>0){
      digitalWrite(ledRed_2,HIGH);
      digitalWrite(ledYellow,HIGH);
      digitalWrite(ledGreen,LOW);
      Serial.println("+COT1+YELLOW+"+String(data_green)+"+COT2+Red+"+String(data_red)+"+");
      }else if(data_red == 0){
        digitalWrite(ledYellow_2,HIGH);
        digitalWrite(ledYellow,HIGH);
        Serial.println("+COT1+YELLOW+"+String(data_red)+"+COT2+YELLOW+"+String(data_green)+"+");
        }
   
  }
void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval){ 
  
    if(time_red <= 0 && thoi_gian <= 0){
      time_yellow = 5;
      time_red = _start - time_yellow;
      time_green=time_red - time_yellow;
      state = !state;
    }
    else{
      time_red--;
      time_green--;
       if(time_green<=1){
        time_green=0;
        }
       if(time_red <=0){
       time_yellow--;
       
       }
    }
   previousMillis = currentMillis;
  }

  if(state==true){
  HienThiSoCot13(time_red);
  HienThiSoCot24(time_green);
  DieuKhienLed13(time_red,time_green);    
  }else if(state==false){
    HienThiSoCot13(time_green);
    HienThiSoCot24(time_red);
    DieuKhienLed24(time_red,time_green);

    }
}
    
