
#define sensorOptico 2 //pino que informa a leitura do sensor optico
#define IN1 5 //IN1 E IN 2 SÃO DO MOTOR A
#define IN2 6
#define IN3 10//IN3 E IN 4 SÃO DO MOTOR B
#define IN4 11
#define TRIG 12
#define ECHO 13
#define LONJURA 900


//MODIFICADO


int valor = 0; //Inteiro que armazena o valor lido pelo sensor optico
int atravessou=0; //atravessou é pra saber se o carrinho cruzou a linha preta
int estado = 0;
int dist = 256000; //  iniciamos em um inteiro grande , pois a condiçao de parada é um inteiro pequeno

void setup() // FUNÇÃO QUE SERVE PARA DECLARAR OS PINOS QUE SERÃO UTILIZADOS NA FUNÇÃO (VOID LOOP)<---
{
   Serial.begin(9600); //inicializando a porta serial
   pinMode(sensorOptico, INPUT); //colocando a porta 2 como a leitura do sensor
   pinMode(IN1, OUTPUT); // primeiro pino do motor A
   pinMode(IN2, OUTPUT); // segundo pino do motor A
   pinMode(IN3, OUTPUT); // primeiro pino do motor B
   pinMode(IN4, OUTPUT); // segundo pino do motor B
   pinMode(TRIG, OUTPUT); // pulso de saida
   pinMode(ECHO, INPUT); //  pulso de entrada
}

// DECLARAÇÃO DAS FUNÇÕES UTILIZADAS NA FUNÇÃO (VOID LOOP) <---
int direita_Esquerda();
int esquerda_Direita();
void ultra();
void desvioInicio();
void esquerda_Volver();
void direita_Volver();
void siga_Em_Frente();
void da_Uma_Paradinha();
void desvioFim();


//FUNÇÃO QUE FICA EM LOOP INFINITO, AQUI É ONDE ACONTECE TODA A AÇÃO PARA O PROJETO, TODAS AS CHAMADAS DAS FUNÇÕES E ETC....S<--
void loop(){ 
    switch(estado){
      case 0:
          estado = direita_Esquerda(); //A variavel (estado) define as condições para o switch, com a mudança de estado, é alterado 
                                       //  então o modo em que o robô precisa se mover, no caso as funções direita_Esquerda, e esquerda_Direita definem o lado 
                                     //    em que o robô está.<--
                                         
          ultra(); //Função que verifica e muda a variavel (dist) que define a distância em que o robô está do obstáculo  <--
          
          if(dist < LONJURA){ //Se (dist) for menos que LONJURA é porque o objetivo está próximo demais  <--
            desvioInicio(0);// desvioInicio é uma função desvia do obstaculo, nesse (case) sabe-se que precisa desviar de acordo com o estado 0 (zero)<--
           }
       break;
       
       case 1:  //Mesma coisa da função no case (0), com a diferença que é adaptada para o case (1)<--
          estado = esquerda_Direita();
          ultra();
          if(dist < LONJURA){
            desvioInicio(1);
          }
       break;
    }
}

//Faz o tratamento para o carrinho ir da direita para a esquerda passando da parte branca do lado direito
//para a parte branca do lado esquerdo com referencial na linha preta

int direita_Esquerda(){
          analogWrite(IN2,85);       //iniciando o carro do lado do motor A, na parte branca, aí ele vai atravessar a parte preta e vai pra parte
          analogWrite(IN1,0);    // branca do lado onde ta o motor B aí ele vai começar a fazer da parte branca do lado do motor B para o lado do motor A
          analogWrite(IN3,0);
          analogWrite(IN4,0);
          valor = digitalRead(sensorOptico);//realizando a leitura no sensor optico
          if (valor == HIGH)
          {
              Serial.write("branco"); //caso o valor seja alto - cor branca
          } 
          else
          {
               Serial.write("preto"); //caso o valor lido seja baixo - cor preta
               atravessou = 1; //nos garante que o carrinho atravessou a linha preta
          }
          if((atravessou == 1) && (digitalRead(sensorOptico))==HIGH){ //caso o carrinho tenha atravessado a linha preta e tenha chegado na parte branca do outro lado ele começa a fazer a transição pelo lado oposto
            atravessou = 0; //pois eu ainda vou atravessar a linha pelo outro lado
            return 1; // muda o estado
          } else {
            return 0;
          }
}

