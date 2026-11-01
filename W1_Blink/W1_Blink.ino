  // 引入常量与变量。
  const unsigned long BAUD_RATE = 115200;
  const int led_pin= 2;

  int BlinkCount = 0;
  bool ledOn = false;
  
void setup() {
  // 初始化串口。
  Serial.begin(BAUD_RATE);
  // 设置led引脚。
  pinMode(led_pin,OUTPUT);
  // 打印开头
  Serial.printf("[BOOT]W1_Blink v0.1 | %lu | compiled %s %s\n", BAUD_RATE, __DATE__, __TIME__);
  Serial.println("[INIT] pin=2 mode=OUTPUT interval=500ms");
}

void loop() {
  // 初始化计数。
  ledOn = !ledOn;
  BlinkCount++;
  digitalWrite(led_pin, ledOn ? HIGH : LOW);

  // 根据变化打印。
    Serial.printf("[T=%lu] led=%s count=%d\n", millis(), ledOn ? "ON" : "OFF", BlinkCount);

  // 延时。
  delay(500);
}
