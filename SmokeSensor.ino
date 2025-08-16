#define BLYNK_TEMPLATE_ID "TMPL6y_PmF6d6"
#define BLYNK_TEMPLATE_NAME "Smoke Sensor"
#define BLYNK_AUTH_TOKEN "ifItvzJgZltuyngt9K4_5llUq21j-uMk" // Đã sửa token (xóa khoảng trắng đầu dòng)

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Thông tin WiFi
char ssid[] = "Viettel_Duc Duong";
char pass[] = "ducduong95";

// Khai báo chân
const int MQ2_PIN = 34;    // AO của MQ2 nối vào GPIO34
const int GREEN_LED = 22;  // LED xanh nối GPIO22
const int RED_LED = 23;    // LED đỏ nối GPIO23

// Ngưỡng khí gas
const int GAS_THRESHOLD = 500;

BlynkTimer timer;

// Hàm đồng bộ trạng thái khi kết nối
BLYNK_CONNECTED() {
  Blynk.syncVirtual(V1); // Đồng bộ LED xanh
  Blynk.syncVirtual(V2); // Đồng bộ LED đỏ
}

BLYNK_WRITE(V1) { // Xử lý khi bật/tắt LED xanh ảo
  int value = param.asInt();
  digitalWrite(GREEN_LED, value);
  Serial.print("LED xanh thay đổi: ");
  Serial.println(value);
}

BLYNK_WRITE(V2) { // Xử lý khi bật/tắt LED đỏ ảo
  int value = param.asInt();
  digitalWrite(RED_LED, value);
  Serial.print("LED đỏ thay đổi: ");
  Serial.println(value);
}

// Hàm gửi dữ liệu cảm biến lên Blynk
void sendSensorData() {
  // Đọc giá trị cảm biến
  int gasValue = analogRead(MQ2_PIN);
  
  // Gửi giá trị đến Virtual Pin V0 (Gauge)
  Blynk.virtualWrite(V0, gasValue);
  
  // Tự động điều khiển LED theo ngưỡng
  if (gasValue < GAS_THRESHOLD) {
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else {
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }
  
  // Đồng bộ trạng thái LED ảo (quan trọng)
  Blynk.virtualWrite(V1, digitalRead(GREEN_LED));
  Blynk.virtualWrite(V2, digitalRead(RED_LED));
  
  // Debug trên Serial
  Serial.print("Gas: ");
  Serial.print(gasValue);
  Serial.print(" | LED xanh: ");
  Serial.print(digitalRead(GREEN_LED));
  Serial.print(" | LED đỏ: ");
  Serial.println(digitalRead(RED_LED));
}

void setup() {
  // Khởi tạo Serial
  Serial.begin(115200);
  
  // Thiết lập chân LED
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  digitalWrite(GREEN_LED, HIGH); // Ban đầu bật LED xanh
  digitalWrite(RED_LED, LOW);
  
  // Kết nối Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  // Thiết lập hàm gửi dữ liệu mỗi 1 giây
  timer.setInterval(1000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}