#include <Arduino.h>
#include "esp_camera.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <iostream>

#define PWDN_GPIO_NUM 38
#define RESET_GPIO_NUM -1

#define XCLK_GPIO_NUM 15
#define SIOD_GPIO_NUM 4
#define SIOC_GPIO_NUM 5
#define HREF_GPIO_NUM 7
#define VSYNC_GPIO_NUM 6
#define PCLK_GPIO_NUM 13

#define CAM_PIN_D7 16
#define CAM_PIN_D6 17
#define CAM_PIN_D5 18
#define CAM_PIN_D4 12
#define CAM_PIN_D3 8
#define CAM_PIN_D2 8
#define CAM_PIN_D1 9
#define CAM_PIN_D0 11



static camera_config_t camera_config = {
  .pin_pwdn       = PWDN_GPIO_NUM,
  .pin_reset      = RESET_GPIO_NUM,
  .pin_xclk       = XCLK_GPIO_NUM,
  .pin_sccb_sda   = SIOD_GPIO_NUM,
  .pin_sccb_scl   = SIOC_GPIO_NUM,
  .pin_d7         = CAM_PIN_D7,
  .pin_d6         = CAM_PIN_D6,
  .pin_d5         = CAM_PIN_D5,
  .pin_d4         = CAM_PIN_D4,
  .pin_d3         = CAM_PIN_D3,
  .pin_d2         = CAM_PIN_D2,
  .pin_d1         = CAM_PIN_D1,
  .pin_d0         = CAM_PIN_D0,
  .pin_vsync      = VSYNC_GPIO_NUM,
  .pin_href       = HREF_GPIO_NUM,
  .pin_pclk       = PCLK_GPIO_NUM,

  
  .xclk_freq_hz   = 20000000, // The clock frequency of the image sensor
   // Set the frame buffer storage location
  .pixel_format   = PIXFORMAT_JPEG,// The pixel format of the image: PIXFORMAT_ + YUV422|GRAYSCALE|RGB565|JPEG
  .frame_size     = FRAMESIZE_UXGA, // The resolution size of the image: FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
  .jpeg_quality   = 12, // The quality of the JPEG image, ranging from 0 to 63.
  .fb_count       = 2, // The number of frame buffers to use.
  .fb_location = CAMERA_FB_IN_PSRAM,
  .grab_mode      = CAMERA_GRAB_WHEN_EMPTY //  The image capture mode.
};

// put function declarations here:
esp_err_t camera_init(const camera_config_t*);


// define the camera buffer structure
typedef struct {
  uint8_t *buf;
  size_t  len;
  size_t width;
  size_t height;
  pixformat_t format;
  struct timeval timestamp;
  float frame_rate;
  size_t frame_number;
}camera_buffer;

void setup() {
  esp_err_t err = camera_init(&camera_config);
  if (err != ESP_OK) {
    Serial.println("Camera initialization failed");
    printf("Camera initialization failed");
    return;
    
  }

  Serial.begin(96000);
  Serial.println("Camera initialized successfully");
  Serial.printf("Camera initialized successfully\n");

  
}

void loop() {
  // put your main code here, to run repeatedly:
}


