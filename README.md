Como usar PWM no Servo Motor?
Um servo motor é controlado por sinais PWM com um período fixo de 20 ms (50 Hz). A posição do servo é determinada pela largura do pulso (duty cycle) dentro desse período:

1 ms de pulso: Posição de 0 graus.
1,5 ms de pulso: Posição de 90 graus.
2 ms de pulso: Posição de 180 graus.

Ao variar o duty cycle entre 1 ms e 2 ms, o servo se move suavemente entre as posições.

Funcionalidade do Código:
O código controla um servo motor usando PWM no Raspberry Pi Pico. Ele faz o seguinte:

Configura o PWM:

Define a frequência do PWM para 50 Hz (período de 20 ms), que é o padrão para servos.

Configura o pino GPIO para gerar o sinal PWM.

Move o Servo para Posições Específicas:

O servo é movido para três posições fixas: 0°, 90° e 180°, com um intervalo de 5 segundos entre cada movimento.

Movimento Suave entre Posições:

Após mover o servo para as posições fixas, o código faz o servo se mover suavemente de 0° a 180°, incrementando a posição em pequenos passos.

. Para calcular o divisor, usando o warp como 65 535, valor max de 16 bits, usei uma manipulação algébrica da formula de frequência, achando o divisor com 38.147, formula apos manipulação : div = freq_clock/(div*(warp+1)) == 38.147.
. Para achar o valor do Duty cicle para a função do pwm, coloquei ((valor ms)/20.0)*warp.

Led: apos os experimentos, foi verificado que ele pisca quando altera a intensidade

1. Por que o LED pisca?
O efeito de piscar ocorre quando a frequência do PWM é muito baixa, fazendo com que o olho humano perceba a alternância entre os estados "ligado" e "desligado" do LED. Isso acontece porque:

Frequência do PWM:

Se a frequência do PWM for menor que 50 Hz, o olho humano consegue perceber a alternância entre os estados, resultando em um efeito de piscar.

Para evitar o piscar, a frequência do PWM deve ser superior a 50 Hz (idealmente acima de 100 Hz).

Velocidade da transição (fade):

Se o tempo de transição entre os níveis de brilho for muito lento (por exemplo, com um sleep_ms muito alto), o LED pode parecer piscar em vez de variar o brilho suavemente.

