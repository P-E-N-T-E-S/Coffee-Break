#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <HX711.h>

#define col 16 // Serve para definir o numero de colunas do display utilizado
#define lin  2 // Serve para definir o numero de linhas do display utilizado
#define ende  0x3F // Serve para definir o endereço do display.

LiquidCrystal_I2C lcd(0x3F,16,2);

//balança
long ZEROVAL = 44629;  //valor cru para 0 gramas (sem base), a ser redefinido após testar balança
long CALIBVAL = 131496; //valor cru do peso do peso de calibração, a ser redefinido para testar a balança
float PESOBASE = 220; //peso base da calibração em gramas
float PesoCompleto = 2000;


const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
bool calibrado = false;
long long BUFF[25] = {0}; //array de 25 posições para formar um buffer rotativo, serve para aumentar a precisão e remover ruidos
byte BUFFL = 0; //retorna o tamanho do buffer de forma interativa
HX711 scale; //objeto para executar funções da biblioteca


long ReadRAW(); //para ler os valores cru da balança ja aplicando a filtragem
float ConvertVal(long RAWVAL); //converte o valor cru em gramas para mostrar
void Vizualizador_Calibrado(long RAW, float Peso);

void setup() {
  lcd.init();
  Serial.begin(9600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); //inicializa a biblioteca com os pinos de dado e de clock
  BUFFL = sizeof(BUFF) / sizeof(BUFF[0]); //tamanho do buffer rotativo, calcula o tamanho total em bytes dividido por uma menor parte
}

void loop() {
  long RAW = ReadRAW();
  float Peso = ConvertVal(RAW);
  float porcentagem = map(Peso,0,PesoCompleto,0,100);
  Serial.print("RAW: ");
  Serial.print(RAW);
  Serial.print("   Gramas: ");
  Serial.print(Peso);
  Serial.print("   Procentagem: ");
  Serial.println(porcentagem);
  Vizualizador_Calibrado(Peso,porcentagem);
  
}


