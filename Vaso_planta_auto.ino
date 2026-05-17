#include <LiquidCrystal.h>

//Comando para configurar os pinos lcd
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

//Comando para definir os limites da planta (ajustavel conforme a necessidade da planta)
const float TEMP_MAX = 35.0;
const float TEMP_MIN = 15.0;
const int UMID_MIN = 30;
const int LUZ_MIN = 200;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
}
//Comando para configurar o sensor de temperatura
float leituraTemperatura(int pinoTemp){
  int leitura = analogRead(pinoTemp);
  float voltagem = leitura * (5.0 / 1024.0);
  float temperaturaC = (voltagem - 0.5) * 100;
  return temperaturaC; 
}
//Comando para configurar o sensor de luz
int leituraLuz(int pinoLuz){
  return analogRead(pinoLuz); 
}
//Comando para configurar o sensor de umidade
int leituraUmidade(int pinoUmidade){
  int leituraBruta = analogRead(pinoUmidade);
  return map(leituraBruta, 0, 1023, 0, 100); 
}

void loop() {
  float temp = leituraTemperatura(A0);
  int luz = leituraLuz(A1);
  int umid = leituraUmidade(A2);

  //Comando para aparecer na tela lcd a temperatura
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: "); lcd.print(temp, 1); lcd.print("C");
  
  lcd.setCursor(0, 1);
  //Comando para aparecer na tela lcd quando estiver em temperatura elavadas
  if (temp > TEMP_MAX) lcd.print("MUITO QUENTE!");
  else if (temp < TEMP_MIN) lcd.print("MUITO FRIO!");
  else lcd.print("Temp. OK");
  
  delay(3000); 

  //Comando para aparecer na tela lcd a luz e a umidade
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umid:"); lcd.print(umid); lcd.print("% ");
  
  //Comando para aparecer na tela lcd se tiver baixa umidade
  if (umid < UMID_MIN) lcd.print("!!SECO!!");
  else lcd.print(" OK");

  lcd.setCursor(0, 1);
  lcd.print("Luz:"); lcd.print(luz);
  
  //Comando para aparecer na tela lcd quando estiver escuro
  if (luz < LUZ_MIN) lcd.print(" ESCURO");
  else lcd.print(" OK");
  
  delay(3000);

  //Comando para aparec na tela lcd se estiver critico
  if (umid < UMID_MIN || temp > TEMP_MAX) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("   ATENCAO!!   ");
    lcd.setCursor(0, 1);
    if (umid < UMID_MIN) lcd.print("PRECISA DE AGUA");
    else lcd.print("MUDE DE LOCAL");
    delay(3000);
  }
}
