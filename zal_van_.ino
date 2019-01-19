//připomínky
////jen testovací verze
////sem příde vypisování
////cislo které jsem přečetl+1

//knihovny
#include <SD.h>


//konstanty
const int pinVlhkomer = 1;


//proměné
int vlhkost;
int hranavlh = 1000;
long cas;


//vrátí aktualní soubor
const char konfigurace(){
  if(!SD.exists("soubor.txt")){
    File a;
    a = SD.open("soubor.txt");
    a.print("log001.txt");
    a.close();
    }
  File konfigurace;
  String soubor;
  soubor = "";
  konfigurace=SD.open("soubor.txt");
  while (konfigurace.available()){
    soubor = soubor + String(konfigurace.read());
    }
  konfigurace.close();
  char output[10];
  soubor.toCharArray(output,10);
  return(output);  
  }


//zápis na SD před výpisem
void zapis(){
  File myFile;
  myFile=SD.open(konfigurace(),FILE_WRITE);
    myFile.print("cas: ");
    myFile.print(cas);
    myFile.print(" vlhkost: ");
    myFile.println(vlhkost);  
  myFile.close();
  }


void vypis(){
  File myFile;
  myFile=SD.open(konfigurace(),FILE_READ);
  //sem příde vypisování
  myFile.close();
  SD.remove("soubor.txt");
  File konfigurace;
  konfigurace=SD.open("soubor.txt",FILE_WRITE);
    konfigurace.print("log");
    konfigurace.print("002");//cislo které jsem přečetl+1
    konfigurace.print(".txt");
  konfigurace.close();
  }









void setup() {
 // jen testovací verze
 Serial.begin(9600);
}


void loop() {


//cas = millis() - 2147483648;
}
