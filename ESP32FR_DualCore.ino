// VERSION 1.1-AP
// Web page html
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Telemetry dashboard</title>
</head>
<body class="halftone">
    <style>
    * {
        font-family: 'Consolas', monospace;
    }
    html, body {
        width: 393px;
        height: 663px;
        margin: 0;
        overflow: hidden;
        background: #001119;
    }
    .halftone {
        background-image: radial-gradient(
            circle at center,
            #01273a 1.5px,
            transparent 0
        );
        background-size: 10px 10px;
        background-repeat: round;
    }

    /* main canvas */
    #screen {
        position: absolute;
        width: 393px;
        height: 663px;
    }
    h1, p {
        color: #e0ffff;
    }
    .centerText {
        text-align: center;
        margin-left: auto; 
        margin-right: auto; 
        display: block;
    }
    .altitudeBar {
        position: absolute;
        border: dashed white 1px;
        width: 20px;
        height: 250px;
        background: #0c5716;
        background: linear-gradient(0deg,rgba(12, 87, 22, 1) 0%, rgba(223, 241, 245, 1) 11%, rgba(177, 209, 227, 1) 59%, rgba(4, 4, 20, 1) 100%);
        left: 20px;
        top: 120px;
    }
    .altitudeArrow {
        position: absolute;
        width: 20px; 
        height: 2px; 
    }
    .AMSLbcg{
        background-color: magenta;
    }
    .AGLbcg{
        background-color: red;
    }
    .AMSLbrdr{
        border: solid magenta;
    }
    .AGLbrdr{
        border: solid red;
    }
    .altText {
        position: absolute;
        top: -18px;
        left: 30px;
        font-size: 12px;
        color: #e0ffff;
        text-wrap: nowrap;
    }
    .arrow {
        border-width: 0 2px 2px 0;
        display: inline-block;
        position:absolute;
        top: -3px;
        left: 20px;
        padding: 3px;
        transform: rotate(135deg);
        -webkit-transform: rotate(135deg);
    }
    .humidityGauge {
    width: 200px;
    height: 100px;
    position: absolute;
    overflow: hidden;
    border-radius: 200px 200px 0 0;
    background: #706a6a;
    left: 150px;
    top: 130px;
    }

    /* colored fill */
    .gaugeFill {
        position: absolute;
        width: 200px;
        height: 200px;
        border-radius: 50%;
        background: conic-gradient(
            from -90deg,
            #4cc9f0 90deg,
            transparent 90deg
        );
        top: 0;
        left: 0;
    }

    /* center cutout */
    .gaugeCover {
        position: absolute;
        width: 160px;
        height: 80px;
        background: #001119;
        border-radius: 160px 160px 0 0;
        top: 20px;
        left: 20px;
        display: flex;
        align-items: center;
        justify-content: center;
        color: white;
        font-size: 24px;
    }
    .pressureText {
        font-size: 16px;
    }
    .tempDiv{
        position: absolute;
        width: 150px;
        height: 80px;
        border: 2px solid #e0ffff;
        top: 290px;
        left: 170px;
    }
    .tempText {
        font-size: 16px;
        text-align: left;
        margin: 5px 0px 0px 13px;
    }
    .buttonsdiv {
        position: absolute;
        width: 45%;
        height: 200px;
        bottom: 50px;
        left: 50%;

    }
    button {
        display: block;
        margin: 20px auto;
        padding: 10px 20px;
        font-size: 16px;
        width: 80%;
        border-radius: 10px;
        border: solid gray;
    }
    .off{
        background-color: green;
        color: white;
    }
    .on{
        background-color: red;
        color: white;
    }
    </style>

    <div id="screen">
        <h1 class="centerText" style="font-size: 28px; margin-bottom: 10px;">Telemetry - <span style="font-style: italic;">Rocket69 🚀</span></h1>
        <div class="centerText" style="margin-top: 10px;">
            <p style="font-size: 16px; float:left; display:inline; width: 49%;">T+  <span id="last-rx" style="text-align: right;">00:00:000</span></p>
            <p style="font-size: 16px; float:left; display:inline; width: 49%;">Frame: <span id="frame-count" style="text-align: right;">00000</span></p>
        </div>
        <div class="altitudeBar">
            <div class="altitudeArrow AMSLbcg" id="altitudeArrowAMSL" ><div class="arrow AMSLbrdr"></div><p class="altText" id="altAMSL">1000 m</p></div>

            <div class="altitudeArrow AGLbcg" id="altitudeArrowAGL" ><div class="arrow AGLbrdr"></div><p class="altText" id="altAGL">1000 m</p></div>

        </div>
        <div class="humidityGauge">
            <div class="gaugeFill" id="humidityFill"></div>
            <div class="gaugeCover halftone">
                <span id="hum">50.0%</span>
            </div>
        </div>
        <div>
            <p class="pressureText" style="position: absolute; top: 240px; left: 160px;">Pressure: <span id="baro">1013.25 hPa</span></p>
        </div>
        <div class="tempDiv">
            <p  class="tempText">temp1: <span id="temp1">20.0 °C</span></p>
            <p class="tempText">temp2: <span id="temp2">20.0 °C</span></p>
            <p class="tempText">temp3: <span id="temp3">20.0 °C</span></p>
        </div>
        <div style="position: absolute; top: 400px; left: 20px;">
            <p>GyroX: <span id="rotX">0.00 °/s</span></p>
            <p>GyroY: <span id="rotY">0.00 °/s</span></p>
            <p>GyroZ: <span id="rotZ">0.00 °/s</span></p>
            <p>AccelX: <span id="accelX">0.00 m/s²</span></p>
            <p>AccelY: <span id="accelY">0.00 m/s²</span></p>
            <p>AccelZ: <span id="accelZ">0.00 m/s²</span></p>
        </div>
        <div class="buttonsdiv">
            <button onclick="calAlt()">Calibrate altitude</button>
            <button onclick="recHandle()" class="off" id="recSS">Start recording</button>
        </div>
    </div>
    <script>
        function parseNum(num, decimals, digits){
            return parseFloat(num).toFixed(decimals).toString().padStart(digits+decimals+1, '0');
        }

        function calAlt() {
            fetch('/calAlt');
        }
        // Change button state based on recording status
        function recHandle() {
            const button = document.getElementById('recSS');

            if (button.classList.contains('off')) {
                button.classList.remove('off');
                button.classList.add('on');
                button.textContent = 'Stop recording';

                fetchWithRetry('/startRec').catch(err => {
                    console.error("Failed to start recording:", err);
                });

            } else {
                button.classList.remove('on');
                button.classList.add('off');
                button.textContent = 'Start recording';

                fetchWithRetry('/stopRec').catch(err => {
                    console.error("Failed to stop recording:", err);
                });
            }
        }

        async function fetchWithRetry(url, attempts = 5, delay = 500) {
            for (let i = 0; i < attempts; i++) {
                try {
                    const res = await fetch(url);

                    if (!res.ok) throw new Error("Bad response");

                    return res; // success → stop retrying
                } catch (err) {
                    if (i === attempts - 1) throw err; // last attempt → give up

                    console.log(`Retry ${i + 1}/${attempts} for ${url}`);
                    await new Promise(r => setTimeout(r, delay));
                }
            }
        }

        function updateLastRX(){
            fetch('/lastRX')
            // convert ms to mm:ss:ms format
            .then(response => response.text())
            .then(data => {
                const ms = Number(data);
                const minutes = Math.floor(ms / 60000);
                const seconds = Math.floor((ms % 60000) / 1000);
                const milliseconds = ms % 1000;
                document.getElementById('last-rx').textContent = `${minutes.toString().padStart(2, '0')}:${seconds.toString().padStart(2, '0')}:${milliseconds.toString().padStart(3, '0')}`;
            }).catch(error => console.error('Error fetching last RX:', error));
        }
        setInterval(updateLastRX, 10);
        function updateFrameCount(){
            if (document.getElementById('recSS').classList.contains('on')){
                fetch('/frameCount').then(r => r.text()).then(data => {
                document.getElementById('frame-count').textContent = parseNum(data, 0, 5);
                }).catch(error => console.error('Error fetching frame count:', error));
            }
        }
        setInterval(updateFrameCount, 100);

        function updateBMP(){
            fetch('/BMP').then(r => r.json()).then(data => {

                const AMSL = Number(String(data.AMSL).replace(",", "."));
                const AGL = Number(String(data.AGL).replace(",", "."));

                document.getElementById('altAMSL').textContent = `${parseNum(AMSL, 2, 3)} m`;
                document.getElementById('altAGL').textContent = `${parseNum(AGL, 2, 3)} m`;
                document.getElementById('baro').textContent = `${parseNum(data.baro, 2, 4)} hPa`;
                document.getElementById('temp1').textContent = `${parseNum(data.temp, 1, 2)} °C`;
                document.getElementById('altitudeArrowAMSL').style.top = `${250 * (1 - AMSL / 1000)}px`;
                document.getElementById('altitudeArrowAGL').style.top = `${250 * (1 - AGL / 1000)}px`;



            }).catch(error => console.error('Error fetching BMP data:', error));
        }
        setInterval(updateBMP, 100);

        function updateAHT(){
            fetch('/AHT').then(r => r.json()).then(data => {
                updateHumidity(data.hum);
                document.getElementById('temp2').textContent = `${parseNum(data.temp, 1, 2)} °C`;
            }).catch(error => console.error('Error fetching AHT data:', error));
        }
        setInterval(updateAHT, 100);
        function updateHumidity(value) {
            value = Math.max(0, Math.min(100, Number(value)));

            const degrees = value * 1.8; // 0–100 → 0–180°
            
            document.getElementById("humidityFill").style.background =
                `conic-gradient(from -90deg, #4cc9f0 ${degrees}deg, transparent ${degrees}deg)`;

            document.getElementById("hum").textContent =
                `${parseNum(value, 1, 2)} %`;
        }


        function updateMPU(){
            fetch('/MPU').then(r => r.json()).then(data => {
                document.getElementById('rotX').textContent = `${parseNum(data.gyroX, 2, 0)} °/s`;
                document.getElementById('rotY').textContent = `${parseNum(data.gyroY, 2, 0)} °/s`;
                document.getElementById('rotZ').textContent = `${parseNum(data.gyroZ, 2, 0)} °/s`;
                document.getElementById('accelX').textContent = `${parseNum(data.accelX, 2, 0)} m/s²`;
                document.getElementById('accelY').textContent = `${parseNum(data.accelY, 2, 0)} m/s²`;
                document.getElementById('accelZ').textContent = `${parseNum(data.accelZ, 2, 0)} m/s²`;
                document.getElementById('temp3').textContent = `${parseNum(data.temp, 1, 2)} °C`;
            }).catch(error => console.error('Error fetching MPU data:', error));
        }
        setInterval(updateMPU, 100);
    </script>
