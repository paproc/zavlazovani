//připomínky
////jen testovací verze
////sem příde vypisování
////cislo které jsem přečetl+1
//https://github.com/paproc/zavlazovani
//
//knihovny
#include <SD.h>
#include <SoftwareSerial.h>

//konstanty
const int pinVlhkomer = 1;
const int RX = 1;
const int TX = 1;
const int inthranavlh = 1000;

//proměné
int vlhkost;
long cas;


//vrátí aktualní soubor
char konfigurace(){
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
  ///zahájí blutut
  SoftwareSerial blutut =  SoftwareSerial(RX,TX);
  blutut.begin(9600);
  
  //sem příde vypisování
  myFile.close();
  newlog();
  }

  //noví log
void newlog(){
  String jmenos;
  char jmeno[10];
  jmenos = String(konfigurace());
  jmenos.toCharArray(jmeno,10);
  SD.remove("soubor.txt");
  File konfigurace;
  int cislo;
  cislo = int(jmeno[4])*100;
  cislo = cislo + int(jmeno[5])*10;
  cislo = cislo + int(jmeno[6]);
  cislo = cislo + 1;
  konfigurace=SD.open("soubor.txt",FILE_WRITE);
    konfigurace.print("log");
    konfigurace.print(cislo);
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
