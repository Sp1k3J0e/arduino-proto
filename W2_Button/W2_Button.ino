//设置串口、引脚、变量
const unsigned long BAUD_RATE = 9600;
int button_pin = 4;
int led_pin =2;

bool stable = HIGH;
bool last_raw = HIGH;
bool led_on = false;
const unsigned long debounce_ms = 25;
unsigned long change_time = 0;

void setup() {
  // 设置模式
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  pinMode(button_pin, INPUT_PULLUP);

  // 初始化串口
  Serial.begin(BAUD_RATE);

  // 打印开头
  Serial.print("[BOOT] W2_Button v0.2 | ");
  Serial.print(BAUD_RATE);
  Serial.print(" | compiled ");
  Serial.print(__DATE__ );
  Serial.println( __TIME__);
  Serial.println("[INIT] pin=4 mode=INPUT_PULLUP");
}

void loop() {
  // 读当前电平
  bool raw = digitalRead(button_pin);

  // 检测变化，只记录时刻
  if(raw != last_raw){
    change_time = millis();
    last_raw = raw;
  }

  // 检查时间，放在if外面，每圈都走一次
  if(millis() - change_time >= debounce_ms){

    //确认状态变化
    if(raw != stable){
      stable = raw;
      if(stable == LOW){
        Serial.print("Press-  ");
      }else{
        Serial.print("Release-  ");
        // 根据stable控制灯具开关
        led_on = !led_on;
        digitalWrite(led_pin, led_on ? HIGH : LOW);
        Serial.print("led=");
        Serial.print(led_on ? "ON  " : "OFF  ");
      }

      Serial.println(millis());
    }
  }

  

}
