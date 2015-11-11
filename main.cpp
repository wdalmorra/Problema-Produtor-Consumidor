#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <thread>
#include <time.h>

using namespace std;

void *produtor(void *fileName);
void *consumidor(void *i);
void guardaLinha();
string consomeLinha(int i);
void computaString(string s);

vector<string> linhasDoArquivo;
pthread_mutex_t protegeDados = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t protegeResposta = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// pthread_cond_t condConsumidor = PTHREAD_COND_INITIALIZER;

ifstream arq;

bool finished = false;
bool bufferCheio = false;
bool bufferVazio = true;
int respostaFinal = 0;
string stringBuscada;

/* Debug imprime um log de atividades como criacao de
threads, finalizacao e leitura de linhas */
bool DEBUG = false;
bool SLEEP = true;

/* */
int main(int argc, char const *argv[])
{

  int rc;
  int numeroDeThreads;
  pthread_t produtorT;
  
  //  String passada como argumento
  stringBuscada = argv[2];

  // Número de threads concorrentes suportadas, baseada no número de cores
  numeroDeThreads = thread::hardware_concurrency();

  if (numeroDeThreads == 0)
  {
    numeroDeThreads = 1;
  }

  pthread_t consumers[numeroDeThreads];


  rc = pthread_create(&produtorT,NULL,produtor,(void *)argv[1]);

  if (rc)
  {
    cout << "Error:unable to create myThread"  << endl;
  }

  for (int i = 0; i < numeroDeThreads; ++i)
  {
    rc = pthread_create(&consumers[i],NULL,consumidor,(void *)i);
    if (rc)
    {
      cout << "Error:unable to create consumer " << i << endl;
    }
  }

  pthread_join(produtorT,NULL);

  for (int i = 0; i < numeroDeThreads; ++i)
  {
    pthread_join(consumers[i],NULL);
  }

  cout<< respostaFinal << endl;

  pthread_exit(NULL);

  return 0;
}

/* Função Produtor */
void *produtor(void *fileName)
{

  bool aguardar;
  pthread_mutex_lock(&protegeDados);
  arq.open((char*)fileName);
  pthread_mutex_unlock(&protegeDados);
  
  while (!arq.eof())
  {

    // // busy waiting
    // do
    // {
    //   pthread_mutex_lock(&protegeDados);

    //   aguardar = false;

    //   if (bufferCheio)
    //   {
    //     aguardar = true;
    //     pthread_mutex_unlock(&protegeDados);
    //   }

    // } while (aguardar == true);

    // SEÇÃO CRÍTICA

    pthread_mutex_lock(&protegeDados);
    while (bufferCheio)
    {
      pthread_cond_wait(&cond, &protegeDados);
    }

    guardaLinha();
    bufferVazio = false;
    pthread_cond_signal(&cond);

    pthread_mutex_unlock(&protegeDados);

    if (SLEEP)
    {
      usleep(0.1);
    }
  }

  pthread_mutex_lock(&protegeDados);
  finished = true;
  pthread_mutex_unlock(&protegeDados);

  pthread_exit(NULL);
}

/* Função Consumidor */
void *consumidor(void *i)
{

  string s;
  bool aguardar;

  if (DEBUG)
  {
    pthread_mutex_lock(&protegeDados);
    cout << "Created Thread " << *((int*)&i) << endl;
    pthread_mutex_unlock(&protegeDados);
  }
  // Enquanto há algo a ser consumido
  while(!finished || linhasDoArquivo.size() > 0)
  {
    // // Busy waiting
    // do
    // {
    //   pthread_mutex_lock(&protegeDados);

    //   aguardar = false;
    //   if (bufferVazio && !finished)
    //   {
    //     aguardar = true;
    //     pthread_mutex_unlock(&protegeDados);
    //   }
    // }
    // while (aguardar);

    // SEÇÃO CRÍTICA
    pthread_mutex_lock(&protegeDados);
    while (bufferVazio && linhasDoArquivo.size() > 0)
    {
      pthread_cond_wait(&cond, &protegeDados);
    }

    bufferCheio = false;
    // Consome uma linha do buffer
    s = consomeLinha(*((int*)&i));

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&protegeDados);
    // Computa a linha que foi consumida
    computaString(s);

    // Descansa
    if (SLEEP)
    {
      usleep(0.2);
    }

  }

  if (DEBUG)
  {
    pthread_mutex_lock(&protegeDados);
    cout<<"Thread "<< *((int*)&i) << " Finalizou BufferVazio: " << bufferVazio << "Terminou: " << finished << endl;
    pthread_mutex_unlock(&protegeDados);
  }

  pthread_exit(NULL);
}

/* Método simples executado pela Thread produtor
Simplesmente lê uma linha do arquivo e guarda no buffer
respeitando a sincronização das Threads */
void guardaLinha()
{

    string s;

    getline(arq,s);
    if (DEBUG)
    {
      cout << "LINE READ" << endl;
    }

    linhasDoArquivo.push_back(s);

    if (!(linhasDoArquivo.size() < 5))
    {
      bufferCheio = true;
    }

}

/* Consome uma linha do buffer  */
string consomeLinha(int i)
{

  /* s = linha do arquivo */
  string s = "";

  if (linhasDoArquivo.size() > 0)
  {
    s = linhasDoArquivo[0];
    linhasDoArquivo.erase(linhasDoArquivo.begin());
    if (DEBUG)
    {
      cout << "Line erased by " << i << endl;
    }
    if (linhasDoArquivo.size() == 0)
    {
      bufferVazio = true;
    }
  }
  return s;

}

/* Busca a string até o final da linha */
void computaString(string s)
{

  bool ok;
  int counter = 0;
  int j;

  if (s == "")
  {
    return;
  }

  /* Percorre caracter a caracter, da posição 0 até a posição com o valor
  "tamanho da linha" menos "tamanho da string" (após essa posição não seria
  mais possível encontrar a string buscada)*/
  for (int i = 0; i < (s.size()-stringBuscada.size())+1; i++)
  {
    ok = true;
    for (j = 0; j < stringBuscada.size(); j++)
    {
      if (s[i+j] != stringBuscada[j])
      {
        ok = false;
        break;
      }
    }
    /* Se encontra a ocorrência da string, incrementa o contador global */
    if (ok)
    {
      pthread_mutex_lock(&protegeResposta);
      respostaFinal++;
      pthread_mutex_unlock(&protegeResposta);
      i = j+i;
    }
  }

}