</body>
</html>
  )rawliteral";

#include <Wire.h>

#include <SD_MMC.h>
#include <sd_defines.h>

#include <esp_camera.h>
// #include <esp32-hal-i2c.h>

#include <WiFi.h>
#include <WiFiAP.h>

#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_AHTX0.h>
#include <Adafruit_MPU6050.h>
#include <ArduinoJson.h>

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#define SDA_PIN 4
#define SCL_PIN 13

AsyncWebServer server(80);

bool recording = false;

bool BMPexists = false;
bool AHTexists = false;
bool MPUexists = false;

float BMPdata[4];
float AHTdata[2];
float MPUdata[7];

float referenceBaro = 1013.25;

// Task splitting

  void frameCaptureTask(void *pvParameters) {
      while (1) {
          if (recording) {
              captureFrame();
          }
          vTaskDelay(pdMS_TO_TICKS(100)); // adjust for FPS
      }
  }

  void sdWriteTask(void *pvParameters) {
      while(1) {
          saveFrames();
          vTaskDelay(pdMS_TO_TICKS(1));  // short delay to yield CPU
      }
  }

  void csvTask(void *pvParameters) {
      while(1) {
          if (recording) {
              saveFrames();
          } // your existing CSV logic
          vTaskDelay(pdMS_TO_TICKS(50));  // adjust logging rate
      }
  }

