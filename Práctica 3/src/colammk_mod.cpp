#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <list>
#include <iostream>

using namespace std;

#define suceso_llegada 0
#define suceso_salida 1
#define suceso_finsimulacion 3
#define suceso_monitor 4

typedef struct
{
  int suceso;
  float tiempo;
  float retraso;
} suc;
list<suc> lsuc;
suc nodo;
int nada = 0;
list<float> cola;
int m; //numero de servidores
float tparada;
float tlleg;
float tserv;
float valor;
float numero_simulaciones;

float reloj;
;
int libres;
int encola;
int ensistema;
int atendidos;
float acum_cola;
float acum_sistema;
float acum_ocio;
float acum_retraso;
float tultsuc_cola;
float tultsuc_ocio;
float tultsuc_sistema;
float acum_sincola;
float init_sincola;
int maximacola;
bool parar;

float sum_estancia_media = 0.0;
float sum_cola_media = 0.0;
float sum_sistema_media = 0.0;
float sum_no_vacias_media = 0.0;
float sum_ocio_media = 0.0;
float sum_colamaxima_media = 0.0;
float sum_retraso_medio = 0.0;

float estancia_media_desviacion = 0.0;
float cola_media_desviacion = 0.0;
float sistema_media_desviacion = 0.0;
float no_vacias_media_desviacion = 0.0;
float ocio_media_desviacion = 0.0;
float colamaxima_media_desviacion = 0.0;
float retraso_medio_desviacion = 0.0;

bool compare(const suc &s1, const suc &s2)
{
  return s1.tiempo < s2.tiempo;
}

/* Inserta de forma ordenada un elemento en la lista de sucesos */
void insertar_lsuc(suc n)
{
  lsuc.push_back(n);
  // Mantener ordenada la lista por el tiempo de los sucesos
  lsuc.sort(compare);
}

float generador_exponencial(float media)
{
  float u;
  u = (float)random();
  u = u / (float)(RAND_MAX + 1.0);
  return (-media * log(1 - u));
}

// Generador de tiempos entre llegadas (exponencial)
float generallegada(float media)
{
  return generador_exponencial(media);
}

// Generador de tiempos de servicio (exponencial)
float generaservicio(float media)
{
  return generador_exponencial(media);
}

/* Procedimiento inicializacion */
void inicializacion()
{

  srandom(time(NULL));
  reloj = 0.0;
  libres = m;
  encola = 0;
  ensistema = 0;
  atendidos = 0;
  acum_cola = 0.0;
  acum_sistema = 0.0;
  acum_ocio = 0.0;
  acum_retraso = 0.0;
  tultsuc_cola = reloj;
  tultsuc_ocio = reloj;
  tultsuc_sistema = reloj;
  acum_sincola = 0.0;
  init_sincola = reloj;
  maximacola = 0;
  nodo.suceso = suceso_llegada;
  nodo.tiempo = reloj + generallegada(tlleg);
  nodo.retraso = nada;
  insertar_lsuc(nodo);
  nodo.suceso = suceso_finsimulacion;
  nodo.tiempo = reloj + tparada;
  nodo.retraso = nada;
  insertar_lsuc(nodo); //tparada es un par�metro de entrada al programa
  //Inicializar el suceso monitor si que quiere trazar alguna medida del rendimiento a lo largo del tiempo, no solo al final
  /* 
nodo.suceso = suceso_monitor;
nodo.tiempo = reloj+1.0;
nodo.retraso = nada;
insertar_lsuc(nodo);
*/
  parar = false;
}

/* Procedimiento temporizacion */
void temporizacion()
{
  nodo = lsuc.front();
  lsuc.pop_front();
  reloj = nodo.tiempo;
  //  printf("\n%.3f",reloj);
}

