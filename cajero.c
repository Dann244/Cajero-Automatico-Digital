/*
 * =============================================
 *        CAJERO AUTOMATICO DIGITAL
 * =============================================
 * Sistema que simula el funcionamiento basico
 * de un cajero automatico. Permite autenticar
 * usuarios, consultar saldo, depositar, retirar
 * y visualizar el historial de la sesion.
 * =============================================
 */

#include <stdio.h>
#include <string.h>

// Constantes del sistema
#define MAX_USUARIOS     4      // Numero de usuarios registrados
#define MAX_INTENTOS     3      // Intentos maximos de login
#define MONTO_MINIMO     1.00   // Monto minimo para depositar
#define MAX_HISTORIAL    50     // Maximo de transacciones por sesion

/*
 * Estructura: Cuenta
 * Representa a un usuario registrado en el sistema.
 * Campos: nombre de usuario, contrasena y saldo disponible.
 */
typedef struct {
    char usuario[20];
    char contrasena[20];
    float saldo;
} Cuenta;

/*
 * Estructura: Transaccion
 * Representa una operacion realizada durante la sesion.
 * Campos: tipo de operacion, monto y saldo resultante.
 */
typedef struct {
    char tipo[20];
    float monto;
    float saldoResultante;
} Transaccion;

// Usuarios registrados en el sistema con sus saldos iniciales
Cuenta usuarios[MAX_USUARIOS] = {
    {"admin",   "1234",   5000.00},
    {"daniel",  "abcd",   1200.50},
    {"maria",   "pass1",  800.00},
    {"carlos",  "qwerty", 3400.75}
};

// Historial de transacciones de la sesion activa
Transaccion historial[MAX_HISTORIAL];
int totalTransacciones = 0;

/*
 * Funcion: registrarTransaccion
 * Guarda una transaccion en el historial de la sesion.
 * Parametros:
 *   - tipo: "Deposito" o "Retiro"
 *   - monto: cantidad operada
 *   - saldoResultante: saldo despues de la operacion
 */
void registrarTransaccion(char tipo[], float monto, float saldoResultante) {
    if (totalTransacciones < MAX_HISTORIAL) {
        strcpy(historial[totalTransacciones].tipo, tipo);
        historial[totalTransacciones].monto = monto;
        historial[totalTransacciones].saldoResultante = saldoResultante;
        totalTransacciones++;
    }
}

/*
 * Funcion: mostrarHistorial
 * Muestra todas las transacciones realizadas durante la sesion.
 * Si no hay transacciones, informa al usuario.
 */
void mostrarHistorial() {
    printf("\n=================================\n");
    printf("      HISTORIAL DE SESION        \n");
    printf("=================================\n");

    if (totalTransacciones == 0) {
        printf("No se realizaron transacciones en esta sesion.\n");
        return;
    }

    for (int i = 0; i < totalTransacciones; i++) {
        printf("%d. %s - Monto: $%.2f | Saldo resultante: $%.2f\n",
            i + 1,
            historial[i].tipo,
            historial[i].monto,
            historial[i].saldoResultante);
    }
}

/*
 * Funcion: autenticar
 * Solicita usuario y contrasena al usuario.
 * Valida las credenciales contra los usuarios registrados.
 * Permite un maximo de MAX_INTENTOS antes de bloquear el acceso.
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

        // Recorre todos los usuarios buscando coincidencia
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
 * Muestra el nombre de usuario y saldo disponible del usuario autenticado.
 * Parametros: indice del usuario en el array de cuentas.
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
 * Solicita un monto al usuario y lo suma al saldo de su cuenta.
 * Valida que el monto sea mayor o igual al minimo permitido.
 * Registra la operacion en el historial si es exitosa.
 * Parametros: indice del usuario en el array de cuentas.
 */
void depositar(int indice) {
    float monto;
    printf("\n=================================\n");
    printf("            DEPOSITO             \n");
    printf("=================================\n");
    printf("Ingrese el monto a depositar: $");
    scanf("%f", &monto);

    // Validar monto minimo
    if (monto < MONTO_MINIMO) {
        printf("\nError: El monto minimo de deposito es $%.2f\n", MONTO_MINIMO);
        return;
    }

    usuarios[indice].saldo += monto;
    printf("\nDeposito exitoso. Nuevo saldo: $%.2f\n", usuarios[indice].saldo);
    registrarTransaccion("Deposito", monto, usuarios[indice].saldo);
}

/*
 * Funcion: retirar
 * Solicita un monto al usuario y lo resta del saldo de su cuenta.
 * Valida que el monto sea mayor a cero y que haya fondos suficientes.
 * Registra la operacion en el historial si es exitosa.
 * Parametros: indice del usuario en el array de cuentas.
 */
void retirar(int indice) {
    float monto;
    printf("\n=================================\n");
    printf("             RETIRO              \n");
    printf("=================================\n");
    printf("Ingrese el monto a retirar: $");
    scanf("%f", &monto);

    // Validar que el monto sea positivo
    if (monto <= 0) {
        printf("\nError: El monto debe ser mayor a cero.\n");
        return;
    }

    // Validar fondos suficientes
    if (monto > usuarios[indice].saldo) {
        printf("\nError: Fondos insuficientes. Saldo disponible: $%.2f\n", usuarios[indice].saldo);
        return;
    }

    usuarios[indice].saldo -= monto;
    printf("\nRetiro exitoso. Nuevo saldo: $%.2f\n", usuarios[indice].saldo);
    registrarTransaccion("Retiro", monto, usuarios[indice].saldo);
}

/*
 * Funcion: mostrarMenu
 * Imprime en pantalla las opciones disponibles del cajero.
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

/*
 * Funcion principal: main
 * Punto de entrada del programa.
 * Gestiona el flujo general: autenticacion y menu principal.
 */
int main() {
    // Autenticar al usuario antes de permitir el acceso
    int indice = autenticar();

    if (indice == -1) {
        return 0;
    }

    int opcion;

    // Mantener el menu activo hasta que el usuario elija salir
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
                mostrarHistorial();
                printf("\nCerrando sesion. Hasta luego.\n");
                break;
            default:
                printf("\nOpcion invalida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}