Universidade Federal da Paraiba
Centro de Informatica 

Disciplina: Teoria da Computacao (2021.1)
Professor: Bruno Petrato Bruck

Projeto Final

Simulacao de um Automato Finito Nao-determinıstico

Programa para simular o processamento de Automatos Finitos
Nao-determinısticos (AFNs). 


Link do video de apresentacao: 


Descricao:


A proposta entregue pelo professor era de criar um autômato finito não-determinístico de 3 estados onde Q0 é seu estado inicial, enquanto Q1 e Q2 são os estados finais, o alfabeto aceito pelo autômato é: a,b,c,d. Outras características desse projeto é especificar as transições de cada cadeia e simular todos os possíveis processamentos desse autômato indicado se a cadeia colocada pelo usuário será aceita ou não, incluindo também as transições Epsilons ou vazias, e para cumprimento desse projeto foi decidido o uso da linguagem C/C++ .

Automato
o AFN escolhido aceita cadeias que terminem com as letras “a” ou “b”


Função “GetDescricao”
A função “GetDescricao” tem como objetivo obter os 4 elementos que compõem a estrutura do autômato lendo esses dados de um arquivo de texto e separando as informações de alfabeto, estados que compõem o AFN assim como qual deles é inicial e qual deles é o final. Cada uma dessas 4 informações estaria descrita em uma das linhas do arquivo TXT.

- O “for” é usado para ler as 4 linhas do arquivo, e quando isso acontece o “getline” identifica as linhas de textos que contenham os textos iguais ao conjunto “els”. Caso o programa identifique a linha ele acrescenta um valor de 1 para cada linha.

- Caso não haja informação em uma das linhas o valor daquela linha permanecerá 0 e uma mensagem de erro será exibida.

- Mas caso as informações sejam lidas corretamente, o código irá obter as informações após o sinal “=” linha à linha do texto atribuindo cada valor ao representante na matriz elements[4]

- Por fim, o programa irá procurar a linha do arquivo que contenham o termo “transições” e se baseando no formato definido na classe de transição, incrementando o contador de número de transições sempre que uma nova transição for registrada.

- Caso, o valor de erro seja 0, outra mensagem de erro será exibida 

Função “fazParteAlfabeto”

- Função que irá comparar a cadeia recebida pelo usuário com os símbolos correspondentes ao alfabeto do arquivo de texto, verificando os símbolos da cadeia pertencem ao alfabeto.
 Função “Addnewestado”

A função irá adicionar ao array newEstado um novo estado e verificará se o estado já está presente no array para evitar repetições.

Função “Verify Epsilon”

- Função que verifica possíveis transições vazias através de um contador que verifica todas as transições e quais delas teriam “épsilon” como parte do “symbol” adicionando um novo estado e exibindo um texto. 

Função “updateEstado”

- Essa função transfere os estados do array newEstado para o array estado, e prepara o array newEstado para receber os estados da nova transição.

Função principal
Na função main do código, é chamada a função “getdescricao” para obter os valores do arquivo em texto e atribuí-los no array dos objetos elements e transicoes, finalizando em caso de erro. Cada elemento e seus valores são exibidos na tela assim como as possíveis transições todas lidas a partir do arquivo de texto.

- Após apresentada os elementos e transições do AFN o programa solicita ao usuário uma cadeia para iniciar a simulação. Essa cadeia é então verificada, por meio da função “fazParteAlfabeto”, se possui algum símbolo que não faz parte do alfabeto.

- caso a cadeia apenas possua símbolos do alfabeto, o programa roda um “for” com o tamanho da cadeia inserida pelos usuário. é então verificado se há uma possível transição, caso o estado e o símbolo possibilitem a transição o estado para onde a transição foi permitida é armazenado no array newEstado. Esse processo é repetido para todas as transições e todos novos estados são guardados, esse processo transforma a AFN em uma AFD evitando assim o uso de threads. Por fim são verificas se há algum Epsilon na cadeia e então esses estados são atualizados pela função “updateestado”

-  Para verificar se a cadeia será aceita o programa considera se há algum estado final nos estados em que a cadeia finalizou caso aceite, uma mensagem é exibida com o estado final
