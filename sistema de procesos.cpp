#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//====================================
// ESTRUCTURAS
//====================================

struct Proceso {
    int id;
    string nombre;
    string prioridad;
    int memoria;
    Proceso* sig;
};

struct NodoCola {
    int id;
    NodoCola* sig;
};

struct NodoPila {
    int id;
    NodoPila* sig;
};

//====================================
// VARIABLES GLOBALES
//====================================

Proceso* lista = NULL;

NodoCola* cola = NULL;

NodoPila* pila = NULL;
NodoPila* pilaAux = NULL;

//====================================
// LISTA DE PROCESOS
//====================================

void agregarProceso() {

    int id, memoria;
    string nombre, prioridad;

    cout << "ID: ";
    cin >> id;

    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Prioridad (Alta/Media/Baja): ";
    getline(cin, prioridad);

    cout << "Memoria (MB): ";
    cin >> memoria;

    Proceso* nuevo = new Proceso;

    nuevo->id = id;
    nuevo->nombre = nombre;
    nuevo->prioridad = prioridad;
    nuevo->memoria = memoria;
    nuevo->sig = NULL;

    if (lista == NULL) {
        lista = nuevo;
    } else {
        Proceso* p = lista;

        while (p->sig != NULL) {
            p = p->sig;
        }

        p->sig = nuevo;
    }

    cout << "Proceso agregado.\n";
}

void mostrarProcesos() {

    if (lista == NULL) {
        cout << "No hay procesos.\n";
        return;
    }

    Proceso* p = lista;

    while (p != NULL) {

        cout << "ID: " << p->id
             << " | Nombre: " << p->nombre
             << " | Prioridad: " << p->prioridad
             << " | Memoria: " << p->memoria << " MB\n";

        p = p->sig;
    }
}

void buscarPorID() {

    int id;

    cout << "ID a buscar: ";
    cin >> id;

    Proceso* p = lista;

    while (p != NULL) {

        if (p->id == id) {

            cout << "Nombre: " << p->nombre
                 << " | Prioridad: " << p->prioridad
                 << " | Memoria: " << p->memoria << " MB\n";

            return;
        }

        p = p->sig;
    }

    cout << "Proceso no encontrado.\n";
}

void buscarPorNombre() {

    string nombre;

    cin.ignore();

    cout << "Nombre a buscar: ";
    getline(cin, nombre);

    bool encontrado = false;

    Proceso* p = lista;

    while (p != NULL) {

        if (p->nombre == nombre) {

            cout << "ID: " << p->id
                 << " | Prioridad: " << p->prioridad
                 << " | Memoria: " << p->memoria << " MB\n";

            encontrado = true;
        }

        p = p->sig;
    }

    if (!encontrado) {
        cout << "Proceso no encontrado.\n";
    }
}

void modificarProceso() {

    int id;

    cout << "ID a modificar: ";
    cin >> id;

    Proceso* p = lista;

    while (p != NULL) {

        if (p->id == id) {

            cin.ignore();

            cout << "Nuevo nombre: ";
            getline(cin, p->nombre);

            cout << "Nueva prioridad (Alta/Media/Baja): ";
            getline(cin, p->prioridad);

            cout << "Nueva memoria (MB): ";
            cin >> p->memoria;

            cout << "Proceso modificado.\n";
            return;
        }

        p = p->sig;
    }

    cout << "Proceso no encontrado.\n";
}

