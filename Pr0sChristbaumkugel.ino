#include <Adafruit_NeoPixel.h> 
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h> 
#include <esp_wifi.h>

BLEServer* pServer;
BLEDevice Device;
BLEService* pService;

BLEAdvertising* pAdvertising;
Adafruit_NeoPixel stripe(8, 14, NEO_GRB + NEO_KHZ800);


BLECharacteristic* power;
BLECharacteristic* color;
BLECharacteristic* animation;


BLEService* LEDService;
std::string powerMode;
std::string colorMode;
std::string tempcolorMode;
std::string animationMode;
boolean check;

  class ServerCallbacks : public BLEServerCallbacks {
    void onConnect(BLEServer* pServerCallback) { 
      Serial.println("Client successfully connected"); 
      }
      void onDisconnect(BLEServer* pServerCallback){
        Serial.println("Client disconnected");
      }
    };
  class CharacteristicCallbacks : public BLECharacteristicCallbacks {
          void onWrite(BLECharacteristic* pCharacteristic){
            std::string value = pCharacteristic->getValue();
            if(value.length() > 0){
                if(pCharacteristic == power){
                    power->setValue(value);
                    Serial.print("New Powermode from client: ");
                    Serial.println(value.c_str());
                    
                }else if(pCharacteristic == color){
                    color->setValue(value);
                    Serial.print("New Color from Client: ");
                    Serial.println(value.c_str());
                
                }else if(pCharacteristic == animation){
                  animation->setValue(value);
                  Serial.print("New Animation from Client: ");
                  Serial.println(value.c_str());
                }
            }
            powerMode     = power->getValue();
            colorMode     = color->getValue();
            animationMode = animation->getValue();
            }


    };

    void initBLE(){
      Device.init("PrinceRuperts Christbaumkugel");
      pServer = Device.createServer();

      //create Services
      LEDService = pServer-> createService("5af7b375-4f2a-47c1-9d62-24fa9b1ad1fb"); //

      //create Characteristics
      power            = LEDService-> createCharacteristic("8f8b171d-621a-464f-bfea-72f85c7POWER",BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
      color            = LEDService-> createCharacteristic("ace47220-444e-493e-b352-209d2ecCOLOR",BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);
      animation        = LEDService-> createCharacteristic("8a081e5f-e7b5-4750-a8ff-d15c3611a886",BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_READ);

      //Set Default values
      power->setValue       ("default");
      color->setValue       ("default");
      animation->setValue   ("default");

      powerMode     = power->getValue();
      colorMode     = color->getValue();
      animationMode = animation->getValue();
      
      //set Callbacks
      pServer->setCallbacks     (new ServerCallbacks());  
      power->setCallbacks       (new CharacteristicCallbacks());
      color->setCallbacks       (new CharacteristicCallbacks());
      animation->setCallbacks   (new CharacteristicCallbacks());
    
      //starte Services
      LEDService->start();

      //init Advertising
      pAdvertising = Device.getAdvertising();
      pAdvertising->addServiceUUID("23e9a45f-46c2-4624-8672-41ade86b7001"); 
      pAdvertising->setScanResponse(true);
      pAdvertising->setMinPreferred(0x06);
      pAdvertising->setMinPreferred(0x12);
      Device.startAdvertising();
    };

    

    
void setup() {
  Serial.begin(9600);
  Serial.println("Digitale Christbaumkugel erfolgreich gestartet. Das Pr0 sei mit dir! Starte Tötungsmodus!");
  //deactivate WiFi
  esp_wifi_set_mode(WIFI_MODE_NULL);
  stripe.begin();
  stripe.setBrightness(100);
  stripe.clear();
  initBLE();
  }

void loop() {
    if (powerMode == "on" || powerMode == "1" || powerMode == "an" || powerMode == "On" || powerMode == "An"){
      check = false;
      if (colorMode == "red" || colorMode == "rot" || colorMode == "Red" || colorMode == "Rot") {
          stripe.fill(stripe.Color(255,0,0), 0, 8);
    } else if (colorMode == "orange" || colorMode=="Orange") {
          stripe.fill(stripe.Color(255,128,64), 0, 8);
    } else if (colorMode == "yellow") {
          stripe.fill(stripe.Color(255,255,0), 0, 8);
    } else if (colorMode == "green") {
          stripe.fill(stripe.Color(0,255,0), 0, 8);
    } else if (colorMode == "lime") {
          stripe.fill(stripe.Color(50,250,50), 0, 8);
    } else if (colorMode == "blue") {
          stripe.fill(stripe.Color(0,0,255), 0, 8);
    } else if (colorMode == "purple") {
          stripe.fill(stripe.Color(163,73,164), 0, 8);
    } else if (colorMode == "magenta") {
          stripe.fill(stripe.Color(226,1,116), 0, 8);
    } else if(colorMode == "jump7"){
          uint32_t colors[7] = {stripe.Color(255, 0, 0), stripe.Color(255, 127, 0), stripe.Color(255, 255, 0), stripe.Color(0, 255, 0), stripe.Color(0, 0, 255), stripe.Color(75, 0, 130), stripe.Color(139, 0, 255)};
          for (int c = 0; c <= 6; c++) {
              stripe.fill(colors[c],0,8);
              stripe.show();
              delay(2000);
              }

   }else if (colorMode == "jump"){
          stripe.setBrightness(100);
          stripe.fill(stripe.Color(0,0,255), 0, 8);
          stripe.show();
          delay(1500);
          stripe.fill(stripe.Color(0,255,0), 0, 8);
          stripe.show();
          delay(1500);
          stripe.fill(stripe.Color(255,0,0), 0, 8);
          stripe.show();
          delay(1500);
    }else if(colorMode == "fade"){
          stripe.setBrightness(100);
          int d = 255;
          for (int c = 0; c < 255; c++) {
          stripe.fill(stripe.Color(d--,c,0), 0, 8);
          stripe.show();
          delay(2);
          }
          d = 255;
          for (int c = 0; c < 255; c++) {
          stripe.fill(stripe.Color(0,d--,c), 0, 8);
          stripe.show();
          delay(2);
          }
          d = 255;
          for (int c = 0; c < 255; c++) {
          stripe.fill(stripe.Color(c,0,d--), 0, 8);
          stripe.show();
          delay(2);
          }
    }else {
          stripe.fill(stripe.Color(255,255,255), 0, 8); //white
    }

    if(animationMode == "once"){
          stripe.setBrightness(100);
          stripe.show();
          delay(500);
          stripe.setBrightness(1);
          stripe.show();
          delay(100);
    }  else if(animationMode == "double"){
          stripe.setBrightness(1);
          stripe.show();
          delay(300);
          stripe.setBrightness(100);
          stripe.show();
          delay(100);
          stripe.setBrightness(1);
          stripe.show();
          delay(200);
          stripe.setBrightness(100);
          stripe.show();
          delay(100);
    }   else if(animationMode == "strobo"){
          stripe.setBrightness(1);
          stripe.show();
          delay(30);
          stripe.setBrightness(100);
          stripe.show();
          delay(30);
    }else if(animationMode == "brightfade"){
          for(int i=1; i<255; i++){
            stripe.setBrightness(i);
            stripe.show();
            delay(5);
          }
          for(int i=255; i>0;i--){
            stripe.setBrightness(i);
            stripe.show();
            delay(5);
          }
     }else if(animationMode == "rainbow"){
          uint32_t colors[7] = {stripe.Color(255, 0, 0), stripe.Color(255, 127, 0), stripe.Color(255, 255, 0), stripe.Color(0, 255, 0), stripe.Color(0, 0, 255), stripe.Color(75, 0, 130), stripe.Color(139, 0, 255)};
          stripe.setBrightness(100);
          for (int c = 0; c <= 6; c++) {
              for (int x = 0; x <= 7; x++) {
              stripe.setPixelColor(x, colors[c]);
              }
          stripe.show();
          delay(1000);
          int fadeVal = 0, fadeMax = 100;

  for (uint32_t firstPixelHue = 0; firstPixelHue < 65536;
       firstPixelHue += 256) {

    for (int i = 0; i < stripe.numPixels(); i++) {

      uint32_t pixelHue = firstPixelHue + (i * 65536L / stripe.numPixels());

      stripe.setPixelColor(i, stripe.gamma32(stripe.ColorHSV(pixelHue, 255,
                                           255 * fadeVal / fadeMax)));
    }

    stripe.show();
    delay(5);

    if (firstPixelHue < 65536) {
      if (fadeVal < fadeMax) fadeVal++;
    } else if (firstPixelHue >=  65536) {
      if (fadeVal > 0) fadeVal--;
    } else {
      fadeVal = fadeMax;
    }
  }
          } 
    }else if(animationMode == "rainbow-pure"){
       int fadeVal = 0, fadeMax = 100;

      for (uint32_t firstPixelHue = 0; firstPixelHue < 65536;
       firstPixelHue += 256) {

    for (int i = 0; i < stripe.numPixels(); i++) {

      uint32_t pixelHue = firstPixelHue + (i * 65536L / stripe.numPixels());

      stripe.setPixelColor(i, stripe.gamma32(stripe.ColorHSV(pixelHue, 255,
                                           255 * fadeVal / fadeMax)));
    }

    stripe.show();
    delay(5);
    
      if (firstPixelHue < 65536) {
      if (fadeVal < fadeMax) fadeVal++;
    } else if (firstPixelHue >=  65536) {
      if (fadeVal > 0) fadeVal--;
    } else {
      fadeVal = fadeMax;
    }

  }      
    }else{
          stripe.setBrightness(100);
          stripe.show();
          delay (100);
    }
    }else if(check != true){
      stripe.fill(stripe.Color(0,0,0), 0, 8);
      stripe.show();
      stripe.clear();
      delay(1000);
      check = true;
      } 
}