void setup() {
  Serial.begin(115200);
  disableBOD();
  setupSD();
  setupWiFiAP();
  setupWebUI();
  setupCam();
  setupI2C();
  initBMP();
  initAHT();
  initMPU();
  ramReadout();

  xTaskCreatePinnedToCore(frameCaptureTask, "FrameCapture", 8192, NULL, 3, NULL, 1);
  xTaskCreatePinnedToCore(sdWriteTask, "SDWrite", 8192, NULL, 2, NULL, 1);
  xTaskCreatePinnedToCore(csvTask, "CSVTask", 4096, NULL, 1, NULL, 1);
}

// Video vars
  const char *videoFolder = "/video";
  unsigned long lastFrame = 0;
  const int frameInterval = 100; // ms between frames (~10 FPS)
  #define FRAMES_PER_FOLDER 200

  uint32_t frameNr = 0;
  uint16_t currentFolder = 0;

void loop() {
    // Nothing here, all tasks run in FreeRTOS
}
// Disable brownout detector
  void disableBOD(){
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); // disable brownout detector
  }

// RAM readout
  void ramReadout() {
    sSep(" RAM readout ");
    if (psramFound()) {
      Serial.println("PSRAM detected!");
      Serial.printf("Total PSRAM: %u bytes\n", ESP.getPsramSize());
      Serial.printf("Free PSRAM: %d bytes\n", ESP.getFreePsram());
      Serial.printf("Total heap: %u bytes\n", ESP.getHeapSize());
      Serial.printf("Free heap: %u bytes\n", ESP.getFreeHeap());
    } else {
      Serial.println("No PSRAM detected!");
      Serial.printf("Total heap: %u bytes\n", ESP.getHeapSize());
      Serial.printf("Free heap: %u bytes\n", ESP.getFreeHeap());
    }
    eSep(" RAM readout ");
  }
