Trabalho Pratico - "Supermercado "Vende++" - suporte para decisões informadas"

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

O projeto está funcional e concluido, cumprindo todos os objetivos e com todas as medidas implementadas de acordo com o enunciado do projeto:

1.Ler e guardar a informação de clientes, produtos (só leitura)  e transações em ficheiros;
2.Gestão de clientes: criar, alterar,  remover e listar os clientes por ordem alfabética do seu nome. 
3.Gestão  de  transações:   listar  todas  as   transações  num   intervalo  de  tempo  data;  listar  por  ordem cronológica as transações de um cliente cujo nome foi dado;
4.Efetuar compras (adicionar transações). Ao efetuar uma compra deve actualizar o montante total de compras do correspondente cliente;
5.Visualizar de modo formatado informação: de um cliente ou de todos os clientes;
6.Visualizar   de   modo   formatado   as   transações:   de   um   cliente;   de   um   dia;   entre   duas   datas especificadas; ou todas as transações;
7.Calcular os  Bottom10  (piores) clientes. Um cliente é tanto pior quanto menor for o montante de compras efetuado.
8.Efetuar publicidade personalizada para um cliente, para os  Bottom10  clientes utilizando o sistema de recomendação.


Foi implementado vários controlos de erros a todos os niveis.
A publicidade individual foi utilizada uma matriz de booleanos como referido no enunciado, para a parte dos bottom10 foi utilizado outro processo há base de multimaps.
