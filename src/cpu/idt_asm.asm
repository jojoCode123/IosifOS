global default_handler_init
extern default_handler

global isr0
extern isr0_handler

default_handler_init:
    pusha
    call default_handler
    popa
    iret

isr0:
    pusha
    call isr0_handler
    popa
    iret