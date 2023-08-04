// Inclua a biblioteca AccelStepper
#include <AccelStepper.h>
const int bufferSize = 50; // Tamanho máximo da string recebida via serial
char buffer[bufferSize]; // Buffer para armazenar a string recebida
char* commands[10]; // Array para armazenar os comandos individuais (máximo de 10 comandos)



#define DIR_PIN_U 4
#define STEP_PIN_U 3
#define ENABLE_PIN_U 2

AccelStepper stepper_u(AccelStepper::DRIVER, STEP_PIN_U, DIR_PIN_U);

#define DIR_PIN_R 7
#define STEP_PIN_R 6
#define ENABLE_PIN_R 5

AccelStepper stepper_r(AccelStepper::DRIVER, STEP_PIN_R, DIR_PIN_R);

#define DIR_PIN_F 10
#define STEP_PIN_F 9
#define ENABLE_PIN_F 8

AccelStepper stepper_f(AccelStepper::DRIVER, STEP_PIN_F, DIR_PIN_F);

#define DIR_PIN_L 11
#define STEP_PIN_L 12
#define ENABLE_PIN_L 13

AccelStepper stepper_l(AccelStepper::DRIVER, STEP_PIN_L, DIR_PIN_L);

#define DIR_PIN_B A5
#define STEP_PIN_B A4
#define ENABLE_PIN_B A3

AccelStepper stepper_b(AccelStepper::DRIVER, STEP_PIN_B, DIR_PIN_B);

#define DIR_PIN_D A2
#define STEP_PIN_D A1
#define ENABLE_PIN_D A0

AccelStepper stepper_d(AccelStepper::DRIVER, STEP_PIN_D, DIR_PIN_D);

