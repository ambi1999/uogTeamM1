int incomingByte = 0;   // for incoming serial data
 
void setup(){
  Serial.begin(9600);
  pinMode(12, OUTPUT);     
  pinMode(8, OUTPUT);     
}
 
 
void loop(){
  // send data only when you receive data:
        if (Serial.available() > 0) {
                //digitalWrite(12, HIGH);   
                // read the incoming byte:
                incomingByte = Serial.read()-'0';
                //incomingByte = Serial.read();
                Serial.println("I received "+ incomingByte);
 
                // say what you got:
                if(incomingByte==1){
                  digitalWrite(12, HIGH);
                }else if(incomingByte==2){
                  digitalWrite(12, LOW);
                }else if(incomingByte==3){
                  digitalWrite(8, HIGH);
                }else if(incomingByte==4){
                  digitalWrite(8, LOW);
                }
        }
}

