# sisop_2015_2_t1 - Team2
Inessa Diniz Luerce
William Dalmorra de Souza

Trabalho 1 de SO 2015/2 -- façam fork desse repositório e o tornem privado.

## Descrição

O trabalho 1 consiste em desenvolver um programa paralelo em pThreads e C/C++ que execute em Linux e resolva o problema de contagem de ocorrências de uma string em um arquivo de texto, incluindo ocorrências na mesma linha.

Uma thread deverá ser criada para ler o arquivo para um buffer, enquanto outras threads devem ser criadas para fazer a busca pela string. O resultado final será um número impresso na stdio (nada mais deverá ser impresso na stdio no código final a ser testado).

## Restrições

- O programa deverá ser feito em pThreads e C ou C++ e executar em Linux sem precisar de bibliotecas adicionais;
- Uma thread de processamento deverá ser criada para cada processador/core disponível no computador;
- O paralelismo deve ser aproveitado (ou seja, vários cores -- melhor desempenho);
- O repositório deve ser privado;
- O programa deverá ter apenas dois parâmetros -- o nome do arquivo a ser analisado e a string a ser buscada;
- A string a ser buscada pode ter até 80 caracteres;
- O arquivo terá linhas de até 132 caracteres;
- O trabalho pode ser feito em duplas.

## Material a ser entregue

O material a ser entregue deve estar contido em um repositório privado do github que o professor possa clonar. Entreguem no Classrooom apenas o link para clonar o repositório, a "SSH Clone URL" (algo tipo git@github.com:compufpel/sisop_2015_2_t1.git).

Dentro do repositório:

- Makefile que gere um executável <psearch>;
- README.md contendo os nomes dos alunos e descrevendo a implementação, como os problemas de paralelização e sincronização foram resolvidos, ambiente onde experimentos foram executados e apresentando resultados de tempo de execução e speedup para um número razoável de execuções;
- Link para Google Drive com os casos de teste usados e os resultados esperados (acessível pelo professor);
- Código fonte comentado;
- Commits que façam sentido e mostrem a participação de todos os integrantes do grupo.

## Data de entrega

- Repositórios devem ser atualizados até dia *30/09*
- Apresentação no dia *01/10* em aula

## Referências

- POSIX Threads Programming https://computing.llnl.gov/tutorials/pthreads/
- Linux POSIX Threads http://www.yolinux.com/TUTORIALS/LinuxTutorialPosixThreads.html
