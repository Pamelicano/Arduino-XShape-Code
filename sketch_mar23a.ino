#include <LiquidCrystal_I2C.h>

#include <DHT.h>  

#define DHTPIN 2       // Пин, к которому подключен DHT11
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

int buzzer = 8;        // Пин для буззера
int lightSensor = A0;  // Пин фоторезистора

// Пороги срабатывания
int tempThreshold = 30;     // Температура для активации
int humidityThreshold = 50; // (Можно добавить проверку влажности)
int lightThreshold = 600;   // Яркость для активации (подбирается вручную)

// Ноты "Happy Birthday"
int melody[] = {262, 262, 294, 262, 349, 330,
                262, 262, 294, 262, 392, 349,
                262, 262, 523, 440, 349, 330, 294,
                466, 466, 440, 349, 392, 349};
int durations[] = {4, 8, 4, 4, 4, 2,
                   4, 8, 4, 4, 4, 2,
                   4, 8, 4, 4, 4, 4, 2,
                   4, 8, 4, 4, 4, 2};

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(lightSensor, INPUT);
  dht.begin();
  Serial.begin(9600); // Включаем Serial Monitor
}

void loop() {
  // Читаем показания датчиков
  float temp = dht.readTemperature(); // Температура в °C
  float humidity = dht.readHumidity(); // Влажность в %
  int light = analogRead(lightSensor); // Освещённость (0-1023)

  // Выводим данные в Serial Monitor
  Serial.print("Температура: ");
  Serial.print(temp);
  Serial.print("°C (порог: ");
  Serial.print(tempThreshold);
  Serial.println("°C)");

  Serial.print("Влажность: ");
  Serial.print(humidity);
  Serial.print("% (порог: ");
  Serial.print(humidityThreshold);
  Serial.println("%)");

  Serial.print("Освещенность: ");
  Serial.print(light);
  Serial.print(" (порог: ");
  Serial.print(lightThreshold);
  Serial.println(")");

  Serial.println("--------------------------------");

  // Проверяем условия срабатывания
  if (temp > tempThreshold && light > lightThreshold) {
    playMelody(); // Включаем буззер
  } else {
    noTone(buzzer); // Выключаем звук
  }

  delay(2000); // Обновляем данные раз в 2 секунды
}

// Функция проигрывания мелодии
void playMelody() {
  Serial.println("🔥 ЖАРКО и СВЕТЛО! Включаю Happy Birthday! 🎶");

  for (int i = 0; i < 25; i++) {
    int duration = 1000 / durations[i];
    tone(buzzer, melody[i], duration);
    delay(duration * 1.3);
    noTone(buzzer);
  }

  Serial.println("🎵 Мелодия окончена. Ждём нового срабатывания.");
}

