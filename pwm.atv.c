#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

const uint servo_pin = 22;
#define warp 65535  // Valor máximo de 16 bits

/* calculo do divisor:
freq_clock = 125*10^6, warp = 65535, freq = 50
div = freq_clock/(div*(warp+1)) == 38.147*/

/* calculo dos Duty cicle: 
case1:  2.4 ms(180 graus)
case2: 1.47 ms(90 graus)
case3: 0.5 ms(0 graus)


*/
/* ciclo ativo convertido, formula: ((ton)/20.0f)*warp
ton1: 2.4 == 7864(Dc)
ton2: 1.47 == 4816(Dc)
ton3: 0.5 == 1638 (Dc)
*/

// Tempos em milissegundos para as posições do servo
#define position1 2.4f  // 180 graus
#define position2 1.47f // 90 graus
#define position3 0.5f  // 0 graus

// Função para configurar o PWM no pino GPIO
void setup_pwm(uint servo_pin) {
    gpio_set_function(servo_pin, GPIO_FUNC_PWM);  // Configura o pino para função PWM
    uint slice_num = pwm_gpio_to_slice_num(servo_pin);  // Obtém o slice do PWM
    uint channel = pwm_gpio_to_channel(servo_pin);  // Obtém o canal do PWM

    // Configura a frequência do PWM para 50 Hz (período de 20 ms)
    pwm_set_clkdiv(slice_num, 38.147f);  // Divisor de clock
    pwm_set_wrap(slice_num, warp);  // Wrap = 65.535
    pwm_set_enabled(slice_num, true);  // Habilita o PWM
}

int main() {
    stdio_init_all();  // Inicializa a comunicação serial (para debug)
    setup_pwm(servo_pin);  // Configura o PWM no pino

    uint slice_num = pwm_gpio_to_slice_num(servo_pin);
    uint channel = pwm_gpio_to_channel(servo_pin);
    uint16_t convert1 = (uint16_t)((position1 / 20.0f) * warp);
    uint16_t convert2 = (uint16_t)((position3 / 20.0f) * warp);
    float current = position3;

    pwm_set_chan_level(slice_num, channel, (uint16_t)((position3 / 20.0f) * warp));
    while (true) {
        // Move o servo para a posição de 180 graus (2,4 ms de duty cycle)
        pwm_set_chan_level(slice_num, channel, (uint16_t)((position1 / 20.0f) * warp));
        sleep_ms(5000);

        // Move o servo para a posição de 90 graus (1,47 ms de duty cycle)
        pwm_set_chan_level(slice_num, channel, (uint16_t)((position2 / 20.0f) * warp));
        sleep_ms(5000);

        // Move o servo para a posição de 0 graus (0,5 ms de duty cycle)
        pwm_set_chan_level(slice_num, channel, (uint16_t)((position3 / 20.0f) * warp));
        sleep_ms(5000);

        //giros de 180 graus de forma infinita        
        while(true){
            if(current<position1){
                while(position1>current){
                    current +=0.05;
                    pwm_set_chan_level(slice_num, channel, (uint16_t)((current / 20.0f) * warp));
                    sleep_ms(10);
                }
            }
            else{
                while(current>position3){
                    current -=0.05;
                    pwm_set_chan_level(slice_num, channel, (uint16_t)((current / 20.0f) * warp));
                    sleep_ms(10);
                }
            }
            
        }
            
    }

    return 0;
}