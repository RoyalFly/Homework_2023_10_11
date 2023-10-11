//
// Created by 98383 on 2023/9/30.
//

#include "main.h"

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) { // 收包
  CAN_RxHeaderTypeDef Rx_Message;
  uint8_t data[8];
  //if (HAL_CAN_GetState(hcan) != HAL_CAN_STATE_RESET) {
    HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &Rx_Message, data);
    HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_1);
  /*  if (data == 0) {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_RESET);
    } else if (data == 1) {
      HAL_GPIO_WritePin(GPIOG, GPIO_PIN_1, GPIO_PIN_SET);
    } */
  //}
}

