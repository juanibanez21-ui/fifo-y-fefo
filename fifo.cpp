#include <iostream>
#include <string>
using namespace std;

struct Nodo {
    int codigo;
    string nombre;
    int fechaVencimiento;
    Nodo* siguiente;
};

class Inventario {
private:
    Nodo* frente;
    Nodo* final;

public:
    Inventario() {
        frente = nullptr;
        final = nullptr;
    }

    void insertar(int codigo, string nombre, int fecha) {
        Nodo* nuevo = new Nodo();

        nuevo->codigo = codigo;
        nuevo->nombre = nombre;
        nuevo->fechaVencimiento = fecha;
        nuevo->siguiente = nullptr;

        if (frente == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }

        cout << "Producto registrado correctamente.\n";
    }

    void mostrar() {
        if (frente == nullptr) {
            cout << "El inventario esta vacio.\n";
            return;
        }

        Nodo* actual = frente;

        cout << "\n===== INVENTARIO =====\n";

        while (actual != nullptr) {
            cout << "Codigo: " << actual->codigo << "\n";
            cout << "Producto: " << actual->nombre << "\n";
            cout << "Vencimiento: " << actual->fechaVencimiento << "\n";
            cout << "----------------------\n";

            actual = actual->siguiente;
        }
    }

    void FIFO() {
        if (frente == nullptr) {
            cout << "No hay productos disponibles.\n";
            return;
        }

        Nodo* temporal = frente;

        cout << "FIFO - Producto retirado: "
             << temporal->nombre << "\n";

        frente = frente->siguiente;

        if (frente == nullptr) {
            final = nullptr;
        }

        delete temporal;
    }

    void FEFO() {
        if (frente == nullptr) {
            cout << "No hay productos disponibles.\n";
            return;
        }

        Nodo* actual = frente;
        Nodo* anterior = nullptr;

        Nodo* menor = frente;
        Nodo* anteriorMenor = nullptr;

        while (actual != nullptr) {
            if (actual->fechaVencimiento < menor->fechaVencimiento) {
                menor = actual;
                anteriorMenor = anterior;
            }

            anterior = actual;
            actual = actual->siguiente;
        }

        cout << "FEFO - Producto retirado: "
             << menor->nombre << "\n";

        if (anteriorMenor == nullptr) {
            frente = menor->siguiente;
        } else {
            anteriorMenor->siguiente = menor->siguiente;
        }

        if (menor == final) {
            final = anteriorMenor;
        }

        delete menor;
    }

    ~Inventario() {
        while (frente != nullptr) {
            Nodo* temporal = frente;
            frente = frente->siguiente;
            delete temporal;
        }
    }
};

int main() {
    Inventario inventario;

    int opcion;
    int codigo;
    int fecha;
    string nombre;

    do {
        cout << "\n===== SISTEMA FIFO Y FEFO =====\n";
        cout << "1. Registrar producto\n";
        cout << "2. Mostrar inventario\n";
        cout << "3. Retirar producto FIFO\n";
        cout << "4. Retirar producto FEFO\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                cout << "Ingrese el codigo: ";
                cin >> codigo;

                cout << "Ingrese el nombre del producto: ";
                getline(cin >> ws, nombre);

                cout << "Ingrese fecha de vencimiento (AAAAMMDD): ";
                cin >> fecha;

                inventario.insertar(codigo, nombre, fecha);
                break;

            case 2:
                inventario.mostrar();
                break;

            case 3:
                inventario.FIFO();
                break;

            case 4:
                inventario.FEFO();
                break;

            case 5:
                cout << "Finalizando programa...\n";
                break;

            default:
                cout << "Opcion no valida.\n";
        }

    } while (opcion != 5);

    return 0;
}