// Setup SD card and writeout stats
  void setupSD() {
    sSep(" SD init ");
    if (!SD_MMC.begin("/sdcard", true)) {
      Serial.println("Card Mount Failed");
      return;
    } else {
      Serial.println("Card Mount Successful");
    }
    uint8_t cardType = SD_MMC.cardType();

    if (cardType == CARD_NONE) {
      Serial.println("No SD_MMC card attached");
      return;
    }

    Serial.print("SD_MMC Card Type: ");
    if (cardType == CARD_MMC) {
      Serial.println("MMC");
    } else if (cardType == CARD_SD) {
      Serial.println("SDSC");
    } else if (cardType == CARD_SDHC) {
      Serial.println("SDHC");
    } else {
      Serial.println("UNKNOWN");
    }

    uint64_t cardSize = SD_MMC.cardSize() / (1024 * 1024);
    Serial.printf("SD_MMC Card size: %lluMB\n", cardSize);

    uint64_t cardFree = (SD_MMC.totalBytes() - SD_MMC.usedBytes()) / (1024 * 1024);
    Serial.printf("SD_MMC Card free space: %lluMB\n", cardFree);

    if(!SD_MMC.exists("/video")) {
      SD_MMC.mkdir("/video");
      Serial.println("Added /video folder to SD");
    }

    File file = SD_MMC.open("/data.csv", FILE_WRITE);

    if (!file) {
        Serial.println("CSV create failed");
    }
    else {
      Serial.println("CSV created");
    }

    if (file.size() == 0) {
        file.println("time;altAMSL;altAGL;baro;temp1;temp2;temp3;hum;rotx;roty;rotz;accelx;accely;accelz");
    }

    file.close();
    eSep(" SD init ");
  }

// Setup camera
  #define CAMERA_MODEL_AI_THINKER
  #define PWDN_GPIO_NUM 32
  #define RESET_GPIO_NUM -1
  #define XCLK_GPIO_NUM 0
  #define SIOD_GPIO_NUM 26
  #define SIOC_GPIO_NUM 27

  #define Y9_GPIO_NUM 35
  #define Y8_GPIO_NUM 34
  #define Y7_GPIO_NUM 39
  #define Y6_GPIO_NUM 36
  #define Y5_GPIO_NUM 21
  #define Y4_GPIO_NUM 19
  #define Y3_GPIO_NUM 18
  #define Y2_GPIO_NUM 5
  #define VSYNC_GPIO_NUM 25
  #define HREF_GPIO_NUM 23
  #define PCLK_GPIO_NUM 22

  void setupCam() {
    sSep(" CAM init ");
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_SVGA;  // FRAMESIZE_ + QVGA|CIF|VGA|SVGA|XGA|SXGA|UXGA
    config.jpeg_quality = 12;
    config.fb_count = 4;
    config.fb_location = CAMERA_FB_IN_PSRAM;
    Serial.println("Camera configured");
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
      Serial.printf("Camera init failed with error 0x%x\n", err);
      return;
    } else {
      Serial.println("Camera init succeeded");
    }
    // Make sure the folder exists
    if (!SD_MMC.exists(videoFolder)) {
      SD_MMC.mkdir(videoFolder);
    }

    eSep(" CAM init ");
  }

