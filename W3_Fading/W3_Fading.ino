//设置串口、引脚、变量
const unsigned long BAUD_RATE = 9600;
int button_pin = 4;
int led_pin =2;

bool stable = HIGH;
bool last_raw = HIGH;
const unsigned long debounce_ms = 25;
unsigned long change_time = 0;

// 设置LED状态、亮度、调光时间变量
enum State { IDLE, FADING };
State state = IDLE;

int brightness = 0;
int target = 0;

unsigned long last_step = 0;

int step_ms = 20;
int step_size = 256 / 50;

void setup() {
  // 设置模式
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  pinMode(button_pin, INPUT_PULLUP);

  // 初始化串口
  Serial.begin(BAUD_RATE);

  // 打印开头
  Serial.print("[BOOT] W3_Fading v0.3 | ");
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

  // 检查时间，放在if外面，每圈都走一次，消抖
  if(millis() - change_time >= debounce_ms){

    //确认状态变化
    if(raw != stable){
      stable = raw;
      if(stable == LOW){
        Serial.print("Press-  ");
        Serial.println(millis());
      }else{
        Serial.print("Release-  ");
        // 根据stable控制灯具开关
        target = (target == 0) ? 255 : 0;
        state = FADING;
        Serial.print("[STATE] FADING target=");
        Serial.print(target);
        Serial.print("-  ");
        Serial.println(millis());        
      }
    }
  }

  if(state == FADING && millis() - last_step >= step_ms){
    last_step = millis();
    if(brightness < target){
      brightness += step_size;
      if(brightness > target) brightness = target;
    }else if(brightness > target){
      brightness -= step_size;
      if(brightness < target) brightness = target;
    }
    analogWrite(led_pin, brightness);

    if(brightness == target){
      state = IDLE;
      Serial.print("[STATE] IDLE-  ");
      Serial.println(millis());
    }
  }

  

}
