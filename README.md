# Compilação
Nesta sessão será abordada a forma de compilação do projeto.

## Dependências

- Compilador C++.

- cmake.

Entre no diretório `build`. 

    cd build

Execute o comando do cmake para compilar o projeto:

    cmake --build .


# Execução 
Para executar o projeto: 

    ./snaze

## Avaliação CP1

### Snake/Pacman
O jogo deveria conter o modo snake/pacman. Em ambos os modos não é possível andar pra trás. No modo snake deve ser desenhado o corpo.

**Avaliação**

50% apenas o modo pacman foi feito

### Render.ui
O jogo deveria desenhar a UI corretamente, mostrando ao menos as vidas, o nível e o score.

**Avaliação**

Ok

### Render.mapa
O jogo deveria desenhar o mapa corretamente, com base no arquivo passado como argumento. Ok

**Avaliação**

70% o programa lê um arquivo porém não usa os argumentos passados.

### Render.snake
O jogo deveria desenhar a snake corretamente.

**Avaliação**
Neste caso vou considerar Ok, pois estou mais preocupado com o posicionamento e movimentação da snake no mapa.

### Logic.colisão e Logic.comida
O jogo deve se comportar corretamente quando ocorre uma colisão com comida e com paredes.

**Avaliação**

Vou considera 60% uma vez que existem bugs quando a cobrinha colide com a comida ou com as paredes.

### Transição de mapas
O jogo deve ter transição de mapa uma vez que um mapa é terminado.

**Avaliação**

Não implementado.

### Interação com o usuário
O jogo deve perguntar ao usuário se quer continuar/reiniciar o nível/reiniciar o jogo a cada transição de mapa

**Avaliação**

Não implementado

### Classe Level ou similar
O software deve encapsular as funcionalidades do nível em uma classe.

**Avaliação**

Ok

### Classe Player ou similar
O software deve encapsular as decisões do jogo em uma classe.

**Avaliação**

Ok

### Classe Snake ou similar
O software deve encapsular as funcionalidades relacionadas à snake em uma classe. 

**Avaliação**

OK

## Comentários gerais CP1

- Embora você tenha feito todas as implementaçãoes no .h não vou tirar pontos.
- No caso do pacman, como tinhamos conversado não quero que você considere a direção em que o pacman volta, assim deixa o problema mais próximo do snake.
- Seu algoritmo para encontrar a ação aleatória não ficou muito bom, como te falei, o ideal era vc verificar primeiro quais as ações possíveis e depois escolher uma delas aleatóriamente. No seu caso o algoritmo fica um tempo significante tomando decisoes erradas.
- Quando ocorre uma colisão sempre dá um segfault, não entendi exatamente o que pode ser, mas sugiro que você compile com o address sanitizer antes para verificar.