// Start WiFi AP
  const char *SSID = "Telemetry";
  const char *passwd = "Rocket69";
  void setupWiFiAP() {
    sSep(" WiFi init ");
    WiFi.mode(WIFI_AP);
    if (!WiFi.softAP(SSID, passwd)) {
      Serial.println("WiFi AP init failed");
    } else {
      Serial.println("WiFi AP init succeeded");
    }
    Serial.printf("SSID: %s\nPassword: %s\n", SSID, passwd);
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("WiFi AP IP address: ");
    Serial.println(myIP);
    eSep(" WiFi init ");
  }

// Start HTTP server
  void setupWebUI() {
      sSep(" Web UI init ");
      Serial.println("Routes:");

      // Root page
      server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
          rootHandle(request);
      });
      Serial.println("/ - index");

      // Calibrate altitude
      server.on("/calAlt", HTTP_GET, [](AsyncWebServerRequest *request){
          calAltHandle(request);
      });
      Serial.println("/calAlt - calibrate altitude");

      // Start/Stop recording
      server.on("/startRec", HTTP_GET, [](AsyncWebServerRequest *request){
          startRecHandle(request);
      });
      Serial.println("/startRec - start recording");

      server.on("/stopRec", HTTP_GET, [](AsyncWebServerRequest *request){
          stopRecHandle(request);
      });
      Serial.println("/stopRec - stop recording");

      // Frame count
      server.on("/frameCount", HTTP_GET, [](AsyncWebServerRequest *request){
          frameCountHandle(request);
      });

      Serial.println("set routes for updating data");

      // Sensor updates
      server.on("/lastRX", HTTP_GET, [](AsyncWebServerRequest *request){
          lastRXHandle(request);
      });

      server.on("/BMP", HTTP_GET, [](AsyncWebServerRequest *request){
          BMPHandle(request);
      });

      server.on("/AHT", HTTP_GET, [](AsyncWebServerRequest *request){
          AHTHandle(request);
      });

      server.on("/MPU", HTTP_GET, [](AsyncWebServerRequest *request){
          MPUHandle(request);
      });

      // 404 handler
      server.onNotFound([](AsyncWebServerRequest *request){
          notFoundHandle(request);
      });

      server.begin();
      Serial.println("HTTP server started, routes set");
      eSep(" Web UI init ");
  }

// Setup I2C
  void setupI2C(){
    sSep(" I2C init ");
    Wire.begin(SDA_PIN, SCL_PIN, 100000);
    Serial.printf("I2C setup on pins:\nSDA: %d\nSCL: %d\n", SDA_PIN, SCL_PIN);
    eSep(" I2C init ");
  }
// Initialize BMP280
  Adafruit_BMP280 bmp;
  void initBMP(){
    sSep(" BME280 init ");
    if(bmp.begin(0x77)){
      Serial.println("BMP280 initialized successfully");
      BMPexists=true;
    }
    else {
      Serial.println("BMP280 initialization FAILED!");
      BMPexists=false;
    }
    eSep(" BMP280 init ");
  }
// Initialize AHT20
  Adafruit_AHTX0 aht;
  void initAHT(){
    sSep(" AHT20 init ");
    if(aht.begin()){
      Serial.println("AHT20 initialized successfully");
      AHTexists = true;
    }
    else{
      Serial.println("AHT20 initialization FAILED!");
      AHTexists = false;
    }
    eSep(" AHT20 init ");
  }
