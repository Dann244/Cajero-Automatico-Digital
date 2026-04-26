#include <stdio.h>
#include <string.h>

#define MAX_USUARIOS 4
#define MAX_INTENTOS 3
#define MONTO_MINIMO 1.00

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

/*
 * Funcion: consultarSaldo
 * Muestra el saldo actual del usuario autenticado.
 */
void consultarSaldo(int indice) {
    printf("\n=================================\n");
    printf("         CONSULTA DE SALDO       \n");
    printf("=================================\n");
    printf("Usuario: %s\n", usuarios[indice].usuario);
    printf("Saldo disponible: $%.2f\n", usuarios[indice].saldo);
}

/*
 * Funcion: depositar
 * Solicita un monto y lo agrega al saldo del usuario.
 * Valida que el monto sea mayor al minimo permitido.
 */
void depositar(int indice) {
    float monto;
    printf("\n=================================\n");
    printf("            DEPOSITO             \n");
    printf("=================================\n");
    printf("Ingrese el monto a depositar: $");
    scanf("%f", &monto);

    if (monto < MONTO_MINIMO) {
        printf("\nError: El monto minimo de deposito es $%.2f\n", MONTO_MINIMO);
        return;
    }

    usuarios[indice].saldo += monto;
    printf("\nDeposito exitoso. Nuevo saldo: $%.2f\n", usuarios[indice].saldo);
}

/*
 * Funcion: retirar
 * Solicita un monto y lo descuenta del saldo del usuario.
 * Valida que haya fondos suficientes y que el monto sea valido.
 */
void retirar(int indice) {
    float monto;
    printf("\n=================================\n");
    printf("             RETIRO              \n");
    printf("=================================\n");
    printf("Ingrese el monto a retirar: $");
    scanf("%f", &monto);

    if (monto <= 0) {
        printf("\nError: El monto debe ser mayor a cero.\n");
        return;
    }

    if (monto > usuarios[indice].saldo) {
        printf("\nError: Fondos insuficientes. Saldo disponible: $%.2f\n", usuarios[indice].saldo);
        return;
    }

    usuarios[indice].saldo -= monto;
    printf("\nRetiro exitoso. Nuevo saldo: $%.2f\n", usuarios[indice].saldo);
}

/*
 * Funcion: mostrarMenu
 * Muestra las opciones disponibles del cajero.
 */
void mostrarMenu() {
    printf("\n=================================\n");
    printf("            MENU PRINCIPAL       \n");
    printf("=================================\n");
    printf("1. Consultar saldo\n");
    printf("2. Depositar\n");
    printf("3. Retirar\n");
    printf("4. Salir\n");
    printf("=================================\n");
    printf("Seleccione una opcion: ");
}

int main() {
    int indice = autenticar();

    if (indice == -1) {
        return 0;
    }

    int opcion;

    do {
        mostrarMenu();
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                consultarSaldo(indice);
                break;
            case 2:
                depositar(indice);
                break;
            case 3:
                retirar(indice);
                break;
            case 4:
                printf("\nCerrando sesion. Hasta luego.\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}