/*Una empresa de transporte cuenta con camiones de diferente tamaño.
Al finalizar el día se cuenta con los datos de cada viaje ordenados por patente en forma ascendente:

- Patente
- Hora de inicio
- Hora de fin
- Kilómetros recorridos
- Importe

Y en forma separada, los datos de cada vehículo:

- Patente
- Modelo
- Consumo por kilómetro

Para escribir el código, se asume que los datos ya están cargados en vectores estáticos y que cada vector tiene una variable 
asociada que indica la cantidad de elementos cargados.
Se asume que cada vehículo realiza al menos un viaje en el día.


1) Escribir una función que ordene el vector de vehículos por modelo (ordenamiento burbuja).
2) Escribir una función que busque en el vector de vehículos por patente y devuelva la posición en el vector (búsqueda binaria).
3) Escribir una función que calcule el costo total del combustible utilizado por todos los camiones en el día.
4) Escribir una función que indique la patente del vehículo con mejor y peor rendimiento, de acuerdo al consumo total de combustible en relación con el total 
de los importes cobrados por los viajes.*/

/*Integrantes:
Federico Gomez
Alan Coronel 
Flavio Huamancayo
Agustin Belmonte
*/

#include <iostream>
using namespace std;

const int MAX = 100;

struct Viaje {
    char patente[10];
    int horaInicio;
    int horaFin;
    float kmRecorridos;
    float importe;
};


struct Vehiculo {
    char patente[10];
    char modelo[20];
    float consumoKm; 
};

// 1)(burbujeo)
int compararTexto(const char a[], const char b[]) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i])
            return a[i] - b[i];
        i++;
    }
    return a[i] - b[i];
}

void ordenarPorModelo(Vehiculo vehiculos[], int cantVehiculos) {
    for (int i = 0; i < cantVehiculos - 1; i++) {
        for (int j = 0; j < cantVehiculos - i - 1; j++) {
            if (compararTexto(vehiculos[j].modelo, vehiculos[j + 1].modelo) > 0) {
                Vehiculo aux = vehiculos[j];
                vehiculos[j] = vehiculos[j + 1];
                vehiculos[j + 1] = aux;
            }
        }
    }
}

// 2) Busqueda binaria por patente
int buscarPorPatente(Vehiculo vehiculos[], int cantVehiculos, const char patenteBuscada[]) {
    int inicio = 0, fin = cantVehiculos - 1;
    while (inicio <= fin) {
        int medio = (inicio + fin) / 2;
        int cmp = compararTexto(vehiculos[medio].patente, patenteBuscada);
        if (cmp == 0)
            return medio;
        else if (cmp < 0)
            inicio = medio + 1;
        else
            fin = medio - 1;
    }
    return -1; 
}

// 3)total combustible
float calcularCostoTotalCombustible(Viaje viajes[], int cantViajes, Vehiculo vehiculos[], int cantVehiculos, float precioCombustible) {
    float total = 0;
    for (int i = 0; i < cantViajes; i++) {
        int pos = buscarPorPatente(vehiculos, cantVehiculos, viajes[i].patente);
        if (pos != -1) {
            float litros = viajes[i].kmRecorridos * vehiculos[pos].consumoKm;
            total += litros * precioCombustible;
        }
    }
    return total;
}

// 4) Mejor y peor rendimiento
void copiarTexto(char destino[], const char origen[]) {
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

void calcularRendimientos(Viaje viajes[], int cantViajes, Vehiculo vehiculos[], int cantVehiculos, char patenteMejor[], char patentePeor[]) {
    float consumoTotal[MAX] = {0};
    float ingresoTotal[MAX] = {0};

    for (int i = 0; i < cantViajes; i++) {
        int pos = buscarPorPatente(vehiculos, cantVehiculos, viajes[i].patente);
        if (pos != -1) {
            consumoTotal[pos] += viajes[i].kmRecorridos * vehiculos[pos].consumoKm;
            ingresoTotal[pos] += viajes[i].importe;
        }
    }

    int mejor = -1, peor = -1;
    float mejorRend, peorRend;

    for (int i = 0; i < cantVehiculos; i++) {
        if (consumoTotal[i] == 0) continue; // evitar divisiÃ³n por cero

        float rend = ingresoTotal[i] / consumoTotal[i];

        if (mejor == -1 || rend > mejorRend) {
            mejor = i;
            mejorRend = rend;
        }

        if (peor == -1 || rend < peorRend) {
            peor = i;
            peorRend = rend;
        }
    }

    if (mejor != -1) copiarTexto(patenteMejor, vehiculos[mejor].patente);
    else copiarTexto(patenteMejor, "N/A");

    if (peor != -1) copiarTexto(patentePeor, vehiculos[peor].patente);
    else copiarTexto(patentePeor, "N/A");
}



int main() {
    Vehiculo vehiculos[MAX] = {
        {"AAA123", "Volvo", 0.3},
        {"BBB234", "Scania", 0.25},
        {"CCC345", "Mercedes", 0.4}
    };
    int cantVehiculos = 3;

    Viaje viajes[MAX] = {
        {"AAA123", 800, 900, 100, 2000},
        {"BBB234", 900, 1000, 150, 2500},
        {"CCC345", 1000, 1100, 120, 3000},
        {"AAA123", 1200, 1300, 80, 1800},
    };
    int cantViajes = 4;

    cout << "\n--- COSTO TOTAL COMBUSTIBLE ---\n";
    float total = calcularCostoTotalCombustible(viajes, cantViajes, vehiculos, cantVehiculos, 800);
    cout << "Total: $" << total << endl;

    cout << "\n--- MEJOR Y PEOR RENDIMIENTO ---\n";
    char mejor[10], peor[10];
    calcularRendimientos(viajes, cantViajes, vehiculos, cantVehiculos, mejor, peor);
    cout << "Mejor rendimiento: " << mejor << endl;
    cout << "Peor rendimiento: " << peor << endl;

    cout << "\n--- ORDENANDO POR MODELO ---\n";
    ordenarPorModelo(vehiculos, cantVehiculos);
    for (int i = 0; i < cantVehiculos; i++) {
        cout << vehiculos[i].modelo << " - " << vehiculos[i].patente << endl;
    }

    return 0;
}
