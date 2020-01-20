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
    return (int)x; 
}

int main(int argc, char *argv[])
{
    // declaro los peso de cada huevo, los el precio del pedido en cada epoca y el precio de venta
    double peso_huevo = 0.25;
    double precio_kilo_a = 1;
    double precio_kilo_d = 1.5;
    double precio_venta = 0.6;
    // Donde guardare el numero de repeticiones que pone el usuario
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
    // Repetimos desde el valor minimo, hasta el maximo del intervalo triangular
    for (int i = a; i < b; i++)
    {
        //Variable para guardar la media
        double media = 0.0;
        //Repetimos tantas veces como indique el usuario
        for (int x = 0; x < num_repeticiones; x++)
        {
            //Generamos una demanda 
            demanda = generademanda();
            ganancia_ventas = (double)demanda * precio_venta;
            //Si los pedidos son menores a los que podemos producir
            if(i >= demanda){
                costes = (i*peso_huevo)*precio_kilo_a;
            }else{ // SI los pedidos es mayores a loo que podemos realizar, tenemos que pedir de nuevo
                costes = (i*peso_huevo)*precio_kilo_a+((demanda - i)*peso_huevo)*precio_kilo_d;
            }
            //Calculamos el beneficio restando las ventas menos los costes
            beneficio = ganancia_ventas - costes;

            media += beneficio;
        }
        //Calculamos la media y guardamos la mejor
        media /= num_repeticiones;
        if(media > mejor_ganancia){
            mejor_suministro = i*peso_huevo;
            mejor_ganancia = media;
        }
    }
    //Mostramos los dsatos
    cout << "La mejor ganancia ha sido: " << mejor_ganancia << endl;
    cout << "El mejor pedido en agosto es: " << mejor_suministro << endl;

}