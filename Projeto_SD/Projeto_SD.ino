#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <HX711.h>

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x3F // Serve para definir o endereço do display.
//balança
#define ZEROVAL 134130 //valor cru para 0 gramas (sem base), a ser redefinido após testar balança
#define CALIBVAL 1267387 //valor cru do peso da base de plástico, a ser redefinido após testar a balança
#define PESOBASE 200 //peso base da calibração em gramas

int distance;
LiquidCrystal_I2C lcd(0x3F,16,2);
Ultrasonic ultrasonic(12, 13);
SoftwareSerial bluetooth(10, 11); // RX, TX
//balança
const int LOADCELL_DOUT_PIN 2;
const int LOADCELL_SCK_PIN 3;
long long BUFF[25] = {0}; //array de 25 posições para formar um buffer rotativo, serve para aumentar a precisão e remover ruidos
byte BUFFL = 0; //retorna o tamanho do buffer de forma interativa
int pct, valCheio, valVazio;

HX711 scale; //objeto para executar funções da biblioteca

long READRAW(); //para ler os valores cru da balança ja aplicando a filtragem
float CONVERTVAL(long RAWVAL) //converte o valor cru em gramas para mostrar
void setup() {
  lcd.init();
  bluetooth.begin(9600);
  Serial.begin(9600);
  //Serial.begin(115200);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //inicializa a biblioteca com os pinos de dado e de clock
  BUFFL = sizeof(BUFF) / sizeof(BUFF[0]) //tamanho do buffer rotativo, calcula o tamanho total em bytes dividido por uma menor parte
}

void loop() {
  Serial.print("RAW: ");
  long RAW = ReadRAW();
  Serial.print(RAW)
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Peso atual:");
  lcd.setCursor(0,1);
  lcd.print(ConvertVal(RAW));
  pct = (ConvertVal(RAW)-valVazio)*100 / valCheio-valVazio;
  lcd.setCursor(1,0);
  lcd.print(pct);
  lcd.setCursor(1,1);
  lcd.print("%");
  delay(1000);

  /*
  distance = ultrasonic.read();
  lcd.print("Distance in CM: ");
  lcd.setCursor(0,1);
  lcd.print(distance);
  delay(1000);*/
}
