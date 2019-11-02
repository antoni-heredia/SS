#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
//Genera un número uniformemente distribuido en el
//intervalo [0,1) a partir de uno de los generadores
//disponibles en C. Lo utiliza el generador de demanda
double uniforme()
{
    int t = random();
    double f = ((double)RAND_MAX + 1.0);
    return (double)t / f;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (a).
float *construye_prop_a(int n)
{
    int i;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n", stderr);
        exit(1);
    }
    temp[0] = 1.0 / n;
    for (i = 1; i < n; i++)
        temp[i] = temp[i - 1] + 1.0 / n;
    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (b).
float *construye_prop_b(int n)
{
    int i, max;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n", stderr);
        exit(1);
    }
    max = (n / 2) * (n + 1);
    temp[0] = n * 1.0 / max;
    for (i = 1; i < n; i++)
        temp[i] = temp[i - 1] + (float)(n - i) / max;
    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (c).
float *construye_prop_c(int n)
{
    int i, max;
    float *temp;
    if ((temp = (float *)malloc(n * sizeof(float))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n", stderr);
        exit(1);
    }
    max = n * n / 4;
    temp[0] = 0.0;
    for (i = 1; i < (n / 2); i++)
        temp[i] = temp[i - 1] + (float)i / max;
    for (i = (n / 2); i < n; i++)
        temp[i] = temp[i - 1] + (float)(n - i) / max;
    return temp;
}
// Genera un valor de la
// distribución de la demanda codificada en tabla, por el
// método de tablas de búsqueda.
// tama es el tamaño de la tabla, 100 en nuestro caso particular
int genera_demanda(int tama)
{
    double u = uniforme();
    int i = u*tama;
    return i;
}

int main(int argc, char *argv[])
{
    

    srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
    int demanda;

    int veces[] = {1, 10, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int x = 0; x < 10; x++)
    {
        clock_t start = clock();

        for (int i = 0; i < veces[x]; i++)
        {
            demanda = genera_demanda(100);
        }
        clock_t stop = clock();
        double diferencia = -(double)(start - stop) / (CLOCKS_PER_SEC/1000);
        printf("veces:%d\ntiempo:%f\n",veces[x],diferencia);
    }
};