global default_handler_init
extern default_handler

global isr1
extern isr1_handler

default_handler_init:
    pusha
    call default_handler
    popa
    iret

isr1:
    pusha
    call isr1_handler
    popa
    iret