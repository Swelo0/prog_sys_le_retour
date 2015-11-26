%include "const.inc"

extern exception_handler
extern irq_handler

section .text   ; start of the text (code) section
align 4         ; the code must be 4 byte aligned

;------------------------------------------------
; Loading into CPU
global idt_flush
idt_flush:
	mov  eax, [esp+4]	; Get the pointer to the IDT (parameter)
	lidt [eax]			; Loading
	ret

;------------------------------------------------
; CPU exceptions (no code)
%macro isr_nocode 1
global _isr_%1
_isr_%1:
	cli          	; disable interrupts
    push    0    	; dummy error code
    push    byte %1 ; exception number
    jmp     exception_wrapper
%endmacro

;------------------------------------------------
; CPU exceptions (code)
%macro isr_code 1
global _isr_%1
_isr_%1:
	cli          	; disable interrupts
    push    byte %1 ; exception number
    jmp     exception_wrapper
%endmacro	

;------------------------------------------------
; IRQ
%macro irq 1
global _irq_%1
_irq_%1:
	cli          	; disable interrupts
    push    0    	; dummy error code
    push    byte %1 ; exception number
    jmp     irq_wrapper
%endmacro	

;------------------------------------------------
; Wrappers
%macro wrapper 1
%1_wrapper:
    ; Save all registers
    push    eax
    push    ebx
    push    ecx
    push    edx
    push    esi
    push    edi
    push    ebp
    push    ds
    push    es
    push    fs
    push    gs

    ; Load kernel data descriptor into all segments
    mov     ax,GDT_KERNEL_DATA_SELECTOR
    mov     ds,ax
    mov     es,ax
    mov     fs,ax
    mov     gs,ax

    ; Pass the stack pointer (which gives the CPU context) to the C function
    mov     eax,esp
    push    eax
    call    %1_handler  ; implemented in idt.c
    pop     eax  ; only here to balance the "push eax" done before the call

    ; Restore all registers
    pop     gs
    pop     fs
    pop     es
    pop     ds
    pop     ebp
    pop     edi
    pop     esi
    pop     edx
    pop     ecx
    pop     ebx
    pop     eax
    
	; Fix the stack pointer due to the 2 push done before the call to exception_wrapper
    add     esp,8
    iret
%endmacro

;------------------------------------------------
; Functions generation
; CPU exceptions
isr_nocode 0
isr_nocode 1
isr_nocode 2
isr_nocode 3
isr_nocode 4
isr_nocode 5
isr_nocode 6
isr_nocode 7
isr_code 8
isr_nocode 9
isr_code 10
isr_code 11
isr_code 12
isr_code 13
isr_code 14
isr_nocode 15
isr_nocode 16
isr_code 17
isr_nocode 18
isr_nocode 19
isr_nocode 20
; Hardware interrupts
irq 0
irq 1
irq 2
irq 3
irq 4
irq 5
irq 6
irq 7
irq 8
irq 9
irq 10
irq 11
irq 12
irq 13
irq 14
irq 15
; Wrappers
wrapper exception
wrapper irq