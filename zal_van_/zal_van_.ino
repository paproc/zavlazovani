//připomínky
////napsat "zalij();"
//https://github.com/paproc/zavlazovani

//knihovny
#include <SD.h>
#include <SoftwareSerial.h>

//konstanty
//piny
const int pinvypis = D6;
const int pinVlhkomer = A2;
const int RX = D2;
const int TX = D3;
const int pinslunce = A1;
const int pinvodaini = D4;
const int pinvoda = D5; 
//další
const int hranavlh = 100;
const int dobazavlazovani = 1000;
const int maxslunce = 100;
const long posuncasu = 1800000;


//proměné
int vlhkost;
unsigned long cas;
unsigned long caszalit = 10000;
int slunce;
int vzdalenost;
bool voda = false;

void setup() {
 

}


void loop() {
  cas = millis();
  if((cas > caszalit) & (cas - caszalit < 3600000)){
   digitalWrite(pinvodaini, HIGH);
    if(digitalRead(pinvoda) == HIGH){voda = true;}
    else{voda = false;}
   digitalWrite(pinvodaini, LOW);
   vlhkost = analogRead(pinVlhkomer);
   slunce = analogRead(pinslunce);
   while(vlhkost < hranavlh & slunce < maxslunce & voda == true){                 //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    zalij();
   }
   caszalit = caszalit + posuncasu ;
   zapis();
  }
  if (digitalRead(pinvypis) == HIGH) {
    vypis();
  }
  delay(1000);
}



//zaleje
void zalij(){
 delay(500);                                                                      //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
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
    myFile.print(vlhkost);  
    myFile.print(" voda: ");
    myFile.println(voda);
  myFile.close();
  }

//vypis skrze blutut
void vypis(){
  File myFile;
  myFile=SD.open(konfigurace(),FILE_READ);
  ///zahájí blutut
  SoftwareSerial blutut =  SoftwareSerial(RX,TX);
  blutut.begin(9600);
  while(blutut.available() == 0){delay(100);}
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
