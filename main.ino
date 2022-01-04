    
    #include <ESP8266WebServer.h>
    #include <ESP8266HTTPClient.h>
    #include <ESP8266WiFi.h> 

    //Access point credentials
    const char* ssid = "avi";
    const char* pwd = "12345678";
    WiFiServer server(85);  // open port 80 for server connection
    
    // sensior 1st varible
    int trigPin1 = 5;    //Trig - green Jumper
    int echoPin1 = 4;    //Echo - yellow Jumper
    long duration1, inches1;
    
    // sensior 2nd varible
    int trigPin2 = 14;    //Trig - green Jumper
    int echoPin2 = 12;    //Echo - yellow Jumper
    long duration2, inches2;

    //wifi connection
    void wifi_con()
    {
      Serial.begin(115200); //initialise the serial communication
      delay(10);
      //connecting to wifi
      Serial.println();
      Serial.println();
      Serial.print("Connecting to wifi ");
      Serial.println(ssid);
      WiFi.begin(ssid, pwd);
      //attempt to connect to wifi
      while (WiFi.status() != WL_CONNECTED)
      {
        delay(500);
        Serial.print("."); //progress with dots until the wifi is connected
      }
        Serial.println("");
        //while connected print this
        Serial.println("Wifi connected");
        //starting the server
        Serial.println("Server started.");
        //get the ip address and print it
        Serial.print("This is your ip address: ");
        Serial.print("http://");
        Serial.print(WiFi.localIP());
        Serial.println("/");  
    }
    

    // BY PASS THE LINK USING USING GET METHOD  
    void http_upload_get(String para)
    {
        HTTPClient http;//Declare object of class HTTPClient
        http.begin(para);//Specify request destination
        http.addHeader("Content-Type", "application/x-www-form-urlencoded");//Specify content-type header
        int httpCode = http.GET();//Send the request
        String payload = http.getString();//Get the response payload
        Serial.println(httpCode);//Print HTTP return code
        Serial.println(payload);//Print request response payload
        http.end();  //Close connection   
      
      }
    
void setup() 
{
      wifi_con(); 
}

void loop()
{
    
  
 
//******************************************************** 1st sensior ***************************************************/
  
  //Define 1st inputs and outputs pinMode
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
 // 1st sensor is triggered by a HIGH pulse of 10 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  
  // Read the signal from the sensor: a HIGH pulse whose duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
  pinMode(echoPin1, INPUT);
  duration1 = pulseIn(echoPin1, HIGH);
 
  // convert the time into a distance
int  cm1 = (duration1/2) / 29.1;
      Serial.print(cm1);

  //inches1 = (duration1/2) / 74; 
//******************************************************** 2st sensior ***************************************************/

  //Define 2st inputs and outputs pinMode
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // 2nd sensor is triggered by a HIGH pulse of 10 or more microseconds.Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin2, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
 
  //2nd sensior Read the signal from the sensor: a HIGH pulse whose duration is the time (in microseconds) from the sending of the ping to the reception of its echo off of an object.
  pinMode(echoPin2, INPUT);
  duration2 = pulseIn(echoPin2, HIGH);
 
  // convert the time into a distance
  int cm2 = (duration2/2) / 29.1;
      Serial.print(cm1);

  //inches2 = (duration2/2) / 74; 
  
//******************************************************************************************************************
        
       
        String url ="http://192.168.43.200:85/mcu/DDS/input/reciver.php?value1="+String(cm1)+"&value2="+String(cm2);
        http_upload_get(url);
}
