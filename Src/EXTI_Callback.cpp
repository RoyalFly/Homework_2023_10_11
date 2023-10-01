//
// Created by 98383 on 2023/9/30.
//

#include "main.h"
#include "can.h"


void CAN_Send_Message(uint8_t flag);

void Led1_Control();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN) { // 按一次发一个包
  if (GPIO_PIN == GPIO_PIN_2) {
    Led1_Control();
  }
}

void Led1_Control() {
  static bool led1_state = false; // 默认LED状态为关闭
  if (led1_state) {
    CAN_Send_Message(0); // 若为打开，向另一块板传入0即关闭信号
  } else {
    CAN_Send_Message(1); // 传入1为开启信号
  }
  led1_state = !led1_state;
}

void CAN_Send_Message(uint8_t flag) { // 发送开关信号，0为关信号，1为开信号
  uint8_t data;
  extern int d;
  d++;
  CAN_TxHeaderTypeDef CAN_Tx_structure;
  CAN_Tx_structure.DLC = 1;
  CAN_Tx_structure.StdId = 0x200;
  CAN_Tx_structure.IDE = CAN_ID_STD;
  CAN_Tx_structure.RTR = CAN_RTR_DATA;
  data = flag;

  HAL_CAN_AddTxMessage(&hcan1, &CAN_Tx_structure, &data,
                       (uint32_t *)CAN_TX_MAILBOX0);
}