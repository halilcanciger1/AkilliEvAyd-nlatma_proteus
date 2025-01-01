#include <xc.h>

#define _XTAL_FREQ 4000000  // Oscilat�r frekans? tan?m?

// Konfig�rasyon ayarlar?
#pragma config FOSC = XT  // XT Osilat�r
#pragma config WDTE = OFF  // Watchdog Timer devre d???
#pragma config PWRTE = ON  // G�� a�ma zamanlay?c?s? aktif
#pragma config BOREN = ON  // Brown-out Reset aktif
#pragma config LVP = OFF   // D�?�k voltajl? programlama devre d???
#pragma config CPD = OFF   // Veri belle?i korumas? devre d???
#pragma config WRT = OFF   // Flash bellek yazma korumas? devre d???
#pragma config CP = OFF    // Program bellek korumas? devre d???

void main() {
    TRISD = 0x00;  // PORTD �?k?? olarak ayarland? (LED'ler)
    TRISA = 0x02;  // RA1 giri? (PIR sens�r), di?erleri �?k??
    ADCON1 = 0x06; // AN0 pinini analog giri? olarak kullan
    
    int isikSeviyesi;
    int isikEsigi = 512;
    
    
    while(1) {
        ADCON0 = 0x01;  // ADC kanal 0 se�ildi
        __delay_ms(2);
        GO_nDONE = 1;   // ADC d�n�?�m� ba?lat
        while(GO_nDONE);  // D�n�?�m tamamlanana kadar bekle
        isikSeviyesi = ((ADRESH << 8) + ADRESL);  // 10-bit ADC sonucu

        if (isikSeviyesi < isikEsigi || PORTAbits.RA1 == 1) {
            PORTD = 0x07;  // LED'leri yak
        } else {
            PORTD = 0x00;  // LED'leri kapat
        }
    }
}
