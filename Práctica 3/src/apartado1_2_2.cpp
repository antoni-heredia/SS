#include <chrono>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;
using namespace std::chrono;

bool servidor;
double acum_cola, inicio_ocio, tiempo_ocio, reloj, tlleg, tserv, tiempo_salida, tiempo_llegada, tultsuc;
long long int atendidos, encola, infinito, cantSimulaciones, total_a_atender;

float generaLlegada(float tllegada)
{
    float u = (float)((float)random() / (RAND_MAX + 1.0));

    return (-tllegada * log(1 - u));
}

float generaServicio(float tservicio)
{
    float u = (float)((float)random() / (RAND_MAX + 1.0));
    return (-tservicio * log(1 - u));
}

int main(int argc, char *argv[])
{
    if (argc == 5)
    {
        tlleg = atof(argv[1]);
        tserv = atof(argv[2]);
        total_a_atender = atoi(argv[3]);
        cantSimulaciones = atoi(argv[4]);
    }
    else
    {
        cerr << "Numero de parametros incorrectos" << endl;
        cerr << argv[0] << " tlleg tserv total_a_atender cantSimulaciones" << endl;
        exit(1);
    }

    double tTotal = 0.0;
    double tCola = 0.0;
    double tOcio = 0.0;

    srand(time(NULL));

    for (int i = 0; i < cantSimulaciones; i++)
    {
        infinito = 1e30;
        atendidos = 0;
        inicio_ocio = 0.0;
        acum_cola = 0.0;
        reloj = 0.0;
        tultsuc = reloj;
        servidor = true;
        encola = 0;
        tiempo_llegada = reloj + generaLlegada(tlleg);
        tiempo_salida = infinito;
        tiempo_ocio = 0.0;

        high_resolution_clock::time_point tiempoInicio, tiempoFin;

        tiempoInicio = high_resolution_clock::now();

        while (atendidos < total_a_atender)
        {
            reloj = min(tiempo_llegada, tiempo_salida); //una función que calcula el mínimo

            if (reloj == tiempo_llegada)
            {
                // Generar llegada
                tiempo_llegada = reloj + (generaLlegada(tlleg));

                if (servidor)
                {
                    servidor = false;
                    tiempo_salida = reloj + (generaServicio(tserv));
                    tiempo_ocio += reloj - inicio_ocio;
                }
                else
                {
                    acum_cola += (reloj - tultsuc) * encola;
                    tultsuc = reloj;
                    encola++;
                }
            }

            if (reloj == tiempo_salida)
            {
                atendidos++;

                if (encola > 0)
                {
                    acum_cola += (reloj - tultsuc) * encola;
                    tultsuc = reloj;
                    encola--;

                    tiempo_salida = reloj + (generaServicio(tserv));
                }
                else
                {
                    servidor = true;
                    inicio_ocio = reloj;
                    tiempo_salida = infinito;
                }
            }
        }

        tiempoFin = high_resolution_clock::now();

        double porcent_ocio = tiempo_ocio * 100 / reloj;
        double media_encola = acum_cola / reloj;
        double tiempoIter = duration_cast<duration<double>>(tiempoFin - tiempoInicio).count();

        tTotal += tiempoIter;
        tCola += media_encola;
        tOcio += porcent_ocio;

        cout << i << ":" << media_encola << ":" << porcent_ocio << ":" << total_a_atender << ":" << tiempoIter << endl;
    }

    double tiempoMedio = tTotal / cantSimulaciones;
    double colaMedia = tCola / cantSimulaciones;
    double mediaOcio = tOcio / cantSimulaciones;

    cout << endl << "tiempo_medio: " << tiempoMedio << " seg." << endl;
    cout << "cliente_medios: " << colaMedia << endl;
    cout << "tiempo_ocio: " << mediaOcio << endl;

    return 0;
}