void llegada()
{
  acum_sistema += (reloj - tultsuc_sistema) * ensistema;
  tultsuc_sistema = reloj;
  ensistema++;
  nodo.suceso = suceso_llegada;
  nodo.tiempo = reloj + generallegada(tlleg);
  nodo.retraso = nada;
  insertar_lsuc(nodo);
  if (libres > 0)
  {
    acum_ocio += (reloj - tultsuc_ocio) * libres;
    tultsuc_ocio = reloj;
    libres--;
    nodo.suceso = suceso_salida;
    nodo.tiempo = reloj + generaservicio(tserv);
    nodo.retraso = nada;
    insertar_lsuc(nodo);
  }
  else
  {
    if (encola == 0)
      acum_sincola += reloj - init_sincola;
    acum_cola += (reloj - tultsuc_cola) * encola;
    tultsuc_cola = reloj;
    encola++;
    if (encola > maximacola)
      maximacola = encola;
    cola.push_back(reloj);
  }
}

void salida()
{
  acum_sistema += (reloj - tultsuc_sistema) * ensistema;
  tultsuc_sistema = reloj;
  ensistema--;
  atendidos++;
  acum_retraso += nodo.retraso;
  if (encola > 0)
  {
    acum_cola += (reloj - tultsuc_cola) * encola;
    tultsuc_cola = reloj;
    encola--;
    if (encola == 0)
      init_sincola = reloj;
    valor = cola.front();
    cola.pop_front();
    nodo.suceso = suceso_salida;
    nodo.tiempo = reloj + generaservicio(tserv);
    nodo.retraso = reloj - valor;
    insertar_lsuc(nodo);
  }
  else
  {
    acum_ocio += (reloj - tultsuc_ocio) * libres;
    tultsuc_ocio = reloj;
    libres++;
  }
}

void fin()
{
  parar = true; //para detener la simulaci�n
                //habr� que hacer las �ltimas actualizaciones de algunas variables
  float retrasomedio = acum_retraso / atendidos;
  printf("\nTiempo medio de espera en cola = %.3f", retrasomedio);
  float estanciamedia = retrasomedio + tserv;
  printf("\nTiempo medio de estancia en el sistema = %.3f", estanciamedia);
  acum_cola += (reloj - tultsuc_cola) * encola;

  //printf("\nTiempo medio de espera en cola bis = %.3f",acum_cola/atendidos);
  //printf("\nTiempo medio de estancia en el sistema bis= %.3f",acum_cola/atendidos+tserv);

  float encolamedio = acum_cola / reloj;
  printf("\nNumero medio de personas en cola = %.3f", encolamedio);
  acum_sistema += (reloj - tultsuc_sistema) * ensistema;
  float ensistemamedio = acum_sistema / reloj;
  printf("\nNumero medio de personas en el sistema = %.3f", ensistemamedio);
  if (encola == 0)
    acum_sincola += reloj - init_sincola;
  float colasnovaciasmedio = acum_cola / (reloj - acum_sincola);
  printf("\nLongitud media de colas no vacias = %.3f", colasnovaciasmedio);
  acum_ocio += (reloj - tultsuc_ocio) * libres;
  float porcentajemedioocio = 100 * acum_ocio / (m * reloj);
  printf("\nporcentaje medio de tiempo de ocio por servidor = %.3f", porcentajemedioocio);
  printf("\nLongitud m�xima de la cola = %d", maximacola);
  printf("\n");

  sum_estancia_media += estanciamedia;
  sum_cola_media += encolamedio;
  sum_sistema_media += ensistemamedio;
  sum_no_vacias_media += colasnovaciasmedio;
  sum_ocio_media += porcentajemedioocio;
  sum_colamaxima_media += maximacola;
  sum_retraso_medio += retrasomedio;

  estancia_media_desviacion += pow(estanciamedia, 2);
  cola_media_desviacion += pow(encolamedio, 2);
  sistema_media_desviacion += pow(ensistemamedio, 2);
  no_vacias_media_desviacion += pow(colasnovaciasmedio, 2);
  ocio_media_desviacion += pow(porcentajemedioocio, 2);
  colamaxima_media_desviacion += pow(maximacola, 2);
  retraso_medio_desviacion += pow(retrasomedio, 2);
}

