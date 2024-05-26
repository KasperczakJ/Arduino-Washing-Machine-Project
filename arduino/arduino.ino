#include <LiquidCrystal_I2C.h>
#include <Encoder.h>

//zdefiniowanie pinow
#define out1 4
#define out2 5
#define out3 2
#define out4 3
#define pwm_1 6 

#define enc_B 11
#define enc_A 12

#define button1 15
#define button2 16
#define button3 17

#define led1 7
#define led2 8
#define led3 9

//zmiennne enkodera
long oldPosition  = -999;
long newPosition;
int menuPosition = 0;

//zmienne ustawien
int temperatura = 0;
int czas = 0;
int obroty = 0;

//zmienne przyciskow
int buttonState1;
int lastButtonState1;
int buttonState2;
int lastButtonState2;
int buttonState3;
int lastButtonState3;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

//zmiennne czasu
unsigned long previousMillis = 0;
const int timeInterval = 1000;

//flagi
bool fPranie = false;
bool fWirowanie = false;
bool fStart = false;

//LCD
LiquidCrystal_I2C lcd(0x27, 20, 4);
Encoder myEnc(enc_A, enc_B);

void setup() {
  //inicjalizacja seriala
  Serial.begin(115200);
  Serial.println("init");

  //ustawienia pinow
  pinMode(out1, OUTPUT);
  pinMode(out2, OUTPUT);
  pinMode(out3, OUTPUT);
  pinMode(out4, OUTPUT);
  pinMode(pwm_1, OUTPUT);
  
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);

  //stany pinow
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);
  digitalWrite(pwm_1, LOW);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);

  //inicjalizacja LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  //init message
  lcd.setCursor(0, 0);
  lcd.print("Init");
  digitalWrite(led1,HIGH);
  delay(100);
  digitalWrite(led1,LOW);
  delay(100);
  digitalWrite(led2,HIGH);
  delay(100);
  digitalWrite(led2,LOW);
  delay(100);
  digitalWrite(led3,HIGH);
  delay(100);
  digitalWrite(led3,LOW); 
  delay(1000); 
}

void loop() {
  newPosition = myEnc.read();
  if (newPosition != oldPosition) {
      menuPosition = newPosition;
      displayMenu();
      oldPosition = newPosition;
      Serial.println(newPosition);
      if(newPosition >= 80){
        myEnc.write(0);
      }
      if(newPosition <= (-4)){
        myEnc.write(76);
      }     
  }

  handleRotationsButton();
  handleTemperatureButton();
  handleStartButton();

}


//---------Wyswietlenie menu--------------
void displayMenu(){
  lcd.clear();
  switch(menuPosition){
    case 0:
      digitalWrite(led1,LOW);
      digitalWrite(led2,LOW);
      digitalWrite(led3,LOW);
      lcd.print("Wybierz program");
      fStart = false;
      break;
    case 4:
    case 8:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 60;
      obroty = 800;
      czas = 60;
      displayMode();
      lcd.print("Bawelna");  
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 12:
    case 16:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 30;
      obroty = 400;
      czas = 120;
      displayMode();
      lcd.print("Delikatne"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 20:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 60;
      obroty = 1200;
      czas = 30;
      displayMode();
      lcd.print("Szybkie");
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break; 
    case 24:
    case 28:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 90;
      obroty = 1200;
      czas = 120;
      displayMode();
      lcd.print("Syntetyczne");
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 32:
    case 36:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 60;
      obroty = 1200;
      czas = 60;
      displayMode();
      lcd.print("Mieszane");
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 40:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 30;
      obroty = 800;
      czas = 60;
      displayMode();
      lcd.print("Ciemne"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 44:
    case 48:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 30;
      obroty = 800;
      czas = 60;
      displayMode(); 
      lcd.print("Jasne"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 52:
    case 56:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 60;
      obroty = 1200;
      czas = 60;
      displayMode();
      lcd.print("Jeansy"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 60:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 60;
      obroty = 800;
      czas = 30;
      displayMode();
      lcd.print("Sportowe"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = true;
      break;
    case 64:
    case 68:
      digitalWrite(led1,HIGH);
      digitalWrite(led2,LOW);
      digitalWrite(led3,HIGH);
      temperatura = 0;
      obroty = 400;
      czas = 10;
      displayMode();
      lcd.print("Wirowanie"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = false;
      fWirowanie = true;
      break;
    case 72:
    case 76:
      digitalWrite(led1,LOW);
      digitalWrite(led2,HIGH);
      digitalWrite(led3,HIGH);
      temperatura = 30;
      obroty = 0;
      czas = 30;
      displayMode();
      lcd.print("Plukanie"); 
      displayTemperature(temperatura);
      displayRotations(obroty);
      displayTime(czas);
      fStart = true;
      fPranie = true;
      fWirowanie = false;
      break;
  }             
}

//wyswietlenie tekstu tryb
void displayMode() {
  lcd.setCursor(0, 0);
  lcd.print("Tryb:"); 
}

//wyswietlenie tekstu temperatury
void displayTemperature(int temp) {
  lcd.setCursor(0, 1);
  lcd.print("Temperatura:");
  lcd.print(temp);
  lcd.write(byte(223));
}

//wyswietlenie tekstu obrotow
void displayRotations(int rot) {
  lcd.setCursor(7, 2);
  lcd.print("    ");
  lcd.setCursor(0, 2);
  lcd.print("Obroty:");
  lcd.print(obroty);
}

//wyswietlenie tekstu czasu
void displayTime(int tim) {
  lcd.setCursor(0, 3);
  lcd.print("Czas:");
  lcd.print(czas);
  lcd.print("min");
}

//obsluga przycisku obrotow
void handleRotationsButton() {
  int reading = digitalRead(button1);

  if (reading != lastButtonState1) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState1) {
      buttonState1 = reading;

      if (buttonState1 == LOW) {
        if (obroty == 400) {
          obroty = 800;
          displayRotations(obroty);
        } else if (obroty == 800) {
          obroty = 1200;
          displayRotations(obroty);
        } else if (obroty == 1200) {
          obroty = 400;
          displayRotations(obroty);
        }
        if (digitalRead(led1) == HIGH) {
          digitalWrite(led1, LOW);
          delay(100);
          digitalWrite(led1, HIGH);
        }
      }
    }
  }

  lastButtonState1 = reading;
}

//obsluga przycisku temperatury
void handleTemperatureButton() {
  int reading = digitalRead(button2);

  if (reading != lastButtonState2) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState2) {
      buttonState2 = reading;

      if (buttonState2 == LOW) {
        if (temperatura == 30) {
          temperatura = 60;
          displayTemperature(temperatura);
        } else if (temperatura == 60) {
          temperatura = 90;
          displayTemperature(temperatura);
        } else if (temperatura == 90) {
          temperatura = 30;
          displayTemperature(temperatura);
        }
        if (digitalRead(led2) == HIGH) {
          digitalWrite(led2, LOW);
          delay(100);
          digitalWrite(led2, HIGH);
        }
      }
    }
  }

  lastButtonState2 = reading;
}

//obsluga przycisku startu
void handleStartButton() {
  int reading = digitalRead(button3);

  if (reading != lastButtonState3) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState3) {
      buttonState3 = reading;

      if(fStart == true){
        if (buttonState3 == LOW) {
          startWashing();
          fStart = false;
          if (digitalRead(led3) == HIGH) {
            digitalWrite(led3, LOW);
            delay(100);
            digitalWrite(led3, HIGH);
          }
        }
      }
    }
  }

  lastButtonState3 = reading;
}

