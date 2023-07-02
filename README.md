Funcionamento do programa 

O projeto conta com 1 biblioteca denominada lista.h que engloba um total de 10 funções responsáveis pelas ações que o programa executa, uma do tipo char, uma que utiliza um ponteiro como retorno e as demais são definidas como void.  

Por padrão, o programa possui uma lista de dez funcionários salvos em um arquivo binário chamado "funcionarios.bin". Os dados desses funcionários são salvos em ordem crescente de código, variando de 1000 a 1009. Cada funcionário possui um código, telefone, celular, nome, departamento e um e-mail único. No entanto, a empresa ACME S.A é igual para todos os funcionários. 

A fim de facilitar a busca por nome e a exibição de um relatório individual de cada funcionário salvo, o programa salva e imprime o nome das pessoas em letras minúsculas independentemente da forma que o usuário o inseriu. 

No menu principal foi utilizado a função switch case dentro de um do while para fazer um controle de quais das funcionalidades o usuário deseja utilizar dentre aquelas que o programa oferece, e assim que cada ação é executada ele volta para o início para que o usuário escolha uma nova função do programa.   

A variável “lista” utilizada para armazenar esses dados foi definida na função main. Para fazer a sua manipulação ela foi passada para as funções como ponteiro para ponteiro, para que assim, seja possível fazer as manipulações dessa variável acessando diretamente o seu endereço na memória. 

 

Manual de instruções 

Ao inicializar o programa, o usuário irá se deparar com um menu que conta com 7 opções responsáveis pelo cadastramento, remoção, busca individual, busca geral, edição e salvamento dos dados. Essas funções são enumeradas de 0 a 6, toda vez que o usuário quiser utilizar alguma funcionalidade específica do programa ele deverá pressionar o número correspondente a chamada de cada funcionalidade, que são elas: 

Opcão 0 - Responsável pelo encerramento imediato do programa. 

Opcão 1 - Responsável pela inserção dos dados dos funcionários. 

Opcão 2 - Responsável pela exclusão dos dados de um determinado funcionário. A exclusão é feita a partir do seu respectivo código. 

Opcão 3 - Responsável pela busca individual de um determinado funcionário. Ao escolher essa opção, o usuário poderá escolher se ele deseja fazer a busca pelo código ou pelo nome. 

Opcão 4 - Responsável pela impressão dos dados de todos os funcionários que estão salvos na lista, essa é a opção que deverá ser utilizada caso o usuário deseja descobri algum dado do funcionário que ele não conhece como código e nome. 

Opcão 5 - Responsável pela edição do funcionário que será selecionado a partir de seu código. 

Opcão 6 – Essa é a última opção do menu principal, ela é responsável pelo salvamento no arquivo.bin de todos as modificações feitas. É importante sempre se atentar a essa função pois o programa NÃO FAZ O SALVAMENTO AUTOMÁTICO DAS MODIFICAÇÕES FEITAS, sendo necessário escolher essa opção sempre que houver alguma alteração antes de sair.  