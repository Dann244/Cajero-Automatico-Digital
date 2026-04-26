# Cajero Automático Digital

Sistema que simula el funcionamiento básico de un cajero automático, desarrollado en C como proyecto de la materia de Programación.

---

## Funcionalidades

- Autenticación de usuarios con nombre de usuario y contraseña
- Límite de 3 intentos antes de bloquear el acceso
- Consulta de saldo disponible
- Depósito de dinero con monto mínimo de $1.00
- Retiro de dinero con validación de fondos suficientes
- Historial de transacciones al cerrar sesión

---

## Usuarios de prueba

| Usuario | Contraseña | Saldo inicial |
|---------|------------|---------------|
| admin   | 1234       | $5000.00      |
| daniel  | abcd       | $1200.50      |
| maria   | pass1      | $800.00       |
| carlos  | qwerty     | $3400.75      |

---

## Compilación

Con GCC:
```bash
gcc cajero.c -o cajero
```

Con Clang:
```bash
clang cajero.c -o cajero
```

---

## Ejecución

```bash
./cajero
```

---

## Mejoras implementadas

### 1. Límite de intentos de autenticación
**Qué se agregó:** El sistema bloquea el acceso luego de 3 intentos fallidos de login consecutivos.  
**Por qué:** Un cajero real no permite intentos ilimitados de contraseña, ya que representa un riesgo de seguridad.  
**Cómo funciona:** Se usa un contador que incrementa cada vez que las credenciales son incorrectas. Si llega a 3, el sistema termina y muestra un mensaje de bloqueo.

### 2. Monto mínimo de depósito
**Qué se agregó:** No se permite depositar montos menores a $1.00.  
**Por qué:** Evita operaciones sin sentido como depositar cero o valores negativos.  
**Cómo funciona:** Antes de sumar el monto al saldo se valida que sea mayor o igual a la constante `MONTO_MINIMO`.

### 3. Historial de transacciones
**Qué se agregó:** Al cerrar sesión el sistema muestra un resumen de todas las operaciones realizadas.  
**Por qué:** Permite al usuario revisar lo que hizo durante la sesión antes de salir.  
**Cómo funciona:** Cada depósito o retiro exitoso se guarda en un arreglo de structs `Transaccion`. Al seleccionar salir, se recorre ese arreglo y se imprime cada operación con su monto y saldo resultante.