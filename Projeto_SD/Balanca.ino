
long ReadRAW() {
  long long ACC = 0;
  for(short z = 0; z< BUFFL;z++){
    while(!scale.is_ready());
    long reading = scale.read();

    for (short i = 0; i < BUFFL - 1; i++){
      BUFF[i] = BUFF[i+1];
    }
    BUFF[BUFFL - 1] = reading;
  }
  for (short i = 0; i < BUFFL; i++){
    ACC = ACC + BUFF[i];
  }
  return(long) ACC / BUFFL;
}

float ConvertVal(long RAWVAL){
  float unit =(float)PESOBASE / (float)(ZEROVAL - CALIBVAL);

  return (float) (ZEROVAL - RAWVAL) * unit;

}

/*void Calibracao() {
  Serial.print("Leitura da Tara:  ");
  Serial.println(scale.read());  // Aguada o termino de verificação do peso
  Serial.println("Aguarde!");
  Serial.println("Iniciando ...");
  scale.set_scale();             // Utiliza uma escala padrão de verificação

  scale.tare(20);                // Fixa o peso como tara
  Serial.println("Insira o item para Pesar"); 

  Serial.print("Valor da Leitura:  ");
  Serial.println(scale.get_value(10),0);  // Retorna peso descontada a tara
  delay(100);
}*/
 