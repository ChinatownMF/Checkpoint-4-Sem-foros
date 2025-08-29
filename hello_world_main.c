/*
* SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
*
* SPDX-License-Identifier: CC0-1.0
*/

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

SemaphoreHandle_t Semaphore1;
SemaphoreHandle_t Semaphore2;
SemaphoreHandle_t Semaphore3;

void vTaskExample1(void *pvParameters) {
    while (1) {
        xSemaphoreTake(Semaphore1, portMAX_DELAY);
        printf("[Tarefa 1] Executou - Luighi\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(Semaphore2);
    }
}

void vTaskExample2(void *pvParameters) {
    while (1) {
        xSemaphoreTake(Semaphore2, portMAX_DELAY);
        printf("[Tarefa 2] Executou - Luighi\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(Semaphore3);
    }
}

void vTaskExample3(void *pvParameters) {
    while (1) {
        xSemaphoreTake(Semaphore3, portMAX_DELAY);
        printf("[Tarefa 3] Executou - Luighi\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
        xSemaphoreGive(Semaphore1);
    }
}

void app_main(void) {
    Semaphore1 = xSemaphoreCreateBinary();
    Semaphore2 = xSemaphoreCreateBinary();
    Semaphore3 = xSemaphoreCreateBinary();

    xSemaphoreGive(Semaphore1);

    xTaskCreate(vTaskExample1, "Tarefa1", 2048, NULL, 1, NULL);
    xTaskCreate(vTaskExample2, "Tarefa2", 2048, NULL, 1, NULL);
    xTaskCreate(vTaskExample3, "Tarefa3", 2048, NULL, 1, NULL);
}
