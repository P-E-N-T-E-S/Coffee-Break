
void Vizualizador_Calibrado(float Peso,float porcentagem){
  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print("Peso: ");
  lcd.print(Peso);
  lcd.setCursor(0,1);
  lcd.print(porcentagem);
  lcd.print("%");
}