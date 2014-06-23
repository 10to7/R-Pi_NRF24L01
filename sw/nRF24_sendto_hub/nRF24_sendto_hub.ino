#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define RF_SETUP 0x17
// Set up nRF24L01 radio on SPI pin for CE, CSN
RF24 radio(9,10);

// For best performance, use P1-P5 for writing and Pipe0 for reading as per the hub setting
// Below is the settings from the hub/receiver listening to P0 to P5
//const uint64_t pipes[6] = { 0x7365727631LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4LL, 0xF0F0F0F0E5LL };
// Example below using pipe5 for writing
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, 0x7365727631LL };

// const uint64_t pipes[2] = { 0xF0F0F0F0E2LL, 0xF0F0F0F0E2LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0E3LL, 0xF0F0F0F0E3LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0E4LL, 0xF0F0F0F0E4LL };
// const uint64_t pipes[2] = { 0xF0F0F0F0E5LL, 0xF0F0F0F0E5LL };
// Pipe0 is F0F0F0F0D2 ( same as reading pipe )

char receivePayload[32];
uint8_t counter=0;

void setup(void)
{

  
  Serial.begin(57600);
  
  printf_begin();
  printf("Sending nodeID & 4 sensor data\n\r");

  radio.begin();

  // Enable this seems to work better
  radio.enableDynamicPayloads();

  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(76);
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]); 
  radio.openReadingPipe(1,pipes[1]); 

      
  // Send only, ignore listening mode
  //radio.startListening();

  // Dump the configuration of the rf unit for debugging
  radio.printDetails(); 
  delay(1000); 
}

void loop(void)
{
  uint8_t Data1,Data2,Data3,Data4 = 0;
  char temp[5];
  bool timeout=0;

  // Get the last two Bytes as node-id
  uint16_t nodeID = pipes[0] & 0xff;

  // Use the last 2 pipes address as nodeID  
  // sprintf(nodeID,"%X",pipes[0]);
  
  char outBuffer[32]=""; // Clear the outBuffer before every loop
  unsigned long send_time, rtt = 0;
    
    // Get readings from sensors, change codes below to read sensors
    Data1 = counter++;
    Data2 = analogRead(0);
    Data3 = analogRead(1);
    Data4 = random(0,1000);
    
    if ( counter > 999 ) counter = 0;

    // Append the hex nodeID to the beginning of the payload    
    sprintf(outBuffer,"%2X",nodeID);
    
    strcat(outBuffer,",");
    
    // Convert int to strings and append with zeros if number smaller than 3 digits
    // 000 to 999
    
    sprintf(temp,"%03d",Data1);  
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");
    
    sprintf(temp,"%04d",Data2);
    strcat(outBuffer,temp);
    
    strcat(outBuffer,",");

    sprintf(temp,"%04d",Data3);
    strcat(outBuffer,temp);
   
    strcat(outBuffer,",");
   
    sprintf(temp,"%03d",Data4);
    strcat(outBuffer,temp); 
            
    printf("outBuffer: %s len: %d\n\r",outBuffer, strlen(outBuffer));

    send_time = millis();
    
    // Stop listening and write to radio 
    radio.stopListening();
    
    // Send to hub
    if ( radio.write( outBuffer, strlen(outBuffer)) ) {
       printf("Send successful\n\r"); 
    }
    else {
       printf("Send failed\n\r");
    }
  
    radio.startListening();
    delay(20);  

  while ( radio.available() && !timeout ) {

         uint8_t len = radio.getDynamicPayloadSize();
         radio.read( receivePayload, len); 
         
         receivePayload[len] = 0;
         printf("inBuffer:  %s\n\r",receivePayload);
        
         // Compare receive payload with outBuffer        
         if ( ! strcmp(outBuffer, receivePayload) ) {
             rtt = millis() - send_time;

             printf("inBuffer --> rtt: %i \n\r",rtt);            

             // Turn on buzzer to Pin 2
             digitalWrite(2,HIGH);

         }       
    
    // Check for timeout and exit the while loop
    if ( millis() - send_time > radio.getMaxTimeout() ) {
         Serial.println("Timeout!!!");
         timeout = 1;
     }          
      
     delay(10);
   } // End while  
     
    delay(250);
    digitalWrite(2,LOW); // Off the buzzer
    
  }