//Si se desea monitorizar, por ejemplo el n�mero medio de clientes en sistema a lo largo del tiempo se puede usar el suceso monitor siguiente, que habr� que inicializar
void monitor()
{
  nodo.suceso = suceso_monitor;
  nodo.tiempo = reloj + 100.0;
  nodo.retraso = nada;
  insertar_lsuc(nodo);
  cout << "tiempo y media en sistema " << reloj << " " << (acum_sistema + (reloj - tultsuc_sistema) * ensistema) / reloj << endl;
  //printf("\n %.3f, %3f","tiempo y media en sistema",reloj,(acum_sistema+(reloj - tultsuc_sistema) * ensistema)/reloj);
}

/* Procedimiento suceso */
void suceso()
{
  switch (nodo.suceso)
  {
  case suceso_llegada:
    llegada();
    break;
  case suceso_salida:
    salida();
    break;
  case suceso_finsimulacion:
    fin();
    break;
  case suceso_monitor:
    monitor();
    break;
  }
}
float desviacion(int n, float media, float sumatorio)
{
  float derecha = sumatorio - (n * media * media);
  return sqrt(derecha / (n - 1));
}

int main(int argc, char *argv[])
{
  int i;

  if (argc != 6)
  {
    printf("\n\nFormato Argumentos -> <numero_servidores tParada tlleg tserv numero_simulaciones>\n\n");
    exit(1);
  }
  sscanf(argv[1], "%d", &m);
  sscanf(argv[2], "%f", &tparada);
  sscanf(argv[3], "%f", &tlleg);
  sscanf(argv[4], "%f", &tserv);
  sscanf(argv[5], "%f", &numero_simulaciones);

  inicializacion();
  for (int i = 0; i < numero_simulaciones; i++)
  {
    inicializacion();
    while (!parar)
    {
      temporizacion();
      suceso();
    }
  }

  float retraso_medio = sum_retraso_medio / numero_simulaciones;
  float estancia_media = sum_estancia_media / numero_simulaciones;
  float cola_media = sum_cola_media / numero_simulaciones;
  float sistema_media = sum_sistema_media / numero_simulaciones;
  float no_vacias_media = sum_no_vacias_media / numero_simulaciones;
  float ocio_media = sum_ocio_media / numero_simulaciones;
  float colamaxima_media = sum_colamaxima_media / numero_simulaciones;

  cout << endl
       << "--------Medias--------" << endl;
  cout << "Retraso: " << retraso_medio << endl;
  cout << "Estancia: " << estancia_media << endl;
  cout << "Personas en cola: " << cola_media << endl;
  cout << "Personas en sistema: " << sistema_media << endl;
  cout << "Longitud colas no vacias: " << no_vacias_media << endl;
  cout << "Porcentaje de ocio: " << ocio_media << endl;
  cout << "Longitud maxima de la cola: " << colamaxima_media << endl;

  cout << endl
       << "--------Desviacion--------" << endl;
  cout << "Retraso: " << desviacion(numero_simulaciones, retraso_medio, retraso_medio_desviacion) << endl;
  cout << "Estancia: " << desviacion(numero_simulaciones, estancia_media, estancia_media_desviacion) << endl;
  cout << "Personas en cola: " << desviacion(numero_simulaciones, cola_media, cola_media_desviacion) << endl;
  cout << "Personas en sistema: " << desviacion(numero_simulaciones, sistema_media, sistema_media_desviacion) << endl;
  cout << "Longitud colas no vacias: " << desviacion(numero_simulaciones, no_vacias_media, no_vacias_media_desviacion) << endl;
  cout << "Porcentaje de ocio: " << desviacion(numero_simulaciones, ocio_media, ocio_media_desviacion) << endl;
  cout << "Longitud maxima de la cola: " << desviacion(numero_simulaciones, colamaxima_media, colamaxima_media_desviacion) << endl;
}