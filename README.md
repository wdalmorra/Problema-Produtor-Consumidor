## sisop_2015_2_t1 - Team2

Alunos: Inessa Luerce, William de Souza

## Implementação

O trabalho foi desenvolvido em C++, inspirado no problema do Produtor-Consumidor.

Problemas encontrados durante a implementação:

- Múltiplos consumidores:

	Ocorreu o problema durante a espera ocupada onde uma Thread trancava o mutex e pegava o ultimo elemento do buffer, porém enquanto ela retirava esse elemento do buffer, outro Thread ficava preso no método lock() do mutex. Quando a Thread que capturou o último elemento finalmente terminava, setava a flag *bufferVazio* para true, portanto a Thread que estava presa esperando a liberação do mutex ficava em espera ocupada infinitamente. Para resolver, foi necessário verificar também a flag *finished* onde indicava quando não haveria novas linhas a ser lidas do arquivo. Assim, se o buffer estava vazio e não havia nada mais para chegar, a Thread poderia sair da espera ocupada.

- Condição de corrida:

	Ocorreram diversos casos de condição de corrida que passaram despercebidos de início, mas foram logo resolvidos.

## Compilação e execução

- Compilar: $ make
- Compilar e remover executável: $ make all
- Executar: $ ./ContadorStrings caminho/para/arquivo string_a_ser_buscada

## Arquivos de teste

Os arquivos para teste estão disponibilizados em uma pasta externa (link abaixo) e com cópia na pasta "arquivos_teste" do repositório. Os arquivos estão estruturados da seguinte forma:

- testeX-conteudo.txt: arquivo onde será buscada a string
- testeX-resposta.txt: indica a string buscada e o número de ocorrências esperadas

## Tempo de execução em relação ao número de threads

Para o caso de teste 5, que faz a busca em um arquivo com 150 linhas e encontra 2400 ocorrências da string "OLA", foram executados os testes com diferentes números de threads em dois sistemas operacionais diferentes.

**OSX Yosemite versão 10.10.4, x64:**

- 1 thread: 2m32.456s (real), 2m25.758s (user), 0m0.354s (sys)
- 2 threads: 0m10.581s (real), 0m4.983s (user), 0m0.019s (sys)
- 4 threads: 0m6.105s (real), 0m1.002s (user) e 0m0.005s (sys)

**Ubuntu 14.04, x64:**

- 1 thread: 2m31.190s (real), 2m25.201s (user), 0m0.45s (sys)
- 2 threads: 1m16.060s (real), 1m11.775s (user), 0m.220s(sys)
- 4 threads: 0m38.030s (real), 0m35.886s (user), 0m0.132s(sys)



## Links

- SSH Clone URL: git@github.com:compufpel/team02-sisop_2015_2_t1.git
- Arquivos utilizados para testes: https://goo.gl/Uayyx8
- Definição do trabalho: https://goo.gl/aDXTyC



## Referências

- POSIX Threads Programming https://computing.llnl.gov/tutorials/pthreads/
- Linux POSIX Threads http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
