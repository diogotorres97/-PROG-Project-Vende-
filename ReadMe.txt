Trabalho Pratico - "Supermercado "Vende++" - suporte para decis�es informadas"

Ficheiros : 
Client.cpp
Client.h
clients.txt
Date.cpp
Date.h
defs.h
main.cpp
Menus.cpp
Menus.h
Product.cpp
Product.h
products.txt
Read_files.cpp
Read_files.h
ReadMe.txt
Transaction.cpp
Transaction.h
transactions.txt
utils.cpp
utils.h
Vende++.cpp
Vende++.h

Data do inicio do projeto :  28 de abril de 2016
Data de fim do projeto : 18 de maio de 2016

Trabalho realizado por:
Grupo 05
Diogo Torres          Rui Quaresma
up201506428           up201503005
Turma 3

O projeto est� funcional e concluido, cumprindo todos os objetivos e com todas as medidas implementadas de acordo com o enunciado do projeto:

1.Ler e guardar a informa��o de clientes, produtos (s� leitura)  e transa��es em ficheiros;
2.Gest�o de clientes: criar, alterar,  remover e listar os clientes por ordem alfab�tica do seu nome. 
3.Gest�o  de  transa��es:   listar  todas  as   transa��es  num   intervalo  de  tempo  data;  listar  por  ordem cronol�gica as transa��es de um cliente cujo nome foi dado;
4.Efetuar compras (adicionar transa��es). Ao efetuar uma compra deve actualizar o montante total de compras do correspondente cliente;
5.Visualizar de modo formatado informa��o: de um cliente ou de todos os clientes;
6.Visualizar   de   modo   formatado   as   transa��es:   de   um   cliente;   de   um   dia;   entre   duas   datas especificadas; ou todas as transa��es;
7.Calcular os  Bottom10  (piores) clientes. Um cliente � tanto pior quanto menor for o montante de compras efetuado.
8.Efetuar publicidade personalizada para um cliente, para os  Bottom10  clientes utilizando o sistema de recomenda��o.


Foi implementado v�rios controlos de erros a todos os niveis.
A publicidade individual foi utilizada uma matriz de booleanos como referido no enunciado, para a parte dos bottom10 foi utilizado outro processo h� base de multimaps.
