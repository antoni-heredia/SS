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
int genera_demanda(float *tabla, int tama)
{
    int i;
    double u = uniforme();
    i = 0;
    while ((i < tama) && (u >= tabla[i]))
        i++;
    return i;
}

int main(int argc, char *argv[])
{

    if (argc < 6)
    {
        printf("No se ha introducido los parametros correctos");
        printf("%s  <cantidad maxima pedida>  <dias a simular> <tipo de tabla [a,b,c]> <beneficio por unidad> <coste devolucion> \n", argv[0]);
        exit(-1);
    }

    int cant_maxima = atoi(argv[1]);
    int veces = atoi(argv[2]);
    char tipo_tabla = argv[3][0];
    int beneficio = atoi(argv[4]);
    int coste = atoi(argv[5]);

    srand(time(NULL)); //Inicializa el generador de números pseudoaleatorios
    float *tablabdemanda;
    if (tolower(tipo_tabla) == 'a')
        tablabdemanda = construye_prop_a(cant_maxima);
    else if (tolower(tipo_tabla) == 'b')
        tablabdemanda = construye_prop_b(cant_maxima);
    else if (tolower(tipo_tabla) == 'c')
        tablabdemanda = construye_prop_c(cant_maxima);
    else
    {
        printf("Tipo de tabla incorrecto. El tipo es a, b o c\n");
        exit(-1);
    }

    //Repetimos la simulación con diferentes cantidades de pedidos
    for (int s = 1; s <= cant_maxima; s++)
    {
        printf("s:%d \n",s);
        float sum = 0.0;
        float sum2 = 0.0;
        for (int h = 0; h < veces; h++)
        {
            int ganancia;
            int demanda = genera_demanda(tablabdemanda, cant_maxima);
            if (s > demanda)
            {
                ganancia = demanda*beneficio-coste;
            }else
            {
                ganancia = s*beneficio;
            }
            sum+=ganancia;
            sum2+=ganancia*ganancia;
        }
        float ganancia_esperada = sum/veces;
        float desviacion = sqrt((sum2-veces*ganancia_esperada*ganancia_esperada));
        printf("ganacia:%f:desviacion:%f\n",ganancia_esperada,desviacion);
    }
    free(tablabdemanda);
};