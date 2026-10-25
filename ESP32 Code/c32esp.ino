
int piniTaste[] = {1, 2, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
const int numarTaste = 12;

const int buzzerPin = 14; 


const int butonOctavaSus = 15;
const int butonOctavaJos = 16;
int deplasareOctava = 0; 


const int encoderCLK = 17;
const int encoderDT  = 18;
int volum = 5; 
int stareUltimaCLK;


int frecventeBase[] = {
  262,
  294, 
  330, 
  349, 
  392, 
  440, 
  494, 
  523, 
  587, 
  659, 
  698, 
  784  
};

void setup() {
  Serial.begin(115200);
  delay(1000);

  pinMode(buzzerPin, OUTPUT);
 
  pinMode(butonOctavaSus, INPUT_PULLUP);
  pinMode(butonOctavaJos, INPUT_PULLUP);


  pinMode(encoderCLK, INPUT);
  pinMode(encoderDT, INPUT);
  stareUltimaCLK = digitalRead(encoderCLK);

  Serial.println("Sintetizatorul a pornit! Pregătit de cântat...");
}

void loop() {
 
  if (digitalRead(butonOctavaSus) == LOW) {
    deplasareOctava = 1; 
    Serial.println("Octavă sus!");
    delay(200); 
  }
  if (digitalRead(butonOctavaJos) == LOW) {
    deplasareOctava = -1; 
    Serial.println("Octavă jos!");
    delay(200);
  }

 
  int stareCurentaCLK = digitalRead(encoderCLK);
  if (stareCurentaCLK != stareUltimaCLK) {
    if (digitalRead(encoderDT) != stareCurentaCLK) {
      volum++; 
      if (volum > 10) volum = 10;
    } else {
      volum--; 
      if (volum < 0) volum = 0;

    }
    Serial.print("Volum setat la: "); Serial.println(volum);
  }
  stareUltimaCLK = stareCurentaCLK;


  
  bool tastaApasata = false;

  for (int i = 0; i < numarTaste; i++) {
  
    int valoareTouch = touchRead(piniTaste[i]);

  
    if (valoareTouch < 40000) { 
    
      int frecventaFinala = frecventeBase[i];
      if (deplasareOctava == 1)  frecventaFinala *= 2;   
      if (deplasareOctava == -1) frecventaFinala /= 2;   
      if (volum > 0) {
        tone(buzzerPin, frecventaFinala);
      } else {
        noTone(buzzerPin);
      }

      Serial.print("Tasta "); Serial.print(i + 1); Serial.println(" apăsată.");
      tastaApasata = true;
      break; 
    }
  }

  if (!tastaApasata) {
    noTone(buzzerPin);
  }

  delay(20);
}