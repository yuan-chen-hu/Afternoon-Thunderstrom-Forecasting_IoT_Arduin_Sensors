/////////////////////////////////wifi include 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
//////////////////////////////////wifi define
#define _baudrate   9600
//*-- IoT Information
//#define SSID    "YC's WiFi"
//#define SSID    "Hu iPhone"
#define SSID      "METL-105"
//#define PASS    "AP0916225180"
//#define PASS    "12961296"
#define PASS      "33669821"
#define READAPIKEY  "4C2WA2TPRNPY88C5"  // READ APIKEY for the CHANNEL_ID
#define HOST        "api.thingspeak.com" // ThingSpeak IP Address: 184.106.153.149
#define iftttHOST   "maker.ifttt.com"//"192.33.31.166" // maker.ifttt.com"
#define PORT        80
////////////////////////////////wifi global
String GET = "GET /update?api_key=4C2WA2TPRNPY88C5";
//////////////////////////////// sd include
#include <SPI.h>
#include <SD.h>
//////////////////////sd class
File myFile; 
////////////////////flag operation global


//////////////////thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest
int thetest=600;
/////////////////////////////////////////////thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest


double avg_p[6]={0};
double avg_h[6]={0};
double goal_p[6]={29.0,30.5,31.0,31.5,31.0,31.0};
double goal_h[6]={74.0,70.5,69.0,67.5,67.0,67.5};
double total_p[6]={0};
double total_h[6]={0};
double threshold_p[6]={0};
double threshold_h[6]={0};
double data_p[6]={0};
double data_h[6]={0};
double delta_p[6]={0};
double delta_h[6]={0};
int in_time_section_count[6]={0};
int flag=0;
int deltaflag=0;
double read_p();
double read_h();
int read_the_ideal_flag();
void restart();
int read_the_time;//thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest

/*
    int globaltime=String (createdat);
    int read_the_time=globaltime.substring(11,14).toInt()*100+globaltime.substring(14,17).toInt();
*/
double themax=0;
int themaxi=0;
int themaxiisp=2;

double themin=100;
int themini=0;
int theminiisp=2;

int first_upload_flag=1;

double read_p()
{  
  double temp;//remember to change// read
  //temp=retrieveField(530724,1);
  ///////////////////////////
  //thetest++;
  temp=25+thetest%3;
  ////////////////////////////thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest
  
  
  
  
  double p=exp(20.386-5132/temp)*1.333*read_h();
  //p=((p*10)%1.0)/10;//小數點一位
  Serial.print("read_p");
  Serial.println(p);
  return p;
}
double read_h()
{   

  //thetest++;
  Serial.print("read_h");
  Serial.println(30+thetest%50);
  return 30+thetest%50;//thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest
  //return retrieveField(530724,2);
}
int read_the_ideal_flag()
{
  return 7;//thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest
  //return retrieveField(530724,5);
}

void restart()
{
  for (int i=0;i++;i<=5)
  {
    avg_p[i]={0};
    avg_h[i]={0};
    //goal_p[6]={29.0,30.5,31.0,31.5,31.0,31.0};
    //goal_h[6]={74.0,70.5,69.0,67.5,67.0,67.5};
    total_p[i]={0};
    total_h[i]={0};
    threshold_p[i]={0};
    threshold_h[i]={0};
    data_p[i]={0};
    data_h[i]={0};
    delta_p[i]={0};
    delta_h[i]={0};
    in_time_section_count[i]={0};
    flag=0;
    deltaflag=0;
    /////////////////////////////
    //read_the_time;
    first_upload_flag=1;
    ////////////////////////
    themax=0;
    themaxi=0;
    themaxiisp=2;
    ////////////////////////////
    themin=100;
    themini=0;
    theminiisp=2;
    /////////////////////////////
    first_upload_flag=1;
    //////////////////////////////
    thetest=0;
  }

}

