int LED_G = 9 ;
int BUZZER = 11 ;

void setup()
{
  pinMode(  LED_G  ,  OUTPUT  ) ; 
    pinMode(  BUZZER  ,  OUTPUT  ) ;
}

void loop()
{
  //   0  -  255    <--  SALIDA  0 => 0v <-> 255 => 5v
    //analogWrite(  LED_G  , 255 ) ;  5v
    //analogWrite(  LED_G  , 128 ) ;  2.5v
    analogWrite(  LED_G  , 510 ) ;
    analogWrite(  BUZZER  , 200 ) ;
}
