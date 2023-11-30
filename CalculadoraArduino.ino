#include <IRremote.h>
#include <LiquidCrystal.h>

int countDigits(int num) {
    int count = 0;

    // Handle the case when the number is 0 separately
    if (num == 0) {
        return 1;
    }

    // Count digits using a loop
    while (num != 0) {
        num /= 10;
        count++;
    }

    return count;
}

LiquidCrystal lcd(6, 4, 7, 8, 2, 3);

IRrecv IR(5);
void setup() {
  // put your setup code here, to run once:
  IR.enableIRIn();
  Serial.begin(9600);
  // Set up the number of columns and rows in the LCD
  lcd.begin(16,2);
  
  // Print a message to the LCD

}

void loop() {

  int num = 0;
  int num1 = 0;
  float resultado = 0;

  char operador;

  do{
    if (IR.decode()) {
      switch (IR.decodedIRData.decodedRawData){
        case 0xEA15FF00:
          num = num*10+0;
          break;
        case 0xF30CFF00:
          num = num*10+1;
          break;
        case 0xE718FF00:
          num = num*10+2;
          break;
        case 0xA15EFF00:
          num = num*10+3;
          break;
        case 0xF708FF00:
          num = num*10+4;
          break;
        case 0xE31CFF00:
          num = num*10+5;
          break;
        case 0xA55AFF00:
          num = num*10+6;
          break;
        case 0xBD42FF00:
          num = num*10+7;
          break;
        case 0xAD52FF00:
          num = num*10+8;
          break;
        case 0xB54AFF00:
          num = num*10+9;
          break;

        case 0xBF40FF00:
          operador = '+';
          break;
        case 0xE619FF00:
          operador = '-';
          break;
        case 0xF807FF00:
          operador = '*';
          break;
        case 0xF609FF00:
          operador = '/';
          break;
      }
      lcd.print(num);
      lcd.setCursor(0,0);
      Serial.println(IR.decodedIRData.decodedRawData, HEX);
      Serial.println(num, DEC);
    }
    IR.resume();

  }while(IR.decodedIRData.decodedRawData != 0xBF40FF00 && IR.decodedIRData.decodedRawData != 0xE619FF00 && IR.decodedIRData.decodedRawData != 0xF807FF00 && IR.decodedIRData.decodedRawData != 0xF609FF00);
  
  lcd.setCursor(countDigits(num),0);
  lcd.print(operador);

  while(IR.decodedIRData.decodedRawData !=0xB847FF00){
    if(IR.decode()){  
      switch (IR.decodedIRData.decodedRawData){
        case 0xEA15FF00:
          num1 = num1*10+0;
          break;
        case 0xF30CFF00:
          num1 = num1*10+1;
          break;
        case 0xE718FF00:
          num1 = num1*10+2;
          break;
        case 0xA15EFF00:
          num1 = num1*10+3;
          break;
        case 0xF708FF00:
          num1 = num1*10+4;
          break;
        case 0xE31CFF00:
          num1 = num1*10+5;
          break;
        case 0xA55AFF00:
          num1 = num1*10+6;
          break;
        case 0xBD42FF00:
          num1 = num1*10+7;
          break;
        case 0xAD52FF00:
          num1 = num1*10+8;
          break;
        case 0xB54AFF00:
          num1 = num1*10+9;
      }
      lcd.print(num1);
      lcd.setCursor(countDigits(num)+1,0);
      Serial.println(num1, DEC);
    }
    IR.resume();
  }

  switch (operador){
    case '+':
      resultado = num+num1;
      break;

    case '-':
      resultado = num-num1;
      break;
    
    case '*':
      resultado = num*num1;
      break;

    case '/':
      resultado = (float)num/(float)num1;
      break;
  }
  

  Serial.println(resultado, DEC); // Print the IR code in hexadecimal format
  lcd.setCursor(countDigits(num)+countDigits(num1)+1, 0);
  lcd.print("=");
  lcd.print(resultado);
  delay(5000);
  lcd.clear();
  
}
