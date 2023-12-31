# Desenvolvimento de Algoritmos para Solucionar o Problema “Somando Dominós”

- Autores: Gabriel Hoffmann e Vanessa Silveira

A solução possui uma classe Domino para salvar o ladoX, ladoY, inverterDiff e removerDiff de cada dominó na entrada. 
É criada uma dominoList e essa é passada para uma instância da classe ComparadorDomino que será responsável por manipular essa lista através da função recursiva compararValores.
O objetivo é encontrar o array listaSucesso que possuirá uma lista de dominós a serem invertidos para a resolução do problema ou uma listaSucessoDescarte que é uma lista encadeada com várias listas de dominós que solucionariam o nosso problema invertendo e descartadando o dominó de mesmo índice na listaDescarte.

Para compilar o projeto deve ser usado o Java 12 e de preferência o Intellij como IDE.

Abrindo o projeto com o Intellij, dentro da pasta src, existe a classe Main, na estrutura do projeto deve-se clicar com o botão direito e selecionar a opção Run 'Main.main()'. Outras opções é abrir o arquivo da classe Main no Intellij e clicar no botão verde de play ao lado da declaração da classe Main ou da função main. Ou simplesmente pressionar Shift+F10 que é o comando de execução no Intellij.

