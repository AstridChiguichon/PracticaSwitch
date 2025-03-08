#include <iostream>
#include <vector>
#include <string>

using namespace std;

class CuentaBancaria {
private:
    double saldo;
    bool activa;
    int intentosFallidos;
    bool operacionReciente;
    int ciclosInactivos;

public:
    CuentaBancaria(double _saldo = 0) : saldo(_saldo), activa(true), intentosFallidos(0), operacionReciente(true), ciclosInactivos(0) {}

    void depositar(double monto) {
        if (!activa) {
            cout << "Cuenta inactiva. No se puede depositar." << endl;
            return;
        }
        saldo += monto;
        operacionReciente = true;
        ciclosInactivos = 0;
        cout << "Depósito exitoso, saldo actual: " << saldo << endl;
    }

    void retirar(double monto) {
        if (!activa) {
            cout << "Cuenta inactiva. No se puede retirar." << endl;
            return;
        }
        if (monto > saldo) {
            intentosFallidos++;
            cout << "Fondos insuficientes. Intentos fallidos: " << intentosFallidos << endl;
            if (intentosFallidos >= 3) {
                activa = false;
                cout << "Cuenta bloqueada por demasiados intentos fallidos." << endl;
            }
            return;
        }
        saldo -= monto;
        intentosFallidos = 0;
        operacionReciente = true;
        ciclosInactivos = 0;
        cout << "Retiro exitoso, saldo actual: " << saldo << endl;
        if (saldo < 100) {
            cout << "Advertencia: Su saldo es bajo." << endl;
        }
    }

    void mostrarSaldo() const {
        cout << "Su saldo es: " << saldo << endl;
    }

    void aplicarPenalizacion() {
        if (!operacionReciente && activa) {
            ciclosInactivos++; 
            if (ciclosInactivos >= 3) { 
                saldo -= 50;
                cout << "Penalización por inactividad aplicada. Nuevo saldo: " << saldo << endl;
                ciclosInactivos = 0; 
            }
        }
        operacionReciente = false;
    }

    bool isActive() const {
        return activa;
    }
};

class SistemaBancario {
private:
    vector<CuentaBancaria> cuentas;

public:
    SistemaBancario(int numCuentas) {
        for (int i = 0; i < numCuentas; i++) {
            cuentas.emplace_back(1000);
        }
    }

    void realizarOperacion(int numCuenta, int opcion, double monto) {
        if (numCuenta < 1 || numCuenta > cuentas.size()) {
            cout << "Número de cuenta inválido." << endl;
            return;
        }

        CuentaBancaria& cuenta = cuentas[numCuenta - 1];

        switch (opcion) {
        case 1:
            cuenta.depositar(monto);
            break;
        case 2:
            cuenta.retirar(monto);
            break;
        case 3:
            cuenta.mostrarSaldo();
            break;
        case 4:
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opción no válida." << endl;
            break;
        }
    }

    void aplicarPenalizaciones() {
        for (auto& cuenta : cuentas) {
            cuenta.aplicarPenalizacion();
        }
    }
};
int main() {
    SistemaBancario sistema(30); 
    int opcion, numCuenta;
    double monto;

    do {
        cout << "\nIngrese el número de cuenta (1-30): ";
        cin >> numCuenta;

        cout << "\nMenú de opciones:\n";
        cout << "1. Depositar\n";
        cout << "2. Retirar\n";
        cout << "3. Consultar saldo\n";
        cout << "4. Salir\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (opcion == 1 || opcion == 2) {
            cout << "Ingrese monto: ";
            cin >> monto;
        }
        else {
            monto = 0; 
        }

        if (opcion != 4) {  
            sistema.realizarOperacion(numCuenta, opcion, monto);
            sistema.aplicarPenalizaciones();
        }

    } while (opcion != 4);

    cout << "Salien" << endl;
    return 0;
}
