#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 4
#define MAX_INTENTOS 3

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

/*
 * Funcion: autenticar
 * Solicita usuario y contrasena, valida contra los registrados.
 * Permite un maximo de 3 intentos antes de bloquear el acceso.
 * Retorna el indice del usuario autenticado, o -1 si falla.
 */
int autenticar() {
    char usuario[20];
    char contrasena[20];
    int intentos = 0;

    while (intentos < MAX_INTENTOS) {
        printf("\n=================================\n");
        printf("   CAJERO AUTOMATICO DIGITAL     \n");
        printf("=================================\n");
        printf("Usuario: ");
        scanf("%s", usuario);
        printf("Contrasena: ");
        scanf("%s", contrasena);

        for (int i = 0; i < MAX_USUARIOS; i++) {
            if (strcmp(usuarios[i].usuario, usuario) == 0 &&
                strcmp(usuarios[i].contrasena, contrasena) == 0) {
                printf("\nAcceso concedido. Bienvenido, %s.\n", usuario);
                return i;
            }
        }

        intentos++;
        if (intentos < MAX_INTENTOS) {
            printf("\nCredenciales incorrectas. Intentos restantes: %d\n", MAX_INTENTOS - intentos);
        }
    }

    printf("\nAcceso bloqueado. Demasiados intentos fallidos.\n");
    return -1;
}

int main() {
    int indice = autenticar();

    if (indice == -1) {
        return 0;
    }

    printf("\n[Menu (proximamente)]\n");

    return 0;
}