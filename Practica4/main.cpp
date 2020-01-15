#include <iostream>
#include <cstdlib>
#Compilar con g++ main.cpp
using namespace std;
double a11, a12, a21, a22;
int x, y;
const int numeq = 2;
double oldestado[2];
double estado[2];
double dt;
double t, tinic, tfin;
//Declaro las cabeceras de las funciones
void integracion();
void salida();
void one_step_runge_kutta(double inp[numeq], double out[numeq], double tt, double hh);
void one_step_euler(double inp[numeq], double out[numeq], double tt, double hh);
void derivacion(double est[numeq], double f[numeq], double tt);

int main(int argc, char *argv[])
{

    if (argc != 10)
    {
        cout << "Numero de parametros incorrecto" << endl;
        cout << "Uso: " << argv[0] << " <a11> <a12> <a21> <a22> <x> <y> <dt> <tinic> <tfin>" << endl;
        return 1;
    }
    t = tinic;
    a11 = atof(argv[1]);
    a12 = atof(argv[2]);
    a21 = atof(argv[3]);
    a22 = atof(argv[4]);
    estado[0] = atof(argv[5]);
    estado[1] = atof(argv[6]);
    dt = atof(argv[7]);
    tinic = atof(argv[8]);
    tfin = atof(argv[9]);

    integracion();
    return 0;
}
void salida()
{
    std::cout << estado[0] << ";" << estado[1] << ";" << t << endl;
}
void integracion()

{
    do
    {
        salida();
        oldestado[0] = estado[0];
        oldestado[1] = estado[1];
        one_step_euler(oldestado, estado, t, dt); //sustituir por one-step-runge-kutta o por one-step-euler
        t += dt;
    } while (t < tfin);
}

void one_step_runge_kutta(double inp[numeq], double out[numeq], double tt, double hh)

{
    double time, incr, k[numeq][4], f[numeq];

    for (int i = 0; i < numeq; i++)
        out[i] = inp[i];
    time = tt;

    for (int j = 0; j < 4; j++)
    {
        derivacion(out, f, time);
        for (int i = 0; i < numeq; i++)
            k[i][j] = f[i];

        if (j < 2)
            incr = hh / 2;
        else
            incr = hh;
        time = tt + incr;

        for (int i = 0; i < numeq; i++)
            out[i] = inp[i] + k[i][j] * incr;
    }
    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh / 6 * (k[i][0] + 2 * k[i][1] + 2 * k[i][2] + k[i][3]);
}

void one_step_euler(double inp[numeq], double out[numeq], double tt, double hh)

{
    double f[2];
    derivacion(inp, f, tt);
    for (int i = 0; i < numeq; i++)
        out[i] = inp[i] + hh * f[i];
}

void derivacion(double est[numeq], double f[numeq], double tt)
// espec�fico para el modelo considerado
{
    f[0] = a11 * est[0] - a12 * est[0] * est[1];
    f[1] = a21 * est[0] * est[1] - a22 * est[1];
}
