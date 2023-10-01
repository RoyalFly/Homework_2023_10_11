//
// Created by 98383 on 2023/9/30.
//

#include "main.h"

extern CAN_HandleTypeDef hcan1;

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) { // 收包
  CAN_RxHeaderTypeDef Rx_Message;
  uint8_t data;
  extern int g;
  // 设置接收帧类型
  Rx_Message.DLC = 1;
  Rx_Message.StdId = 0x200;
  Rx_Message.IDE = CAN_ID_STD;
  Rx_Message.RTR = CAN_RTR_DATA;
  if (HAL_CAN_GetState(&hcan1) != HAL_CAN_STATE_RESET) {
    g++;
    HAL_CAN_GetRxMessage(&hcan1, CAN_RX_FIFO0, &Rx_Message, &data);
    if (data == 0) {
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
    } else if (data == 1) {
      HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    }
  }
}