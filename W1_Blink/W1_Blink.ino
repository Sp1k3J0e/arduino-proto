// 引入常量与变量。
const unsigned long BAUD_RATE = 115200;
const int led_pin= 2;

int blink_count = 0;
bool led_on = false;

void setup() {
  // 初始化串口。
  Serial.begin(BAUD_RATE);
  // 设置led引脚。
  pinMode(led_pin,OUTPUT);
  // 打印开头
  Serial.printf("[BOOT] W1_Blink v0.1 | %lu | compiled %s %s\n", BAUD_RATE, __DATE__, __TIME__);
  Serial.println("[INIT] pin=2 mode=OUTPUT interval=500ms");
}

void loop() {
  // 翻转状态，开始计数。
  led_on = !led_on;
  blink_count++;
  digitalWrite(led_pin, led_on ? HIGH : LOW);

  // 根据变化打印。
  Serial.printf("[T=%lu] led=%s count=%d\n", millis(), led_on ? "ON" : "OFF", blink_count);

  // 延时。
  delay(500);
}
