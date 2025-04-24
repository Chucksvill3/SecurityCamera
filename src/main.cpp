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
  Serial.begin(1150200);
while (!Serial) {
  camera_config_t config;
config.ledc_channel = LEDC_CHANNEL_0;       // LED control channel
config.ledc_timer = LEDC_TIMER_0;           // LED control timer
config.pin_d0 = GPIO_NUM_5;                 // Data pins
config.pin_d1 = GPIO_NUM_18;
config.pin_d2 = GPIO_NUM_19;
config.pin_d3 = GPIO_NUM_21;
config.pin_d4 = GPIO_NUM_36;
config.pin_d5 = GPIO_NUM_39;
config.pin_d6 = GPIO_NUM_34;
config.pin_d7 = GPIO_NUM_35;
config.pin_xclk = GPIO_NUM_0;               // External clock pin
// config.pin_pclk = GPIO_NUM_22;              // Pixel clock pin
// config.pin_vsync = GPIO_NUM_25;             // Vertical sync pin
// config.pin_href = GPIO_NUM_23;              // Horizontal reference pin
config.pin_sscb_sda = GPIO_NUM_26;          // Serial data pin
config.pin_sscb_scl = GPIO_NUM_27;          // Serial clock pin
config.pin_pwdn = GPIO_NUM_32;              // Power down pin
config.pin_reset = GPIO_NUM_33;             // Reset pin
config.xclk_freq_hz = 20000000;             // External clock frequency (20 MHz)
config.frame_size = FRAMESIZE_QVGA;         // Frame size (e.g., QVGA: 320x240)
config.pixel_format = PIXFORMAT_JPEG;       // Pixel format (JPEG for streaming)
config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;  // Frame grab mode
config.fb_location = CAMERA_FB_IN_PSRAM;   // Frame buffer location
config.jpeg_quality = 10;                   // JPEG quality (0 = best, 63 = lowest)
config.fb_count = 2;    

if (config.pixel_format == PIXFORMAT_JPEG) { // If the pixel format is JPEG
  if(psramFound()){  // If PSRAM is available use it for frame buffer cos it has more memory
    config.fb_location = CAMERA_FB_IN_PSRAM;
    config.frame_size = FRAMESIZE_UXGA; // Set the frame size to UXGA (1600x1200)
    config.jpeg_quality = 10;
    config.fb_count = 2;
    config.grab_mode = CAMERA_GRAB_LATEST;
  } else {
    // Limit the frame size when PSRAM is not available to avoid memory issues and use DRAM for frame buffer cos smaller memory
    config.frame_size = FRAMESIZE_SVGA;
    config.fb_location = CAMERA_FB_IN_DRAM;
  }
} else {
 
  config.frame_size = FRAMESIZE_240X240; // If the pixel format is not JPEG, set the frame size to 240x240
  config.fb_location = CAMERA_FB_IN_DRAM; // Use DRAM for frame buffer
  config.grab_mode = CAMERA_GRAB_LATEST;
#if CONFIG_IDF_TARGET_ESP32S3
  config.fb_count = 2;
#endif
}



}
  
  esp_err_t err = camera_init(&camera_config);
  if (err != ESP_OK) {
  
    Serial.println("Camera initialization failed");
    printf("Camera initialization failed");
    return;
    
  }


  Serial.println("Camera initialized successfully");
  Serial.printf("Camera initialized successfully\n");

  
}

void loop() {
  // put your main code here, to run repeatedly:
}


