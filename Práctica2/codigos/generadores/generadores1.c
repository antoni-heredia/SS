#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
typedef struct
{
    int valor;
    double probabilidad;
} valores;

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
valores *construye_prop_a(int n)
{
    int i;
    valores *temp;
    if ((temp = (valores *)malloc(n * sizeof(valores))) == NULL)
    {
        fputs("Error reservando memoria para generador uniforme\n", stderr);
        exit(1);
    }
    temp[0].valor = 0;
    temp[0].probabilidad = 1.0 / n;
    for (i = 1; i < n; i++)
    {
        temp[i].valor = i;
        temp[i].probabilidad = temp[i - 1].probabilidad + 1.0 / n;
    }

    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (b).
valores *construye_prop_b(int n)
{
    int i, max;
    valores *temp;
    if ((temp = (valores *)malloc(n * sizeof(valores))) == NULL)
    {
        fputs("Error reservando memoria para generador proporcional\n", stderr);
        exit(1);
    }
    max = (n / 2) * (n + 1);

    temp[0].valor = 0;
    temp[0].probabilidad = n * 1.0 / max;
    for (i = 1; i < n; i++)
    {
        temp[i].valor = i;
        temp[i].probabilidad = temp[i - 1].probabilidad + (float)(n - i) / max;
    }
    return temp;
}
//Construye la tabla de búsqueda de
//tamaño n para la distribución de
//la demanda del apartado (c).
valores *construye_prop_c(int n)
{
    int i, max;
    valores *temp;
    if ((temp = (valores *)malloc(n * sizeof(valores))) == NULL)
    {
        fputs("Error reservando memoria para generador triangular\n", stderr);
        exit(1);
    }
    max = n * n / 4;
    int mitad = floor(n / 2.0);

    int inicializadorBucle = mitad;

    double acomulada = 0.0;
    int pos = 0;

    temp[0].valor = mitad;
    temp[0].probabilidad = (mitad + 1.0) / max;
    acomulada += (mitad + 1) / max;
    pos++;

    inicializadorBucle--;

    for (i = inicializadorBucle; i > 0; i--)
    {
        acomulada += (float)i / max;
        temp[pos].valor = i;
        temp[pos].probabilidad = acomulada;
        pos += 1;
        acomulada += (float)i / max;
        temp[pos].valor = mitad + (mitad - i);
        temp[pos].probabilidad = acomulada;
        pos += 1;
    }
    return temp;
}
// Genera un valor de la
// distribución de la demanda codificada en tabla, por el
// método de tablas de búsqueda.
// tama es el tamaño de la tabla, 100 en nuestro caso particular
int genera_demanda(valores *tabla, int tama)
{
    int i;
    double u = uniforme();
    i = 0;
    while ((i < tama) && (u >= tabla[i].probabilidad))
        i++;
    return tabla[i].valor;
}

int main(int argc, char *argv[])
{

    srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
    valores *tablabdemanda;
    tablabdemanda = construye_prop_c(100);
    int demanda;

    int veces[] = {1, 10, 100, 1000, 5000, 10000, 50000, 100000, 500000, 1000000};
    for (int x = 0; x < 10; x++)
    {
        clock_t start = clock();

        for (int i = 0; i < veces[x]; i++)
        {
            demanda = genera_demanda(tablabdemanda, 100);
        }
        clock_t stop = clock();
        double diferencia = -(double)(start - stop) / (CLOCKS_PER_SEC/1000);
        printf("veces:%d\ntiempo:%f\n",veces[x],diferencia);
    }
};