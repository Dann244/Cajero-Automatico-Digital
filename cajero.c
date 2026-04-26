#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 4
#define MAX_HISTORIAL 50

// Estructura que representa una cuenta bancaria
typedef struct {
    char usuario[20];
    char contrasena[20];
    float saldo;
} Cuenta;

// Usuarios registrados en el sistema con sus saldos iniciales
Cuenta usuarios[MAX_USUARIOS] = {
    {"admin",   "1234",   5000.00},
    {"daniel",  "abcd",   1200.50},
    {"maria",   "pass1",  800.00},
    {"carlos",  "qwerty", 3400.75}
};

int main() {
    printf("=================================\n");
    printf("   CAJERO AUTOMATICO DIGITAL     \n");
    printf("=================================\n");

    return 0;
}