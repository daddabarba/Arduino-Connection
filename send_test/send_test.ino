int data;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    data = Serial.read();
    
    if (data!=NULL && data!=EOF) 
      Serial.write(data);
}
