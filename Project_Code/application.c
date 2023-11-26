/* 
 * File:   application.c
 * Author: AyaAli
 * Created on September 22, 2023, 10:24 AM
 */
#include "application.h"


volatile uint_8 Program_Selected = 0;
led_t led1 = {
.Port_Name = PORTC_INDEX,
.pin = PIN0,
.led_statues = LED_OFF
};
led_t led2 = {
.Port_Name = PORTC_INDEX,
.pin = PIN1,
.led_statues = LED_OFF
};


Ex_Interrupt_INTx_t int0_obj= {
.Ext_Intterrupt = int0_ISR,
.edge = EX_Interrupt_Rising_Edge,
.priority = Interrupt_Periority_HIGH,
.source = EX_Interrupt_INT0,
.mcu_pin.port = PORTB_INDEX,
.mcu_pin.pin = PIN0,
.mcu_pin.direction = Input
};

void int0_ISR(void){
Std_ReturnType ret = E_NOT_OK;    
Program_Selected++;
if(Program_Selected == 3){
Program_Selected = 0;
}
ret = Data_EEPROM_Write_Data(0x3ff, Program_Selected);
}

void Program_1(void){
    led_toggle(&led1);
    
}
void Program_2(void){
    led_toggle(&led2);
}

int main() {
   
Std_ReturnType ret = E_NOT_OK;
ret = Interrupt_INTx_Initialization(&int0_obj);
ret = led_initialize(&led1);
ret = led_initialize(&led2);


application_initialize();

ret = Data_EEPROM_Read_Data(0x3ff, &Program_Selected);
while(1){  
    if(Program_Selected == 1){
        Program_1();
    }
    else if(Program_Selected == 2){
        Program_2();
    }
    else{
    led_turn_off(&led2);
    led_turn_off(&led1);
    }

}
 return (EXIT_SUCCESS);
}
void application_initialize(void){
   ECU_Layer_initialize();
  
}