//-----------------Pranie-------------
void startWashing() {
  digitalWrite(led1,LOW);
  digitalWrite(led2,LOW);
  digitalWrite(led3,LOW);  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Rozpoczeto pranie");
  delay(1000);
  if(fPranie == true)
    pump();
    pranie();
    pump();
  if(fWirowanie == true)
    wirowanie();
  lcd.setCursor(0, 0);
  lcd.print("KONIEC PRANIA");

}

//obsluga pompy - start
void start_pompa(){
  Serial.println("pompa start");
  digitalWrite(out1, LOW);
  digitalWrite(out2, HIGH); 
}

//obsluga pompy - stop
void stop_pompa(){
  Serial.println("pompa stop");
  digitalWrite(out1, LOW);
  digitalWrite(out2, LOW);  
}

//obsluga silnika - obroty w prawo
void lewo_silnik(){
  Serial.println("silnik lewo");
  digitalWrite(out3, LOW);
  digitalWrite(out4, HIGH); 
}

//obsluga silnika - obroty w lewo
void prawo_silnik(){
  Serial.println("silnik prawo");
  digitalWrite(out3, HIGH);
  digitalWrite(out4, LOW);  
}

//obsluga silnika - stop
void stop_silnik(){
  Serial.println("silnik stop");
  digitalWrite(out3, LOW);
  digitalWrite(out4, LOW);  
}

//pompowanie wody
void pump() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pompowanie wody");
  start_pompa();
  countdown(3);
  stop_pompa();
  lcd.setCursor(0, 1);
  lcd.print(0);
  delay(1000);
  lcd.clear();
}

//pranie
void pranie(){
  analogWrite(pwm_1, 80);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Pranie");
  prawo_silnik();
  countdown(czas);
  stop_silnik();
  lcd.setCursor(0, 1);
  lcd.print(0);
  delay(1000);
  lcd.clear();
}

//wirowanie
void wirowanie(){
  if(obroty == 400){
    analogWrite(pwm_1, 120);
    Serial.println("400");}
    else if(obroty == 800){
    analogWrite(pwm_1, 150);
    Serial.println("800");}
    else if(obroty == 1200){
    analogWrite(pwm_1, 180);
    Serial.println("1200");}
    
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Wirowanie");
  lewo_silnik();
  countdown(10);
  stop_silnik();
  lcd.setCursor(0, 1);
  lcd.print(0);
  delay(1000);
  lcd.clear();
}

//cas prania
void countdown(int startValue) {  
  while (startValue >= 0) {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= timeInterval) {

      lcd.setCursor(0, 1);
      lcd.print("   ");
      lcd.setCursor(0, 1);
      lcd.print(startValue);

      previousMillis = currentMillis;
      startValue--;
    }
  }
}
