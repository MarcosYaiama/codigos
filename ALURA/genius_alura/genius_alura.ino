//Alteracao teste GIT

#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4
#define LED_AZUL 5
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500
#define INDEFINIDO -1

//BOTOES
#define BOTAO_VERDE 8
#define BOTAO_AMARELO 9
#define BOTAO_VERMELHO 10
#define BOTAO_AZUL 11

#define TAMANHO_SEQUENCIA 4

enum Estados{
  PRONTO_PARA_PROX_RODADA, 
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};

    int sequenciaLuzes[TAMANHO_SEQUENCIA];
    
    int rodada = 0;

    int leds_respondidos = 0;
  
  
void setup() {
  // put your setup code here, to run once:
    Serial.begin(9600);
    iniciaPortas();
    iniciaJogo();
}

void iniciaJogo(){
  int jogo = analogRead(A0);
   randomSeed(jogo);
   for(int i = 0;i < TAMANHO_SEQUENCIA;i++){
   
    sequenciaLuzes[i] = sorteiaCor();
                       
   }

}
int sorteiaCor(){
  return random(LED_VERDE, LED_AZUL + 1);
}


void iniciaPortas(){
    pinMode(LED_VERDE,1);
    pinMode(LED_AMARELO,1);
    pinMode(LED_VERMELHO,1);
    pinMode(LED_AZUL,1);

    pinMode(BOTAO_VERDE, INPUT_PULLUP);
    pinMode(BOTAO_AMARELO, INPUT_PULLUP);
    pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
    pinMode(BOTAO_AZUL, INPUT_PULLUP);
}

void loop() {
  switch(estadoAtual()){
    case PRONTO_PARA_PROX_RODADA:
      Serial.println("Pronto para a próxima rodada");
      preparaNovaRodada();
      break;
    case USUARIO_RESPONDENDO:
      Serial.println("Usuário respondendo");
      processaRespostaUsuario();
      break;
    case JOGO_FINALIZADO_SUCESSO:
      Serial.println("Jogo finalizado com sucesso");
      break;    
    case JOGO_FINALIZADO_FALHA:
      Serial.println("Jogo finalizado com falha");
      break;
   }
   delay(500);
 }

 void preparaNovaRodada(){
  rodada++;
  leds_respondidos = 0;
  if(rodada < TAMANHO_SEQUENCIA){
    tocaLedsRodada();
  }
}

void processaRespostaUsuario(){
  leds_respondidos++;
}

int estadoAtual(){
  if(rodada <= TAMANHO_SEQUENCIA){
    if(leds_respondidos == rodada){
       return PRONTO_PARA_PROX_RODADA;
      }else{
        return USUARIO_RESPONDENDO;
      }
  }else{
      return JOGO_FINALIZADO_SUCESSO;
    }
  }


void tocaLedsRodada(){
    for(int i = 0; i < rodada; i++){
    Serial.println(i);
    piscaLed(sequenciaLuzes[i]);
 }
}
int checaRespostaJogador(){

  if(digitalRead(BOTAO_VERDE)){
    return LED_VERDE;
  }
  
  if(digitalRead(BOTAO_AMARELO)){
    return LED_AMARELO;
  }
  
  if(digitalRead(BOTAO_VERMELHO)){
    return LED_VERMELHO;
  }
  
  if(digitalRead(BOTAO_AZUL)){
    return LED_AZUL;
  }
  return INDEFINIDO;
}


void piscaLed(int portaLed){
    digitalWrite(portaLed,1);
    delay(UM_SEGUNDO);
    digitalWrite(portaLed,0);
    delay(UM_SEGUNDO);

  return portaLed;
}

void piscaSequencia1(){
    piscaLed(LED_VERDE);
    piscaLed(LED_AMARELO);
    piscaLed(LED_VERMELHO);
    piscaLed(LED_AZUL);
}

void piscaSequencia2(){
    digitalWrite(LED_VERDE,1);
    digitalWrite(LED_AMARELO,1);
    digitalWrite(LED_VERMELHO,1);
    digitalWrite(LED_AZUL,1);

    delay(UM_SEGUNDO);

    digitalWrite(LED_VERDE,0);
    digitalWrite(LED_AMARELO,0);
    digitalWrite(LED_VERMELHO,0);
    digitalWrite(LED_AZUL,0);

    delay(MEIO_SEGUNDO);
}



bool leBotao(int porta){
  int estado = digitalRead(porta);
  return !estado;
}