void setup() {
  /*
   * UP
   */
  stepper_u.setMaxSpeed(2000.0);
  stepper_u.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_U, OUTPUT);
  
  /*
   * RIGHT
   */ 
  stepper_r.setMaxSpeed(2000.0);
  stepper_r.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_R, OUTPUT);
  
  /*
   * FRONT
   */
  stepper_f.setMaxSpeed(2000.0);
  stepper_f.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_F, OUTPUT);

  /*
   * LEFT
  */
  stepper_l.setMaxSpeed(2000.0);
  stepper_l.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_L, OUTPUT);

  /*
   * DOWN
   * 
  */
  stepper_d.setMaxSpeed(2000.0);
  stepper_d.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_D, OUTPUT);

  /*
   * BACL
   * 
  */
  stepper_b.setMaxSpeed(2000.0);
  stepper_b.setAcceleration(1000.0);
  pinMode(ENABLE_PIN_B, OUTPUT);

  digitalWrite(ENABLE_PIN_U, HIGH);
  digitalWrite(ENABLE_PIN_R, HIGH);
  digitalWrite(ENABLE_PIN_F, HIGH);
  digitalWrite(ENABLE_PIN_L, HIGH);
  digitalWrite(ENABLE_PIN_D, HIGH);
  digitalWrite(ENABLE_PIN_B, HIGH);
  delay(1000);
  digitalWrite(ENABLE_PIN_U, LOW);
  digitalWrite(ENABLE_PIN_R, LOW);
  digitalWrite(ENABLE_PIN_F, LOW);
  digitalWrite(ENABLE_PIN_L, LOW);
  digitalWrite(ENABLE_PIN_D, LOW);
  digitalWrite(ENABLE_PIN_B, LOW);
  
  // Inicializa a comunicação serial
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) { // Verifica se há dados disponíveis na porta serial
    int bytesRead = Serial.readBytesUntil('\n', buffer, bufferSize); // Lê a string enviada até o caractere de nova linha ('\n') ou até preencher o buffer

    // Adiciona o caractere nulo (\0) ao final da string para torná-la uma string válida
    buffer[bytesRead] = '\0';

    // Processa os comandos
    processCommands(buffer);
  }
  /*// Verifique se há dados disponíveis na porta serial
  if (Serial.available() > 0) {
    // Ler a string enviada pela porta serial
    String command = Serial.readStringUntil('\n');

    // Verifica se o comando recebido é igual à string esperada
    if (command == "F") {
      move_front(true);
    }else if (command == "F'") {
      move_front(false);
    }else if (command == "D") {
      move_down(true);
    }else if (command == "D'") {
      move_down(false);
    }else if (command == "U") {
      move_up(true);
    }else if (command == "U'") {
      move_up(false);
    }else if (command == "B") {
      move_back(true);
    }else if (command == "B'") {
      move_back(false);
    }else if (command == "L") {
      move_left(true);
    }else if (command == "L'") {
      move_left(false);
    }else if (command == "R") {
      move_right(true);
    }else if (command == "R'") {
      move_right(false);
    }else if (command == "disable"){
      digitalWrite(ENABLE_PIN_U, HIGH);
      digitalWrite(ENABLE_PIN_R, HIGH);
      digitalWrite(ENABLE_PIN_F, HIGH);
      digitalWrite(ENABLE_PIN_L, HIGH);
      digitalWrite(ENABLE_PIN_D, HIGH);
      digitalWrite(ENABLE_PIN_B, HIGH);
    }else if (command == "enable"){
      digitalWrite(ENABLE_PIN_U, LOW);
      digitalWrite(ENABLE_PIN_R, LOW);
      digitalWrite(ENABLE_PIN_F, LOW);
      digitalWrite(ENABLE_PIN_L, LOW);
      digitalWrite(ENABLE_PIN_D, LOW);
      digitalWrite(ENABLE_PIN_B, LOW);
    }
  }*/
}
void processCommands(char* commandString) {
  char* token = strtok(commandString, " "); // Primeiro token
  while (token != NULL) {
    if (strcmp(token, "F") == 0) {
      move_front(true);
    }else if (strcmp(token, "F'") == 0) {
      move_front(false);
    }else if (strcmp(token, "D") == 0) {
      move_down(true);
    }else if (strcmp(token, "D'") == 0) {
      move_down(false);
    }else if (strcmp(token, "U") == 0) {
      move_up(true);
    }else if (strcmp(token, "U'") == 0) {
      move_up(false);
    }else if (strcmp(token, "B") == 0) {
      move_back(true);
    }else if (strcmp(token, "B'") == 0) {
      move_back(false);
    }else if (strcmp(token, "L") == 0) {
      move_left(true);
    }else if (strcmp(token, "L'") == 0) {
      move_left(false);
    }else if (strcmp(token, "R") == 0) {
      move_right(true);
    }else if (strcmp(token, "R'") == 0) {
      move_right(false);
    }else if (strcmp(token, "X") == 0) {
      digitalWrite(ENABLE_PIN_U, HIGH);
      digitalWrite(ENABLE_PIN_R, HIGH);
      digitalWrite(ENABLE_PIN_F, HIGH);
      digitalWrite(ENABLE_PIN_L, HIGH);
      digitalWrite(ENABLE_PIN_D, HIGH);
      digitalWrite(ENABLE_PIN_B, HIGH);
    }else if (strcmp(token, "X'") == 0) {
      digitalWrite(ENABLE_PIN_U, LOW);
      digitalWrite(ENABLE_PIN_R, LOW);
      digitalWrite(ENABLE_PIN_F, LOW);
      digitalWrite(ENABLE_PIN_L, LOW);
      digitalWrite(ENABLE_PIN_D, LOW);
      digitalWrite(ENABLE_PIN_B, LOW);
    }
    token = strtok(NULL, " "); // Próximo token
  }
}
void move_up(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_u.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_u.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_u.move(50);
    // Executa a movimentação até a posição desejada
    stepper_u.runToPosition();
  }
}

void move_right(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_r.move(50);
    // Executa a movimentação até a posição desejada
    stepper_r.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_r.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_r.runToPosition();
  }
}

void move_front(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_f.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_f.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_f.move(50);
    // Executa a movimentação até a posição desejada
    stepper_f.runToPosition();
  }
}

void move_left(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_l.move(50);
    // Executa a movimentação até a posição desejada
    stepper_l.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_l.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_l.runToPosition();
  }
}

void move_back(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_b.move(50);
    // Executa a movimentação até a posição desejada
    stepper_b.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_b.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_b.runToPosition();
  }
}

void move_down(bool clock_s){
  if(clock_s == true){
    // Move o motor -50 passos no sentido anti-horário
    stepper_d.move(50);
    // Executa a movimentação até a posição desejada
    stepper_d.runToPosition();
  }else{
    // Move o motor -50 passos no sentido anti-horário
    stepper_d.move(-50);
    // Executa a movimentação até a posição desejada
    stepper_d.runToPosition();
  }
}
