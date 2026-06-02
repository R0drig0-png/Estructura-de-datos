#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// ---- ESTRUCTURAS ----

struct Proceso {
    int id;
    string nombre;
    string prioridad;
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

// ---- VARIABLES GLOBALES ----

Proceso*  lista = NULL;
NodoCola* cola  = NULL;
NodoPila* pila  = NULL;

// ================================================
//  LISTA DE PROCESOS
// ================================================

void agregarProceso() {
    int id;
    string nombre, prioridad;

    cout << "ID: ";
    cin >> id;
    cin.ignore();

    cout << "Nombre: ";
    getline(cin, nombre);

    cout << "Prioridad: ";
    getline(cin, prioridad);

    Proceso* nuevo = new Proceso;
    nuevo->id        = id;
    nuevo->nombre    = nombre;
    nuevo->prioridad = prioridad;
    nuevo->sig       = NULL;

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
             << " | Prioridad: " << p->prioridad << "\n";
        p = p->sig;
    }
}

// Buscar por ID
void buscarPorID() {
    int id;
    cout << "ID a buscar: ";
    cin >> id;

    Proceso* p = lista;
    while (p != NULL) {
        if (p->id == id) {
            cout << "Encontrado -> Nombre: " << p->nombre
                 << " | Prioridad: " << p->prioridad << "\n";
            return;
        }
        p = p->sig;
    }
    cout << "No encontrado.\n";
}

// Buscar por nombre
void buscarPorNombre() {
    string nombre;
    cin.ignore();
    cout << "Nombre a buscar: ";
    getline(cin, nombre);

    bool encontrado = false;
    Proceso* p = lista;
    while (p != NULL) {
        if (p->nombre == nombre) {
            cout << "Encontrado -> ID: " << p->id
                 << " | Prioridad: " << p->prioridad << "\n";
            encontrado = true;
        }
        p = p->sig;
    }

    if (!encontrado) {
        cout << "No encontrado.\n";
    }
}

void eliminarProceso() {
    int id;
    cout << "ID a eliminar: ";
    cin >> id;

    Proceso* actual   = lista;
    Proceso* anterior = NULL;

    while (actual != NULL && actual->id != id) {
        anterior = actual;
        actual   = actual->sig;
    }

    if (actual == NULL) {
        cout << "No encontrado.\n";
        return;
    }

    if (anterior == NULL) {
        lista = actual->sig;
    } else {
        anterior->sig = actual->sig;
    }

    delete actual;
    cout << "Eliminado.\n";
}

// ================================================
//  COLA
// ================================================

void encolar() {
    int id;
    cout << "ID a encolar: ";
    cin >> id;

    NodoCola* nuevo = new NodoCola;
    nuevo->id  = id;
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
    cout << "Encolado.\n";
}

void desencolar() {
    if (cola == NULL) {
        cout << "Cola vacia.\n";
        return;
    }

    NodoCola* aux = cola;
    cout << "Ejecutando ID: " << aux->id << "\n";
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

// ================================================
//  PILA
// ================================================

void apilar() {
    int id;
    cout << "ID a apilar: ";
    cin >> id;

    NodoPila* nuevo = new NodoPila;
    nuevo->id  = id;
    nuevo->sig = pila;
    pila = nuevo;
    cout << "Apilado.\n";
}

void desapilar() {
    if (pila == NULL) {
        cout << "Pila vacia.\n";
        return;
    }

    NodoPila* aux = pila;
    cout << "Desapilando ID: " << aux->id << "\n";
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

// ================================================
//  GUARDAR Y CARGAR (PERSISTENCIA)
// ================================================

void guardarDatos() {
    ofstream archivo("datos.txt");

    Proceso* p = lista;
    while (p != NULL) {
        archivo << p->id << " " << p->prioridad << " " << p->nombre << "\n";
        p = p->sig;
    }

    archivo.close();
    cout << "Datos guardados.\n";
}

void cargarDatos() {
    ifstream archivo("datos.txt");
    if (!archivo) return;

    int id, prioridad;
    string nombre;

    while (archivo >> id >> prioridad) {
        archivo.ignore();
        getline(archivo, nombre);

        Proceso* nuevo = new Proceso;
        nuevo->id        = id;
        nuevo->nombre    = nombre;
        nuevo->prioridad = prioridad;
        nuevo->sig       = NULL;

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

// ================================================
//  MENU
// ================================================

int main() {

    cargarDatos();  // Al iniciar carga los datos guardados

    int opcion;

    do {
        cout << "\n--- MENU ---\n";
        cout << "1.  Agregar proceso\n";
        cout << "2.  Mostrar procesos\n";
        cout << "3.  Buscar por ID\n";
        cout << "4.  Buscar por nombre\n";
        cout << "5.  Eliminar proceso\n";
        cout << "6.  Encolar proceso\n";
        cout << "7.  Desencolar proceso\n";
        cout << "8.  Mostrar cola\n";
        cout << "9.  Apilar proceso\n";
        cout << "10. Desapilar proceso\n";	
        cout << "11. Mostrar pila\n";
        cout << "0.  Salir\n";
        cout << "Opcion: ";
        cin >> opcion;

        if      (opcion == 1)  agregarProceso();
        else if (opcion == 2)  mostrarProcesos();
        else if (opcion == 3)  buscarPorID();
        else if (opcion == 4)  buscarPorNombre();
        else if (opcion == 5)  eliminarProceso();
        else if (opcion == 6)  encolar();
        else if (opcion == 7)  desencolar();
        else if (opcion == 8)  mostrarCola();
        else if (opcion == 9)  apilar();
        else if (opcion == 10) desapilar();
        else if (opcion == 11) mostrarPila();
        else if (opcion == 0)  cout << "Hasta luego!\n";

    } while (opcion != 0);

    guardarDatos();  // Al salir guarda todo

    return 0;
}
