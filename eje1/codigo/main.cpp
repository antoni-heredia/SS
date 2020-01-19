#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

//Pseudo codigo ofrecido por el profesor
int a = 2000, b = 3000, c = 2600;
float uniforme()
{
    float u;
    u = (float)random();
    u = u / (float)(RAND_MAX + 1.0);
    return u;
}
int generademanda()
{
    float u, x;
    u = uniforme();
    if (u < (c - a) / (b - a))
        x = a + sqrt((b - a) * (c - a) * u);
    else
        x = b - sqrt((b - a) * (b - c) * (1 - u));
    return (int)x; //se convierte a entero porque es la demanda de huevos de pascua
}

int main(int argc, char *argv[])
{
    double peso_huevo = 0.25;
    double precio_kilo_a = 1;
    double precio_kilo_d = 1.5;
    double precio_venta = 0.6;
    int num_repeticiones;
    if (argc != 2)
    {
        cout << "Numero de parametros incorrecto." << endl;
        cout << "Uso" << argv[0] << " <numero de repeticiones>" << endl;
        return 1;
    }
    else
    {
        num_repeticiones = atoi(argv[1]);
    }
    srand(time(NULL));
    int demanda;
    double ganancia_ventas,costes, beneficio;
    double mejor_ganancia = 0;
    int mejor_suministro;

    for (int i = a; i < b; i++)
    {
        double media = 0.0;
        for (int x = 0; x < num_repeticiones; x++)
        {
            demanda = generademanda();
            ganancia_ventas = (double)demanda * precio_venta;
            if(i >= demanda){
                costes = (i/4)*precio_kilo_a;
            }else{
                costes = (i/4)*precio_kilo_a+((demanda - i)/4)*precio_kilo_d;
            }
            beneficio = ganancia_ventas - costes;

            media += beneficio;
        }
        media /= num_repeticiones;
        cout << "Media: " << media << endl;
        if(media > mejor_ganancia){
            mejor_suministro = i/4;
            mejor_ganancia = media;
        }
    }

    cout << "La mejor ganancia ha sido: " << mejor_ganancia << endl;
    cout << "El mejor pedido en agosto es: " << mejor_suministro << endl;

}