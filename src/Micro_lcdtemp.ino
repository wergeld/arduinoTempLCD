//www.elegoo.com
//2018.10.25


// include the library code:
#include <LiquidCrystal.h>
#include <dht_nonblocking.h>
#define DHT_SENSOR_TYPE DHT_TYPE_11

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
static const int DHT_SENSOR_PIN = 2;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_SENSOR_TYPE );



/*
 * Initialize the serial port.
 */
void setup( )
{
  Serial.begin( 9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Current Status");
}



/*
 * Poll for a measurement, keeping the state machine alive.  Returns
 * true if a measurement is available.
 */
static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );

  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }

  return( false );
}



/*
 * Main program loop.
 */
void loop( )
{
  float temperature;
  float humidity;
  float converted = 0.0;

  /* Measure temperature and humidity.  If the functions returns
     true, then a measurement is available. */
  if( measure_environment( &temperature, &humidity ) == true )
  {
    //Fahrenheit
    //T(°F) = T(°C) × 9/5 + 32
    converted = ( temperature * 1.8 ) + 32;
    Serial.print( "T = " );
    Serial.print( converted, 1 );
    Serial.print( " deg. F, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  
    // set the cursor to column 0, line 1
    // (note: line 1 is the second row, since counting begins with 0):
    lcd.setCursor(0, 1);
    // print the number of seconds since reset:
    //lcd.print(millis() / 1000);
    lcd.print("T: ");
    lcd.print(converted, 1);
    lcd.print((char)223);
    lcd.print("F H: ");
    lcd.print(humidity, 0);
    lcd.print("%");
    }
}
