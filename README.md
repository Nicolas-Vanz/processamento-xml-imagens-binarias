Esse projeto foi desenvolvido com o intuito de apresentar um método para contagem
de componentes conexos de imagens binárias extraídas de arquivos XML.
Segue um conjunto de definições para melhor entendimento do projeto.

 - Vizinhança-4 : a vizinhança-4 de um pixel P de coordenada (x, y) é o conjunto de pixels adjacentes a P, isto é, os pixels cujas coordenadas são: (x + 1, y), (x – 1, y), (x, y + 1), ou (x, y – 1).

 - Caminho: Um caminho de um pixel P ao Q é o conjunto de pixels P = a 1 , a 2 , ... , a n = Q, tal que a i + 1 está na vizinhança-4 de a i . No contexto desse projeto o caminho pode apenas ser composto por pixels de cor branca, representados pelo valor 1 nos arquivos xml.

 - Componente conexo: é o maior conjunto de pixels tal que para todo par de pixels P, Q desse conjunto é possível encontrar um caminho de P a Q.
