SYSTEM_THREAD(ENABLED);

Servo myservo;
int pos = 0;

SerialLogHandler logHandler;

int feedCount = 0;
int currentLight = 0;

void myHandler(const char *event, const char *data)
{
    if (feedCount < 3)
    {
        if (event = "motion")
        {
            feedMoo("on");
        }
        if (event = "light")
        {
            if ((int)data < 30 and (int)data != 0)
            {
                feedMoo("on");
            }
        }
    }
}

int feedMoo(String command) //5grams dispensed
{
    if (command.equals("on"))
    {
        for(pos = 150; pos>=1; pos-=2) 
        {                                  
            myservo.write(pos);           
            delay(50);                      
        }
        
        feedCount++;
        Particle.publish("Fed successfully - " + String(feedCount) + "/3");
        
    return 0;
    }
    else
    {
        // Unknown option
        return -1;
    }
}

void setup()
{
    myservo.attach(A0);
    Particle.function("feed", feedMoo);
    Particle.subscribe("motion", myHandler);
    Particle.subscribe("light", myHandler);
    Particle.variable("feedCount", feedCount);
    Time.zone(+10);
}

void loop()
{
    int hour = Time.hour(Time.now());
    int minute = Time.minute(Time.now());
    
    // Reset feed count at 7am
    if (hour == 7 and minute == 00)
    {
        int feedCount = 0;
    }
    
    // Reset feed count at 3pm
    if (hour == 15 and minute == 00)
    {
        int feedCount = 0;
    }
    
    // Reset feed count at 11pm
    if (hour == 23 and minute == 00)
    {
        int feedCount = 0;
    }
    
    delay(60000); //check every minute
}
