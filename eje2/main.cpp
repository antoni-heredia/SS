#include <iostream>
#include <cmath>
#include <cstdlib>
#include <list>
#include <vector>
#include <numeric>

using namespace std;

const int suceso_llegada = 0;
const int suceso_fin_a = 1;
const int suceso_fin_b = 2;
const int suceso_finsimulacion = 3;
const double tLleg = 1.0;
const double tServA = 0.8;
const double tServB = 0.85;
const double tInic = 0;
const double tFin = 480;

struct suc
{
  int suceso;
  float tiempo;
  bool operator<(const suc &otroSuc)
  {
    return tiempo < otroSuc.tiempo;
  }
} ;
list<suc> lsuc;
list<double> tLlegadas;

bool libreA, libreB;
int enColaServA, enColaServB, nClientAntent;

double reloj, tParada, tTotalEnSistemas;
suc Actual;

bool fin;

vector<double> tMedioEstan;
int nSimulaciones;
float generador_exponencial(float media)
{
  float u;
  u = (float)random();
  u = u / (float)(RAND_MAX + 1.0);
  return (-media * log(1 - u));
}

suc nuevo_suceso(int tipo, double tMedio)
{
  suc nuevoSuceso;
  nuevoSuceso.suceso = tipo;
  nuevoSuceso.tiempo = reloj + generador_exponencial(tMedio);
  return nuevoSuceso;
}
suc siguienteSuceso()
{
  Actual = lsuc.front();
  lsuc.pop_front();
  reloj = Actual.tiempo;
}
suc suceso_final()
{
  suc fin_suceso;
  fin_suceso.suceso = suceso_finsimulacion;
  fin_suceso.tiempo = reloj + tFin;
  return fin_suceso;
}

void insertar(suc &suceso)
{
  lsuc.push_back(suceso);
  lsuc.sort();
}

void llegaServ()
{
  tLlegadas.push_back(reloj);
  suc nuevallegada = nuevo_suceso(suceso_llegada, tLleg);
  insertar(nuevallegada);

  if (libreA)
  {
    libreA = false;
    suc servicioA = nuevo_suceso(suceso_fin_a, tServA);
    insertar(servicioA);
  }
  else
  {
    enColaServA++;
  }
}

void suc_fin_a()
{
  if (enColaServA > 0)
  {
    enColaServA--;
    suc nuevoServidor = nuevo_suceso(suceso_fin_a, tServA);
    insertar(nuevoServidor);
  }
  else
  {
    libreA = true;
  }
  if (libreB)
  {
    libreB = false;
    suc nuevoServidor = nuevo_suceso(suceso_fin_b, tServB);
    insertar(nuevoServidor);
  }
  else
  {
    enColaServB++;
  }
}

void suc_fin_b()
{
  nClientAntent++;
  tTotalEnSistemas += reloj - tLlegadas.front();
  tLlegadas.pop_front();
  if (enColaServB > 0)
  {
    enColaServB--;
    suc nuevoServidor = nuevo_suceso(suceso_fin_b, tServB);
    insertar(nuevoServidor);
  }
  else
  {
    libreB = true;
  }
}

void suceso_fin()
{
  fin = true;
  double tMedio = tTotalEnSistemas / nClientAntent;
  tMedioEstan.push_back(tMedio);
}

void iniciar_variables()
{
  reloj = tInic;
  tParada = tFin;

  enColaServA = 0;
  enColaServB = 0;
  libreA = true;
  libreB = true;
  nClientAntent = 0;
  tTotalEnSistemas = 0;
  lsuc.clear();
  tLlegadas.clear();
  suc inicial = nuevo_suceso(suceso_llegada, tLleg);
  insertar(inicial);
  suc final = suceso_final();
  insertar(final);
  fin = false;
}


void suceso()
{

  switch (Actual.suceso)
  {
  case suceso_llegada:
    llegaServ();
    break;
  case suceso_fin_a:
    suc_fin_a();
    break;
  case suceso_fin_b:
    suc_fin_b();
    break;
  case suceso_finsimulacion:
    suceso_fin();
    break;

  }
}

int main(int argc, char* argv[])
{

  nSimulaciones = 1000;
  srand(time(NULL));


  for(int x = 0; x < nSimulaciones;x++){
    iniciar_variables();
    while(!fin){
      siguienteSuceso();
      suceso();
    }
  }
  double media = accumulate(tMedioEstan.begin(), tMedioEstan.end(),0);
  media = media / nSimulaciones;
  cout << "La media de tiempo en estancia es: " << media << endl;
  return 0;
} 