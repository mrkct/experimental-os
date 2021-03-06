#ifndef INT_H
#define INT_H

/*
    The value at which external interrupts start from. This value needs 
    to be >= 32, as the numbers below that are reserved for Intel 
    exceptions.
*/
#define IRQ_OFFSET 32
#define IRQ_TIMER       (IRQ_OFFSET + 0)
#define IRQ_KEYBOARD    (IRQ_OFFSET + 1)
#define IRQ_PS2MOUSE    (IRQ_OFFSET + 12)
#define IRQ_ATA_PRIMARY (IRQ_OFFSET + 14)
#define IRQ_ATA_SECONDARY (IRQ_OFFSET + 15)
#define IRQ_SYSCALL     (0x80)


static inline const char *get_exception_message(uint32_t code)
{
    const char *messages[] = {
        "Divide-by-zero Error",
        "Debug",
        "Non-maskable Interrupt",
        "Breakpoint",
        "Overflow",
        "Bound Range Exceeded",
        "Invalid Opcode",
        "Device Not Available",
        "Double Fault",
        "Coprocessor Segment Overrun",
        "Invalid TSS",
        "Segment Not Present",
        "Stack-Segment Fault",
        "General Protection Fault",
        "Page Fault",
        "[Intel Reserved]",
        "x87 Floating-Point Exception",
        "Alignment Check",
        "Machine Check",
        "SIMD Floating-Point Exception",
        "Virtualization Exception",
        "[Intel Reserved]",
        "Security Exception",
        "[Intel Reserved]",
        "Triple Fault",
        "FPU Error Interrupt"
    };
    if (code < 26) {
        return messages[code];
    } else if (code == IRQ_SYSCALL) {
        return "System Call";
    } else {
        return "Unknown Interrupt";
    }
}

#endif