// Initialize MPU6050
  Adafruit_MPU6050 mpu;
  void initMPU(){
    sSep(" MPU6050 init ");
    if (!mpu.begin()){
      Serial.println("MPU6050 initialization FAILED!");
      MPUexists = false;
    }
    else {
      Serial.println("MPU6050 initialized successfully");
      MPUexists = true;
    }
    eSep(" MPU6050 init ");
  }
// Recording
  #define MAX_QUEUE 4  // number of frames in RAM queue

  camera_fb_t* frameQueue[MAX_QUEUE] = {nullptr};
  int queueStart = 0;
  int queueEnd = 0;

  bool queueFull() {
      return ((queueEnd + 1) % MAX_QUEUE) == queueStart;
  }

  bool queueEmpty() {
      return queueStart == queueEnd;
  }

  void enqueueFrame(camera_fb_t* fb) {
      if(queueFull()) {
          // drop oldest frame if full
          esp_camera_fb_return(frameQueue[queueStart]);
          queueStart = (queueStart + 1) % MAX_QUEUE;
      }
      frameQueue[queueEnd] = fb;
      queueEnd = (queueEnd + 1) % MAX_QUEUE;
  }

  camera_fb_t* dequeueFrame() {
      if(queueEmpty()) return nullptr;
      camera_fb_t* fb = frameQueue[queueStart];
      queueStart = (queueStart + 1) % MAX_QUEUE;
      return fb;
  }
  void captureFrame() {
    camera_fb_t* fb = esp_camera_fb_get();
    if(fb) {
        enqueueFrame(fb);  // store in PSRAM queue
    } else {
        Serial.println("Camera capture failed");
    }
  }

  void saveFrames() {
    camera_fb_t* fb;

    while((fb = dequeueFrame()) != nullptr) {

        // determine folder from frame number
        currentFolder = frameNr / FRAMES_PER_FOLDER;
        ensureFolderExists(currentFolder);

        char path[40];
        sprintf(path,
                "/video/%03d/frame%05lu.jpg",
                currentFolder,
                frameNr);

        File file = SD_MMC.open(path, FILE_WRITE);

        if(file) {
            file.write(fb->buf, fb->len);
            Serial.printf("Wrote file: %d\n", frameNr);
            file.close();
        } else {
            Serial.printf("Failed to open %s\n", path);
        }

        frameNr++;
        esp_camera_fb_return(fb);
    }
  }
  void ensureFolderExists(uint16_t folderNr) {
    char folderPath[20];
    sprintf(folderPath, "/video/%03d", folderNr);

    if(!SD_MMC.exists(folderPath)) {
        if(SD_MMC.mkdir(folderPath)) {
            Serial.printf("Created folder: %s\n", folderPath);
        } else {
            Serial.printf("FAILED to create folder: %s\n", folderPath);
        }
    }
  }

// HTTP handling
  void rootHandle(AsyncWebServerRequest *request) {
    request->send(200, "text/html", index_html);
  }
  void lastRXHandle(AsyncWebServerRequest *request) {
    char ms[21];
    sprintf(ms, "%d", millis());
    request->send(200, "text/plain", ms);
  }
  void BMPHandle(AsyncWebServerRequest *request){
    requestBMP();
    float temp = isnan(BMPdata[0]) ? 0 : BMPdata[0];
    float baro = isnan(BMPdata[1]) ? 0 : BMPdata[1];
    float amsl = isnan(BMPdata[2]) ? 0 : BMPdata[2];
    float agl  = isnan(BMPdata[3]) ? 0 : BMPdata[3];

    JsonDocument doc;

    doc["temp"] = temp;
    doc["baro"] = baro;
    doc["AMSL"] = amsl;
    doc["AGL"] = agl;

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
  }
  void AHTHandle(AsyncWebServerRequest *request){
    requestAHT();

    JsonDocument doc;

    doc["temp"] = AHTdata[0];
    doc["hum"] = AHTdata[1];

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
  }
  void MPUHandle(AsyncWebServerRequest *request){
    requestMPU();
    JsonDocument doc;

    doc["accelX"] = MPUdata[0];
    doc["accelY"] = MPUdata[1];
    doc["accelZ"] = MPUdata[2];
    doc["gyroX"] = MPUdata[3];
    doc["gyroY"] = MPUdata[4];
    doc["gyroZ"] = MPUdata[5];
    doc["temp"] = MPUdata[6];

    String json;
    serializeJson(doc, json);

    request->send(200, "application/json", json);
  }

  void calAltHandle(AsyncWebServerRequest *request) {
    requestBMP();
    referenceBaro = BMPdata[1];
  }
  void startRecHandle(AsyncWebServerRequest *request) {
    recording = true;
    request->send(200, "application/json", "{\"status\":\"ok\",\"recording\":true}");
  }
  void stopRecHandle(AsyncWebServerRequest *request) {
    recording = false;
    request->send(200, "application/json", "{\"status\":\"ok\",\"recording\":false}");
  }
  void frameCountHandle(AsyncWebServerRequest *request){
    char buffer[11];
    snprintf(buffer, sizeof(buffer), "%lu", (unsigned long)frameNr);
    request->send(200, "text/plain", buffer);
  }
  void notFoundHandle(AsyncWebServerRequest *request) {
    String page = "<h1>404 - not found</h1>";
    page += "<p>Go back to <a href=\"/\">homepage</a></p>";
    request->send(404, "text/html", page);
  }