//faz o tratamento para o carrinho ir da Esquerda para a direita passando da parte branca do lado direito para a parte branca do lado esquerdo com referencial na linha preta
int esquerda_Direita(){
          analogWrite(IN2,0); //iniciando o carro do lado branco do motor B indo atravessar a linha preta
          analogWrite(IN1,0); // até chegar no lado branco do motor A
          analogWrite(IN3,90);
          analogWrite(IN4,0);
          valor = digitalRead(sensorOptico);//realizando a leitura no sensor optico
          if (valor == HIGH)
          {
              Serial.write("branco"); //caso o valor seja alto - cor branca
          } 
         else
          {
               Serial.write("preto"); //caso o valor lido seja baixo - cor preta
               atravessou = 1; //checa se o carrinho cruzou a linha preta
          }
          if((atravessou == 1) && (digitalRead(sensorOptico))==HIGH){ //caso o carrinho tenha cruzado a linha preta e tenha chegado do outro lado ele começa do estado zero
            atravessou = 0; //como ele vai começar o estado ele ainda vai atravessar a linha preta,(para o próximo estado)
            return 0;
          } 
          else {
            return 1;
          }
          
}

//faz a medição da distancia
void ultra(){
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  dist  = pulseIn(ECHO, HIGH);
}

void esquerda_Volver(){
            //Vira para a esquerda
     analogWrite(IN2,75);       
     analogWrite(IN1,0);
     analogWrite(IN3,0);
     analogWrite(IN4,0);
}

void direita_Volver(){
            //Vira para a direita
     analogWrite(IN2,0); 
     analogWrite(IN1,0);
     analogWrite(IN3,116);
     analogWrite(IN4,0); 
}

void siga_Em_Frente(){
    analogWrite(IN2,75);       
    analogWrite(IN1,0);
    analogWrite(IN3,106);
    analogWrite(IN4,0);
}
void da_Uma_Paradinha(){
    analogWrite(IN2,255);       
    analogWrite(IN1,255);
    analogWrite(IN3,255);
    analogWrite(IN4,255);
}


//desvio de obstaculo
void desvioInicio(int k){
    da_Uma_Paradinha();
    Serial.println("desvioInicio");
    delay(1000);
    direita_Volver();
    Serial.println("direita_Volver");
    delay(500);      
    da_Uma_Paradinha();
    delay(1000);
    siga_Em_Frente();
    Serial.println("siga_Em_Frente");
    delay(750);
    da_Uma_Paradinha();
    Serial.println("da_Uma_Paradinha");
    delay(1000);
    esquerda_Volver();
    delay(500);
    Serial.println("esquerda_Volver");
    da_Uma_Paradinha();
    delay(500);
    while(digitalRead(sensorOptico) == HIGH){
    siga_Em_Frente();
    Serial.println("siga_Em_Frente");
    }
    da_Uma_Paradinha();
    delay(500);
  //ultra();
 // if(dist < LONJURA){
 //   desvioInicio(k);
 // }else{
//    desvioFim(k);
//  }
}

/*void desvioFim(int k){
  siga_Em_Frente();
  da_Uma_Paradinha();
  esquerda_Volver();
  da_Uma_Paradinha();
  ultra();
  if(dist < LONJURA){
    direita_Volver();
    da_Uma_Paradinha();
    desvioFim(k);
  }else{
    siga_Em_Frente();*/
   // while(digitalRead(sensorOptico) != LOW);
    //atravessou = 1;
  //}

  
//}
 
// analogWrite --> imprimir um sinal pseudo-analogico (nem digital nem analogico)-- PWM-- 0 a 255
// digitalWrite --> imprimir sinal HIGH=(Ligado) ou LOW=(Desliga)
