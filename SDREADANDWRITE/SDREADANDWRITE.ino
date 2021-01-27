#include <SPI.h>
#include <SD.h>

File myFile; 


//void sdwrite(String);
//void sdread();
void setup()
{
  // Open serial communications and wait for port to open:  
  Serial.begin(9600);
  while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  SD_setup();

  }
void SD_setup()
{
  Serial.print("Initializing SD card...");
  if (!SD.begin(10))
  {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  }
 

void loop() 
{  
  int sensordata=0;
  sensordata+=123;
  sdwrite(sensordata);
  sdread();
  delay(50000);
}
void sdwrite(int sensordata)
{
    myFile = SD.open("test.txt", FILE_WRITE);
    String inputdata = "";
    inputdata+=String((int)sensordata);
  // if the file opened okay, write to it:
  if (myFile) 
  {
    Serial.print("Writing to test.txt...");
    myFile.println(inputdata);
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
int* sdread()
{
  // re-open the file for reading:
  //String outputdata="";
  myFile = SD.open("test.txt");
  int count=0;
  int store[100]={0};
  if (myFile)
  {
    Serial.println("reading test.txt:");

    // read from the file until there's nothing else in it:

    while (myFile.available())
    {      
      //outputdata=myFile.read();
    
      Serial.println(count);
      store[count]=myFile.parseInt();
      Serial.println(store[count]);
      count++;
     

      //outputdata.remove(1);

    }
    // close the file:
    myFile.close();
    //SD.remove("test.txt");
  } 
  else
  {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  //return outputdata;
  return store;
}


