#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "PE_Types.h"
#include "PE_LDD.h"

typedef struct {
  LDD_TDeviceData *handle; /* LDD device handle */
  volatile uint8_t isSent; /* this will be set to 1 once the block has been sent */
  uint8_t rxChar; /* single character buffer for receiving chars */
  uint8_t (*rxPutFct)(uint8_t); /* callback to put received character into buffer */
} UART_Desc;

void SendChar(uint8_t ch, UART_Desc *desc);
void SendString(const unsigned char *str,  UART_Desc *desc);
void Init(void);
void APP_Run(void);

#endif /* APPLICATION_H_ */
