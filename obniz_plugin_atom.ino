#include "M5Atom.h"
#include "obniz.h"
#define BUTTON 39
#define LED 27

void onEvent(os_event_t event, uint8_t* data, uint16_t length);
void control_led(void *pvParameters);

void setup() {
  TaskHandle_t xHandle = NULL;
  xTaskCreate( control_led, "LED", 1000, NULL, tskIDLE_PRIORITY, &xHandle );
  configASSERT( xHandle );
  
  Serial.begin(115200);

  // obniz.setKey("obniz_plugin_key"); // release Key
  obniz.onEvent(onEvent);
  obniz.start();
}

void loop() {
}

typedef enum {
  LED_INIT,//起動直後
  LED_WIFI_CONNECTING,
  LED_SERVER_CONNECTING,
  LED_RUNNING,
  LED_SETTING,
  LED_ERROR,
  LED_OTA
} led_status_t;
volatile led_status_t led_status = LED_INIT;
void led_status_set(led_status_t led);

void onEvent(os_event_t event, uint8_t* data, uint16_t length) {
  switch (event) {
    case PLUGIN_EVENT_NETWORK_HARDWARE_CONNECTED:
      led_status_set(LED_SERVER_CONNECTING);
      break;
    case PLUGIN_EVENT_NETWORK_CLOUD_CONNECTED:
      led_status_set(LED_RUNNING);
      break;
    case PLUGIN_EVENT_NETWORK_CLOUD_DISCONNECTED:
      led_status_set(LED_SERVER_CONNECTING);
      break;
    case PLUGIN_EVENT_NETWORK_HARDWARE_DISCONNECTED:
    case PLUGIN_EVENT_NETWORK_WIFI_NOTFOUND:
    case PLUGIN_EVENT_NETWORK_WIFI_CONNECTING:
    case PLUGIN_EVENT_NETWORK_WIFI_SOFTAP_CONNECTED:
    case PLUGIN_EVENT_NETWORK_WIFI_SCANNING:
      led_status_set(LED_WIFI_CONNECTING);
      break;
    case PLUGIN_EVENT_NETWORK_WIFI_FAIL:
    case PLUGIN_EVENT_FAIL:
    case PLUGIN_EVENT_OTA_ERROR:
      led_status_set(LED_ERROR);
      break;
    case PLUGIN_EVENT_OTA_START:
    case PLUGIN_EVENT_OTA_END:
      led_status_set(LED_OTA);
      break;
    case PLUGIN_EVENT_INITIALIZED:
      if (digitalRead(BUTTON) == LOW) {
        led_status_set(LED_SETTING);
        delay(10);
        obniz.startSettingPage();
      }
      led_status_set(LED_INIT);
      break;
  }
}

void control_led(void *pvParameters) {
  obniz.pinReserve(LED);
  M5.begin(false, false, true);
  bool led_status_blink = true;
  while (1) {
    led_status_blink = !led_status_blink;
    if (led_status == LED_INIT) {
      M5.dis.fillpix(0xff0000);
    } else if (led_status == LED_WIFI_CONNECTING) {
      M5.dis.fillpix(led_status_blink * 0xff << 16);
    } else if (led_status == LED_SERVER_CONNECTING) {
      M5.dis.fillpix(led_status_blink * 0xff);
    } else if (led_status == LED_RUNNING) {
      M5.dis.fillpix(0x0000ff);
    } else if (led_status == LED_SETTING) {
      M5.dis.fillpix((led_status_blink * 0xff) << 8 | led_status_blink * 0xff);
    } else if (led_status == LED_ERROR) {
      M5.dis.fillpix(0xff0000);
    } else if (led_status == LED_OTA) {
      M5.dis.fillpix(led_status_blink * 0xff << 8);
    }
    vTaskDelay(250 / portTICK_PERIOD_MS);
  }
}

void led_status_set(led_status_t led) {
  led_status = led;
}
