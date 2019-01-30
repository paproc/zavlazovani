//připomínky
////jen testovací verze
//https://github.com/paproc/zavlazovani

//knihovny
#include <SD.h>
#include <SoftwareSerial.h>

//konstanty
const int pinVlhkomer = 1;
const int RX = 1;
const int TX = 1;
const int hranavlh = 1000;
const int pinslunce = 1;
const int vzdalenostini = 1;
const int vzdalenostodcit = 1; 

//proměné
int vlhkost;
long cas;
int slunce;
int vzdalenost


void setup() {
 // jen testovací verze
 Serial.begin(9600);

}


void loop() {
 cas = millis() - 2147483648;
 vlhkost = analogRead(pinVlhkomer);
 slunce = analogRead(pinslunce);
 
}





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

//vypis skrze blutut
void vypis(){
  File myFile;
  myFile=SD.open(konfigurace(),FILE_READ);
  ///zahájí blutut
  SoftwareSerial blutut =  SoftwareSerial(RX,TX);
  blutut.begin(9600);
  delay(500);
  while(myFile.available()){
  blutut.print(myFile.read());
  }
  blutut.end();
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
  int cislo;
  cislo = int(jmeno[4])*100;
  cislo = cislo + int(jmeno[5])*10;
  cislo = cislo + int(jmeno[6]);
  cislo = cislo + 1;
  File konfigurace;
  konfigurace=SD.open("soubor.txt",FILE_WRITE);
    konfigurace.print("log");
    konfigurace.print(cislo);
    konfigurace.print(".txt");
  konfigurace.close();
  }
//vzdálenost od vrchu nádrže v cm
int vzdalenost(){
  digitalWrite(vzdalenostini,HIGH);
  delay(2);
  digitalWrite(vzdalenostini,LOW);
  int odezva = pulseIn(vzdalenostodcit,HIGH);
  return(odezva/58.31);
}