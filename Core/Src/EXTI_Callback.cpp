//
// Created by 98383 on 2023/9/30.
//

#include "main.h"
#include "can.h"

void CAN_Send_Message(uint8_t flag);

void Led1_Control();

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_PIN) { // 按一次发一个包
  //HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_1);
  if (GPIO_PIN == GPIO_PIN_2) {
    //HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_1);
    Led1_Control();
  }
}

void Led1_Control() {
  static bool led1_state = false; // 默认LED状态为关闭
  if (led1_state) {
    CAN_Send_Message(10);
  } else {
    CAN_Send_Message(20);
  }
  led1_state = !led1_state;
}


void CAN_Send_Message(uint8_t flag) {
  uint8_t data[2];
  uint32_t can_tx_mail_box_=CAN_TX_MAILBOX0;
  CAN_TxHeaderTypeDef CAN_Tx_structure;
  CAN_Tx_structure.DLC = 2; // 数据长度
  CAN_Tx_structure.StdId = 0x200;
  CAN_Tx_structure.IDE = CAN_ID_STD;
  CAN_Tx_structure.RTR = CAN_RTR_DATA;
  data[0]=(flag)>>8;
  data[1]=flag;
  if (HAL_CAN_AddTxMessage(&hcan1, &CAN_Tx_structure, data,
                       &can_tx_mail_box_) != HAL_OK){
    HAL_GPIO_TogglePin(GPIOG,GPIO_PIN_1);
  }
  while (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) != 3);
}
