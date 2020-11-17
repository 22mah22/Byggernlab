/*
 * usart.c
 *
 * Created: 11.11.2020 15:24:11
 *  Author: magneah
 */ 
#include "usart.h"
#include "sam.h"

void usart_init(){
	
	uint32_t ul_sr;
	
	
	PIOB->PIO_PDR |= PIO_PDR_P21; //disable io on pinb 21   RXD2
	PIOB->PIO_PDR |= PIO_PDR_P20; //disable io on pinb 20    TXD2
	PIOB->PIO_ABSR &= ~PIO_ABSR_P21; //PIO set peripheral b on pinb 21*/
	PIOB->PIO_ABSR &= ~PIO_ABSR_P20; //PIO set peripheral b on pinb 20*/


	
	// Enable the peripheral USART2 controller in Power Management Controller (PMC)
	PMC->PMC_PCER0 = 1 << ID_USART2;
	
	// Enable USART interrupt in the Nested Vectored Interrupt Controller(NVIC)
	NVIC_EnableIRQ((IRQn_Type) ID_UART);
	
	
	
	PIOA->PIO_IDR = PIO_PA10A_RXD0 | PIO_PA11A_TXD0;

	// Disable the Parallel IO (PIO) of the URXD and UTXD pins so that the peripheral controller can use them
	PIOA->PIO_PDR = PIO_PA10A_RXD0 | PIO_PA11A_TXD0;

	// Read current peripheral AB select register and set the UTXD and URXD pins to 0 (UART is connected as peripheral A)
	ul_sr = PIOA->PIO_ABSR;
	PIOA->PIO_ABSR &= ~(PIO_PA10A_RXD0 | PIO_PA11A_TXD0) & ul_sr;

	// Enable pull up resistor on URXD and UTXD pin
	PIOA->PIO_PUER = PIO_PA10A_RXD0 | PIO_PA11A_TXD0;

	// Uart configuration
	
	// Enable the peripheral UART controller in Power Management Controller (PMC)
	PMC->PMC_PCER0 = 1 << ID_USART0;

	// Reset and disable receiver and transmitter
	UART->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS;

	// Set the baudrate
	UART->UART_BRGR = 547; // MCK / 16 * x = BaudRate (write x into UART_BRGR)

	// No parity bits
	UART->UART_MR = UART_MR_PAR_NO | UART_MR_CHMODE_NORMAL;

	// Disable PDC channel
	UART->UART_PTCR = UART_PTCR_RXTDIS | UART_PTCR_TXTDIS;

	// Configure interrupts on receive ready and errors
	UART->UART_IDR = 0xFFFFFFFF;
	UART->UART_IER = UART_IER_RXRDY | UART_IER_OVRE | UART_IER_FRAME | UART_IER_PARE;

	// Enable UART interrupt in the Nested Vectored Interrupt Controller(NVIC)
	NVIC_EnableIRQ((IRQn_Type) ID_UART);

	// Enable UART receiver and transmitter
	UART->UART_CR = UART_CR_RXEN | UART_CR_TXEN;
}