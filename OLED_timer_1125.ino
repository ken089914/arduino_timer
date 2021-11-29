//ヘッダ
#include<Wire.h>
#include<Adafruit_GFX.h>
#include<Adafruit_SSD1306.h>
int x= 999;
int sec=12;
int minute=30;
bool flag = false;
bool set_values_flag =false;
int reset_flag=0;
//ディスプレイ変数
Adafruit_SSD1306 display(-1);
void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(8,INPUT_PULLUP);
  pinMode(9,INPUT_PULLUP);
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  Serial.begin(9600);
}


//文字セット
void set_text(int minu, int se){
      display.clearDisplay();
      // 出力する文字の大きさ
      display.setTextSize(4);
      // 出力する文字の色
      display.setTextColor(WHITE);
      // 文字の一番端の位置
      display.setCursor(1, 0);
      if(se<10){ //秒数が10未満
        if (minute <10){ //分数も秒数も10未満
          display.println("0"+String(minu)+":0"+String(se));
        }
        else{
          display.println(String(minu)+":0"+String(se));
        }
    
      }
  
      else if(minute<10){ //分数が10未満
          display.println("0"+String(minu)+":"+String(se));
        }

      else{
        display.println(String(minu)+":"+String(se));
      }
      // ディスプレイへの表示
      display.display();
}


//秒数リターン
void return_value(){
  //秒が0以下{
      if (sec <1){
        minute --;
        sec =60;
      }
      //分も秒も0以下
      if ((sec <1)&& (minute <1)){
        minute=0;
        sec=0;
      }
      else{
        sec --;
        //min_value --;
      }
}

void set_values(){
  if(sec>=60){
      sec=0;
    }
  else{
    sec++;
  }

  if(minute>=100){
    minute=0;
  }
  else{
    minute++;
  }

}
void loop() {
  //2番がLOWで3番がHIGHでflagがfalseだったらtrueにする
  if((digitalRead(2)==LOW)&&(digitalRead(3)==HIGH)&&(flag==false)){
      flag=true;
      return_value();
      set_text(minute,sec);
      delay(990);
  }


  //2番がHIGHで3番がLOWでflagがfalseだったらtrueにする
  if((digitalRead(2)==HIGH)&&(digitalRead(3)==LOW)&&(flag==true)){
      flag=false;
      set_text(minute,sec);
      reset_flag++;
      //if (reset_flag<=10){
        //reset_flag=0;
        //minute=0;
        //sec=0;
      //}
      delay(990);
  }

  //どちらもLOWでflagがtrue
  if((digitalRead(2)==LOW)&&(digitalRead(3)==LOW)&&(flag==true)){
      //flag=false;
      return_value();
      set_text(minute,sec);
      delay(990);
  }

  if((digitalRead(2)==LOW)&&(digitalRead(3)==LOW)&&(flag==false)){
      
      //set_values();
      
      set_text(minute,sec);
      delay(990);
  }
  //チャタリング防止
  delay(10);
  
}