// Sensor readouts
  void requestBMP(){
    if (BMPexists){
      BMPdata[0] = bmp.readTemperature();
      BMPdata[1] = bmp.readPressure()/100;
      BMPdata[2] = bmp.readAltitude(1013.25);
      BMPdata[3] = bmp.readAltitude(referenceBaro);
    }
    else{
      BMPdata[0] = -1;
      BMPdata[1] = -1;
      BMPdata[2] = -1;
      BMPdata[3] = -1;
    }
  }

  void requestAHT(){
    if(AHTexists){
      sensors_event_t humidity, temp;
      aht.getEvent(&humidity,&temp);
      AHTdata[0] = temp.temperature;
      AHTdata[1] = humidity.relative_humidity;
    }
    else{
      AHTdata[0] = -1;
      AHTdata[1] = -1;
    }
  }
  #define PI 3.1415926535897932384626433832795
  void requestMPU(){
    if(MPUexists){
      sensors_event_t a, g, temp;
      mpu.getEvent(&a, &g, &temp);
      MPUdata[0] = a.acceleration.x;
      MPUdata[1] = a.acceleration.y;
      MPUdata[2] = a.acceleration.z;
      MPUdata[3] = g.gyro.x * 180/PI;
      MPUdata[4] = g.gyro.y * 180/PI;
      MPUdata[5] = g.gyro.z * 180/PI;
      MPUdata[6] = temp.temperature;
    }
    else{
      MPUdata[0] = -1;
      MPUdata[1] = -1;
      MPUdata[2] = -1;
      MPUdata[3] = -1;
      MPUdata[4] = -1;
      MPUdata[5] = -1;
      MPUdata[6] = -1;
    }
  }

// Sensor data to CSV
  void sendCSV(){
    File file = SD_MMC.open("/data.csv", FILE_APPEND);

    if (!file) {
        Serial.println("CSV open failed");
        return;
    }
    requestBMP();
    requestAHT();
    requestMPU();

    file.printf("%s;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f\n",
        formatMillis(millis()),
        BMPdata[2],
        BMPdata[3],
        BMPdata[1],
        BMPdata[0],
        AHTdata[0],
        MPUdata[6],
        AHTdata[1],
        MPUdata[3],
        MPUdata[4],
        MPUdata[5],
        MPUdata[0],
        MPUdata[1],
        MPUdata[2]
    );

    file.close();
  }
  String formatMillis(uint32_t ms) {
    uint32_t minutes = ms / 60000;          // 1 min = 60,000 ms
    uint32_t seconds = (ms % 60000) / 1000; // leftover seconds
    uint32_t millisec = ms % 1000;          // leftover milliseconds

    char buf[16];
    sprintf(buf, "%02lu:%02lu:%03lu", minutes, seconds, millisec);
    return String(buf);
  }
// Separator functions for fanciness reasons
  char separator[] = "\n----------------%s----------------\n\n";
  void sSep(const char *s) {
    printf(separator, s);
  }
  void eSep(const char *s) {
    int len = strlen(s);
    printf("\n----------------");
    for (int i = 0; i < len; i++) printf("-");
    printf("----------------\n\n");
  }
