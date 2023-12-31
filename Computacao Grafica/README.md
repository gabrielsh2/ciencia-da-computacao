# Computação Gráfica - Gabriel Hoffmann

## M1

Adicionado os Projetos:

- Hello3D
- Hello3D - withShaderClass
- HelloTextures

Seguindo como base o exemplo passado na tarefa e fazendo as alterações solicitadas.

## M2

Adicionado o projeto M2 - Cubo.

Esse projeto foi criado com base na pirâmide e primeiramente foi alterado o vetor de vértices e a função de desenhar triângulos para representar um cubo.

Após isso foram criadas funcionalidades de escala usando o glm::scale e de translação utilizando o glm:translate. Permitindo alterar aumentar e diminuir a escala do cubo e move-lo a partir do teclado.

Por último foi criada mais uma instância de cubo alterando o vertexShader, atualizado a função de desenho para uma função com instâncias e alterado o método setupGeometry para utilizar um segundo VBO que controle as instâncias.

## M2 - Vivencial

Adicionado o projeto M2 Vivencial - Suzanne

Utilizando o OBJ disponibilizado pela professora no git e o projeto M2 - Cubo como base foi feito a leitura do OBJ Suzanne e mostrado em tela.

Para isso busquei tutoriais para ler um OBJ e armazenar seus vértices em um vetor. Substituindo dessa forma o array de vértices que representavam o cubo e suas cores.

Além disso também foi mudado as chamadas das funções de desenho no loop para representar a Suzanne da mesma forma que está no gif da professora no teams.

## M3

Adicionado o projeto M3 - Texturas.

Nesse projeto foi adicionado texturas na Suzanne.

Não evoluí a partir do projeto da vivencial pois ao ver o projeto de exemplo HelloTextures acreditei que serviria melhor para o propósito da atividade. Além de já ter uma base com o carregamento de texturas o vertex shader e fragment shader estão separados em outros arquivos facilitando a legibilidade do código.

Além disso refatorei o método loadOBJ para adapta-lo para a atividade e remover o uso de deprecateds como o fscanf. Foi criado também uma função para ler o .mtl.

## M4

Adicionando o projeto M4 - Iluminação

Nesse projeto foi adicionado iluminação da Suzanne.

Esse código foi desenvolvido a partir do projeto do M3 e com o auxílio do projeto Hello3D Phong que a professora disponibilizou no repositório. A partir disso foi criado um vetor para armazenar os vertices normais do OBJ da Suzanne, foi lido do MTL as constantes necessárias para o modelo de iluminação Phong. No fragment shader foi usado as fórmulas passadas em aula para criar o efeito de iluminação.

## M5

Adicionado o projeto M5 - Camera

Nesse projeto foi adicionado uma câmera em primeira pessoa que pode ser rotacionada pelo mouse e movida via WASD no teclado.

Esse código foi evoluido do código de iluminação do M4, primeiramente configurando a câmera conforme visto em aula, criando uma classe Camera capaz de configurar os parâmetros e com funções auxiliares de movimentação e rotação. Além disso foi utilizada a classe Mesh disponibilizada no exemplo Hello3D Phong para deixar mais limpo e simples o código de como a Suzanne é renderizada em tela.

## M6

Adicionado o projeto M6 - Trajetórias

Nesse projeto foi adicionado uma trajetória na Suzanne a partir de uma interpolação bezier.

O código foi evoluido a partir do projeto de câmera do M5, adicionei as classes de curva disponibilizadas no projeto exemplo, estou entregando utilizando a classe Bezier no código, porém as outras classes estão disponíveis no código para alternar entre elas.

Os pontos de controle da trajetória são configurados a partir do arquivo config.txt na pasta animation, lá eles podem ser alterados e refletir no objeto. A trajetória da Suzanne é alterada a partir desse conjunto de pontos, que são lidos e iterados atualizando a posição do objeto dentro do loop principal.

## Grau B

Adicionado o projeto Projeto Final - GB

Nesse projeto foi combinado os aprendizados de outras aulas e assim feito um Visualizador de Cenas 3D.

Mais informações sobre o projeto no README de seu diretório.
