#include <WiFiManager.h>          //https://github.com/kentaylor/WiFiManager 
void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");  
  printf("SDK version:%s\n", system_get_sdk_version());
  size_t cfgAddr = 1024; //(ESP.getFlashChipSize() - 0x4000);
  size_t cfgSize = 1024;//ESP.getFlashChipSize();//(8*1024);
  int last = (ESP.getFlashChipSize()/0x10)/(SPI_FLASH_SEC_SIZE);
  Serial.println(last);
 
  noInterrupts();
  for (int j=0; j<last; j++) {
  Serial.print("j = ");
  Serial.println(j);
     if(spi_flash_erase_sector((j * SPI_FLASH_SEC_SIZE/0x100)) != SPI_FLASH_RESULT_OK) {
        printf("addressFail: %d - 0x%x\n", (j * SPI_FLASH_SEC_SIZE), (j * SPI_FLASH_SEC_SIZE));
      }
      else {
        printf("addressSucceed: %d - 0x%x\n", (j * SPI_FLASH_SEC_SIZE), (j * SPI_FLASH_SEC_SIZE));
      }    
    }
  interrupts(); 
}

void loop() {
}