void eliminarProceso() {

    int id;

    cout << "ID a eliminar: ";
    cin >> id;

    Proceso* actual = lista;
    Proceso* anterior = NULL;

    while (actual != NULL && actual->id != id) {

        anterior = actual;
        actual = actual->sig;
    }

    if (actual == NULL) {

        cout << "Proceso no encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        lista = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }

    cout << "Memoria liberada: "
         << actual->memoria
         << " MB\n";

    delete actual;

    cout << "Proceso eliminado.\n";
}

void mostrarMemoriaTotal() {

    int total = 0;

    Proceso* p = lista;

    while (p != NULL) {

        total += p->memoria;
        p = p->sig;
    }

    cout << "Memoria total utilizada: "
         << total
         << " MB\n";
}

//====================================
// COLA FIFO
//====================================

void encolar() {

    int id;

    cout << "ID a encolar: ";
    cin >> id;

    NodoCola* nuevo = new NodoCola;

    nuevo->id = id;
    nuevo->sig = NULL;

    if (cola == NULL) {

        cola = nuevo;
    } else {

        NodoCola* p = cola;

        while (p->sig != NULL) {
            p = p->sig;
        }

        p->sig = nuevo;
    }

    cout << "Proceso encolado.\n";
}

void desencolar() {

    if (cola == NULL) {

        cout << "Cola vacia.\n";
        return;
    }

    NodoCola* aux = cola;

    cout << "Ejecutando proceso ID: "
         << aux->id << "\n";

    cola = cola->sig;

    delete aux;
}

void mostrarCola() {

    if (cola == NULL) {

        cout << "Cola vacia.\n";
        return;
    }

    NodoCola* p = cola;

    while (p != NULL) {

        cout << "ID: " << p->id << "\n";
        p = p->sig;
    }
}

//====================================
// PILA PRINCIPAL
//====================================

void apilar() {

    int id;

    cout << "ID a apilar: ";
    cin >> id;

    NodoPila* nuevo = new NodoPila;

    nuevo->id = id;
    nuevo->sig = pila;

    pila = nuevo;

    cout << "Proceso apilado.\n";
}

void desapilar() {

    if (pila == NULL) {

        cout << "Pila vacia.\n";
        return;
    }

    NodoPila* aux = pila;

    cout << "Desapilando ID: "
         << aux->id << "\n";

    pila = pila->sig;

    delete aux;
}

void mostrarPila() {

    if (pila == NULL) {

        cout << "Pila vacia.\n";
        return;
    }

    NodoPila* p = pila;

    while (p != NULL) {

        cout << "ID: " << p->id << "\n";
        p = p->sig;
    }
}

//====================================
// PILA AUXILIAR
//====================================

void pushAux(int id) {

    NodoPila* nuevo = new NodoPila;

    nuevo->id = id;
    nuevo->sig = pilaAux;

    pilaAux = nuevo;
}

void eliminarDePila() {

    int id;

    cout << "ID a eliminar de la pila: ";
    cin >> id;

    bool encontrado = false;

    while (pila != NULL) {

        if (pila->id == id) {

            NodoPila* borrar = pila;

            pila = pila->sig;

            delete borrar;

            encontrado = true;
            break;
        }

        pushAux(pila->id);

        NodoPila* temp = pila;

        pila = pila->sig;

        delete temp;
    }

    while (pilaAux != NULL) {

        NodoPila* nuevo = new NodoPila;

        nuevo->id = pilaAux->id;
        nuevo->sig = pila;

        pila = nuevo;

        NodoPila* borrar = pilaAux;
        pilaAux = pilaAux->sig;

        delete borrar;
    }

    if (encontrado)
        cout << "ID eliminado usando pila auxiliar.\n";
    else
        cout << "ID no encontrado.\n";
}

//====================================
// ARCHIVO
//====================================

void guardarDatos() {

    ofstream archivo("datos.txt");

    Proceso* p = lista;

    while (p != NULL) {

        archivo << p->id << " "
                << p->prioridad << " "
                << p->memoria << " "
                << p->nombre << endl;

        p = p->sig;
    }

    archivo.close();
}

void cargarDatos() {

    ifstream archivo("datos.txt");

    if (!archivo)
        return;

    int id, memoria;
    string prioridad, nombre;

    while (archivo >> id >> prioridad >> memoria) {

        archivo.ignore();

        getline(archivo, nombre);

        Proceso* nuevo = new Proceso;

        nuevo->id = id;
        nuevo->prioridad = prioridad;
        nuevo->memoria = memoria;
        nuevo->nombre = nombre;
        nuevo->sig = NULL;

        if (lista == NULL) {
            lista = nuevo;
        } else {

            Proceso* p = lista;

            while (p->sig != NULL) {
                p = p->sig;
            }

            p->sig = nuevo;
        }
    }

    archivo.close();
}

//====================================
// MAIN
//====================================

int main() {

    cargarDatos();

    int opcion;

    do {

        cout << "\n===== MENU =====\n";
        cout << "1. Agregar proceso\n";
        cout << "2. Mostrar procesos\n";
        cout << "3. Buscar por ID\n";
        cout << "4. Buscar por nombre\n";
        cout << "5. Modificar proceso\n";
        cout << "6. Eliminar proceso\n";
        cout << "7. Encolar proceso\n";
        cout << "8. Desencolar proceso\n";
        cout << "9. Mostrar cola\n";
        cout << "10. Apilar proceso\n";
        cout << "11. Desapilar proceso\n";
        cout << "12. Mostrar pila\n";
        cout << "13. Eliminar de pila (auxiliar)\n";
        cout << "14. Mostrar memoria total\n";
        cout << "0. Salir\n";

        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {

            case 1: agregarProceso(); break;
            case 2: mostrarProcesos(); break;
            case 3: buscarPorID(); break;
            case 4: buscarPorNombre(); break;
            case 5: modificarProceso(); break;
            case 6: eliminarProceso(); break;
            case 7: encolar(); break;
            case 8: desencolar(); break;
            case 9: mostrarCola(); break;
            case 10: apilar(); break;
            case 11: desapilar(); break;
            case 12: mostrarPila(); break;
            case 13: eliminarDePila(); break;
            case 14: mostrarMemoriaTotal(); break;
            case 0: guardarDatos(); break;

            default:
                cout << "Opcion invalida.\n";
        }

    } while (opcion != 0);

    cout << "Hasta luego.\n";

    return 0;
}