void flag_operation()
{
  for(int i=0;i++;i<=5)
  {
    if (read_the_time>=730+100*i  && read_the_time<830+100*i)
    {
      total_p[i]+=read_p();
      total_h[i]+=read_h();
      in_time_section_count[i]++;
    }
    
  }
  for(int i=0;i++;i<=5)
  {
    avg_p[i]=total_p[i]/in_time_section_count[i];
    avg_h[i]=total_h[i]/in_time_section_count[i];
    data_p[i]=avg_p[i]-goal_p[i];
    data_h[i]=avg_h[i]-goal_h[i];
    delta_p[i]=data_p[i]-threshold_p[i];
    delta_h[i]=data_h[i]-threshold_h[i];
    if (delta_p[i]>=0)
      flag++;
    if  (delta_h[i]>=0)
      flag++;   
  }

  if(read_the_time>=1330&&read_the_time<=2000)
  { 
    if (first_upload_flag==1&&flag>6)
    {           
      update_ifttt();
      first_upload_flag=0;
    }     
    deltaflag=read_the_ideal_flag()-flag;
    if(deltaflag>0&&flag<7)
    {
      for(int i=0;i++;i<deltaflag)
      {
        for(int k=0;k++;k<=5)
        {
          if(delta_p[i]>themax)
          {
            themax=delta_p[i];
            themaxi=i;
            themaxiisp=1;
          }
        if(delta_h[i]>themax)
        {
          themax=delta_h[i];
          themaxi=i;
          themaxiisp=0;
        }   
      }
      if(themaxiisp==1) 
      {
        threshold_p[themaxi]+=delta_p[themaxi];
        delta_p[themaxi]=0;      
      }
      else
      {
        threshold_h[themaxi]+=delta_h[themaxi];
        delta_h[themaxi]=0;      
      } 
    }
  }
    if(deltaflag<0&&flag>6)
  {
    deltaflag*=-1;
    for(int i=0;i++;i<deltaflag)
    {
      for(int k=0;k++;k<=5)
      {
        if(delta_p[i]<themin)
        {
          themin=delta_p[i];
          themini=i;
          theminiisp=1;
        }
        if(delta_h[i]<themin)
        {
          themin=delta_h[i];
          themini=i;
          theminiisp=0;
        }    
      }
      if(theminiisp==1)
      {
        threshold_p[themini]+=delta_p[themini];
        delta_p[themini]=0;     
      } 
      else
      {
        threshold_h[themini]+=delta_h[themini];
        delta_h[themini]=0;         
      } 
    }
    }
  }
  if(read_the_time>=0&&read_the_time<=729)
  {
    restart();
  }   
  
}


