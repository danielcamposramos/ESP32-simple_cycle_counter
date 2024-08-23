#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "math.h"

#define LED_PIN GPIO_NUM_2

int ciclos_MAX = 50;
int ciclos_MIN = 0;
int ciclo_de_trabalho_MAX = 25;
int ciclo_de_trabalho_MIN = 0;
int total_de_ciclos = 0;

void app_main()
{
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    int contador_de_ciclos = 0;
inicio:
    int ciclo_de_trabalho = ciclo_de_trabalho_MIN;
    int apagado = ciclo_de_trabalho_MIN;
    int aceso = ciclo_de_trabalho_MIN;
    for (contador_de_ciclos = contador_de_ciclos; contador_de_ciclos < ciclos_MAX; contador_de_ciclos++)
    {
        for (ciclo_de_trabalho = ciclo_de_trabalho; ciclo_de_trabalho <= ciclo_de_trabalho_MAX; ciclo_de_trabalho++)
            {
                apagado = ciclo_de_trabalho_MAX - ciclo_de_trabalho;
                aceso = ciclo_de_trabalho_MAX - apagado;
                gpio_set_level(LED_PIN,1);
                vTaskDelay(aceso / portTICK_PERIOD_MS);
                gpio_set_level(LED_PIN,0);
                vTaskDelay(apagado / portTICK_PERIOD_MS);
            }
        contador_de_ciclos++;
    }  
    contador_de_ciclos = ciclos_MAX;
    ciclo_de_trabalho = ciclo_de_trabalho_MAX;
    for (contador_de_ciclos = contador_de_ciclos; contador_de_ciclos >= ciclos_MIN; contador_de_ciclos--)
    {
        for (ciclo_de_trabalho = ciclo_de_trabalho; ciclo_de_trabalho >= ciclo_de_trabalho_MIN; ciclo_de_trabalho--)
            {
                apagado = ciclo_de_trabalho_MAX - ciclo_de_trabalho;
                aceso = ciclo_de_trabalho_MAX - apagado;
                gpio_set_level(LED_PIN,1);
                vTaskDelay(aceso / portTICK_PERIOD_MS);
                gpio_set_level(LED_PIN,0);
                vTaskDelay(apagado / portTICK_PERIOD_MS);                
            }     
        contador_de_ciclos--;
    }
	total_de_ciclos++;
	printf("Ciclo %d\n", total_de_ciclos);
    goto inicio;
}
