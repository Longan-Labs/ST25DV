/**
 ******************************************************************************
 * @file    ST25DV_HelloWorld.ino
 * @author  STMicroelectronics
 * @version V1.0.0
 * @date    22 November 2017
 * @brief   Arduino test application for the STMicrolectronics
 *          ST25DV NFC device.
 *          This application makes use of C++ classes obtained from the C
 *          components' drivers.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 STMicroelectronics</center></h2>
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright notice,
 *      this list of conditions and the following disclaimer in the documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */

/**
******************************************************************************
* How to use this sketch
*
* This sketch uses the I2C interface to communicate with the NFC device.
* It writes an NFC tag type URI (Uniform Resource Identifier) and reads this same tag.
* Choose the uri by changing the content of uri_write.
*
* When the NFC module is started and ready, the message "Sytstem init done!" is
* displayed on the monitor window. Next, the tag is written, read and printed on
* the monitor window.
*
* You can also use your smartphone to read/write a tag.
* On Android, download a NFC Tools. Then start the app, check if NFC is activated
* on your smartphone. Put your smartphone near the tag, you can read it. You can
* write a tag with this app.
******************************************************************************
*/

#include "ST25DVSensor.h"

#define DEV_I2C         Wire
ST25DV st25dv(12, -1, &DEV_I2C);

void setup() {
  const char uri_write_message[] = "seeedstudio.com";       // Uri message to write in the tag
  const char uri_write_protocol[] = URI_ID_0x01_STRING; // Uri protocol to write in the tag
  String uri_write = String(uri_write_protocol) + String(uri_write_message);
  String uri_read;

  // Initialize serial for output.
  Serial.begin(115200);

  // The wire instance used can be omitted in case you use default Wire instance
  if(st25dv.begin() == 0) {
    Serial.println("System Init done!");
  } else {
    Serial.println("System Init failed!");
    while(1);
  }

  if(st25dv.writeURI(uri_write_protocol, uri_write_message, "")) {
    Serial.println("Write failed!");
    while(1);
  }

  delay(100);
  
  if(st25dv.readURI(&uri_read)) {
    Serial.println("Read failed!");
    while(1);
  }

  Serial.println(uri_read.c_str());

  if(strcmp(uri_read.c_str(), uri_write.c_str()) == 0) {
    Serial.println("Successfully written and read!");
  } else {
    Serial.println("Read bad string!");
  }
}

void loop() {  
  //empty loop
} 