float retrieveField( uint32_t channel_id, uint8_t field_id )
{
    float thefield; 
    //Serial.println("retrieve");
    // 設定 ESP8266 作為 Client 端
    WiFiClient client;
    if( !client.connect( HOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return 1;
    }
    else
    {
      Serial.print("clientconnect");
      ////// 使用 GET 取回最後一筆 FIELD_ID 資料 //////
        // 有兩種方式可以取回 Field_id 中的最後一筆資料
        //
        //  NOTE: 
        //      If your channel is public, you don't need a key. 
        //      If your channel is private, you need to generate a read key.
        //
        /*** Method 1: ***/
        //
        //-- Get a Channel Field Feed --//
        // To view a Channel's field feed, send an HTTP GET to 
        //
        //  https://api.thingspeak.com/channels/CHANNEL_ID/fields/FIELD_ID.json
        //
        //  replacing CHANNEL_ID with the ID of your Channel and FIELD_ID with the ID of your field. 
        //
        // Example:
        // https://api.thingspeak.com/channels/18795/fields/1.json?key=READAPIKEY012345&results=1
        //
        // DHT11, field 1: temperature, field 2: humidity
        //----
        String GET = "GET /channels/" + String(channel_id) + "/fields/" + String(field_id) + ".json?key=" +READAPIKEY + "&results=3";
        //----
        String getStr = GET + " HTTP/1.1\r\n";;
        client.print( getStr );
        client.print( "Host: api.thingspeak.com\n" );
        client.print( "Connection: close\r\n\r\n" );        
        delay(1000);        
        // 讀取所有從 ThingSpeak IoT Server 的回應並輸出到串列埠
        String section="HEAD";
        while(client.available())
        {
            String line = client.readStringUntil('\r');

            //** parsing the JSON response here ! **//
            // parse the HTML body
            if(section == "HEAD" )  // HEAD
            {
                Serial.print( "." );
                if( line == "\n" )  // 空白行
                {
                    section = "LENGTH";
                }
            }
            else if( section == "LENGTH" )
            {
                // 這裡可以取回 JSON　字串的長度
                // String content_length = line.substring(1);
                /* 有需要處理的寫程式在這裡 */
                section = "JSON";
            }
            else if( section == "JSON" )    // print the good stuff
            {
                Serial.println( "" );
                section = "END"; 
                int size = line.length();
                String jsonStr = line.substring(1, size - 2);
                size = jsonStr.length() + 1;
                char json[size];
                jsonStr.toCharArray(json, size);
                Serial.println("--Json String --");
                Serial.println( json );
                for(int i = 0; i < size; i++)
                {
                    if(json[i] == '}')
                    {
                        if(json[i+1] == ',')
                        {
                            if(json[i+2]=='{')
                            {
                                json[i+1] = ' ';
                            }
                        }
                    }
                }
                char* feeds = (strstr( json, "\"feeds\"") + 9);
                Serial.println("-- Removed comma inside feeds string --");
                Serial.println(feeds); // 輸出 JSON 字串
                char* field;
                field = strtok( feeds, " " );
                while(field)
                {
                    Serial.println("-- Field --");
                    Serial.println(field);
                    StaticJsonBuffer<200> jsonBuffer;
                    JsonObject& jsonParsed = jsonBuffer.parseObject(field);
                    if (!jsonParsed.success())
                    {
                        Serial.println("parseObject() failed");
                        return 2;
                    }
                    const char *createdat = jsonParsed["created_at"];
          
                    if(field_id==1||field_id==2)
          { 
          String globaltime=String (createdat);//thetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetestthetest
          /////////////////////////////////////////int read_the_time=globaltime.substring(11,14).toInt()*100+globaltime.substring(14,17).toInt();
          }
                                        
                    int entryid = jsonParsed["entry_id"];
                    thefield = jsonParsed["field"+String(field_id)];//!!!!!!!!!!!!!!!!!!換field要改
                    Serial.println("-- Decoding / Parsing --");
                    Serial.print( "Created at: " ); Serial.println( createdat );
                    Serial.print( "Entry id: " ); Serial.println( entryid );
                    Serial.print( "Field 5: " ); Serial.println( thefield, 1 );//!!!!!!!!!!!!!!!!!!!換field要改
                    field = strtok( NULL, " " );
                }               
            }
        }  
        client.stop(); 
    }
    return  thefield;
}
void update_thingspeak()
{
    // 設定 ESP8266 作為 Client 端
    WiFiClient client;
    if( !client.connect( HOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return;
    }
    else
    {
        // 準備上傳到 ThingSpeak IoT Server 的資料
        // 已經預先設定好 ThingSpeak IoT Channel 的欄位
        // field1：溫度；field2：濕度......
        String getStr = GET + "&field1=" + String((double)1) + 
                              "&field2=" + String((double)1) +                                                          
                              " HTTP/1.1\r\n";//from global                              
        client.print( getStr );        
        client.print( "Host: api.thingspeak.com\n" );
        client.print( "Connection: close\r\n\r\n" );                
        delay(100);
        //
        // 處理遠端伺服器回傳的訊息，程式碼可以寫在這裡！
        //
        client.stop();
    }
}
void update_ifttt()
{
    // 設定 ESP8266 作為 Client 端
    WiFiClient client;
    if( !client.connect( iftttHOST, PORT ) )
    {
        Serial.println( "connection failed" );
        return;
    }
    else
    {
    // 準備上傳到 ThingSpeak IoT Server 的資料
    // 已經預先設定好 ThingSpeak IoT Channel 的欄位
    int temp=11;
    String toSend = "GET /trigger/";
    toSend += "sensorfusion";////////////////////////
    toSend += "/with/key/";
    toSend += "bMR45PEmza-MtzR69l46mO";
    toSend += "?value1=";
    toSend += temp;///////////////////////////////
    toSend+="&value2=";
    toSend+=  temp;//////////////////////////////////
    toSend += " HTTP/1.1\r\n";
    toSend += "Host: ";
    toSend += iftttHOST;
    toSend += "\r\n";
    toSend += "Connection: close\r\n\r\n";
    client.print(toSend);                                           
    /*
  delay(1000);
  long interval = 2000;
    unsigned long currentMillis = millis(), previousMillis = millis();
  
    while(!client.available())
    {
  
      if( (currentMillis - previousMillis) > interval )
      {
        Serial.println("Timeout");
        client.stop();     
        return;
      }
      currentMillis = millis();
    }

    while (client.connected())
    {
      if ( client.available() )
    {
    Serial.println("hereherehereherehereherehere");
      char str=client.read();
      Serial.print(str);
    }      
    }  
        client.stop();
    */
  }
  
}
void wifi_setup() 
{
    Serial.begin( _baudrate );
    Serial.println( "ESP8266 Ready!" );
    // Connecting to a WiFi network
    Serial.print("Connect to ");
    Serial.println( SSID );
    WiFi.begin( SSID, PASS );
    // 持續等待並連接到指定的 WiFi SSID
    while( WiFi.status() != WL_CONNECTED )
    {
        delay(500);
        Serial.print( "." );
    }
    Serial.println( "" );
    Serial.println( "WiFi connected" );
    Serial.println( "IP address: " );
    Serial.println( WiFi.localIP());
    Serial.println( "" );
}

void serial_setup()
{
  Serial.begin(9600);
    while (!Serial) 
  {
    ; // wait for serial port to connect. Needed for native USB port only
  }
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
void sdwrite(int sensordata)
{
    myFile = SD.open("thetest.txt", FILE_WRITE);
    String inputdata = "";
    inputdata+=String((int)sensordata);
  // if the file opened okay, write to it:
  if (myFile) 
  {
    Serial.print("Writing to thetest.txt...");
    myFile.println(inputdata);
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
  else 
  {
    // if the file didn't open, print an error:
    Serial.println("error opening thetest.txt");
  }
}
int* sdread()
{
// re-open the file for reading:
//String outputdata="";
myFile = SD.open("thetest.txt");
int count=0;
int store[100]={0};
if (myFile)
{
  Serial.println("reading thetest.txt:");
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
    //SD.remove("thetest.txt");
} 
else
{
// if the file didn't open, print an error:
Serial.println("error opening thetest.txt");
}
//return outputdata;
return store;
}
void setup()
{
  serial_setup();
  wifi_setup();
  //SD_setup();  
}
void loop()
{
  thetest+=5;
  read_the_time=thetest%2400;
  Serial.print("flag:");
  Serial.println(flag);
  Serial.print("deltaflag:");
  Serial.println(deltaflag);
  Serial.print("threshold_p:");
  //for(int i=0;i++;i<=5)
  //{
  Serial.println(threshold_p[0]);
  //}
  Serial.print("threshold_h[]");
  //for(int i=0;i++;i<=5)
  //{
  Serial.println(threshold_h[0]);
  //}
  Serial.print("avg_p");
  Serial.println(avg_h[0]);
  Serial.print("avg_p");
  Serial.println(avg_p[0]); 
  Serial.print("total_p");
  Serial.println(total_p[0]);
  Serial.print("total_h");
  Serial.println(total_h[0]);
  Serial.print("data_p");
  Serial.println(data_p[0]);
  Serial.print("data_h");
  Serial.println(data_h[0]);
  Serial.print("delta_p");
  Serial.println(delta_p[0]);
  Serial.print("delta_h");
  Serial.println(delta_h[0]);
  Serial.print("in_time_section_count");
  Serial.println(in_time_section_count[0]);
  Serial.print("themax");
  Serial.println(themax);
  Serial.print("themaxi");
  Serial.println(themaxi);
  Serial.print("themaxiisp");
  Serial.println(themaxiisp);
  Serial.print("themin");
  Serial.println(themin);
  Serial.print("themini");
  Serial.println(themini);
  Serial.print("theminiisp");
  Serial.println(theminiisp); 
  Serial.print("thetest:");
  Serial.println(thetest);
  Serial.print("read_the_time");
  Serial.println(read_the_time); 
  flag_operation();  
}

