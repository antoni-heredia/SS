#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long int congruencial_entero(int a, long long int x, int c, long long int m)
{
    return (((a * x) + c) % m);
}

long long int real_artesanal(int a, long long int x, int c, int m)
{
    double nuevoX = (a * (double)x + c) / m;
    nuevoX = (nuevoX - (long long int)nuevoX) * m;;
    return (long long int) nuevoX;
}

long long int real_artesanal_corregida(int a, long long int x, int c, int m)
{
    double nuevoX = (a * (double)x + c) / m;
    nuevoX = (nuevoX - (long long int)nuevoX) * m;;

    return  (long long int)(nuevoX + 0.5);
}

long long int usando_fmod(int a, long long int x, int c, long long int m)
{
    return fmod((a * x + c), m);
}

int existe(long long int *numeros, int tamanio, long long int valor)
{
    for (int i = 0; i < tamanio; i++)
    {
        if (numeros[i] == valor)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{

    int a1 = 2061;
    int a2 = 2060;
    int c = 4231;
    long long int m = 1e4;

    long long int numeros[m];

    for(int i =0;i<m;i++)
        numeros[i] = -1;
        
    long long int x = 19;

    x = congruencial_entero(a1, x, c, m);
    
    printf("----------Generados con aritmetica entera------------\n");
    long long int pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = congruencial_entero(a1, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a1,pos);
    for(int i =0;i<m;i++)
        numeros[i] = -1;

    x = congruencial_entero(a2, x, c, m);

    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = congruencial_entero(a2, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a2,pos);


    /*******************************************************************************************/
    printf("----------Generados con aritmetica real------------\n");
    for(int i =0;i<m;i++)
        numeros[i] = -1;
    x = 19;
    x = real_artesanal(a1, x, c, m);
    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = real_artesanal(a1, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a1,pos);

    for(int i =0;i<m;i++)
        numeros[i] = -1;

    x = 19;
    x = real_artesanal(a2, x, c, m);

    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = real_artesanal(a2, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a2,pos);

    /*******************************************************************************************/
    printf("----------Generados con aritmetica real corregida------------\n");
    for(int i =0;i<m;i++)
        numeros[i] = -1;
        
    x = 19;
    x = real_artesanal_corregida(a1, x, c, m);
    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = real_artesanal_corregida(a1, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a1,pos);
    for(int i =0;i<m;i++)
        numeros[i] = -1;

    x = 19;
    x = real_artesanal_corregida(a2, x, c, m);
    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = real_artesanal_corregida(a2, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a2,pos);

    /*******************************************************************************************/
    printf("----------Generados con fmod------------\n");

    pos = 0;
    x = 19;
    x = usando_fmod(a1, x, c, m);
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = usando_fmod(a1, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a1,pos);

    for(int i =0;i<m;i++)
        numeros[i] = -1;

    pos = 0;
    x = usando_fmod(a2, x, c, m);
    pos = 0;
    while (existe(numeros, m, x))
    {
        numeros[pos] = x;
        pos++;
        x = usando_fmod(a2, x, c, m);
    }
    
    printf("Generados con %d , Tarda en ciclar %lld\n", a2,pos);
};