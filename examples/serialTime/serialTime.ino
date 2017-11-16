/**
 * Ejemplo que muestra la hora y fecha obtenida via NTP
 */
#include <ESP8266WiFi.h>
#include <Time.h>
#include <NTP.h>

NTP ntp;

int hora = -1;
int minuto, segundo;
void setup(){
  Serial.begin(9600);
  ntp.begin();
  Serial.println("Conectando");
  WiFi.begin("sindormir.net","espaciomiscela");

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

 Serial.println ( "" );
 Serial.print ( "IP address: " );
 Serial.println ( WiFi.localIP() );
 delay(500);

  while ( ntp.onTime() == -1 ){
    Serial.println("Error al conectar con el servidor NTP, reintentando");
    delay(500);
  }
  
  hora = ntp.get_hour();
  minuto = ntp.get_minutes();
  segundo = ntp.get_secons();

  
  
  Serial.print("Hora del NTP: ");
  Serial.println(String(hora)+":"+String(minuto)+":"+String(segundo));

  //Ponemos en hora la libreria time
  setTime(hora,minuto,segundo,ntp.get_day(),ntp.get_month(),ntp.get_year());

}

void loop(){
  time_t t = now();  

 Serial.print(hour(t)+ntp.ajusteHorario(day(t),month(t),year(t), hour(t), minute(t),second(t)));
 Serial.print(":");
 Serial.print(minute(t));
 Serial.print(":");
 Serial.println(second(t));
 
 Serial.print(day(t));
 Serial.print("/");
 Serial.print(month(t));
 Serial.print("/");
 Serial.print(year(t));
 Serial.println("");
 
  delay(1000);
}
