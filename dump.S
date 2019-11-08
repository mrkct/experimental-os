
kernel.bin:     formato del file elf32-i386


Disassemblamento della sezione .text:

00100000 <alltraps-0xc>:
  100000:	02 b0 ad 1b 03 00    	add    0x31bad(%eax),%dh
  100006:	00 00                	add    %al,(%eax)
  100008:	fb                   	sti    
  100009:	4f                   	dec    %edi
  10000a:	52                   	push   %edx
  10000b:	e4                   	.byte 0xe4

0010000c <alltraps>:
    [$0]
    [roba CPU]
*/

alltraps:
    pusha
  10000c:	60                   	pusha  
    
    mov %ds, %eax
  10000d:	8c d8                	mov    %ds,%eax
    push %eax
  10000f:	50                   	push   %eax

    mov $0x10, %eax
  100010:	b8 10 00 00 00       	mov    $0x10,%eax
    mov %ax, %ds
  100015:	8e d8                	mov    %eax,%ds
    mov %ax, %es
  100017:	8e c0                	mov    %eax,%es
    mov %ax, %gs
  100019:	8e e8                	mov    %eax,%gs
    mov %ax, %fs
  10001b:	8e e0                	mov    %eax,%fs

    push %esp
  10001d:	54                   	push   %esp
    call interrupt_handler
  10001e:	e8 e5 17 00 00       	call   101808 <interrupt_handler>
    add $4, %esp
  100023:	83 c4 04             	add    $0x4,%esp

    pop %eax
  100026:	58                   	pop    %eax
    mov %ax, %ds
  100027:	8e d8                	mov    %eax,%ds
    mov %ax, %es
  100029:	8e c0                	mov    %eax,%es
    mov %ax, %gs
  10002b:	8e e8                	mov    %eax,%gs
    mov %ax, %fs
  10002d:	8e e0                	mov    %eax,%fs
    
    popa
  10002f:	61                   	popa   
    add $8, %esp    # to remove the error code + int number
  100030:	83 c4 08             	add    $0x8,%esp
    
    iret
  100033:	cf                   	iret   

00100034 <isr0>:

ISR_NOERRCODE isr0, 0
  100034:	6a 00                	push   $0x0
  100036:	6a 00                	push   $0x0
  100038:	eb d2                	jmp    10000c <alltraps>

0010003a <isr1>:
ISR_NOERRCODE isr1, 1
  10003a:	6a 00                	push   $0x0
  10003c:	6a 01                	push   $0x1
  10003e:	eb cc                	jmp    10000c <alltraps>

00100040 <isr2>:
ISR_NOERRCODE isr2, 2
  100040:	6a 00                	push   $0x0
  100042:	6a 02                	push   $0x2
  100044:	eb c6                	jmp    10000c <alltraps>

00100046 <isr3>:
ISR_NOERRCODE isr3, 3
  100046:	6a 00                	push   $0x0
  100048:	6a 03                	push   $0x3
  10004a:	eb c0                	jmp    10000c <alltraps>

0010004c <isr4>:
ISR_NOERRCODE isr4, 4
  10004c:	6a 00                	push   $0x0
  10004e:	6a 04                	push   $0x4
  100050:	eb ba                	jmp    10000c <alltraps>

00100052 <isr5>:
ISR_NOERRCODE isr5, 5
  100052:	6a 00                	push   $0x0
  100054:	6a 05                	push   $0x5
  100056:	eb b4                	jmp    10000c <alltraps>

00100058 <isr6>:
ISR_NOERRCODE isr6, 6
  100058:	6a 00                	push   $0x0
  10005a:	6a 06                	push   $0x6
  10005c:	eb ae                	jmp    10000c <alltraps>

0010005e <isr7>:
ISR_NOERRCODE isr7, 7
  10005e:	6a 00                	push   $0x0
  100060:	6a 07                	push   $0x7
  100062:	eb a8                	jmp    10000c <alltraps>

00100064 <isr8>:
ISR_ERRCODE isr8, 8
  100064:	6a 08                	push   $0x8
  100066:	eb a4                	jmp    10000c <alltraps>

00100068 <isr9>:
ISR_NOERRCODE isr9, 9
  100068:	6a 00                	push   $0x0
  10006a:	6a 09                	push   $0x9
  10006c:	eb 9e                	jmp    10000c <alltraps>

0010006e <isr10>:
ISR_ERRCODE isr10, 10
  10006e:	6a 0a                	push   $0xa
  100070:	eb 9a                	jmp    10000c <alltraps>

00100072 <isr11>:
ISR_ERRCODE isr11, 11
  100072:	6a 0b                	push   $0xb
  100074:	eb 96                	jmp    10000c <alltraps>

00100076 <isr12>:
ISR_ERRCODE isr12, 12
  100076:	6a 0c                	push   $0xc
  100078:	eb 92                	jmp    10000c <alltraps>

0010007a <isr13>:
ISR_ERRCODE isr13, 13
  10007a:	6a 0d                	push   $0xd
  10007c:	eb 8e                	jmp    10000c <alltraps>

0010007e <isr14>:
ISR_ERRCODE isr14, 14
  10007e:	6a 0e                	push   $0xe
  100080:	eb 8a                	jmp    10000c <alltraps>

00100082 <isr15>:
ISR_NOERRCODE isr15, 15
  100082:	6a 00                	push   $0x0
  100084:	6a 0f                	push   $0xf
  100086:	eb 84                	jmp    10000c <alltraps>

00100088 <isr16>:
ISR_NOERRCODE isr16, 16
  100088:	6a 00                	push   $0x0
  10008a:	6a 10                	push   $0x10
  10008c:	e9 7b ff ff ff       	jmp    10000c <alltraps>
  100091:	90                   	nop

00100092 <isr17>:
ISR_NOERRCODE isr17, 17
  100092:	6a 00                	push   $0x0
  100094:	6a 11                	push   $0x11
  100096:	e9 71 ff ff ff       	jmp    10000c <alltraps>
  10009b:	90                   	nop

0010009c <isr18>:
ISR_NOERRCODE isr18, 18
  10009c:	6a 00                	push   $0x0
  10009e:	6a 12                	push   $0x12
  1000a0:	e9 67 ff ff ff       	jmp    10000c <alltraps>
  1000a5:	90                   	nop

001000a6 <isr19>:
ISR_NOERRCODE isr19, 19
  1000a6:	6a 00                	push   $0x0
  1000a8:	6a 13                	push   $0x13
  1000aa:	e9 5d ff ff ff       	jmp    10000c <alltraps>
  1000af:	90                   	nop

001000b0 <isr20>:
ISR_NOERRCODE isr20, 20
  1000b0:	6a 00                	push   $0x0
  1000b2:	6a 14                	push   $0x14
  1000b4:	e9 53 ff ff ff       	jmp    10000c <alltraps>
  1000b9:	90                   	nop

001000ba <isr21>:
ISR_NOERRCODE isr21, 21
  1000ba:	6a 00                	push   $0x0
  1000bc:	6a 15                	push   $0x15
  1000be:	e9 49 ff ff ff       	jmp    10000c <alltraps>
  1000c3:	90                   	nop

001000c4 <isr22>:
ISR_NOERRCODE isr22, 22
  1000c4:	6a 00                	push   $0x0
  1000c6:	6a 16                	push   $0x16
  1000c8:	e9 3f ff ff ff       	jmp    10000c <alltraps>
  1000cd:	90                   	nop

001000ce <isr23>:
ISR_NOERRCODE isr23, 23
  1000ce:	6a 00                	push   $0x0
  1000d0:	6a 17                	push   $0x17
  1000d2:	e9 35 ff ff ff       	jmp    10000c <alltraps>
  1000d7:	90                   	nop

001000d8 <isr24>:
ISR_NOERRCODE isr24, 24
  1000d8:	6a 00                	push   $0x0
  1000da:	6a 18                	push   $0x18
  1000dc:	e9 2b ff ff ff       	jmp    10000c <alltraps>
  1000e1:	90                   	nop

001000e2 <isr25>:
ISR_NOERRCODE isr25, 25
  1000e2:	6a 00                	push   $0x0
  1000e4:	6a 19                	push   $0x19
  1000e6:	e9 21 ff ff ff       	jmp    10000c <alltraps>
  1000eb:	90                   	nop

001000ec <isr26>:
ISR_NOERRCODE isr26, 26
  1000ec:	6a 00                	push   $0x0
  1000ee:	6a 1a                	push   $0x1a
  1000f0:	e9 17 ff ff ff       	jmp    10000c <alltraps>
  1000f5:	90                   	nop

001000f6 <isr27>:
ISR_NOERRCODE isr27, 27
  1000f6:	6a 00                	push   $0x0
  1000f8:	6a 1b                	push   $0x1b
  1000fa:	e9 0d ff ff ff       	jmp    10000c <alltraps>
  1000ff:	90                   	nop

00100100 <isr28>:
ISR_NOERRCODE isr28, 28
  100100:	6a 00                	push   $0x0
  100102:	6a 1c                	push   $0x1c
  100104:	e9 03 ff ff ff       	jmp    10000c <alltraps>
  100109:	90                   	nop

0010010a <isr29>:
ISR_NOERRCODE isr29, 29
  10010a:	6a 00                	push   $0x0
  10010c:	6a 1d                	push   $0x1d
  10010e:	e9 f9 fe ff ff       	jmp    10000c <alltraps>
  100113:	90                   	nop

00100114 <isr30>:
ISR_NOERRCODE isr30, 30
  100114:	6a 00                	push   $0x0
  100116:	6a 1e                	push   $0x1e
  100118:	e9 ef fe ff ff       	jmp    10000c <alltraps>
  10011d:	90                   	nop

0010011e <isr31>:
ISR_NOERRCODE isr31, 31
  10011e:	6a 00                	push   $0x0
  100120:	6a 1f                	push   $0x1f
  100122:	e9 e5 fe ff ff       	jmp    10000c <alltraps>
  100127:	90                   	nop

00100128 <isr32>:
ISR_NOERRCODE isr32, 32
  100128:	6a 00                	push   $0x0
  10012a:	6a 20                	push   $0x20
  10012c:	e9 db fe ff ff       	jmp    10000c <alltraps>
  100131:	90                   	nop

00100132 <isr33>:
ISR_NOERRCODE isr33, 33
  100132:	6a 00                	push   $0x0
  100134:	6a 21                	push   $0x21
  100136:	e9 d1 fe ff ff       	jmp    10000c <alltraps>
  10013b:	90                   	nop

0010013c <isr34>:
ISR_NOERRCODE isr34, 34
  10013c:	6a 00                	push   $0x0
  10013e:	6a 22                	push   $0x22
  100140:	e9 c7 fe ff ff       	jmp    10000c <alltraps>
  100145:	90                   	nop

00100146 <isr35>:
ISR_NOERRCODE isr35, 35
  100146:	6a 00                	push   $0x0
  100148:	6a 23                	push   $0x23
  10014a:	e9 bd fe ff ff       	jmp    10000c <alltraps>
  10014f:	90                   	nop

00100150 <isr36>:
ISR_NOERRCODE isr36, 36
  100150:	6a 00                	push   $0x0
  100152:	6a 24                	push   $0x24
  100154:	e9 b3 fe ff ff       	jmp    10000c <alltraps>
  100159:	90                   	nop

0010015a <isr37>:
ISR_NOERRCODE isr37, 37
  10015a:	6a 00                	push   $0x0
  10015c:	6a 25                	push   $0x25
  10015e:	e9 a9 fe ff ff       	jmp    10000c <alltraps>
  100163:	90                   	nop

00100164 <isr38>:
ISR_NOERRCODE isr38, 38
  100164:	6a 00                	push   $0x0
  100166:	6a 26                	push   $0x26
  100168:	e9 9f fe ff ff       	jmp    10000c <alltraps>
  10016d:	90                   	nop

0010016e <isr39>:
ISR_NOERRCODE isr39, 39
  10016e:	6a 00                	push   $0x0
  100170:	6a 27                	push   $0x27
  100172:	e9 95 fe ff ff       	jmp    10000c <alltraps>
  100177:	90                   	nop

00100178 <isr40>:
ISR_NOERRCODE isr40, 40
  100178:	6a 00                	push   $0x0
  10017a:	6a 28                	push   $0x28
  10017c:	e9 8b fe ff ff       	jmp    10000c <alltraps>
  100181:	90                   	nop

00100182 <isr41>:
ISR_NOERRCODE isr41, 41
  100182:	6a 00                	push   $0x0
  100184:	6a 29                	push   $0x29
  100186:	e9 81 fe ff ff       	jmp    10000c <alltraps>
  10018b:	90                   	nop

0010018c <isr42>:
ISR_NOERRCODE isr42, 42
  10018c:	6a 00                	push   $0x0
  10018e:	6a 2a                	push   $0x2a
  100190:	e9 77 fe ff ff       	jmp    10000c <alltraps>
  100195:	90                   	nop

00100196 <isr43>:
ISR_NOERRCODE isr43, 43
  100196:	6a 00                	push   $0x0
  100198:	6a 2b                	push   $0x2b
  10019a:	e9 6d fe ff ff       	jmp    10000c <alltraps>
  10019f:	90                   	nop

001001a0 <isr44>:
ISR_NOERRCODE isr44, 44
  1001a0:	6a 00                	push   $0x0
  1001a2:	6a 2c                	push   $0x2c
  1001a4:	e9 63 fe ff ff       	jmp    10000c <alltraps>
  1001a9:	90                   	nop

001001aa <isr45>:
ISR_NOERRCODE isr45, 45
  1001aa:	6a 00                	push   $0x0
  1001ac:	6a 2d                	push   $0x2d
  1001ae:	e9 59 fe ff ff       	jmp    10000c <alltraps>
  1001b3:	90                   	nop

001001b4 <isr46>:
ISR_NOERRCODE isr46, 46
  1001b4:	6a 00                	push   $0x0
  1001b6:	6a 2e                	push   $0x2e
  1001b8:	e9 4f fe ff ff       	jmp    10000c <alltraps>
  1001bd:	90                   	nop

001001be <isr47>:
ISR_NOERRCODE isr47, 47
  1001be:	6a 00                	push   $0x0
  1001c0:	6a 2f                	push   $0x2f
  1001c2:	e9 45 fe ff ff       	jmp    10000c <alltraps>
  1001c7:	90                   	nop

001001c8 <isr48>:
ISR_NOERRCODE isr48, 48
  1001c8:	6a 00                	push   $0x0
  1001ca:	6a 30                	push   $0x30
  1001cc:	e9 3b fe ff ff       	jmp    10000c <alltraps>
  1001d1:	90                   	nop

001001d2 <isr49>:
ISR_NOERRCODE isr49, 49
  1001d2:	6a 00                	push   $0x0
  1001d4:	6a 31                	push   $0x31
  1001d6:	e9 31 fe ff ff       	jmp    10000c <alltraps>
  1001db:	90                   	nop

001001dc <isr50>:
ISR_NOERRCODE isr50, 50
  1001dc:	6a 00                	push   $0x0
  1001de:	6a 32                	push   $0x32
  1001e0:	e9 27 fe ff ff       	jmp    10000c <alltraps>
  1001e5:	90                   	nop

001001e6 <isr51>:
ISR_NOERRCODE isr51, 51
  1001e6:	6a 00                	push   $0x0
  1001e8:	6a 33                	push   $0x33
  1001ea:	e9 1d fe ff ff       	jmp    10000c <alltraps>
  1001ef:	90                   	nop

001001f0 <isr52>:
ISR_NOERRCODE isr52, 52
  1001f0:	6a 00                	push   $0x0
  1001f2:	6a 34                	push   $0x34
  1001f4:	e9 13 fe ff ff       	jmp    10000c <alltraps>
  1001f9:	90                   	nop

001001fa <isr53>:
ISR_NOERRCODE isr53, 53
  1001fa:	6a 00                	push   $0x0
  1001fc:	6a 35                	push   $0x35
  1001fe:	e9 09 fe ff ff       	jmp    10000c <alltraps>
  100203:	90                   	nop

00100204 <isr54>:
ISR_NOERRCODE isr54, 54
  100204:	6a 00                	push   $0x0
  100206:	6a 36                	push   $0x36
  100208:	e9 ff fd ff ff       	jmp    10000c <alltraps>
  10020d:	90                   	nop

0010020e <isr55>:
ISR_NOERRCODE isr55, 55
  10020e:	6a 00                	push   $0x0
  100210:	6a 37                	push   $0x37
  100212:	e9 f5 fd ff ff       	jmp    10000c <alltraps>
  100217:	90                   	nop

00100218 <isr56>:
ISR_NOERRCODE isr56, 56
  100218:	6a 00                	push   $0x0
  10021a:	6a 38                	push   $0x38
  10021c:	e9 eb fd ff ff       	jmp    10000c <alltraps>
  100221:	90                   	nop

00100222 <isr57>:
ISR_NOERRCODE isr57, 57
  100222:	6a 00                	push   $0x0
  100224:	6a 39                	push   $0x39
  100226:	e9 e1 fd ff ff       	jmp    10000c <alltraps>
  10022b:	90                   	nop

0010022c <isr58>:
ISR_NOERRCODE isr58, 58
  10022c:	6a 00                	push   $0x0
  10022e:	6a 3a                	push   $0x3a
  100230:	e9 d7 fd ff ff       	jmp    10000c <alltraps>
  100235:	90                   	nop

00100236 <isr59>:
ISR_NOERRCODE isr59, 59
  100236:	6a 00                	push   $0x0
  100238:	6a 3b                	push   $0x3b
  10023a:	e9 cd fd ff ff       	jmp    10000c <alltraps>
  10023f:	90                   	nop

00100240 <isr60>:
ISR_NOERRCODE isr60, 60
  100240:	6a 00                	push   $0x0
  100242:	6a 3c                	push   $0x3c
  100244:	e9 c3 fd ff ff       	jmp    10000c <alltraps>
  100249:	90                   	nop

0010024a <isr61>:
ISR_NOERRCODE isr61, 61
  10024a:	6a 00                	push   $0x0
  10024c:	6a 3d                	push   $0x3d
  10024e:	e9 b9 fd ff ff       	jmp    10000c <alltraps>
  100253:	90                   	nop

00100254 <isr62>:
ISR_NOERRCODE isr62, 62
  100254:	6a 00                	push   $0x0
  100256:	6a 3e                	push   $0x3e
  100258:	e9 af fd ff ff       	jmp    10000c <alltraps>
  10025d:	90                   	nop

0010025e <isr63>:
ISR_NOERRCODE isr63, 63
  10025e:	6a 00                	push   $0x0
  100260:	6a 3f                	push   $0x3f
  100262:	e9 a5 fd ff ff       	jmp    10000c <alltraps>
  100267:	90                   	nop

00100268 <isr64>:
ISR_NOERRCODE isr64, 64
  100268:	6a 00                	push   $0x0
  10026a:	6a 40                	push   $0x40
  10026c:	e9 9b fd ff ff       	jmp    10000c <alltraps>
  100271:	90                   	nop

00100272 <isr65>:
ISR_NOERRCODE isr65, 65
  100272:	6a 00                	push   $0x0
  100274:	6a 41                	push   $0x41
  100276:	e9 91 fd ff ff       	jmp    10000c <alltraps>
  10027b:	90                   	nop

0010027c <isr66>:
ISR_NOERRCODE isr66, 66
  10027c:	6a 00                	push   $0x0
  10027e:	6a 42                	push   $0x42
  100280:	e9 87 fd ff ff       	jmp    10000c <alltraps>
  100285:	90                   	nop

00100286 <isr67>:
ISR_NOERRCODE isr67, 67
  100286:	6a 00                	push   $0x0
  100288:	6a 43                	push   $0x43
  10028a:	e9 7d fd ff ff       	jmp    10000c <alltraps>
  10028f:	90                   	nop

00100290 <isr68>:
ISR_NOERRCODE isr68, 68
  100290:	6a 00                	push   $0x0
  100292:	6a 44                	push   $0x44
  100294:	e9 73 fd ff ff       	jmp    10000c <alltraps>
  100299:	90                   	nop

0010029a <isr69>:
ISR_NOERRCODE isr69, 69
  10029a:	6a 00                	push   $0x0
  10029c:	6a 45                	push   $0x45
  10029e:	e9 69 fd ff ff       	jmp    10000c <alltraps>
  1002a3:	90                   	nop

001002a4 <isr70>:
ISR_NOERRCODE isr70, 70
  1002a4:	6a 00                	push   $0x0
  1002a6:	6a 46                	push   $0x46
  1002a8:	e9 5f fd ff ff       	jmp    10000c <alltraps>
  1002ad:	90                   	nop

001002ae <isr71>:
ISR_NOERRCODE isr71, 71
  1002ae:	6a 00                	push   $0x0
  1002b0:	6a 47                	push   $0x47
  1002b2:	e9 55 fd ff ff       	jmp    10000c <alltraps>
  1002b7:	90                   	nop

001002b8 <isr72>:
ISR_NOERRCODE isr72, 72
  1002b8:	6a 00                	push   $0x0
  1002ba:	6a 48                	push   $0x48
  1002bc:	e9 4b fd ff ff       	jmp    10000c <alltraps>
  1002c1:	90                   	nop

001002c2 <isr73>:
ISR_NOERRCODE isr73, 73
  1002c2:	6a 00                	push   $0x0
  1002c4:	6a 49                	push   $0x49
  1002c6:	e9 41 fd ff ff       	jmp    10000c <alltraps>
  1002cb:	90                   	nop

001002cc <isr74>:
ISR_NOERRCODE isr74, 74
  1002cc:	6a 00                	push   $0x0
  1002ce:	6a 4a                	push   $0x4a
  1002d0:	e9 37 fd ff ff       	jmp    10000c <alltraps>
  1002d5:	90                   	nop

001002d6 <isr75>:
ISR_NOERRCODE isr75, 75
  1002d6:	6a 00                	push   $0x0
  1002d8:	6a 4b                	push   $0x4b
  1002da:	e9 2d fd ff ff       	jmp    10000c <alltraps>
  1002df:	90                   	nop

001002e0 <isr76>:
ISR_NOERRCODE isr76, 76
  1002e0:	6a 00                	push   $0x0
  1002e2:	6a 4c                	push   $0x4c
  1002e4:	e9 23 fd ff ff       	jmp    10000c <alltraps>
  1002e9:	90                   	nop

001002ea <isr77>:
ISR_NOERRCODE isr77, 77
  1002ea:	6a 00                	push   $0x0
  1002ec:	6a 4d                	push   $0x4d
  1002ee:	e9 19 fd ff ff       	jmp    10000c <alltraps>
  1002f3:	90                   	nop

001002f4 <isr78>:
ISR_NOERRCODE isr78, 78
  1002f4:	6a 00                	push   $0x0
  1002f6:	6a 4e                	push   $0x4e
  1002f8:	e9 0f fd ff ff       	jmp    10000c <alltraps>
  1002fd:	90                   	nop

001002fe <isr79>:
ISR_NOERRCODE isr79, 79
  1002fe:	6a 00                	push   $0x0
  100300:	6a 4f                	push   $0x4f
  100302:	e9 05 fd ff ff       	jmp    10000c <alltraps>
  100307:	90                   	nop

00100308 <isr80>:
ISR_NOERRCODE isr80, 80
  100308:	6a 00                	push   $0x0
  10030a:	6a 50                	push   $0x50
  10030c:	e9 fb fc ff ff       	jmp    10000c <alltraps>
  100311:	90                   	nop

00100312 <isr81>:
ISR_NOERRCODE isr81, 81
  100312:	6a 00                	push   $0x0
  100314:	6a 51                	push   $0x51
  100316:	e9 f1 fc ff ff       	jmp    10000c <alltraps>
  10031b:	90                   	nop

0010031c <isr82>:
ISR_NOERRCODE isr82, 82
  10031c:	6a 00                	push   $0x0
  10031e:	6a 52                	push   $0x52
  100320:	e9 e7 fc ff ff       	jmp    10000c <alltraps>
  100325:	90                   	nop

00100326 <isr83>:
ISR_NOERRCODE isr83, 83
  100326:	6a 00                	push   $0x0
  100328:	6a 53                	push   $0x53
  10032a:	e9 dd fc ff ff       	jmp    10000c <alltraps>
  10032f:	90                   	nop

00100330 <isr84>:
ISR_NOERRCODE isr84, 84
  100330:	6a 00                	push   $0x0
  100332:	6a 54                	push   $0x54
  100334:	e9 d3 fc ff ff       	jmp    10000c <alltraps>
  100339:	90                   	nop

0010033a <isr85>:
ISR_NOERRCODE isr85, 85
  10033a:	6a 00                	push   $0x0
  10033c:	6a 55                	push   $0x55
  10033e:	e9 c9 fc ff ff       	jmp    10000c <alltraps>
  100343:	90                   	nop

00100344 <isr86>:
ISR_NOERRCODE isr86, 86
  100344:	6a 00                	push   $0x0
  100346:	6a 56                	push   $0x56
  100348:	e9 bf fc ff ff       	jmp    10000c <alltraps>
  10034d:	90                   	nop

0010034e <isr87>:
ISR_NOERRCODE isr87, 87
  10034e:	6a 00                	push   $0x0
  100350:	6a 57                	push   $0x57
  100352:	e9 b5 fc ff ff       	jmp    10000c <alltraps>
  100357:	90                   	nop

00100358 <isr88>:
ISR_NOERRCODE isr88, 88
  100358:	6a 00                	push   $0x0
  10035a:	6a 58                	push   $0x58
  10035c:	e9 ab fc ff ff       	jmp    10000c <alltraps>
  100361:	90                   	nop

00100362 <isr89>:
ISR_NOERRCODE isr89, 89
  100362:	6a 00                	push   $0x0
  100364:	6a 59                	push   $0x59
  100366:	e9 a1 fc ff ff       	jmp    10000c <alltraps>
  10036b:	90                   	nop

0010036c <isr90>:
ISR_NOERRCODE isr90, 90
  10036c:	6a 00                	push   $0x0
  10036e:	6a 5a                	push   $0x5a
  100370:	e9 97 fc ff ff       	jmp    10000c <alltraps>
  100375:	90                   	nop

00100376 <isr91>:
ISR_NOERRCODE isr91, 91
  100376:	6a 00                	push   $0x0
  100378:	6a 5b                	push   $0x5b
  10037a:	e9 8d fc ff ff       	jmp    10000c <alltraps>
  10037f:	90                   	nop

00100380 <isr92>:
ISR_NOERRCODE isr92, 92
  100380:	6a 00                	push   $0x0
  100382:	6a 5c                	push   $0x5c
  100384:	e9 83 fc ff ff       	jmp    10000c <alltraps>
  100389:	90                   	nop

0010038a <isr93>:
ISR_NOERRCODE isr93, 93
  10038a:	6a 00                	push   $0x0
  10038c:	6a 5d                	push   $0x5d
  10038e:	e9 79 fc ff ff       	jmp    10000c <alltraps>
  100393:	90                   	nop

00100394 <isr94>:
ISR_NOERRCODE isr94, 94
  100394:	6a 00                	push   $0x0
  100396:	6a 5e                	push   $0x5e
  100398:	e9 6f fc ff ff       	jmp    10000c <alltraps>
  10039d:	90                   	nop

0010039e <isr95>:
ISR_NOERRCODE isr95, 95
  10039e:	6a 00                	push   $0x0
  1003a0:	6a 5f                	push   $0x5f
  1003a2:	e9 65 fc ff ff       	jmp    10000c <alltraps>
  1003a7:	90                   	nop

001003a8 <isr96>:
ISR_NOERRCODE isr96, 96
  1003a8:	6a 00                	push   $0x0
  1003aa:	6a 60                	push   $0x60
  1003ac:	e9 5b fc ff ff       	jmp    10000c <alltraps>
  1003b1:	90                   	nop

001003b2 <isr97>:
ISR_NOERRCODE isr97, 97
  1003b2:	6a 00                	push   $0x0
  1003b4:	6a 61                	push   $0x61
  1003b6:	e9 51 fc ff ff       	jmp    10000c <alltraps>
  1003bb:	90                   	nop

001003bc <isr98>:
ISR_NOERRCODE isr98, 98
  1003bc:	6a 00                	push   $0x0
  1003be:	6a 62                	push   $0x62
  1003c0:	e9 47 fc ff ff       	jmp    10000c <alltraps>
  1003c5:	90                   	nop

001003c6 <isr99>:
ISR_NOERRCODE isr99, 99
  1003c6:	6a 00                	push   $0x0
  1003c8:	6a 63                	push   $0x63
  1003ca:	e9 3d fc ff ff       	jmp    10000c <alltraps>
  1003cf:	90                   	nop

001003d0 <isr100>:
ISR_NOERRCODE isr100, 100
  1003d0:	6a 00                	push   $0x0
  1003d2:	6a 64                	push   $0x64
  1003d4:	e9 33 fc ff ff       	jmp    10000c <alltraps>
  1003d9:	90                   	nop

001003da <isr101>:
ISR_NOERRCODE isr101, 101
  1003da:	6a 00                	push   $0x0
  1003dc:	6a 65                	push   $0x65
  1003de:	e9 29 fc ff ff       	jmp    10000c <alltraps>
  1003e3:	90                   	nop

001003e4 <isr102>:
ISR_NOERRCODE isr102, 102
  1003e4:	6a 00                	push   $0x0
  1003e6:	6a 66                	push   $0x66
  1003e8:	e9 1f fc ff ff       	jmp    10000c <alltraps>
  1003ed:	90                   	nop

001003ee <isr103>:
ISR_NOERRCODE isr103, 103
  1003ee:	6a 00                	push   $0x0
  1003f0:	6a 67                	push   $0x67
  1003f2:	e9 15 fc ff ff       	jmp    10000c <alltraps>
  1003f7:	90                   	nop

001003f8 <isr104>:
ISR_NOERRCODE isr104, 104
  1003f8:	6a 00                	push   $0x0
  1003fa:	6a 68                	push   $0x68
  1003fc:	e9 0b fc ff ff       	jmp    10000c <alltraps>
  100401:	90                   	nop

00100402 <isr105>:
ISR_NOERRCODE isr105, 105
  100402:	6a 00                	push   $0x0
  100404:	6a 69                	push   $0x69
  100406:	e9 01 fc ff ff       	jmp    10000c <alltraps>
  10040b:	90                   	nop

0010040c <isr106>:
ISR_NOERRCODE isr106, 106
  10040c:	6a 00                	push   $0x0
  10040e:	6a 6a                	push   $0x6a
  100410:	e9 f7 fb ff ff       	jmp    10000c <alltraps>
  100415:	90                   	nop

00100416 <isr107>:
ISR_NOERRCODE isr107, 107
  100416:	6a 00                	push   $0x0
  100418:	6a 6b                	push   $0x6b
  10041a:	e9 ed fb ff ff       	jmp    10000c <alltraps>
  10041f:	90                   	nop

00100420 <isr108>:
ISR_NOERRCODE isr108, 108
  100420:	6a 00                	push   $0x0
  100422:	6a 6c                	push   $0x6c
  100424:	e9 e3 fb ff ff       	jmp    10000c <alltraps>
  100429:	90                   	nop

0010042a <isr109>:
ISR_NOERRCODE isr109, 109
  10042a:	6a 00                	push   $0x0
  10042c:	6a 6d                	push   $0x6d
  10042e:	e9 d9 fb ff ff       	jmp    10000c <alltraps>
  100433:	90                   	nop

00100434 <isr110>:
ISR_NOERRCODE isr110, 110
  100434:	6a 00                	push   $0x0
  100436:	6a 6e                	push   $0x6e
  100438:	e9 cf fb ff ff       	jmp    10000c <alltraps>
  10043d:	90                   	nop

0010043e <isr111>:
ISR_NOERRCODE isr111, 111
  10043e:	6a 00                	push   $0x0
  100440:	6a 6f                	push   $0x6f
  100442:	e9 c5 fb ff ff       	jmp    10000c <alltraps>
  100447:	90                   	nop

00100448 <isr112>:
ISR_NOERRCODE isr112, 112
  100448:	6a 00                	push   $0x0
  10044a:	6a 70                	push   $0x70
  10044c:	e9 bb fb ff ff       	jmp    10000c <alltraps>
  100451:	90                   	nop

00100452 <isr113>:
ISR_NOERRCODE isr113, 113
  100452:	6a 00                	push   $0x0
  100454:	6a 71                	push   $0x71
  100456:	e9 b1 fb ff ff       	jmp    10000c <alltraps>
  10045b:	90                   	nop

0010045c <isr114>:
ISR_NOERRCODE isr114, 114
  10045c:	6a 00                	push   $0x0
  10045e:	6a 72                	push   $0x72
  100460:	e9 a7 fb ff ff       	jmp    10000c <alltraps>
  100465:	90                   	nop

00100466 <isr115>:
ISR_NOERRCODE isr115, 115
  100466:	6a 00                	push   $0x0
  100468:	6a 73                	push   $0x73
  10046a:	e9 9d fb ff ff       	jmp    10000c <alltraps>
  10046f:	90                   	nop

00100470 <isr116>:
ISR_NOERRCODE isr116, 116
  100470:	6a 00                	push   $0x0
  100472:	6a 74                	push   $0x74
  100474:	e9 93 fb ff ff       	jmp    10000c <alltraps>
  100479:	90                   	nop

0010047a <isr117>:
ISR_NOERRCODE isr117, 117
  10047a:	6a 00                	push   $0x0
  10047c:	6a 75                	push   $0x75
  10047e:	e9 89 fb ff ff       	jmp    10000c <alltraps>
  100483:	90                   	nop

00100484 <isr118>:
ISR_NOERRCODE isr118, 118
  100484:	6a 00                	push   $0x0
  100486:	6a 76                	push   $0x76
  100488:	e9 7f fb ff ff       	jmp    10000c <alltraps>
  10048d:	90                   	nop

0010048e <isr119>:
ISR_NOERRCODE isr119, 119
  10048e:	6a 00                	push   $0x0
  100490:	6a 77                	push   $0x77
  100492:	e9 75 fb ff ff       	jmp    10000c <alltraps>
  100497:	90                   	nop

00100498 <isr120>:
ISR_NOERRCODE isr120, 120
  100498:	6a 00                	push   $0x0
  10049a:	6a 78                	push   $0x78
  10049c:	e9 6b fb ff ff       	jmp    10000c <alltraps>
  1004a1:	90                   	nop

001004a2 <isr121>:
ISR_NOERRCODE isr121, 121
  1004a2:	6a 00                	push   $0x0
  1004a4:	6a 79                	push   $0x79
  1004a6:	e9 61 fb ff ff       	jmp    10000c <alltraps>
  1004ab:	90                   	nop

001004ac <isr122>:
ISR_NOERRCODE isr122, 122
  1004ac:	6a 00                	push   $0x0
  1004ae:	6a 7a                	push   $0x7a
  1004b0:	e9 57 fb ff ff       	jmp    10000c <alltraps>
  1004b5:	90                   	nop

001004b6 <isr123>:
ISR_NOERRCODE isr123, 123
  1004b6:	6a 00                	push   $0x0
  1004b8:	6a 7b                	push   $0x7b
  1004ba:	e9 4d fb ff ff       	jmp    10000c <alltraps>
  1004bf:	90                   	nop

001004c0 <isr124>:
ISR_NOERRCODE isr124, 124
  1004c0:	6a 00                	push   $0x0
  1004c2:	6a 7c                	push   $0x7c
  1004c4:	e9 43 fb ff ff       	jmp    10000c <alltraps>
  1004c9:	90                   	nop

001004ca <isr125>:
ISR_NOERRCODE isr125, 125
  1004ca:	6a 00                	push   $0x0
  1004cc:	6a 7d                	push   $0x7d
  1004ce:	e9 39 fb ff ff       	jmp    10000c <alltraps>
  1004d3:	90                   	nop

001004d4 <isr126>:
ISR_NOERRCODE isr126, 126
  1004d4:	6a 00                	push   $0x0
  1004d6:	6a 7e                	push   $0x7e
  1004d8:	e9 2f fb ff ff       	jmp    10000c <alltraps>
  1004dd:	90                   	nop

001004de <isr127>:
ISR_NOERRCODE isr127, 127
  1004de:	6a 00                	push   $0x0
  1004e0:	6a 7f                	push   $0x7f
  1004e2:	e9 25 fb ff ff       	jmp    10000c <alltraps>
  1004e7:	90                   	nop

001004e8 <isr128>:
ISR_NOERRCODE isr128, 128
  1004e8:	6a 00                	push   $0x0
  1004ea:	68 80 00 00 00       	push   $0x80
  1004ef:	e9 18 fb ff ff       	jmp    10000c <alltraps>

001004f4 <isr129>:
ISR_NOERRCODE isr129, 129
  1004f4:	6a 00                	push   $0x0
  1004f6:	68 81 00 00 00       	push   $0x81
  1004fb:	e9 0c fb ff ff       	jmp    10000c <alltraps>

00100500 <isr130>:
ISR_NOERRCODE isr130, 130
  100500:	6a 00                	push   $0x0
  100502:	68 82 00 00 00       	push   $0x82
  100507:	e9 00 fb ff ff       	jmp    10000c <alltraps>

0010050c <isr131>:
ISR_NOERRCODE isr131, 131
  10050c:	6a 00                	push   $0x0
  10050e:	68 83 00 00 00       	push   $0x83
  100513:	e9 f4 fa ff ff       	jmp    10000c <alltraps>

00100518 <isr132>:
ISR_NOERRCODE isr132, 132
  100518:	6a 00                	push   $0x0
  10051a:	68 84 00 00 00       	push   $0x84
  10051f:	e9 e8 fa ff ff       	jmp    10000c <alltraps>

00100524 <isr133>:
ISR_NOERRCODE isr133, 133
  100524:	6a 00                	push   $0x0
  100526:	68 85 00 00 00       	push   $0x85
  10052b:	e9 dc fa ff ff       	jmp    10000c <alltraps>

00100530 <isr134>:
ISR_NOERRCODE isr134, 134
  100530:	6a 00                	push   $0x0
  100532:	68 86 00 00 00       	push   $0x86
  100537:	e9 d0 fa ff ff       	jmp    10000c <alltraps>

0010053c <isr135>:
ISR_NOERRCODE isr135, 135
  10053c:	6a 00                	push   $0x0
  10053e:	68 87 00 00 00       	push   $0x87
  100543:	e9 c4 fa ff ff       	jmp    10000c <alltraps>

00100548 <isr136>:
ISR_NOERRCODE isr136, 136
  100548:	6a 00                	push   $0x0
  10054a:	68 88 00 00 00       	push   $0x88
  10054f:	e9 b8 fa ff ff       	jmp    10000c <alltraps>

00100554 <isr137>:
ISR_NOERRCODE isr137, 137
  100554:	6a 00                	push   $0x0
  100556:	68 89 00 00 00       	push   $0x89
  10055b:	e9 ac fa ff ff       	jmp    10000c <alltraps>

00100560 <isr138>:
ISR_NOERRCODE isr138, 138
  100560:	6a 00                	push   $0x0
  100562:	68 8a 00 00 00       	push   $0x8a
  100567:	e9 a0 fa ff ff       	jmp    10000c <alltraps>

0010056c <isr139>:
ISR_NOERRCODE isr139, 139
  10056c:	6a 00                	push   $0x0
  10056e:	68 8b 00 00 00       	push   $0x8b
  100573:	e9 94 fa ff ff       	jmp    10000c <alltraps>

00100578 <isr140>:
ISR_NOERRCODE isr140, 140
  100578:	6a 00                	push   $0x0
  10057a:	68 8c 00 00 00       	push   $0x8c
  10057f:	e9 88 fa ff ff       	jmp    10000c <alltraps>

00100584 <isr141>:
ISR_NOERRCODE isr141, 141
  100584:	6a 00                	push   $0x0
  100586:	68 8d 00 00 00       	push   $0x8d
  10058b:	e9 7c fa ff ff       	jmp    10000c <alltraps>

00100590 <isr142>:
ISR_NOERRCODE isr142, 142
  100590:	6a 00                	push   $0x0
  100592:	68 8e 00 00 00       	push   $0x8e
  100597:	e9 70 fa ff ff       	jmp    10000c <alltraps>

0010059c <isr143>:
ISR_NOERRCODE isr143, 143
  10059c:	6a 00                	push   $0x0
  10059e:	68 8f 00 00 00       	push   $0x8f
  1005a3:	e9 64 fa ff ff       	jmp    10000c <alltraps>

001005a8 <isr144>:
ISR_NOERRCODE isr144, 144
  1005a8:	6a 00                	push   $0x0
  1005aa:	68 90 00 00 00       	push   $0x90
  1005af:	e9 58 fa ff ff       	jmp    10000c <alltraps>

001005b4 <isr145>:
ISR_NOERRCODE isr145, 145
  1005b4:	6a 00                	push   $0x0
  1005b6:	68 91 00 00 00       	push   $0x91
  1005bb:	e9 4c fa ff ff       	jmp    10000c <alltraps>

001005c0 <isr146>:
ISR_NOERRCODE isr146, 146
  1005c0:	6a 00                	push   $0x0
  1005c2:	68 92 00 00 00       	push   $0x92
  1005c7:	e9 40 fa ff ff       	jmp    10000c <alltraps>

001005cc <isr147>:
ISR_NOERRCODE isr147, 147
  1005cc:	6a 00                	push   $0x0
  1005ce:	68 93 00 00 00       	push   $0x93
  1005d3:	e9 34 fa ff ff       	jmp    10000c <alltraps>

001005d8 <isr148>:
ISR_NOERRCODE isr148, 148
  1005d8:	6a 00                	push   $0x0
  1005da:	68 94 00 00 00       	push   $0x94
  1005df:	e9 28 fa ff ff       	jmp    10000c <alltraps>

001005e4 <isr149>:
ISR_NOERRCODE isr149, 149
  1005e4:	6a 00                	push   $0x0
  1005e6:	68 95 00 00 00       	push   $0x95
  1005eb:	e9 1c fa ff ff       	jmp    10000c <alltraps>

001005f0 <isr150>:
ISR_NOERRCODE isr150, 150
  1005f0:	6a 00                	push   $0x0
  1005f2:	68 96 00 00 00       	push   $0x96
  1005f7:	e9 10 fa ff ff       	jmp    10000c <alltraps>

001005fc <isr151>:
ISR_NOERRCODE isr151, 151
  1005fc:	6a 00                	push   $0x0
  1005fe:	68 97 00 00 00       	push   $0x97
  100603:	e9 04 fa ff ff       	jmp    10000c <alltraps>

00100608 <isr152>:
ISR_NOERRCODE isr152, 152
  100608:	6a 00                	push   $0x0
  10060a:	68 98 00 00 00       	push   $0x98
  10060f:	e9 f8 f9 ff ff       	jmp    10000c <alltraps>

00100614 <isr153>:
ISR_NOERRCODE isr153, 153
  100614:	6a 00                	push   $0x0
  100616:	68 99 00 00 00       	push   $0x99
  10061b:	e9 ec f9 ff ff       	jmp    10000c <alltraps>

00100620 <isr154>:
ISR_NOERRCODE isr154, 154
  100620:	6a 00                	push   $0x0
  100622:	68 9a 00 00 00       	push   $0x9a
  100627:	e9 e0 f9 ff ff       	jmp    10000c <alltraps>

0010062c <isr155>:
ISR_NOERRCODE isr155, 155
  10062c:	6a 00                	push   $0x0
  10062e:	68 9b 00 00 00       	push   $0x9b
  100633:	e9 d4 f9 ff ff       	jmp    10000c <alltraps>

00100638 <isr156>:
ISR_NOERRCODE isr156, 156
  100638:	6a 00                	push   $0x0
  10063a:	68 9c 00 00 00       	push   $0x9c
  10063f:	e9 c8 f9 ff ff       	jmp    10000c <alltraps>

00100644 <isr157>:
ISR_NOERRCODE isr157, 157
  100644:	6a 00                	push   $0x0
  100646:	68 9d 00 00 00       	push   $0x9d
  10064b:	e9 bc f9 ff ff       	jmp    10000c <alltraps>

00100650 <isr158>:
ISR_NOERRCODE isr158, 158
  100650:	6a 00                	push   $0x0
  100652:	68 9e 00 00 00       	push   $0x9e
  100657:	e9 b0 f9 ff ff       	jmp    10000c <alltraps>

0010065c <isr159>:
ISR_NOERRCODE isr159, 159
  10065c:	6a 00                	push   $0x0
  10065e:	68 9f 00 00 00       	push   $0x9f
  100663:	e9 a4 f9 ff ff       	jmp    10000c <alltraps>

00100668 <isr160>:
ISR_NOERRCODE isr160, 160
  100668:	6a 00                	push   $0x0
  10066a:	68 a0 00 00 00       	push   $0xa0
  10066f:	e9 98 f9 ff ff       	jmp    10000c <alltraps>

00100674 <isr161>:
ISR_NOERRCODE isr161, 161
  100674:	6a 00                	push   $0x0
  100676:	68 a1 00 00 00       	push   $0xa1
  10067b:	e9 8c f9 ff ff       	jmp    10000c <alltraps>

00100680 <isr162>:
ISR_NOERRCODE isr162, 162
  100680:	6a 00                	push   $0x0
  100682:	68 a2 00 00 00       	push   $0xa2
  100687:	e9 80 f9 ff ff       	jmp    10000c <alltraps>

0010068c <isr163>:
ISR_NOERRCODE isr163, 163
  10068c:	6a 00                	push   $0x0
  10068e:	68 a3 00 00 00       	push   $0xa3
  100693:	e9 74 f9 ff ff       	jmp    10000c <alltraps>

00100698 <isr164>:
ISR_NOERRCODE isr164, 164
  100698:	6a 00                	push   $0x0
  10069a:	68 a4 00 00 00       	push   $0xa4
  10069f:	e9 68 f9 ff ff       	jmp    10000c <alltraps>

001006a4 <isr165>:
ISR_NOERRCODE isr165, 165
  1006a4:	6a 00                	push   $0x0
  1006a6:	68 a5 00 00 00       	push   $0xa5
  1006ab:	e9 5c f9 ff ff       	jmp    10000c <alltraps>

001006b0 <isr166>:
ISR_NOERRCODE isr166, 166
  1006b0:	6a 00                	push   $0x0
  1006b2:	68 a6 00 00 00       	push   $0xa6
  1006b7:	e9 50 f9 ff ff       	jmp    10000c <alltraps>

001006bc <isr167>:
ISR_NOERRCODE isr167, 167
  1006bc:	6a 00                	push   $0x0
  1006be:	68 a7 00 00 00       	push   $0xa7
  1006c3:	e9 44 f9 ff ff       	jmp    10000c <alltraps>

001006c8 <isr168>:
ISR_NOERRCODE isr168, 168
  1006c8:	6a 00                	push   $0x0
  1006ca:	68 a8 00 00 00       	push   $0xa8
  1006cf:	e9 38 f9 ff ff       	jmp    10000c <alltraps>

001006d4 <isr169>:
ISR_NOERRCODE isr169, 169
  1006d4:	6a 00                	push   $0x0
  1006d6:	68 a9 00 00 00       	push   $0xa9
  1006db:	e9 2c f9 ff ff       	jmp    10000c <alltraps>

001006e0 <isr170>:
ISR_NOERRCODE isr170, 170
  1006e0:	6a 00                	push   $0x0
  1006e2:	68 aa 00 00 00       	push   $0xaa
  1006e7:	e9 20 f9 ff ff       	jmp    10000c <alltraps>

001006ec <isr171>:
ISR_NOERRCODE isr171, 171
  1006ec:	6a 00                	push   $0x0
  1006ee:	68 ab 00 00 00       	push   $0xab
  1006f3:	e9 14 f9 ff ff       	jmp    10000c <alltraps>

001006f8 <isr172>:
ISR_NOERRCODE isr172, 172
  1006f8:	6a 00                	push   $0x0
  1006fa:	68 ac 00 00 00       	push   $0xac
  1006ff:	e9 08 f9 ff ff       	jmp    10000c <alltraps>

00100704 <isr173>:
ISR_NOERRCODE isr173, 173
  100704:	6a 00                	push   $0x0
  100706:	68 ad 00 00 00       	push   $0xad
  10070b:	e9 fc f8 ff ff       	jmp    10000c <alltraps>

00100710 <isr174>:
ISR_NOERRCODE isr174, 174
  100710:	6a 00                	push   $0x0
  100712:	68 ae 00 00 00       	push   $0xae
  100717:	e9 f0 f8 ff ff       	jmp    10000c <alltraps>

0010071c <isr175>:
ISR_NOERRCODE isr175, 175
  10071c:	6a 00                	push   $0x0
  10071e:	68 af 00 00 00       	push   $0xaf
  100723:	e9 e4 f8 ff ff       	jmp    10000c <alltraps>

00100728 <isr176>:
ISR_NOERRCODE isr176, 176
  100728:	6a 00                	push   $0x0
  10072a:	68 b0 00 00 00       	push   $0xb0
  10072f:	e9 d8 f8 ff ff       	jmp    10000c <alltraps>

00100734 <isr177>:
ISR_NOERRCODE isr177, 177
  100734:	6a 00                	push   $0x0
  100736:	68 b1 00 00 00       	push   $0xb1
  10073b:	e9 cc f8 ff ff       	jmp    10000c <alltraps>

00100740 <isr178>:
ISR_NOERRCODE isr178, 178
  100740:	6a 00                	push   $0x0
  100742:	68 b2 00 00 00       	push   $0xb2
  100747:	e9 c0 f8 ff ff       	jmp    10000c <alltraps>

0010074c <isr179>:
ISR_NOERRCODE isr179, 179
  10074c:	6a 00                	push   $0x0
  10074e:	68 b3 00 00 00       	push   $0xb3
  100753:	e9 b4 f8 ff ff       	jmp    10000c <alltraps>

00100758 <isr180>:
ISR_NOERRCODE isr180, 180
  100758:	6a 00                	push   $0x0
  10075a:	68 b4 00 00 00       	push   $0xb4
  10075f:	e9 a8 f8 ff ff       	jmp    10000c <alltraps>

00100764 <isr181>:
ISR_NOERRCODE isr181, 181
  100764:	6a 00                	push   $0x0
  100766:	68 b5 00 00 00       	push   $0xb5
  10076b:	e9 9c f8 ff ff       	jmp    10000c <alltraps>

00100770 <isr182>:
ISR_NOERRCODE isr182, 182
  100770:	6a 00                	push   $0x0
  100772:	68 b6 00 00 00       	push   $0xb6
  100777:	e9 90 f8 ff ff       	jmp    10000c <alltraps>

0010077c <isr183>:
ISR_NOERRCODE isr183, 183
  10077c:	6a 00                	push   $0x0
  10077e:	68 b7 00 00 00       	push   $0xb7
  100783:	e9 84 f8 ff ff       	jmp    10000c <alltraps>

00100788 <isr184>:
ISR_NOERRCODE isr184, 184
  100788:	6a 00                	push   $0x0
  10078a:	68 b8 00 00 00       	push   $0xb8
  10078f:	e9 78 f8 ff ff       	jmp    10000c <alltraps>

00100794 <isr185>:
ISR_NOERRCODE isr185, 185
  100794:	6a 00                	push   $0x0
  100796:	68 b9 00 00 00       	push   $0xb9
  10079b:	e9 6c f8 ff ff       	jmp    10000c <alltraps>

001007a0 <isr186>:
ISR_NOERRCODE isr186, 186
  1007a0:	6a 00                	push   $0x0
  1007a2:	68 ba 00 00 00       	push   $0xba
  1007a7:	e9 60 f8 ff ff       	jmp    10000c <alltraps>

001007ac <isr187>:
ISR_NOERRCODE isr187, 187
  1007ac:	6a 00                	push   $0x0
  1007ae:	68 bb 00 00 00       	push   $0xbb
  1007b3:	e9 54 f8 ff ff       	jmp    10000c <alltraps>

001007b8 <isr188>:
ISR_NOERRCODE isr188, 188
  1007b8:	6a 00                	push   $0x0
  1007ba:	68 bc 00 00 00       	push   $0xbc
  1007bf:	e9 48 f8 ff ff       	jmp    10000c <alltraps>

001007c4 <isr189>:
ISR_NOERRCODE isr189, 189
  1007c4:	6a 00                	push   $0x0
  1007c6:	68 bd 00 00 00       	push   $0xbd
  1007cb:	e9 3c f8 ff ff       	jmp    10000c <alltraps>

001007d0 <isr190>:
ISR_NOERRCODE isr190, 190
  1007d0:	6a 00                	push   $0x0
  1007d2:	68 be 00 00 00       	push   $0xbe
  1007d7:	e9 30 f8 ff ff       	jmp    10000c <alltraps>

001007dc <isr191>:
ISR_NOERRCODE isr191, 191
  1007dc:	6a 00                	push   $0x0
  1007de:	68 bf 00 00 00       	push   $0xbf
  1007e3:	e9 24 f8 ff ff       	jmp    10000c <alltraps>

001007e8 <isr192>:
ISR_NOERRCODE isr192, 192
  1007e8:	6a 00                	push   $0x0
  1007ea:	68 c0 00 00 00       	push   $0xc0
  1007ef:	e9 18 f8 ff ff       	jmp    10000c <alltraps>

001007f4 <isr193>:
ISR_NOERRCODE isr193, 193
  1007f4:	6a 00                	push   $0x0
  1007f6:	68 c1 00 00 00       	push   $0xc1
  1007fb:	e9 0c f8 ff ff       	jmp    10000c <alltraps>

00100800 <isr194>:
ISR_NOERRCODE isr194, 194
  100800:	6a 00                	push   $0x0
  100802:	68 c2 00 00 00       	push   $0xc2
  100807:	e9 00 f8 ff ff       	jmp    10000c <alltraps>

0010080c <isr195>:
ISR_NOERRCODE isr195, 195
  10080c:	6a 00                	push   $0x0
  10080e:	68 c3 00 00 00       	push   $0xc3
  100813:	e9 f4 f7 ff ff       	jmp    10000c <alltraps>

00100818 <isr196>:
ISR_NOERRCODE isr196, 196
  100818:	6a 00                	push   $0x0
  10081a:	68 c4 00 00 00       	push   $0xc4
  10081f:	e9 e8 f7 ff ff       	jmp    10000c <alltraps>

00100824 <isr197>:
ISR_NOERRCODE isr197, 197
  100824:	6a 00                	push   $0x0
  100826:	68 c5 00 00 00       	push   $0xc5
  10082b:	e9 dc f7 ff ff       	jmp    10000c <alltraps>

00100830 <isr198>:
ISR_NOERRCODE isr198, 198
  100830:	6a 00                	push   $0x0
  100832:	68 c6 00 00 00       	push   $0xc6
  100837:	e9 d0 f7 ff ff       	jmp    10000c <alltraps>

0010083c <isr199>:
ISR_NOERRCODE isr199, 199
  10083c:	6a 00                	push   $0x0
  10083e:	68 c7 00 00 00       	push   $0xc7
  100843:	e9 c4 f7 ff ff       	jmp    10000c <alltraps>

00100848 <isr200>:
ISR_NOERRCODE isr200, 200
  100848:	6a 00                	push   $0x0
  10084a:	68 c8 00 00 00       	push   $0xc8
  10084f:	e9 b8 f7 ff ff       	jmp    10000c <alltraps>

00100854 <isr201>:
ISR_NOERRCODE isr201, 201
  100854:	6a 00                	push   $0x0
  100856:	68 c9 00 00 00       	push   $0xc9
  10085b:	e9 ac f7 ff ff       	jmp    10000c <alltraps>

00100860 <isr202>:
ISR_NOERRCODE isr202, 202
  100860:	6a 00                	push   $0x0
  100862:	68 ca 00 00 00       	push   $0xca
  100867:	e9 a0 f7 ff ff       	jmp    10000c <alltraps>

0010086c <isr203>:
ISR_NOERRCODE isr203, 203
  10086c:	6a 00                	push   $0x0
  10086e:	68 cb 00 00 00       	push   $0xcb
  100873:	e9 94 f7 ff ff       	jmp    10000c <alltraps>

00100878 <isr204>:
ISR_NOERRCODE isr204, 204
  100878:	6a 00                	push   $0x0
  10087a:	68 cc 00 00 00       	push   $0xcc
  10087f:	e9 88 f7 ff ff       	jmp    10000c <alltraps>

00100884 <isr205>:
ISR_NOERRCODE isr205, 205
  100884:	6a 00                	push   $0x0
  100886:	68 cd 00 00 00       	push   $0xcd
  10088b:	e9 7c f7 ff ff       	jmp    10000c <alltraps>

00100890 <isr206>:
ISR_NOERRCODE isr206, 206
  100890:	6a 00                	push   $0x0
  100892:	68 ce 00 00 00       	push   $0xce
  100897:	e9 70 f7 ff ff       	jmp    10000c <alltraps>

0010089c <isr207>:
ISR_NOERRCODE isr207, 207
  10089c:	6a 00                	push   $0x0
  10089e:	68 cf 00 00 00       	push   $0xcf
  1008a3:	e9 64 f7 ff ff       	jmp    10000c <alltraps>

001008a8 <isr208>:
ISR_NOERRCODE isr208, 208
  1008a8:	6a 00                	push   $0x0
  1008aa:	68 d0 00 00 00       	push   $0xd0
  1008af:	e9 58 f7 ff ff       	jmp    10000c <alltraps>

001008b4 <isr209>:
ISR_NOERRCODE isr209, 209
  1008b4:	6a 00                	push   $0x0
  1008b6:	68 d1 00 00 00       	push   $0xd1
  1008bb:	e9 4c f7 ff ff       	jmp    10000c <alltraps>

001008c0 <isr210>:
ISR_NOERRCODE isr210, 210
  1008c0:	6a 00                	push   $0x0
  1008c2:	68 d2 00 00 00       	push   $0xd2
  1008c7:	e9 40 f7 ff ff       	jmp    10000c <alltraps>

001008cc <isr211>:
ISR_NOERRCODE isr211, 211
  1008cc:	6a 00                	push   $0x0
  1008ce:	68 d3 00 00 00       	push   $0xd3
  1008d3:	e9 34 f7 ff ff       	jmp    10000c <alltraps>

001008d8 <isr212>:
ISR_NOERRCODE isr212, 212
  1008d8:	6a 00                	push   $0x0
  1008da:	68 d4 00 00 00       	push   $0xd4
  1008df:	e9 28 f7 ff ff       	jmp    10000c <alltraps>

001008e4 <isr213>:
ISR_NOERRCODE isr213, 213
  1008e4:	6a 00                	push   $0x0
  1008e6:	68 d5 00 00 00       	push   $0xd5
  1008eb:	e9 1c f7 ff ff       	jmp    10000c <alltraps>

001008f0 <isr214>:
ISR_NOERRCODE isr214, 214
  1008f0:	6a 00                	push   $0x0
  1008f2:	68 d6 00 00 00       	push   $0xd6
  1008f7:	e9 10 f7 ff ff       	jmp    10000c <alltraps>

001008fc <isr215>:
ISR_NOERRCODE isr215, 215
  1008fc:	6a 00                	push   $0x0
  1008fe:	68 d7 00 00 00       	push   $0xd7
  100903:	e9 04 f7 ff ff       	jmp    10000c <alltraps>

00100908 <isr216>:
ISR_NOERRCODE isr216, 216
  100908:	6a 00                	push   $0x0
  10090a:	68 d8 00 00 00       	push   $0xd8
  10090f:	e9 f8 f6 ff ff       	jmp    10000c <alltraps>

00100914 <isr217>:
ISR_NOERRCODE isr217, 217
  100914:	6a 00                	push   $0x0
  100916:	68 d9 00 00 00       	push   $0xd9
  10091b:	e9 ec f6 ff ff       	jmp    10000c <alltraps>

00100920 <isr218>:
ISR_NOERRCODE isr218, 218
  100920:	6a 00                	push   $0x0
  100922:	68 da 00 00 00       	push   $0xda
  100927:	e9 e0 f6 ff ff       	jmp    10000c <alltraps>

0010092c <isr219>:
ISR_NOERRCODE isr219, 219
  10092c:	6a 00                	push   $0x0
  10092e:	68 db 00 00 00       	push   $0xdb
  100933:	e9 d4 f6 ff ff       	jmp    10000c <alltraps>

00100938 <isr220>:
ISR_NOERRCODE isr220, 220
  100938:	6a 00                	push   $0x0
  10093a:	68 dc 00 00 00       	push   $0xdc
  10093f:	e9 c8 f6 ff ff       	jmp    10000c <alltraps>

00100944 <isr221>:
ISR_NOERRCODE isr221, 221
  100944:	6a 00                	push   $0x0
  100946:	68 dd 00 00 00       	push   $0xdd
  10094b:	e9 bc f6 ff ff       	jmp    10000c <alltraps>

00100950 <isr222>:
ISR_NOERRCODE isr222, 222
  100950:	6a 00                	push   $0x0
  100952:	68 de 00 00 00       	push   $0xde
  100957:	e9 b0 f6 ff ff       	jmp    10000c <alltraps>

0010095c <isr223>:
ISR_NOERRCODE isr223, 223
  10095c:	6a 00                	push   $0x0
  10095e:	68 df 00 00 00       	push   $0xdf
  100963:	e9 a4 f6 ff ff       	jmp    10000c <alltraps>

00100968 <isr224>:
ISR_NOERRCODE isr224, 224
  100968:	6a 00                	push   $0x0
  10096a:	68 e0 00 00 00       	push   $0xe0
  10096f:	e9 98 f6 ff ff       	jmp    10000c <alltraps>

00100974 <isr225>:
ISR_NOERRCODE isr225, 225
  100974:	6a 00                	push   $0x0
  100976:	68 e1 00 00 00       	push   $0xe1
  10097b:	e9 8c f6 ff ff       	jmp    10000c <alltraps>

00100980 <isr226>:
ISR_NOERRCODE isr226, 226
  100980:	6a 00                	push   $0x0
  100982:	68 e2 00 00 00       	push   $0xe2
  100987:	e9 80 f6 ff ff       	jmp    10000c <alltraps>

0010098c <isr227>:
ISR_NOERRCODE isr227, 227
  10098c:	6a 00                	push   $0x0
  10098e:	68 e3 00 00 00       	push   $0xe3
  100993:	e9 74 f6 ff ff       	jmp    10000c <alltraps>

00100998 <isr228>:
ISR_NOERRCODE isr228, 228
  100998:	6a 00                	push   $0x0
  10099a:	68 e4 00 00 00       	push   $0xe4
  10099f:	e9 68 f6 ff ff       	jmp    10000c <alltraps>

001009a4 <isr229>:
ISR_NOERRCODE isr229, 229
  1009a4:	6a 00                	push   $0x0
  1009a6:	68 e5 00 00 00       	push   $0xe5
  1009ab:	e9 5c f6 ff ff       	jmp    10000c <alltraps>

001009b0 <isr230>:
ISR_NOERRCODE isr230, 230
  1009b0:	6a 00                	push   $0x0
  1009b2:	68 e6 00 00 00       	push   $0xe6
  1009b7:	e9 50 f6 ff ff       	jmp    10000c <alltraps>

001009bc <isr231>:
ISR_NOERRCODE isr231, 231
  1009bc:	6a 00                	push   $0x0
  1009be:	68 e7 00 00 00       	push   $0xe7
  1009c3:	e9 44 f6 ff ff       	jmp    10000c <alltraps>

001009c8 <isr232>:
ISR_NOERRCODE isr232, 232
  1009c8:	6a 00                	push   $0x0
  1009ca:	68 e8 00 00 00       	push   $0xe8
  1009cf:	e9 38 f6 ff ff       	jmp    10000c <alltraps>

001009d4 <isr233>:
ISR_NOERRCODE isr233, 233
  1009d4:	6a 00                	push   $0x0
  1009d6:	68 e9 00 00 00       	push   $0xe9
  1009db:	e9 2c f6 ff ff       	jmp    10000c <alltraps>

001009e0 <isr234>:
ISR_NOERRCODE isr234, 234
  1009e0:	6a 00                	push   $0x0
  1009e2:	68 ea 00 00 00       	push   $0xea
  1009e7:	e9 20 f6 ff ff       	jmp    10000c <alltraps>

001009ec <isr235>:
ISR_NOERRCODE isr235, 235
  1009ec:	6a 00                	push   $0x0
  1009ee:	68 eb 00 00 00       	push   $0xeb
  1009f3:	e9 14 f6 ff ff       	jmp    10000c <alltraps>

001009f8 <isr236>:
ISR_NOERRCODE isr236, 236
  1009f8:	6a 00                	push   $0x0
  1009fa:	68 ec 00 00 00       	push   $0xec
  1009ff:	e9 08 f6 ff ff       	jmp    10000c <alltraps>

00100a04 <isr237>:
ISR_NOERRCODE isr237, 237
  100a04:	6a 00                	push   $0x0
  100a06:	68 ed 00 00 00       	push   $0xed
  100a0b:	e9 fc f5 ff ff       	jmp    10000c <alltraps>

00100a10 <isr238>:
ISR_NOERRCODE isr238, 238
  100a10:	6a 00                	push   $0x0
  100a12:	68 ee 00 00 00       	push   $0xee
  100a17:	e9 f0 f5 ff ff       	jmp    10000c <alltraps>

00100a1c <isr239>:
ISR_NOERRCODE isr239, 239
  100a1c:	6a 00                	push   $0x0
  100a1e:	68 ef 00 00 00       	push   $0xef
  100a23:	e9 e4 f5 ff ff       	jmp    10000c <alltraps>

00100a28 <isr240>:
ISR_NOERRCODE isr240, 240
  100a28:	6a 00                	push   $0x0
  100a2a:	68 f0 00 00 00       	push   $0xf0
  100a2f:	e9 d8 f5 ff ff       	jmp    10000c <alltraps>

00100a34 <isr241>:
ISR_NOERRCODE isr241, 241
  100a34:	6a 00                	push   $0x0
  100a36:	68 f1 00 00 00       	push   $0xf1
  100a3b:	e9 cc f5 ff ff       	jmp    10000c <alltraps>

00100a40 <isr242>:
ISR_NOERRCODE isr242, 242
  100a40:	6a 00                	push   $0x0
  100a42:	68 f2 00 00 00       	push   $0xf2
  100a47:	e9 c0 f5 ff ff       	jmp    10000c <alltraps>

00100a4c <isr243>:
ISR_NOERRCODE isr243, 243
  100a4c:	6a 00                	push   $0x0
  100a4e:	68 f3 00 00 00       	push   $0xf3
  100a53:	e9 b4 f5 ff ff       	jmp    10000c <alltraps>

00100a58 <isr244>:
ISR_NOERRCODE isr244, 244
  100a58:	6a 00                	push   $0x0
  100a5a:	68 f4 00 00 00       	push   $0xf4
  100a5f:	e9 a8 f5 ff ff       	jmp    10000c <alltraps>

00100a64 <isr245>:
ISR_NOERRCODE isr245, 245
  100a64:	6a 00                	push   $0x0
  100a66:	68 f5 00 00 00       	push   $0xf5
  100a6b:	e9 9c f5 ff ff       	jmp    10000c <alltraps>

00100a70 <isr246>:
ISR_NOERRCODE isr246, 246
  100a70:	6a 00                	push   $0x0
  100a72:	68 f6 00 00 00       	push   $0xf6
  100a77:	e9 90 f5 ff ff       	jmp    10000c <alltraps>

00100a7c <isr247>:
ISR_NOERRCODE isr247, 247
  100a7c:	6a 00                	push   $0x0
  100a7e:	68 f7 00 00 00       	push   $0xf7
  100a83:	e9 84 f5 ff ff       	jmp    10000c <alltraps>

00100a88 <isr248>:
ISR_NOERRCODE isr248, 248
  100a88:	6a 00                	push   $0x0
  100a8a:	68 f8 00 00 00       	push   $0xf8
  100a8f:	e9 78 f5 ff ff       	jmp    10000c <alltraps>

00100a94 <isr249>:
ISR_NOERRCODE isr249, 249
  100a94:	6a 00                	push   $0x0
  100a96:	68 f9 00 00 00       	push   $0xf9
  100a9b:	e9 6c f5 ff ff       	jmp    10000c <alltraps>

00100aa0 <isr250>:
ISR_NOERRCODE isr250, 250
  100aa0:	6a 00                	push   $0x0
  100aa2:	68 fa 00 00 00       	push   $0xfa
  100aa7:	e9 60 f5 ff ff       	jmp    10000c <alltraps>

00100aac <isr251>:
ISR_NOERRCODE isr251, 251
  100aac:	6a 00                	push   $0x0
  100aae:	68 fb 00 00 00       	push   $0xfb
  100ab3:	e9 54 f5 ff ff       	jmp    10000c <alltraps>

00100ab8 <isr252>:
ISR_NOERRCODE isr252, 252
  100ab8:	6a 00                	push   $0x0
  100aba:	68 fc 00 00 00       	push   $0xfc
  100abf:	e9 48 f5 ff ff       	jmp    10000c <alltraps>

00100ac4 <isr253>:
ISR_NOERRCODE isr253, 253
  100ac4:	6a 00                	push   $0x0
  100ac6:	68 fd 00 00 00       	push   $0xfd
  100acb:	e9 3c f5 ff ff       	jmp    10000c <alltraps>

00100ad0 <isr254>:
ISR_NOERRCODE isr254, 254
  100ad0:	6a 00                	push   $0x0
  100ad2:	68 fe 00 00 00       	push   $0xfe
  100ad7:	e9 30 f5 ff ff       	jmp    10000c <alltraps>

00100adc <isr255>:
ISR_NOERRCODE isr255, 255
  100adc:	6a 00                	push   $0x0
  100ade:	68 ff 00 00 00       	push   $0xff
  100ae3:	e9 24 f5 ff ff       	jmp    10000c <alltraps>

00100ae8 <handlers>:
  100ae8:	34 00                	xor    $0x0,%al
  100aea:	10 00                	adc    %al,(%eax)
  100aec:	3a 00                	cmp    (%eax),%al
  100aee:	10 00                	adc    %al,(%eax)
  100af0:	40                   	inc    %eax
  100af1:	00 10                	add    %dl,(%eax)
  100af3:	00 46 00             	add    %al,0x0(%esi)
  100af6:	10 00                	adc    %al,(%eax)
  100af8:	4c                   	dec    %esp
  100af9:	00 10                	add    %dl,(%eax)
  100afb:	00 52 00             	add    %dl,0x0(%edx)
  100afe:	10 00                	adc    %al,(%eax)
  100b00:	58                   	pop    %eax
  100b01:	00 10                	add    %dl,(%eax)
  100b03:	00 5e 00             	add    %bl,0x0(%esi)
  100b06:	10 00                	adc    %al,(%eax)
  100b08:	64 00 10             	add    %dl,%fs:(%eax)
  100b0b:	00 68 00             	add    %ch,0x0(%eax)
  100b0e:	10 00                	adc    %al,(%eax)
  100b10:	6e                   	outsb  %ds:(%esi),(%dx)
  100b11:	00 10                	add    %dl,(%eax)
  100b13:	00 72 00             	add    %dh,0x0(%edx)
  100b16:	10 00                	adc    %al,(%eax)
  100b18:	76 00                	jbe    100b1a <handlers+0x32>
  100b1a:	10 00                	adc    %al,(%eax)
  100b1c:	7a 00                	jp     100b1e <handlers+0x36>
  100b1e:	10 00                	adc    %al,(%eax)
  100b20:	7e 00                	jle    100b22 <handlers+0x3a>
  100b22:	10 00                	adc    %al,(%eax)
  100b24:	82 00 10             	addb   $0x10,(%eax)
  100b27:	00 88 00 10 00 92    	add    %cl,-0x6dfff000(%eax)
  100b2d:	00 10                	add    %dl,(%eax)
  100b2f:	00 9c 00 10 00 a6 00 	add    %bl,0xa60010(%eax,%eax,1)
  100b36:	10 00                	adc    %al,(%eax)
  100b38:	b0 00                	mov    $0x0,%al
  100b3a:	10 00                	adc    %al,(%eax)
  100b3c:	ba 00 10 00 c4       	mov    $0xc4001000,%edx
  100b41:	00 10                	add    %dl,(%eax)
  100b43:	00 ce                	add    %cl,%dh
  100b45:	00 10                	add    %dl,(%eax)
  100b47:	00 d8                	add    %bl,%al
  100b49:	00 10                	add    %dl,(%eax)
  100b4b:	00 e2                	add    %ah,%dl
  100b4d:	00 10                	add    %dl,(%eax)
  100b4f:	00 ec                	add    %ch,%ah
  100b51:	00 10                	add    %dl,(%eax)
  100b53:	00 f6                	add    %dh,%dh
  100b55:	00 10                	add    %dl,(%eax)
  100b57:	00 00                	add    %al,(%eax)
  100b59:	01 10                	add    %edx,(%eax)
  100b5b:	00 0a                	add    %cl,(%edx)
  100b5d:	01 10                	add    %edx,(%eax)
  100b5f:	00 14 01             	add    %dl,(%ecx,%eax,1)
  100b62:	10 00                	adc    %al,(%eax)
  100b64:	1e                   	push   %ds
  100b65:	01 10                	add    %edx,(%eax)
  100b67:	00 28                	add    %ch,(%eax)
  100b69:	01 10                	add    %edx,(%eax)
  100b6b:	00 32                	add    %dh,(%edx)
  100b6d:	01 10                	add    %edx,(%eax)
  100b6f:	00 3c 01             	add    %bh,(%ecx,%eax,1)
  100b72:	10 00                	adc    %al,(%eax)
  100b74:	46                   	inc    %esi
  100b75:	01 10                	add    %edx,(%eax)
  100b77:	00 50 01             	add    %dl,0x1(%eax)
  100b7a:	10 00                	adc    %al,(%eax)
  100b7c:	5a                   	pop    %edx
  100b7d:	01 10                	add    %edx,(%eax)
  100b7f:	00 64 01 10          	add    %ah,0x10(%ecx,%eax,1)
  100b83:	00 6e 01             	add    %ch,0x1(%esi)
  100b86:	10 00                	adc    %al,(%eax)
  100b88:	78 01                	js     100b8b <handlers+0xa3>
  100b8a:	10 00                	adc    %al,(%eax)
  100b8c:	82 01 10             	addb   $0x10,(%ecx)
  100b8f:	00 8c 01 10 00 96 01 	add    %cl,0x1960010(%ecx,%eax,1)
  100b96:	10 00                	adc    %al,(%eax)
  100b98:	a0 01 10 00 aa       	mov    0xaa001001,%al
  100b9d:	01 10                	add    %edx,(%eax)
  100b9f:	00 b4 01 10 00 be 01 	add    %dh,0x1be0010(%ecx,%eax,1)
  100ba6:	10 00                	adc    %al,(%eax)
  100ba8:	c8 01 10 00          	enter  $0x1001,$0x0
  100bac:	d2 01                	rolb   %cl,(%ecx)
  100bae:	10 00                	adc    %al,(%eax)
  100bb0:	dc 01                	faddl  (%ecx)
  100bb2:	10 00                	adc    %al,(%eax)
  100bb4:	e6 01                	out    %al,$0x1
  100bb6:	10 00                	adc    %al,(%eax)
  100bb8:	f0 01 10             	lock add %edx,(%eax)
  100bbb:	00 fa                	add    %bh,%dl
  100bbd:	01 10                	add    %edx,(%eax)
  100bbf:	00 04 02             	add    %al,(%edx,%eax,1)
  100bc2:	10 00                	adc    %al,(%eax)
  100bc4:	0e                   	push   %cs
  100bc5:	02 10                	add    (%eax),%dl
  100bc7:	00 18                	add    %bl,(%eax)
  100bc9:	02 10                	add    (%eax),%dl
  100bcb:	00 22                	add    %ah,(%edx)
  100bcd:	02 10                	add    (%eax),%dl
  100bcf:	00 2c 02             	add    %ch,(%edx,%eax,1)
  100bd2:	10 00                	adc    %al,(%eax)
  100bd4:	36 02 10             	add    %ss:(%eax),%dl
  100bd7:	00 40 02             	add    %al,0x2(%eax)
  100bda:	10 00                	adc    %al,(%eax)
  100bdc:	4a                   	dec    %edx
  100bdd:	02 10                	add    (%eax),%dl
  100bdf:	00 54 02 10          	add    %dl,0x10(%edx,%eax,1)
  100be3:	00 5e 02             	add    %bl,0x2(%esi)
  100be6:	10 00                	adc    %al,(%eax)
  100be8:	68 02 10 00 72       	push   $0x72001002
  100bed:	02 10                	add    (%eax),%dl
  100bef:	00 7c 02 10          	add    %bh,0x10(%edx,%eax,1)
  100bf3:	00 86 02 10 00 90    	add    %al,-0x6fffeffe(%esi)
  100bf9:	02 10                	add    (%eax),%dl
  100bfb:	00 9a 02 10 00 a4    	add    %bl,-0x5bffeffe(%edx)
  100c01:	02 10                	add    (%eax),%dl
  100c03:	00 ae 02 10 00 b8    	add    %ch,-0x47ffeffe(%esi)
  100c09:	02 10                	add    (%eax),%dl
  100c0b:	00 c2                	add    %al,%dl
  100c0d:	02 10                	add    (%eax),%dl
  100c0f:	00 cc                	add    %cl,%ah
  100c11:	02 10                	add    (%eax),%dl
  100c13:	00 d6                	add    %dl,%dh
  100c15:	02 10                	add    (%eax),%dl
  100c17:	00 e0                	add    %ah,%al
  100c19:	02 10                	add    (%eax),%dl
  100c1b:	00 ea                	add    %ch,%dl
  100c1d:	02 10                	add    (%eax),%dl
  100c1f:	00 f4                	add    %dh,%ah
  100c21:	02 10                	add    (%eax),%dl
  100c23:	00 fe                	add    %bh,%dh
  100c25:	02 10                	add    (%eax),%dl
  100c27:	00 08                	add    %cl,(%eax)
  100c29:	03 10                	add    (%eax),%edx
  100c2b:	00 12                	add    %dl,(%edx)
  100c2d:	03 10                	add    (%eax),%edx
  100c2f:	00 1c 03             	add    %bl,(%ebx,%eax,1)
  100c32:	10 00                	adc    %al,(%eax)
  100c34:	26 03 10             	add    %es:(%eax),%edx
  100c37:	00 30                	add    %dh,(%eax)
  100c39:	03 10                	add    (%eax),%edx
  100c3b:	00 3a                	add    %bh,(%edx)
  100c3d:	03 10                	add    (%eax),%edx
  100c3f:	00 44 03 10          	add    %al,0x10(%ebx,%eax,1)
  100c43:	00 4e 03             	add    %cl,0x3(%esi)
  100c46:	10 00                	adc    %al,(%eax)
  100c48:	58                   	pop    %eax
  100c49:	03 10                	add    (%eax),%edx
  100c4b:	00 62 03             	add    %ah,0x3(%edx)
  100c4e:	10 00                	adc    %al,(%eax)
  100c50:	6c                   	insb   (%dx),%es:(%edi)
  100c51:	03 10                	add    (%eax),%edx
  100c53:	00 76 03             	add    %dh,0x3(%esi)
  100c56:	10 00                	adc    %al,(%eax)
  100c58:	80 03 10             	addb   $0x10,(%ebx)
  100c5b:	00 8a 03 10 00 94    	add    %cl,-0x6bffeffd(%edx)
  100c61:	03 10                	add    (%eax),%edx
  100c63:	00 9e 03 10 00 a8    	add    %bl,-0x57ffeffd(%esi)
  100c69:	03 10                	add    (%eax),%edx
  100c6b:	00 b2 03 10 00 bc    	add    %dh,-0x43ffeffd(%edx)
  100c71:	03 10                	add    (%eax),%edx
  100c73:	00 c6                	add    %al,%dh
  100c75:	03 10                	add    (%eax),%edx
  100c77:	00 d0                	add    %dl,%al
  100c79:	03 10                	add    (%eax),%edx
  100c7b:	00 da                	add    %bl,%dl
  100c7d:	03 10                	add    (%eax),%edx
  100c7f:	00 e4                	add    %ah,%ah
  100c81:	03 10                	add    (%eax),%edx
  100c83:	00 ee                	add    %ch,%dh
  100c85:	03 10                	add    (%eax),%edx
  100c87:	00 f8                	add    %bh,%al
  100c89:	03 10                	add    (%eax),%edx
  100c8b:	00 02                	add    %al,(%edx)
  100c8d:	04 10                	add    $0x10,%al
  100c8f:	00 0c 04             	add    %cl,(%esp,%eax,1)
  100c92:	10 00                	adc    %al,(%eax)
  100c94:	16                   	push   %ss
  100c95:	04 10                	add    $0x10,%al
  100c97:	00 20                	add    %ah,(%eax)
  100c99:	04 10                	add    $0x10,%al
  100c9b:	00 2a                	add    %ch,(%edx)
  100c9d:	04 10                	add    $0x10,%al
  100c9f:	00 34 04             	add    %dh,(%esp,%eax,1)
  100ca2:	10 00                	adc    %al,(%eax)
  100ca4:	3e 04 10             	ds add $0x10,%al
  100ca7:	00 48 04             	add    %cl,0x4(%eax)
  100caa:	10 00                	adc    %al,(%eax)
  100cac:	52                   	push   %edx
  100cad:	04 10                	add    $0x10,%al
  100caf:	00 5c 04 10          	add    %bl,0x10(%esp,%eax,1)
  100cb3:	00 66 04             	add    %ah,0x4(%esi)
  100cb6:	10 00                	adc    %al,(%eax)
  100cb8:	70 04                	jo     100cbe <handlers+0x1d6>
  100cba:	10 00                	adc    %al,(%eax)
  100cbc:	7a 04                	jp     100cc2 <handlers+0x1da>
  100cbe:	10 00                	adc    %al,(%eax)
  100cc0:	84 04 10             	test   %al,(%eax,%edx,1)
  100cc3:	00 8e 04 10 00 98    	add    %cl,-0x67ffeffc(%esi)
  100cc9:	04 10                	add    $0x10,%al
  100ccb:	00 a2 04 10 00 ac    	add    %ah,-0x53ffeffc(%edx)
  100cd1:	04 10                	add    $0x10,%al
  100cd3:	00 b6 04 10 00 c0    	add    %dh,-0x3fffeffc(%esi)
  100cd9:	04 10                	add    $0x10,%al
  100cdb:	00 ca                	add    %cl,%dl
  100cdd:	04 10                	add    $0x10,%al
  100cdf:	00 d4                	add    %dl,%ah
  100ce1:	04 10                	add    $0x10,%al
  100ce3:	00 de                	add    %bl,%dh
  100ce5:	04 10                	add    $0x10,%al
  100ce7:	00 e8                	add    %ch,%al
  100ce9:	04 10                	add    $0x10,%al
  100ceb:	00 f4                	add    %dh,%ah
  100ced:	04 10                	add    $0x10,%al
  100cef:	00 00                	add    %al,(%eax)
  100cf1:	05 10 00 0c 05       	add    $0x50c0010,%eax
  100cf6:	10 00                	adc    %al,(%eax)
  100cf8:	18 05 10 00 24 05    	sbb    %al,0x5240010
  100cfe:	10 00                	adc    %al,(%eax)
  100d00:	30 05 10 00 3c 05    	xor    %al,0x53c0010
  100d06:	10 00                	adc    %al,(%eax)
  100d08:	48                   	dec    %eax
  100d09:	05 10 00 54 05       	add    $0x5540010,%eax
  100d0e:	10 00                	adc    %al,(%eax)
  100d10:	60                   	pusha  
  100d11:	05 10 00 6c 05       	add    $0x56c0010,%eax
  100d16:	10 00                	adc    %al,(%eax)
  100d18:	78 05                	js     100d1f <handlers+0x237>
  100d1a:	10 00                	adc    %al,(%eax)
  100d1c:	84 05 10 00 90 05    	test   %al,0x5900010
  100d22:	10 00                	adc    %al,(%eax)
  100d24:	9c                   	pushf  
  100d25:	05 10 00 a8 05       	add    $0x5a80010,%eax
  100d2a:	10 00                	adc    %al,(%eax)
  100d2c:	b4 05                	mov    $0x5,%ah
  100d2e:	10 00                	adc    %al,(%eax)
  100d30:	c0 05 10 00 cc 05 10 	rolb   $0x10,0x5cc0010
  100d37:	00 d8                	add    %bl,%al
  100d39:	05 10 00 e4 05       	add    $0x5e40010,%eax
  100d3e:	10 00                	adc    %al,(%eax)
  100d40:	f0 05 10 00 fc 05    	lock add $0x5fc0010,%eax
  100d46:	10 00                	adc    %al,(%eax)
  100d48:	08 06                	or     %al,(%esi)
  100d4a:	10 00                	adc    %al,(%eax)
  100d4c:	14 06                	adc    $0x6,%al
  100d4e:	10 00                	adc    %al,(%eax)
  100d50:	20 06                	and    %al,(%esi)
  100d52:	10 00                	adc    %al,(%eax)
  100d54:	2c 06                	sub    $0x6,%al
  100d56:	10 00                	adc    %al,(%eax)
  100d58:	38 06                	cmp    %al,(%esi)
  100d5a:	10 00                	adc    %al,(%eax)
  100d5c:	44                   	inc    %esp
  100d5d:	06                   	push   %es
  100d5e:	10 00                	adc    %al,(%eax)
  100d60:	50                   	push   %eax
  100d61:	06                   	push   %es
  100d62:	10 00                	adc    %al,(%eax)
  100d64:	5c                   	pop    %esp
  100d65:	06                   	push   %es
  100d66:	10 00                	adc    %al,(%eax)
  100d68:	68 06 10 00 74       	push   $0x74001006
  100d6d:	06                   	push   %es
  100d6e:	10 00                	adc    %al,(%eax)
  100d70:	80 06 10             	addb   $0x10,(%esi)
  100d73:	00 8c 06 10 00 98 06 	add    %cl,0x6980010(%esi,%eax,1)
  100d7a:	10 00                	adc    %al,(%eax)
  100d7c:	a4                   	movsb  %ds:(%esi),%es:(%edi)
  100d7d:	06                   	push   %es
  100d7e:	10 00                	adc    %al,(%eax)
  100d80:	b0 06                	mov    $0x6,%al
  100d82:	10 00                	adc    %al,(%eax)
  100d84:	bc 06 10 00 c8       	mov    $0xc8001006,%esp
  100d89:	06                   	push   %es
  100d8a:	10 00                	adc    %al,(%eax)
  100d8c:	d4 06                	aam    $0x6
  100d8e:	10 00                	adc    %al,(%eax)
  100d90:	e0 06                	loopne 100d98 <handlers+0x2b0>
  100d92:	10 00                	adc    %al,(%eax)
  100d94:	ec                   	in     (%dx),%al
  100d95:	06                   	push   %es
  100d96:	10 00                	adc    %al,(%eax)
  100d98:	f8                   	clc    
  100d99:	06                   	push   %es
  100d9a:	10 00                	adc    %al,(%eax)
  100d9c:	04 07                	add    $0x7,%al
  100d9e:	10 00                	adc    %al,(%eax)
  100da0:	10 07                	adc    %al,(%edi)
  100da2:	10 00                	adc    %al,(%eax)
  100da4:	1c 07                	sbb    $0x7,%al
  100da6:	10 00                	adc    %al,(%eax)
  100da8:	28 07                	sub    %al,(%edi)
  100daa:	10 00                	adc    %al,(%eax)
  100dac:	34 07                	xor    $0x7,%al
  100dae:	10 00                	adc    %al,(%eax)
  100db0:	40                   	inc    %eax
  100db1:	07                   	pop    %es
  100db2:	10 00                	adc    %al,(%eax)
  100db4:	4c                   	dec    %esp
  100db5:	07                   	pop    %es
  100db6:	10 00                	adc    %al,(%eax)
  100db8:	58                   	pop    %eax
  100db9:	07                   	pop    %es
  100dba:	10 00                	adc    %al,(%eax)
  100dbc:	64 07                	fs pop %es
  100dbe:	10 00                	adc    %al,(%eax)
  100dc0:	70 07                	jo     100dc9 <handlers+0x2e1>
  100dc2:	10 00                	adc    %al,(%eax)
  100dc4:	7c 07                	jl     100dcd <handlers+0x2e5>
  100dc6:	10 00                	adc    %al,(%eax)
  100dc8:	88 07                	mov    %al,(%edi)
  100dca:	10 00                	adc    %al,(%eax)
  100dcc:	94                   	xchg   %eax,%esp
  100dcd:	07                   	pop    %es
  100dce:	10 00                	adc    %al,(%eax)
  100dd0:	a0 07 10 00 ac       	mov    0xac001007,%al
  100dd5:	07                   	pop    %es
  100dd6:	10 00                	adc    %al,(%eax)
  100dd8:	b8 07 10 00 c4       	mov    $0xc4001007,%eax
  100ddd:	07                   	pop    %es
  100dde:	10 00                	adc    %al,(%eax)
  100de0:	d0 07                	rolb   (%edi)
  100de2:	10 00                	adc    %al,(%eax)
  100de4:	dc 07                	faddl  (%edi)
  100de6:	10 00                	adc    %al,(%eax)
  100de8:	e8 07 10 00 f4       	call   f4101df4 <CHECKSUM+0xfbdcdf9>
  100ded:	07                   	pop    %es
  100dee:	10 00                	adc    %al,(%eax)
  100df0:	00 08                	add    %cl,(%eax)
  100df2:	10 00                	adc    %al,(%eax)
  100df4:	0c 08                	or     $0x8,%al
  100df6:	10 00                	adc    %al,(%eax)
  100df8:	18 08                	sbb    %cl,(%eax)
  100dfa:	10 00                	adc    %al,(%eax)
  100dfc:	24 08                	and    $0x8,%al
  100dfe:	10 00                	adc    %al,(%eax)
  100e00:	30 08                	xor    %cl,(%eax)
  100e02:	10 00                	adc    %al,(%eax)
  100e04:	3c 08                	cmp    $0x8,%al
  100e06:	10 00                	adc    %al,(%eax)
  100e08:	48                   	dec    %eax
  100e09:	08 10                	or     %dl,(%eax)
  100e0b:	00 54 08 10          	add    %dl,0x10(%eax,%ecx,1)
  100e0f:	00 60 08             	add    %ah,0x8(%eax)
  100e12:	10 00                	adc    %al,(%eax)
  100e14:	6c                   	insb   (%dx),%es:(%edi)
  100e15:	08 10                	or     %dl,(%eax)
  100e17:	00 78 08             	add    %bh,0x8(%eax)
  100e1a:	10 00                	adc    %al,(%eax)
  100e1c:	84 08                	test   %cl,(%eax)
  100e1e:	10 00                	adc    %al,(%eax)
  100e20:	90                   	nop
  100e21:	08 10                	or     %dl,(%eax)
  100e23:	00 9c 08 10 00 a8 08 	add    %bl,0x8a80010(%eax,%ecx,1)
  100e2a:	10 00                	adc    %al,(%eax)
  100e2c:	b4 08                	mov    $0x8,%ah
  100e2e:	10 00                	adc    %al,(%eax)
  100e30:	c0 08 10             	rorb   $0x10,(%eax)
  100e33:	00 cc                	add    %cl,%ah
  100e35:	08 10                	or     %dl,(%eax)
  100e37:	00 d8                	add    %bl,%al
  100e39:	08 10                	or     %dl,(%eax)
  100e3b:	00 e4                	add    %ah,%ah
  100e3d:	08 10                	or     %dl,(%eax)
  100e3f:	00 f0                	add    %dh,%al
  100e41:	08 10                	or     %dl,(%eax)
  100e43:	00 fc                	add    %bh,%ah
  100e45:	08 10                	or     %dl,(%eax)
  100e47:	00 08                	add    %cl,(%eax)
  100e49:	09 10                	or     %edx,(%eax)
  100e4b:	00 14 09             	add    %dl,(%ecx,%ecx,1)
  100e4e:	10 00                	adc    %al,(%eax)
  100e50:	20 09                	and    %cl,(%ecx)
  100e52:	10 00                	adc    %al,(%eax)
  100e54:	2c 09                	sub    $0x9,%al
  100e56:	10 00                	adc    %al,(%eax)
  100e58:	38 09                	cmp    %cl,(%ecx)
  100e5a:	10 00                	adc    %al,(%eax)
  100e5c:	44                   	inc    %esp
  100e5d:	09 10                	or     %edx,(%eax)
  100e5f:	00 50 09             	add    %dl,0x9(%eax)
  100e62:	10 00                	adc    %al,(%eax)
  100e64:	5c                   	pop    %esp
  100e65:	09 10                	or     %edx,(%eax)
  100e67:	00 68 09             	add    %ch,0x9(%eax)
  100e6a:	10 00                	adc    %al,(%eax)
  100e6c:	74 09                	je     100e77 <handlers+0x38f>
  100e6e:	10 00                	adc    %al,(%eax)
  100e70:	80 09 10             	orb    $0x10,(%ecx)
  100e73:	00 8c 09 10 00 98 09 	add    %cl,0x9980010(%ecx,%ecx,1)
  100e7a:	10 00                	adc    %al,(%eax)
  100e7c:	a4                   	movsb  %ds:(%esi),%es:(%edi)
  100e7d:	09 10                	or     %edx,(%eax)
  100e7f:	00 b0 09 10 00 bc    	add    %dh,-0x43ffeff7(%eax)
  100e85:	09 10                	or     %edx,(%eax)
  100e87:	00 c8                	add    %cl,%al
  100e89:	09 10                	or     %edx,(%eax)
  100e8b:	00 d4                	add    %dl,%ah
  100e8d:	09 10                	or     %edx,(%eax)
  100e8f:	00 e0                	add    %ah,%al
  100e91:	09 10                	or     %edx,(%eax)
  100e93:	00 ec                	add    %ch,%ah
  100e95:	09 10                	or     %edx,(%eax)
  100e97:	00 f8                	add    %bh,%al
  100e99:	09 10                	or     %edx,(%eax)
  100e9b:	00 04 0a             	add    %al,(%edx,%ecx,1)
  100e9e:	10 00                	adc    %al,(%eax)
  100ea0:	10 0a                	adc    %cl,(%edx)
  100ea2:	10 00                	adc    %al,(%eax)
  100ea4:	1c 0a                	sbb    $0xa,%al
  100ea6:	10 00                	adc    %al,(%eax)
  100ea8:	28 0a                	sub    %cl,(%edx)
  100eaa:	10 00                	adc    %al,(%eax)
  100eac:	34 0a                	xor    $0xa,%al
  100eae:	10 00                	adc    %al,(%eax)
  100eb0:	40                   	inc    %eax
  100eb1:	0a 10                	or     (%eax),%dl
  100eb3:	00 4c 0a 10          	add    %cl,0x10(%edx,%ecx,1)
  100eb7:	00 58 0a             	add    %bl,0xa(%eax)
  100eba:	10 00                	adc    %al,(%eax)
  100ebc:	64 0a 10             	or     %fs:(%eax),%dl
  100ebf:	00 70 0a             	add    %dh,0xa(%eax)
  100ec2:	10 00                	adc    %al,(%eax)
  100ec4:	7c 0a                	jl     100ed0 <handlers+0x3e8>
  100ec6:	10 00                	adc    %al,(%eax)
  100ec8:	88 0a                	mov    %cl,(%edx)
  100eca:	10 00                	adc    %al,(%eax)
  100ecc:	94                   	xchg   %eax,%esp
  100ecd:	0a 10                	or     (%eax),%dl
  100ecf:	00 a0 0a 10 00 ac    	add    %ah,-0x53ffeff6(%eax)
  100ed5:	0a 10                	or     (%eax),%dl
  100ed7:	00 b8 0a 10 00 c4    	add    %bh,-0x3bffeff6(%eax)
  100edd:	0a 10                	or     (%eax),%dl
  100edf:	00 d0                	add    %dl,%al
  100ee1:	0a 10                	or     (%eax),%dl
  100ee3:	00 dc                	add    %bl,%ah
  100ee5:	0a 10                	or     (%eax),%dl
	...

00100ee8 <_start>:
.include "interrupt.S"

.global _start
.type _start, @function
_start:
	movl $stack_top, %esp
  100ee8:	bc 70 98 10 00       	mov    $0x109870,%esp
   /*
      GRUB puts in %eax and %ebx a pointer to a data structure useful for 
      detecting the available memory on the system. We push these 2 registers 
      before everything else, so that we avoid accidentaly deleting them
   */
   push %eax
  100eed:	50                   	push   %eax
   push %ebx
  100eee:	53                   	push   %ebx

	# Prepare the terminal, so that we can write to debug easier
	call kernel_setup
  100eef:	e8 74 00 00 00       	call   100f68 <kernel_setup>

	# Transfer control to the main kernel.
	call kernel_main
  100ef4:	e8 f8 00 00 00       	call   100ff1 <kernel_main>

	# Hang if kernel_main unexpectedly returns.
	cli
  100ef9:	fa                   	cli    
1:	hlt
  100efa:	f4                   	hlt    
	jmp 1b
  100efb:	eb fd                	jmp    100efa <_start+0x12>

00100efd <gdt_flush>:

.global gdt_flush

gdt_flush:
   mov 4(%esp), %eax
  100efd:	8b 44 24 04          	mov    0x4(%esp),%eax
   lgdt (%eax)
  100f01:	0f 01 10             	lgdtl  (%eax)

   mov $0x10, %ax
  100f04:	66 b8 10 00          	mov    $0x10,%ax
   mov %ax, %ds
  100f08:	8e d8                	mov    %eax,%ds
   mov %ax, %es
  100f0a:	8e c0                	mov    %eax,%es
   mov %ax, %fs
  100f0c:	8e e0                	mov    %eax,%fs
   mov %ax, %gs
  100f0e:	8e e8                	mov    %eax,%gs
   mov %ax, %ss
  100f10:	8e d0                	mov    %eax,%ss
   jmp $0x08, $flush
  100f12:	ea 19 0f 10 00 08 00 	ljmp   $0x8,$0x100f19

00100f19 <flush>:
flush:
   ret
  100f19:	c3                   	ret    

00100f1a <load_idt>:

.global load_idt

load_idt:
   mov 4(%esp), %eax
  100f1a:	8b 44 24 04          	mov    0x4(%esp),%eax
   lidt (%eax)
  100f1e:	0f 01 18             	lidtl  (%eax)
   ret
  100f21:	c3                   	ret    

00100f22 <_panic>:
#define kassert(cond) do { if(!(cond)) panic(#cond); } while(0)


static void 
_panic(const char *file, const int line, const char *error)
{
  100f22:	55                   	push   %ebp
  100f23:	89 e5                	mov    %esp,%ebp
  100f25:	83 ec 08             	sub    $0x8,%esp
    kprintf("panic: %s at line %d. %s\n", file, line, error);
  100f28:	ff 75 10             	pushl  0x10(%ebp)
  100f2b:	ff 75 0c             	pushl  0xc(%ebp)
  100f2e:	ff 75 08             	pushl  0x8(%ebp)
  100f31:	68 00 30 10 00       	push   $0x103000
  100f36:	e8 a8 05 00 00       	call   1014e3 <kprintf>
  100f3b:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  100f3e:	fa                   	cli    
  100f3f:	fc                   	cld    
    while (true) {}
  100f40:	eb fe                	jmp    100f40 <_panic+0x1e>

00100f42 <_kassert>:
}

static void 
_kassert(const char *file, const int line, const bool cond, const char *strcond)
{
  100f42:	55                   	push   %ebp
  100f43:	89 e5                	mov    %esp,%ebp
  100f45:	83 ec 18             	sub    $0x18,%esp
  100f48:	8b 45 10             	mov    0x10(%ebp),%eax
  100f4b:	88 45 f4             	mov    %al,-0xc(%ebp)
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
  100f4e:	ff 75 14             	pushl  0x14(%ebp)
  100f51:	ff 75 0c             	pushl  0xc(%ebp)
  100f54:	ff 75 08             	pushl  0x8(%ebp)
  100f57:	68 1c 30 10 00       	push   $0x10301c
  100f5c:	e8 82 05 00 00       	call   1014e3 <kprintf>
  100f61:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  100f64:	fa                   	cli    
  100f65:	fc                   	cld    
    while (true) {}
  100f66:	eb fe                	jmp    100f66 <_kassert+0x24>

00100f68 <kernel_setup>:


#include <kernel/i686/multiboot.h>

void kernel_setup(multiboot_info_t *mbd, unsigned int magic)
{
  100f68:	55                   	push   %ebp
  100f69:	89 e5                	mov    %esp,%ebp
  100f6b:	83 ec 08             	sub    $0x8,%esp
    terminal_initialize();
  100f6e:	e8 3b 01 00 00       	call   1010ae <terminal_initialize>

    kprintf("Setting up the GDT...");
  100f73:	83 ec 0c             	sub    $0xc,%esp
  100f76:	68 47 30 10 00       	push   $0x103047
  100f7b:	e8 63 05 00 00       	call   1014e3 <kprintf>
  100f80:	83 c4 10             	add    $0x10,%esp
    init_gdt();
  100f83:	e8 34 07 00 00       	call   1016bc <init_gdt>
    kprintf("done!\n");
  100f88:	83 ec 0c             	sub    $0xc,%esp
  100f8b:	68 5d 30 10 00       	push   $0x10305d
  100f90:	e8 4e 05 00 00       	call   1014e3 <kprintf>
  100f95:	83 c4 10             	add    $0x10,%esp
    kprintf("Setting up the IDT...");
  100f98:	83 ec 0c             	sub    $0xc,%esp
  100f9b:	68 64 30 10 00       	push   $0x103064
  100fa0:	e8 3e 05 00 00       	call   1014e3 <kprintf>
  100fa5:	83 c4 10             	add    $0x10,%esp
    init_idt();
  100fa8:	e8 37 09 00 00       	call   1018e4 <init_idt>
    kprintf("done\n");
  100fad:	83 ec 0c             	sub    $0xc,%esp
  100fb0:	68 7a 30 10 00       	push   $0x10307a
  100fb5:	e8 29 05 00 00       	call   1014e3 <kprintf>
  100fba:	83 c4 10             	add    $0x10,%esp
    timer_init(1000);
  100fbd:	83 ec 0c             	sub    $0xc,%esp
  100fc0:	68 e8 03 00 00       	push   $0x3e8
  100fc5:	e8 4f 0c 00 00       	call   101c19 <timer_init>
  100fca:	83 c4 10             	add    $0x10,%esp

    memory_init(mbd, magic);
  100fcd:	83 ec 08             	sub    $0x8,%esp
  100fd0:	ff 75 0c             	pushl  0xc(%ebp)
  100fd3:	ff 75 08             	pushl  0x8(%ebp)
  100fd6:	e8 a2 14 00 00       	call   10247d <memory_init>
  100fdb:	83 c4 10             	add    $0x10,%esp

    kprintf("-----------------------------\n");
  100fde:	83 ec 0c             	sub    $0xc,%esp
  100fe1:	68 80 30 10 00       	push   $0x103080
  100fe6:	e8 f8 04 00 00       	call   1014e3 <kprintf>
  100feb:	83 c4 10             	add    $0x10,%esp
}
  100fee:	90                   	nop
  100fef:	c9                   	leave  
  100ff0:	c3                   	ret    

00100ff1 <kernel_main>:

void kernel_main(void) 
{
  100ff1:	55                   	push   %ebp
  100ff2:	89 e5                	mov    %esp,%ebp
  100ff4:	83 ec 28             	sub    $0x28,%esp
	kprintf("Hello, kernel World!\n");
  100ff7:	83 ec 0c             	sub    $0xc,%esp
  100ffa:	68 9f 30 10 00       	push   $0x10309f
  100fff:	e8 df 04 00 00       	call   1014e3 <kprintf>
  101004:	83 c4 10             	add    $0x10,%esp
    kprintf("How are you?\n");
  101007:	83 ec 0c             	sub    $0xc,%esp
  10100a:	68 b5 30 10 00       	push   $0x1030b5
  10100f:	e8 cf 04 00 00       	call   1014e3 <kprintf>
  101014:	83 c4 10             	add    $0x10,%esp

    struct KeyAction action;
    while (true) {
        if (kbd_get_keyaction(&action) && action.pressed && action.character != 0) {
  101017:	83 ec 0c             	sub    $0xc,%esp
  10101a:	8d 45 e4             	lea    -0x1c(%ebp),%eax
  10101d:	50                   	push   %eax
  10101e:	e8 83 0f 00 00       	call   101fa6 <kbd_get_keyaction>
  101023:	83 c4 10             	add    $0x10,%esp
  101026:	85 c0                	test   %eax,%eax
  101028:	74 ed                	je     101017 <kernel_main+0x26>
  10102a:	0f b6 45 f0          	movzbl -0x10(%ebp),%eax
  10102e:	84 c0                	test   %al,%al
  101030:	74 e5                	je     101017 <kernel_main+0x26>
  101032:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101036:	84 c0                	test   %al,%al
  101038:	74 dd                	je     101017 <kernel_main+0x26>
            kprintf("%c", action.character);
  10103a:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  10103e:	0f be c0             	movsbl %al,%eax
  101041:	83 ec 08             	sub    $0x8,%esp
  101044:	50                   	push   %eax
  101045:	68 c3 30 10 00       	push   $0x1030c3
  10104a:	e8 94 04 00 00       	call   1014e3 <kprintf>
  10104f:	83 c4 10             	add    $0x10,%esp
        if (kbd_get_keyaction(&action) && action.pressed && action.character != 0) {
  101052:	eb c3                	jmp    101017 <kernel_main+0x26>

00101054 <vga_entry_color>:
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};
 
static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
  101054:	55                   	push   %ebp
  101055:	89 e5                	mov    %esp,%ebp
	return fg | bg << 4;
  101057:	8b 45 0c             	mov    0xc(%ebp),%eax
  10105a:	c1 e0 04             	shl    $0x4,%eax
  10105d:	89 c2                	mov    %eax,%edx
  10105f:	8b 45 08             	mov    0x8(%ebp),%eax
  101062:	09 d0                	or     %edx,%eax
}
  101064:	5d                   	pop    %ebp
  101065:	c3                   	ret    

00101066 <vga_entry>:
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) 
{
  101066:	55                   	push   %ebp
  101067:	89 e5                	mov    %esp,%ebp
  101069:	83 ec 08             	sub    $0x8,%esp
  10106c:	8b 55 08             	mov    0x8(%ebp),%edx
  10106f:	8b 45 0c             	mov    0xc(%ebp),%eax
  101072:	88 55 fc             	mov    %dl,-0x4(%ebp)
  101075:	88 45 f8             	mov    %al,-0x8(%ebp)
	return (uint16_t) uc | (uint16_t) color << 8;
  101078:	0f b6 45 fc          	movzbl -0x4(%ebp),%eax
  10107c:	0f b6 55 f8          	movzbl -0x8(%ebp),%edx
  101080:	c1 e2 08             	shl    $0x8,%edx
  101083:	09 d0                	or     %edx,%eax
}
  101085:	c9                   	leave  
  101086:	c3                   	ret    

00101087 <strlen>:
#include <kernel/tty.h>

#define TAB_SIZE 4
 
size_t strlen(const char* str) 
{
  101087:	55                   	push   %ebp
  101088:	89 e5                	mov    %esp,%ebp
  10108a:	83 ec 10             	sub    $0x10,%esp
	size_t len = 0;
  10108d:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
	while (str[len])
  101094:	eb 04                	jmp    10109a <strlen+0x13>
		len++;
  101096:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
	while (str[len])
  10109a:	8b 55 08             	mov    0x8(%ebp),%edx
  10109d:	8b 45 fc             	mov    -0x4(%ebp),%eax
  1010a0:	01 d0                	add    %edx,%eax
  1010a2:	0f b6 00             	movzbl (%eax),%eax
  1010a5:	84 c0                	test   %al,%al
  1010a7:	75 ed                	jne    101096 <strlen+0xf>
	return len;
  1010a9:	8b 45 fc             	mov    -0x4(%ebp),%eax
}
  1010ac:	c9                   	leave  
  1010ad:	c3                   	ret    

001010ae <terminal_initialize>:
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;
 
void terminal_initialize(void) 
{
  1010ae:	55                   	push   %ebp
  1010af:	89 e5                	mov    %esp,%ebp
  1010b1:	53                   	push   %ebx
  1010b2:	83 ec 10             	sub    $0x10,%esp
	terminal_row = 0;
  1010b5:	c7 05 0c 50 10 00 00 	movl   $0x0,0x10500c
  1010bc:	00 00 00 
	terminal_column = 0;
  1010bf:	c7 05 04 50 10 00 00 	movl   $0x0,0x105004
  1010c6:	00 00 00 
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  1010c9:	6a 00                	push   $0x0
  1010cb:	6a 07                	push   $0x7
  1010cd:	e8 82 ff ff ff       	call   101054 <vga_entry_color>
  1010d2:	83 c4 08             	add    $0x8,%esp
  1010d5:	a2 00 50 10 00       	mov    %al,0x105000
	terminal_buffer = (uint16_t*) 0xB8000;
  1010da:	c7 05 08 50 10 00 00 	movl   $0xb8000,0x105008
  1010e1:	80 0b 00 
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
  1010e4:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%ebp)
  1010eb:	eb 54                	jmp    101141 <terminal_initialize+0x93>
		for (size_t x = 0; x < VGA_WIDTH; x++) {
  1010ed:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  1010f4:	eb 3d                	jmp    101133 <terminal_initialize+0x85>
			const size_t index = y * VGA_WIDTH + x;
  1010f6:	b8 50 00 00 00       	mov    $0x50,%eax
  1010fb:	0f af 45 f8          	imul   -0x8(%ebp),%eax
  1010ff:	89 c2                	mov    %eax,%edx
  101101:	8b 45 f4             	mov    -0xc(%ebp),%eax
  101104:	01 d0                	add    %edx,%eax
  101106:	89 45 f0             	mov    %eax,-0x10(%ebp)
			terminal_buffer[index] = vga_entry(' ', terminal_color);
  101109:	0f b6 05 00 50 10 00 	movzbl 0x105000,%eax
  101110:	0f b6 c0             	movzbl %al,%eax
  101113:	8b 15 08 50 10 00    	mov    0x105008,%edx
  101119:	8b 4d f0             	mov    -0x10(%ebp),%ecx
  10111c:	01 c9                	add    %ecx,%ecx
  10111e:	8d 1c 0a             	lea    (%edx,%ecx,1),%ebx
  101121:	50                   	push   %eax
  101122:	6a 20                	push   $0x20
  101124:	e8 3d ff ff ff       	call   101066 <vga_entry>
  101129:	83 c4 08             	add    $0x8,%esp
  10112c:	66 89 03             	mov    %ax,(%ebx)
		for (size_t x = 0; x < VGA_WIDTH; x++) {
  10112f:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  101133:	b8 50 00 00 00       	mov    $0x50,%eax
  101138:	39 45 f4             	cmp    %eax,-0xc(%ebp)
  10113b:	72 b9                	jb     1010f6 <terminal_initialize+0x48>
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
  10113d:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
  101141:	b8 19 00 00 00       	mov    $0x19,%eax
  101146:	39 45 f8             	cmp    %eax,-0x8(%ebp)
  101149:	72 a2                	jb     1010ed <terminal_initialize+0x3f>
		}
	}
}
  10114b:	90                   	nop
  10114c:	90                   	nop
  10114d:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  101150:	c9                   	leave  
  101151:	c3                   	ret    

00101152 <terminal_setcolor>:
 
void terminal_setcolor(uint8_t color) 
{
  101152:	55                   	push   %ebp
  101153:	89 e5                	mov    %esp,%ebp
  101155:	83 ec 04             	sub    $0x4,%esp
  101158:	8b 45 08             	mov    0x8(%ebp),%eax
  10115b:	88 45 fc             	mov    %al,-0x4(%ebp)
	terminal_color = color;
  10115e:	0f b6 45 fc          	movzbl -0x4(%ebp),%eax
  101162:	a2 00 50 10 00       	mov    %al,0x105000
}
  101167:	90                   	nop
  101168:	c9                   	leave  
  101169:	c3                   	ret    

0010116a <terminal_putentryat>:
 
void terminal_putentryat(char c, uint8_t color, size_t x, size_t y) 
{
  10116a:	55                   	push   %ebp
  10116b:	89 e5                	mov    %esp,%ebp
  10116d:	53                   	push   %ebx
  10116e:	83 ec 18             	sub    $0x18,%esp
  101171:	8b 55 08             	mov    0x8(%ebp),%edx
  101174:	8b 45 0c             	mov    0xc(%ebp),%eax
  101177:	88 55 e8             	mov    %dl,-0x18(%ebp)
  10117a:	88 45 e4             	mov    %al,-0x1c(%ebp)
	const size_t index = y * VGA_WIDTH + x;
  10117d:	b8 50 00 00 00       	mov    $0x50,%eax
  101182:	0f af 45 14          	imul   0x14(%ebp),%eax
  101186:	89 c2                	mov    %eax,%edx
  101188:	8b 45 10             	mov    0x10(%ebp),%eax
  10118b:	01 d0                	add    %edx,%eax
  10118d:	89 45 f8             	mov    %eax,-0x8(%ebp)
	terminal_buffer[index] = vga_entry(c, color);
  101190:	0f b6 55 e4          	movzbl -0x1c(%ebp),%edx
  101194:	0f b6 45 e8          	movzbl -0x18(%ebp),%eax
  101198:	0f b6 c0             	movzbl %al,%eax
  10119b:	8b 0d 08 50 10 00    	mov    0x105008,%ecx
  1011a1:	8b 5d f8             	mov    -0x8(%ebp),%ebx
  1011a4:	01 db                	add    %ebx,%ebx
  1011a6:	01 cb                	add    %ecx,%ebx
  1011a8:	52                   	push   %edx
  1011a9:	50                   	push   %eax
  1011aa:	e8 b7 fe ff ff       	call   101066 <vga_entry>
  1011af:	83 c4 08             	add    $0x8,%esp
  1011b2:	66 89 03             	mov    %ax,(%ebx)
}
  1011b5:	90                   	nop
  1011b6:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  1011b9:	c9                   	leave  
  1011ba:	c3                   	ret    

001011bb <terminal_nextline>:
/**
 * Moves the terminal cursor to the next line. If there are no more
 * rows availabled it moves all the content before up one row to make space
**/
void terminal_nextline(void)
{
  1011bb:	55                   	push   %ebp
  1011bc:	89 e5                	mov    %esp,%ebp
  1011be:	53                   	push   %ebx
  1011bf:	83 ec 10             	sub    $0x10,%esp
    terminal_column = 0;
  1011c2:	c7 05 04 50 10 00 00 	movl   $0x0,0x105004
  1011c9:	00 00 00 
    if (++terminal_row == VGA_HEIGHT) {
  1011cc:	a1 0c 50 10 00       	mov    0x10500c,%eax
  1011d1:	83 c0 01             	add    $0x1,%eax
  1011d4:	a3 0c 50 10 00       	mov    %eax,0x10500c
  1011d9:	a1 0c 50 10 00       	mov    0x10500c,%eax
  1011de:	ba 19 00 00 00       	mov    $0x19,%edx
  1011e3:	39 d0                	cmp    %edx,%eax
  1011e5:	0f 85 af 00 00 00    	jne    10129a <terminal_nextline+0xdf>
        terminal_row = VGA_HEIGHT - 1;
  1011eb:	b8 19 00 00 00       	mov    $0x19,%eax
  1011f0:	83 e8 01             	sub    $0x1,%eax
  1011f3:	a3 0c 50 10 00       	mov    %eax,0x10500c
        for (size_t row = 1; row < VGA_HEIGHT; row++) {
  1011f8:	c7 45 f8 01 00 00 00 	movl   $0x1,-0x8(%ebp)
  1011ff:	eb 57                	jmp    101258 <terminal_nextline+0x9d>
            for (size_t col = 0; col < VGA_WIDTH; col++) {
  101201:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  101208:	eb 40                	jmp    10124a <terminal_nextline+0x8f>
                terminal_buffer[VGA_WIDTH * (row-1) + col] = terminal_buffer[VGA_WIDTH * row + col];
  10120a:	a1 08 50 10 00       	mov    0x105008,%eax
  10120f:	ba 50 00 00 00       	mov    $0x50,%edx
  101214:	89 d1                	mov    %edx,%ecx
  101216:	0f af 4d f8          	imul   -0x8(%ebp),%ecx
  10121a:	8b 55 f4             	mov    -0xc(%ebp),%edx
  10121d:	01 ca                	add    %ecx,%edx
  10121f:	01 d2                	add    %edx,%edx
  101221:	01 d0                	add    %edx,%eax
  101223:	8b 15 08 50 10 00    	mov    0x105008,%edx
  101229:	8b 4d f8             	mov    -0x8(%ebp),%ecx
  10122c:	83 e9 01             	sub    $0x1,%ecx
  10122f:	bb 50 00 00 00       	mov    $0x50,%ebx
  101234:	0f af d9             	imul   %ecx,%ebx
  101237:	8b 4d f4             	mov    -0xc(%ebp),%ecx
  10123a:	01 d9                	add    %ebx,%ecx
  10123c:	01 c9                	add    %ecx,%ecx
  10123e:	01 ca                	add    %ecx,%edx
  101240:	0f b7 00             	movzwl (%eax),%eax
  101243:	66 89 02             	mov    %ax,(%edx)
            for (size_t col = 0; col < VGA_WIDTH; col++) {
  101246:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  10124a:	b8 50 00 00 00       	mov    $0x50,%eax
  10124f:	39 45 f4             	cmp    %eax,-0xc(%ebp)
  101252:	72 b6                	jb     10120a <terminal_nextline+0x4f>
        for (size_t row = 1; row < VGA_HEIGHT; row++) {
  101254:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
  101258:	b8 19 00 00 00       	mov    $0x19,%eax
  10125d:	39 45 f8             	cmp    %eax,-0x8(%ebp)
  101260:	72 9f                	jb     101201 <terminal_nextline+0x46>
            }
        }
		for (size_t col = 0; col < VGA_WIDTH; col++) {
  101262:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
  101269:	eb 25                	jmp    101290 <terminal_nextline+0xd5>
			terminal_putentryat(' ', terminal_color, col, VGA_HEIGHT-1);
  10126b:	b8 19 00 00 00       	mov    $0x19,%eax
  101270:	8d 50 ff             	lea    -0x1(%eax),%edx
  101273:	0f b6 05 00 50 10 00 	movzbl 0x105000,%eax
  10127a:	0f b6 c0             	movzbl %al,%eax
  10127d:	52                   	push   %edx
  10127e:	ff 75 f0             	pushl  -0x10(%ebp)
  101281:	50                   	push   %eax
  101282:	6a 20                	push   $0x20
  101284:	e8 e1 fe ff ff       	call   10116a <terminal_putentryat>
  101289:	83 c4 10             	add    $0x10,%esp
		for (size_t col = 0; col < VGA_WIDTH; col++) {
  10128c:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  101290:	b8 50 00 00 00       	mov    $0x50,%eax
  101295:	39 45 f0             	cmp    %eax,-0x10(%ebp)
  101298:	72 d1                	jb     10126b <terminal_nextline+0xb0>
		}
    }
}
  10129a:	90                   	nop
  10129b:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  10129e:	c9                   	leave  
  10129f:	c3                   	ret    

001012a0 <terminal_putchar>:

void terminal_putchar(char c) 
{
  1012a0:	55                   	push   %ebp
  1012a1:	89 e5                	mov    %esp,%ebp
  1012a3:	53                   	push   %ebx
  1012a4:	83 ec 24             	sub    $0x24,%esp
  1012a7:	8b 45 08             	mov    0x8(%ebp),%eax
  1012aa:	88 45 e4             	mov    %al,-0x1c(%ebp)
    if (c == '\n') {
  1012ad:	80 7d e4 0a          	cmpb   $0xa,-0x1c(%ebp)
  1012b1:	75 0a                	jne    1012bd <terminal_putchar+0x1d>
        terminal_nextline();
  1012b3:	e8 03 ff ff ff       	call   1011bb <terminal_nextline>
        return;
  1012b8:	e9 8c 00 00 00       	jmp    101349 <terminal_putchar+0xa9>
    } else if (c == '\t') {
  1012bd:	80 7d e4 09          	cmpb   $0x9,-0x1c(%ebp)
  1012c1:	75 40                	jne    101303 <terminal_putchar+0x63>
        int spaces = VGA_WIDTH - terminal_column;
  1012c3:	ba 50 00 00 00       	mov    $0x50,%edx
  1012c8:	a1 04 50 10 00       	mov    0x105004,%eax
  1012cd:	29 c2                	sub    %eax,%edx
  1012cf:	89 d0                	mov    %edx,%eax
  1012d1:	89 45 f0             	mov    %eax,-0x10(%ebp)
        if (spaces > TAB_SIZE)
  1012d4:	83 7d f0 04          	cmpl   $0x4,-0x10(%ebp)
  1012d8:	7e 07                	jle    1012e1 <terminal_putchar+0x41>
            spaces = TAB_SIZE;
  1012da:	c7 45 f0 04 00 00 00 	movl   $0x4,-0x10(%ebp)
        for (int i = 0; i < TAB_SIZE; i++)
  1012e1:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  1012e8:	eb 11                	jmp    1012fb <terminal_putchar+0x5b>
            terminal_putchar(' ');
  1012ea:	83 ec 0c             	sub    $0xc,%esp
  1012ed:	6a 20                	push   $0x20
  1012ef:	e8 ac ff ff ff       	call   1012a0 <terminal_putchar>
  1012f4:	83 c4 10             	add    $0x10,%esp
        for (int i = 0; i < TAB_SIZE; i++)
  1012f7:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  1012fb:	83 7d f4 03          	cmpl   $0x3,-0xc(%ebp)
  1012ff:	7e e9                	jle    1012ea <terminal_putchar+0x4a>
        return;
  101301:	eb 46                	jmp    101349 <terminal_putchar+0xa9>
    }
    
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
  101303:	8b 1d 0c 50 10 00    	mov    0x10500c,%ebx
  101309:	8b 0d 04 50 10 00    	mov    0x105004,%ecx
  10130f:	0f b6 05 00 50 10 00 	movzbl 0x105000,%eax
  101316:	0f b6 d0             	movzbl %al,%edx
  101319:	0f be 45 e4          	movsbl -0x1c(%ebp),%eax
  10131d:	53                   	push   %ebx
  10131e:	51                   	push   %ecx
  10131f:	52                   	push   %edx
  101320:	50                   	push   %eax
  101321:	e8 44 fe ff ff       	call   10116a <terminal_putentryat>
  101326:	83 c4 10             	add    $0x10,%esp
	if (++terminal_column == VGA_WIDTH) {
  101329:	a1 04 50 10 00       	mov    0x105004,%eax
  10132e:	83 c0 01             	add    $0x1,%eax
  101331:	a3 04 50 10 00       	mov    %eax,0x105004
  101336:	a1 04 50 10 00       	mov    0x105004,%eax
  10133b:	ba 50 00 00 00       	mov    $0x50,%edx
  101340:	39 d0                	cmp    %edx,%eax
  101342:	75 05                	jne    101349 <terminal_putchar+0xa9>
		terminal_nextline();
  101344:	e8 72 fe ff ff       	call   1011bb <terminal_nextline>
	}
}
  101349:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  10134c:	c9                   	leave  
  10134d:	c3                   	ret    

0010134e <terminal_write>:
 
void terminal_write(const char* data, size_t size) 
{
  10134e:	55                   	push   %ebp
  10134f:	89 e5                	mov    %esp,%ebp
  101351:	83 ec 18             	sub    $0x18,%esp
	for (size_t i = 0; i < size; i++)
  101354:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  10135b:	eb 1e                	jmp    10137b <terminal_write+0x2d>
		terminal_putchar(data[i]);
  10135d:	8b 55 08             	mov    0x8(%ebp),%edx
  101360:	8b 45 f4             	mov    -0xc(%ebp),%eax
  101363:	01 d0                	add    %edx,%eax
  101365:	0f b6 00             	movzbl (%eax),%eax
  101368:	0f be c0             	movsbl %al,%eax
  10136b:	83 ec 0c             	sub    $0xc,%esp
  10136e:	50                   	push   %eax
  10136f:	e8 2c ff ff ff       	call   1012a0 <terminal_putchar>
  101374:	83 c4 10             	add    $0x10,%esp
	for (size_t i = 0; i < size; i++)
  101377:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  10137b:	8b 45 f4             	mov    -0xc(%ebp),%eax
  10137e:	3b 45 0c             	cmp    0xc(%ebp),%eax
  101381:	72 da                	jb     10135d <terminal_write+0xf>
}
  101383:	90                   	nop
  101384:	90                   	nop
  101385:	c9                   	leave  
  101386:	c3                   	ret    

00101387 <terminal_writestring>:
 
void terminal_writestring(const char* data) 
{
  101387:	55                   	push   %ebp
  101388:	89 e5                	mov    %esp,%ebp
  10138a:	83 ec 08             	sub    $0x8,%esp
	terminal_write(data, strlen(data));
  10138d:	ff 75 08             	pushl  0x8(%ebp)
  101390:	e8 f2 fc ff ff       	call   101087 <strlen>
  101395:	83 c4 04             	add    $0x4,%esp
  101398:	83 ec 08             	sub    $0x8,%esp
  10139b:	50                   	push   %eax
  10139c:	ff 75 08             	pushl  0x8(%ebp)
  10139f:	e8 aa ff ff ff       	call   10134e <terminal_write>
  1013a4:	83 c4 10             	add    $0x10,%esp
}
  1013a7:	90                   	nop
  1013a8:	c9                   	leave  
  1013a9:	c3                   	ret    

001013aa <terminal_writeint>:
/**
 * Prints an integer, note that this only supports integers
 * up to 4 bytes. This is only guaranteed to support up-to base 16
 */
void terminal_writeint(int data, const int base)
{
  1013aa:	55                   	push   %ebp
  1013ab:	89 e5                	mov    %esp,%ebp
  1013ad:	83 ec 28             	sub    $0x28,%esp
	bool is_negative = false;
  1013b0:	c6 45 f7 00          	movb   $0x0,-0x9(%ebp)
	if (data < 0) {
  1013b4:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
  1013b8:	79 07                	jns    1013c1 <terminal_writeint+0x17>
		is_negative = true;
  1013ba:	c6 45 f7 01          	movb   $0x1,-0x9(%ebp)
		data *= -1;
  1013be:	f7 5d 08             	negl   0x8(%ebp)
	}
	
	uint8_t digits[10] = {0};
  1013c1:	c7 45 e6 00 00 00 00 	movl   $0x0,-0x1a(%ebp)
  1013c8:	c7 45 ea 00 00 00 00 	movl   $0x0,-0x16(%ebp)
  1013cf:	66 c7 45 ee 00 00    	movw   $0x0,-0x12(%ebp)
	int i = 9;
  1013d5:	c7 45 f0 09 00 00 00 	movl   $0x9,-0x10(%ebp)
	do {
		digits[i--] = data % base;
  1013dc:	8b 45 08             	mov    0x8(%ebp),%eax
  1013df:	99                   	cltd   
  1013e0:	f7 7d 0c             	idivl  0xc(%ebp)
  1013e3:	89 d1                	mov    %edx,%ecx
  1013e5:	8b 45 f0             	mov    -0x10(%ebp),%eax
  1013e8:	8d 50 ff             	lea    -0x1(%eax),%edx
  1013eb:	89 55 f0             	mov    %edx,-0x10(%ebp)
  1013ee:	89 ca                	mov    %ecx,%edx
  1013f0:	88 54 05 e6          	mov    %dl,-0x1a(%ebp,%eax,1)
		data /= base;
  1013f4:	8b 45 08             	mov    0x8(%ebp),%eax
  1013f7:	99                   	cltd   
  1013f8:	f7 7d 0c             	idivl  0xc(%ebp)
  1013fb:	89 45 08             	mov    %eax,0x8(%ebp)
	} while (data != 0); 
  1013fe:	83 7d 08 00          	cmpl   $0x0,0x8(%ebp)
  101402:	75 d8                	jne    1013dc <terminal_writeint+0x32>
	
	if (is_negative && base == 10)
  101404:	80 7d f7 00          	cmpb   $0x0,-0x9(%ebp)
  101408:	74 13                	je     10141d <terminal_writeint+0x73>
  10140a:	83 7d 0c 0a          	cmpl   $0xa,0xc(%ebp)
  10140e:	75 0d                	jne    10141d <terminal_writeint+0x73>
		terminal_putchar('-');
  101410:	83 ec 0c             	sub    $0xc,%esp
  101413:	6a 2d                	push   $0x2d
  101415:	e8 86 fe ff ff       	call   1012a0 <terminal_putchar>
  10141a:	83 c4 10             	add    $0x10,%esp
	
	for (i = i+1; i < 10; i++) {
  10141d:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  101421:	eb 4f                	jmp    101472 <terminal_writeint+0xc8>
		if (digits[i] < 10)
  101423:	8d 55 e6             	lea    -0x1a(%ebp),%edx
  101426:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101429:	01 d0                	add    %edx,%eax
  10142b:	0f b6 00             	movzbl (%eax),%eax
  10142e:	3c 09                	cmp    $0x9,%al
  101430:	77 1f                	ja     101451 <terminal_writeint+0xa7>
			terminal_putchar('0' + digits[i]);
  101432:	8d 55 e6             	lea    -0x1a(%ebp),%edx
  101435:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101438:	01 d0                	add    %edx,%eax
  10143a:	0f b6 00             	movzbl (%eax),%eax
  10143d:	83 c0 30             	add    $0x30,%eax
  101440:	0f be c0             	movsbl %al,%eax
  101443:	83 ec 0c             	sub    $0xc,%esp
  101446:	50                   	push   %eax
  101447:	e8 54 fe ff ff       	call   1012a0 <terminal_putchar>
  10144c:	83 c4 10             	add    $0x10,%esp
  10144f:	eb 1d                	jmp    10146e <terminal_writeint+0xc4>
		else
			terminal_putchar('a' + (digits[i] - 10));
  101451:	8d 55 e6             	lea    -0x1a(%ebp),%edx
  101454:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101457:	01 d0                	add    %edx,%eax
  101459:	0f b6 00             	movzbl (%eax),%eax
  10145c:	83 c0 57             	add    $0x57,%eax
  10145f:	0f be c0             	movsbl %al,%eax
  101462:	83 ec 0c             	sub    $0xc,%esp
  101465:	50                   	push   %eax
  101466:	e8 35 fe ff ff       	call   1012a0 <terminal_putchar>
  10146b:	83 c4 10             	add    $0x10,%esp
	for (i = i+1; i < 10; i++) {
  10146e:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  101472:	83 7d f0 09          	cmpl   $0x9,-0x10(%ebp)
  101476:	7e ab                	jle    101423 <terminal_writeint+0x79>
	}
}
  101478:	90                   	nop
  101479:	90                   	nop
  10147a:	c9                   	leave  
  10147b:	c3                   	ret    

0010147c <terminal_clear>:

void terminal_clear(void)
{
  10147c:	55                   	push   %ebp
  10147d:	89 e5                	mov    %esp,%ebp
  10147f:	83 ec 10             	sub    $0x10,%esp
	terminal_row = 0;
  101482:	c7 05 0c 50 10 00 00 	movl   $0x0,0x10500c
  101489:	00 00 00 
	terminal_column = 0;
  10148c:	c7 05 04 50 10 00 00 	movl   $0x0,0x105004
  101493:	00 00 00 
	for (size_t i = 0; i < VGA_WIDTH; i++)
  101496:	c7 45 fc 00 00 00 00 	movl   $0x0,-0x4(%ebp)
  10149d:	eb 36                	jmp    1014d5 <terminal_clear+0x59>
		for (size_t j = 0; j < VGA_HEIGHT; j++)
  10149f:	c7 45 f8 00 00 00 00 	movl   $0x0,-0x8(%ebp)
  1014a6:	eb 1f                	jmp    1014c7 <terminal_clear+0x4b>
			terminal_putentryat(' ', terminal_color, i, j);
  1014a8:	0f b6 05 00 50 10 00 	movzbl 0x105000,%eax
  1014af:	0f b6 c0             	movzbl %al,%eax
  1014b2:	ff 75 f8             	pushl  -0x8(%ebp)
  1014b5:	ff 75 fc             	pushl  -0x4(%ebp)
  1014b8:	50                   	push   %eax
  1014b9:	6a 20                	push   $0x20
  1014bb:	e8 aa fc ff ff       	call   10116a <terminal_putentryat>
  1014c0:	83 c4 10             	add    $0x10,%esp
		for (size_t j = 0; j < VGA_HEIGHT; j++)
  1014c3:	83 45 f8 01          	addl   $0x1,-0x8(%ebp)
  1014c7:	b8 19 00 00 00       	mov    $0x19,%eax
  1014cc:	39 45 f8             	cmp    %eax,-0x8(%ebp)
  1014cf:	72 d7                	jb     1014a8 <terminal_clear+0x2c>
	for (size_t i = 0; i < VGA_WIDTH; i++)
  1014d1:	83 45 fc 01          	addl   $0x1,-0x4(%ebp)
  1014d5:	b8 50 00 00 00       	mov    $0x50,%eax
  1014da:	39 45 fc             	cmp    %eax,-0x4(%ebp)
  1014dd:	72 c0                	jb     10149f <terminal_clear+0x23>
  1014df:	90                   	nop
  1014e0:	90                   	nop
  1014e1:	c9                   	leave  
  1014e2:	c3                   	ret    

001014e3 <kprintf>:
#include <stdarg.h>
#include <kernel/tty.h>


int kprintf(char *format, ...)
{
  1014e3:	55                   	push   %ebp
  1014e4:	89 e5                	mov    %esp,%ebp
  1014e6:	83 ec 18             	sub    $0x18,%esp
    va_list args;
    va_start(args, format);
  1014e9:	8d 45 0c             	lea    0xc(%ebp),%eax
  1014ec:	89 45 e8             	mov    %eax,-0x18(%ebp)

    int printed = 0;
  1014ef:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
    char *current = format;
  1014f6:	8b 45 08             	mov    0x8(%ebp),%eax
  1014f9:	89 45 f0             	mov    %eax,-0x10(%ebp)
    bool in_format = false;
  1014fc:	c6 45 ef 00          	movb   $0x0,-0x11(%ebp)
    while (*current) {
  101500:	e9 24 01 00 00       	jmp    101629 <kprintf+0x146>
        if (in_format) {
  101505:	80 7d ef 00          	cmpb   $0x0,-0x11(%ebp)
  101509:	0f 84 f1 00 00 00    	je     101600 <kprintf+0x11d>
            switch (*current) {
  10150f:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101512:	0f b6 00             	movzbl (%eax),%eax
  101515:	0f be c0             	movsbl %al,%eax
  101518:	83 f8 25             	cmp    $0x25,%eax
  10151b:	74 4e                	je     10156b <kprintf+0x88>
  10151d:	83 f8 25             	cmp    $0x25,%eax
  101520:	0f 8c bf 00 00 00    	jl     1015e5 <kprintf+0x102>
  101526:	83 f8 78             	cmp    $0x78,%eax
  101529:	0f 8f b6 00 00 00    	jg     1015e5 <kprintf+0x102>
  10152f:	83 f8 58             	cmp    $0x58,%eax
  101532:	0f 8c ad 00 00 00    	jl     1015e5 <kprintf+0x102>
  101538:	83 e8 58             	sub    $0x58,%eax
  10153b:	83 f8 20             	cmp    $0x20,%eax
  10153e:	0f 87 a1 00 00 00    	ja     1015e5 <kprintf+0x102>
  101544:	8b 04 85 f0 30 10 00 	mov    0x1030f0(,%eax,4),%eax
  10154b:	ff e0                	jmp    *%eax
            case 'd':
                terminal_writeint(va_arg(args, int), 10);
  10154d:	8b 45 e8             	mov    -0x18(%ebp),%eax
  101550:	8d 50 04             	lea    0x4(%eax),%edx
  101553:	89 55 e8             	mov    %edx,-0x18(%ebp)
  101556:	8b 00                	mov    (%eax),%eax
  101558:	83 ec 08             	sub    $0x8,%esp
  10155b:	6a 0a                	push   $0xa
  10155d:	50                   	push   %eax
  10155e:	e8 47 fe ff ff       	call   1013aa <terminal_writeint>
  101563:	83 c4 10             	add    $0x10,%esp
                break;
  101566:	e9 8b 00 00 00       	jmp    1015f6 <kprintf+0x113>
            case '%':
                terminal_putchar('%');
  10156b:	83 ec 0c             	sub    $0xc,%esp
  10156e:	6a 25                	push   $0x25
  101570:	e8 2b fd ff ff       	call   1012a0 <terminal_putchar>
  101575:	83 c4 10             	add    $0x10,%esp
                break;
  101578:	eb 7c                	jmp    1015f6 <kprintf+0x113>
            case 'x':
            case 'X':
                terminal_writeint(va_arg(args, int), 16);
  10157a:	8b 45 e8             	mov    -0x18(%ebp),%eax
  10157d:	8d 50 04             	lea    0x4(%eax),%edx
  101580:	89 55 e8             	mov    %edx,-0x18(%ebp)
  101583:	8b 00                	mov    (%eax),%eax
  101585:	83 ec 08             	sub    $0x8,%esp
  101588:	6a 10                	push   $0x10
  10158a:	50                   	push   %eax
  10158b:	e8 1a fe ff ff       	call   1013aa <terminal_writeint>
  101590:	83 c4 10             	add    $0x10,%esp
                break;
  101593:	eb 61                	jmp    1015f6 <kprintf+0x113>
            case 'b':
                terminal_writeint(va_arg(args, int), 2);
  101595:	8b 45 e8             	mov    -0x18(%ebp),%eax
  101598:	8d 50 04             	lea    0x4(%eax),%edx
  10159b:	89 55 e8             	mov    %edx,-0x18(%ebp)
  10159e:	8b 00                	mov    (%eax),%eax
  1015a0:	83 ec 08             	sub    $0x8,%esp
  1015a3:	6a 02                	push   $0x2
  1015a5:	50                   	push   %eax
  1015a6:	e8 ff fd ff ff       	call   1013aa <terminal_writeint>
  1015ab:	83 c4 10             	add    $0x10,%esp
                break;
  1015ae:	eb 46                	jmp    1015f6 <kprintf+0x113>
            case 's':
                terminal_writestring(va_arg(args, char*));
  1015b0:	8b 45 e8             	mov    -0x18(%ebp),%eax
  1015b3:	8d 50 04             	lea    0x4(%eax),%edx
  1015b6:	89 55 e8             	mov    %edx,-0x18(%ebp)
  1015b9:	8b 00                	mov    (%eax),%eax
  1015bb:	83 ec 0c             	sub    $0xc,%esp
  1015be:	50                   	push   %eax
  1015bf:	e8 c3 fd ff ff       	call   101387 <terminal_writestring>
  1015c4:	83 c4 10             	add    $0x10,%esp
                break;
  1015c7:	eb 2d                	jmp    1015f6 <kprintf+0x113>
            case 'c':
                // This is correct as 'int'. 
                // 'char' gets promoted to 'int' when passed through '...'
                terminal_putchar(va_arg(args, int));
  1015c9:	8b 45 e8             	mov    -0x18(%ebp),%eax
  1015cc:	8d 50 04             	lea    0x4(%eax),%edx
  1015cf:	89 55 e8             	mov    %edx,-0x18(%ebp)
  1015d2:	8b 00                	mov    (%eax),%eax
  1015d4:	0f be c0             	movsbl %al,%eax
  1015d7:	83 ec 0c             	sub    $0xc,%esp
  1015da:	50                   	push   %eax
  1015db:	e8 c0 fc ff ff       	call   1012a0 <terminal_putchar>
  1015e0:	83 c4 10             	add    $0x10,%esp
                break;
  1015e3:	eb 11                	jmp    1015f6 <kprintf+0x113>
            default:
                terminal_writestring("[kprintf: unknown specifier]");
  1015e5:	83 ec 0c             	sub    $0xc,%esp
  1015e8:	68 d0 30 10 00       	push   $0x1030d0
  1015ed:	e8 95 fd ff ff       	call   101387 <terminal_writestring>
  1015f2:	83 c4 10             	add    $0x10,%esp
                break;
  1015f5:	90                   	nop
            }
            in_format = false;
  1015f6:	c6 45 ef 00          	movb   $0x0,-0x11(%ebp)
            printed++;
  1015fa:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  1015fe:	eb 25                	jmp    101625 <kprintf+0x142>
        } else {
            if (*current == '%') {
  101600:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101603:	0f b6 00             	movzbl (%eax),%eax
  101606:	3c 25                	cmp    $0x25,%al
  101608:	75 06                	jne    101610 <kprintf+0x12d>
                in_format = true;
  10160a:	c6 45 ef 01          	movb   $0x1,-0x11(%ebp)
  10160e:	eb 15                	jmp    101625 <kprintf+0x142>
            } else {
                terminal_putchar(*current);
  101610:	8b 45 f0             	mov    -0x10(%ebp),%eax
  101613:	0f b6 00             	movzbl (%eax),%eax
  101616:	0f be c0             	movsbl %al,%eax
  101619:	83 ec 0c             	sub    $0xc,%esp
  10161c:	50                   	push   %eax
  10161d:	e8 7e fc ff ff       	call   1012a0 <terminal_putchar>
  101622:	83 c4 10             	add    $0x10,%esp
            }
        }
        current++;
  101625:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
    while (*current) {
  101629:	8b 45 f0             	mov    -0x10(%ebp),%eax
  10162c:	0f b6 00             	movzbl (%eax),%eax
  10162f:	84 c0                	test   %al,%al
  101631:	0f 85 ce fe ff ff    	jne    101505 <kprintf+0x22>
    }

    va_end(args);

    return printed;
  101637:	8b 45 f4             	mov    -0xc(%ebp),%eax
  10163a:	c9                   	leave  
  10163b:	c3                   	ret    

0010163c <_panic>:
{
  10163c:	55                   	push   %ebp
  10163d:	89 e5                	mov    %esp,%ebp
  10163f:	83 ec 08             	sub    $0x8,%esp
    kprintf("panic: %s at line %d. %s\n", file, line, error);
  101642:	ff 75 10             	pushl  0x10(%ebp)
  101645:	ff 75 0c             	pushl  0xc(%ebp)
  101648:	ff 75 08             	pushl  0x8(%ebp)
  10164b:	68 37 33 10 00       	push   $0x103337
  101650:	e8 8e fe ff ff       	call   1014e3 <kprintf>
  101655:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  101658:	fa                   	cli    
  101659:	fc                   	cld    
    while (true) {}
  10165a:	eb fe                	jmp    10165a <_panic+0x1e>

0010165c <_kassert>:
{
  10165c:	55                   	push   %ebp
  10165d:	89 e5                	mov    %esp,%ebp
  10165f:	83 ec 18             	sub    $0x18,%esp
  101662:	8b 45 10             	mov    0x10(%ebp),%eax
  101665:	88 45 f4             	mov    %al,-0xc(%ebp)
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
  101668:	ff 75 14             	pushl  0x14(%ebp)
  10166b:	ff 75 0c             	pushl  0xc(%ebp)
  10166e:	ff 75 08             	pushl  0x8(%ebp)
  101671:	68 54 33 10 00       	push   $0x103354
  101676:	e8 68 fe ff ff       	call   1014e3 <kprintf>
  10167b:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  10167e:	fa                   	cli    
  10167f:	fc                   	cld    
    while (true) {}
  101680:	eb fe                	jmp    101680 <_kassert+0x24>

00101682 <get_exception_message>:
#define IRQ_TIMER       (IRQ_OFFSET + 0)
#define IRQ_KEYBOARD    (IRQ_OFFSET + 1)


static inline const char *get_exception_message(uint32_t code)
{
  101682:	55                   	push   %ebp
  101683:	89 e5                	mov    %esp,%ebp
  101685:	57                   	push   %edi
  101686:	56                   	push   %esi
  101687:	53                   	push   %ebx
  101688:	83 ec 70             	sub    $0x70,%esp
    const char *messages[] = {
  10168b:	8d 45 8c             	lea    -0x74(%ebp),%eax
  10168e:	bb a0 33 10 00       	mov    $0x1033a0,%ebx
  101693:	ba 1a 00 00 00       	mov    $0x1a,%edx
  101698:	89 c7                	mov    %eax,%edi
  10169a:	89 de                	mov    %ebx,%esi
  10169c:	89 d1                	mov    %edx,%ecx
  10169e:	f3 a5                	rep movsl %ds:(%esi),%es:(%edi)
        "Security Exception",
        "[Intel Reserved]",
        "Triple Fault",
        "FPU Error Interrupt"
    };
    if (code < 26) {
  1016a0:	83 7d 08 19          	cmpl   $0x19,0x8(%ebp)
  1016a4:	77 09                	ja     1016af <get_exception_message+0x2d>
        return messages[code];
  1016a6:	8b 45 08             	mov    0x8(%ebp),%eax
  1016a9:	8b 44 85 8c          	mov    -0x74(%ebp,%eax,4),%eax
  1016ad:	eb 05                	jmp    1016b4 <get_exception_message+0x32>
    } else {
        return "Unknown Interrupt";
  1016af:	b8 7f 33 10 00       	mov    $0x10337f,%eax
    }
}
  1016b4:	83 c4 70             	add    $0x70,%esp
  1016b7:	5b                   	pop    %ebx
  1016b8:	5e                   	pop    %esi
  1016b9:	5f                   	pop    %edi
  1016ba:	5d                   	pop    %ebp
  1016bb:	c3                   	ret    

001016bc <init_gdt>:

gdt_entry_t gdt_entries[GDT_ENTRIES];
gdt_ptr_t   gdt_ptr;

void init_gdt()
{
  1016bc:	55                   	push   %ebp
  1016bd:	89 e5                	mov    %esp,%ebp
  1016bf:	83 ec 08             	sub    $0x8,%esp
    gdt_ptr.limit = (sizeof(gdt_entry_t) * GDT_ENTRIES) - 1;
  1016c2:	66 c7 05 60 58 10 00 	movw   $0x27,0x105860
  1016c9:	27 00 
    gdt_ptr.base  = (uint32_t)&gdt_entries;
  1016cb:	b8 20 50 10 00       	mov    $0x105020,%eax
  1016d0:	a3 62 58 10 00       	mov    %eax,0x105862

    gdt_set_gate(0, 0, 0, 0, 0);                // Null segment
  1016d5:	83 ec 0c             	sub    $0xc,%esp
  1016d8:	6a 00                	push   $0x0
  1016da:	6a 00                	push   $0x0
  1016dc:	6a 00                	push   $0x0
  1016de:	6a 00                	push   $0x0
  1016e0:	6a 00                	push   $0x0
  1016e2:	e8 83 00 00 00       	call   10176a <gdt_set_gate>
  1016e7:	83 c4 20             	add    $0x20,%esp
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Code segment
  1016ea:	83 ec 0c             	sub    $0xc,%esp
  1016ed:	68 cf 00 00 00       	push   $0xcf
  1016f2:	68 9a 00 00 00       	push   $0x9a
  1016f7:	6a ff                	push   $0xffffffff
  1016f9:	6a 00                	push   $0x0
  1016fb:	6a 01                	push   $0x1
  1016fd:	e8 68 00 00 00       	call   10176a <gdt_set_gate>
  101702:	83 c4 20             	add    $0x20,%esp
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Data segment
  101705:	83 ec 0c             	sub    $0xc,%esp
  101708:	68 cf 00 00 00       	push   $0xcf
  10170d:	68 92 00 00 00       	push   $0x92
  101712:	6a ff                	push   $0xffffffff
  101714:	6a 00                	push   $0x0
  101716:	6a 02                	push   $0x2
  101718:	e8 4d 00 00 00       	call   10176a <gdt_set_gate>
  10171d:	83 c4 20             	add    $0x20,%esp
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User mode code segment
  101720:	83 ec 0c             	sub    $0xc,%esp
  101723:	68 cf 00 00 00       	push   $0xcf
  101728:	68 fa 00 00 00       	push   $0xfa
  10172d:	6a ff                	push   $0xffffffff
  10172f:	6a 00                	push   $0x0
  101731:	6a 03                	push   $0x3
  101733:	e8 32 00 00 00       	call   10176a <gdt_set_gate>
  101738:	83 c4 20             	add    $0x20,%esp
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User mode data segment
  10173b:	83 ec 0c             	sub    $0xc,%esp
  10173e:	68 cf 00 00 00       	push   $0xcf
  101743:	68 f2 00 00 00       	push   $0xf2
  101748:	6a ff                	push   $0xffffffff
  10174a:	6a 00                	push   $0x0
  10174c:	6a 04                	push   $0x4
  10174e:	e8 17 00 00 00       	call   10176a <gdt_set_gate>
  101753:	83 c4 20             	add    $0x20,%esp

    gdt_flush((uint32_t)&gdt_ptr);
  101756:	b8 60 58 10 00       	mov    $0x105860,%eax
  10175b:	83 ec 0c             	sub    $0xc,%esp
  10175e:	50                   	push   %eax
  10175f:	e8 99 f7 ff ff       	call   100efd <gdt_flush>
  101764:	83 c4 10             	add    $0x10,%esp
}
  101767:	90                   	nop
  101768:	c9                   	leave  
  101769:	c3                   	ret    

0010176a <gdt_set_gate>:

// Set the value of one GDT entry.
static void gdt_set_gate(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
  10176a:	55                   	push   %ebp
  10176b:	89 e5                	mov    %esp,%ebp
  10176d:	83 ec 08             	sub    $0x8,%esp
  101770:	8b 55 14             	mov    0x14(%ebp),%edx
  101773:	8b 45 18             	mov    0x18(%ebp),%eax
  101776:	88 55 fc             	mov    %dl,-0x4(%ebp)
  101779:	88 45 f8             	mov    %al,-0x8(%ebp)
    gdt_entries[num].base_low    = (base & 0xFFFF);
  10177c:	8b 45 0c             	mov    0xc(%ebp),%eax
  10177f:	89 c2                	mov    %eax,%edx
  101781:	8b 45 08             	mov    0x8(%ebp),%eax
  101784:	66 89 14 c5 22 50 10 	mov    %dx,0x105022(,%eax,8)
  10178b:	00 
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  10178c:	8b 45 0c             	mov    0xc(%ebp),%eax
  10178f:	c1 e8 10             	shr    $0x10,%eax
  101792:	89 c2                	mov    %eax,%edx
  101794:	8b 45 08             	mov    0x8(%ebp),%eax
  101797:	88 14 c5 24 50 10 00 	mov    %dl,0x105024(,%eax,8)
    gdt_entries[num].base_high   = (base >> 24) & 0xFF; 
  10179e:	8b 45 0c             	mov    0xc(%ebp),%eax
  1017a1:	c1 e8 18             	shr    $0x18,%eax
  1017a4:	89 c2                	mov    %eax,%edx
  1017a6:	8b 45 08             	mov    0x8(%ebp),%eax
  1017a9:	88 14 c5 27 50 10 00 	mov    %dl,0x105027(,%eax,8)
    
    gdt_entries[num].limit_low   = (limit & 0xFFFF);
  1017b0:	8b 45 10             	mov    0x10(%ebp),%eax
  1017b3:	89 c2                	mov    %eax,%edx
  1017b5:	8b 45 08             	mov    0x8(%ebp),%eax
  1017b8:	66 89 14 c5 20 50 10 	mov    %dx,0x105020(,%eax,8)
  1017bf:	00 
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;    
  1017c0:	8b 45 10             	mov    0x10(%ebp),%eax
  1017c3:	c1 e8 10             	shr    $0x10,%eax
  1017c6:	83 e0 0f             	and    $0xf,%eax
  1017c9:	89 c2                	mov    %eax,%edx
  1017cb:	8b 45 08             	mov    0x8(%ebp),%eax
  1017ce:	88 14 c5 26 50 10 00 	mov    %dl,0x105026(,%eax,8)
    
    gdt_entries[num].granularity |= gran & 0xF0;
  1017d5:	8b 45 08             	mov    0x8(%ebp),%eax
  1017d8:	0f b6 04 c5 26 50 10 	movzbl 0x105026(,%eax,8),%eax
  1017df:	00 
  1017e0:	89 c2                	mov    %eax,%edx
  1017e2:	0f b6 45 f8          	movzbl -0x8(%ebp),%eax
  1017e6:	83 e0 f0             	and    $0xfffffff0,%eax
  1017e9:	09 d0                	or     %edx,%eax
  1017eb:	89 c2                	mov    %eax,%edx
  1017ed:	8b 45 08             	mov    0x8(%ebp),%eax
  1017f0:	88 14 c5 26 50 10 00 	mov    %dl,0x105026(,%eax,8)
    gdt_entries[num].access      = access;
  1017f7:	8b 45 08             	mov    0x8(%ebp),%eax
  1017fa:	0f b6 55 fc          	movzbl -0x4(%ebp),%edx
  1017fe:	88 14 c5 25 50 10 00 	mov    %dl,0x105025(,%eax,8)
}
  101805:	90                   	nop
  101806:	c9                   	leave  
  101807:	c3                   	ret    

00101808 <interrupt_handler>:
*/

static int count = 0;

void interrupt_handler(struct intframe_t *frameptr)
{
  101808:	55                   	push   %ebp
  101809:	89 e5                	mov    %esp,%ebp
  10180b:	56                   	push   %esi
  10180c:	53                   	push   %ebx
    if (frameptr->int_no < IRQ_OFFSET) {
  10180d:	8b 45 08             	mov    0x8(%ebp),%eax
  101810:	8b 40 24             	mov    0x24(%eax),%eax
  101813:	83 f8 1f             	cmp    $0x1f,%eax
  101816:	77 41                	ja     101859 <interrupt_handler+0x51>
        kprintf(
  101818:	8b 45 08             	mov    0x8(%ebp),%eax
  10181b:	8b 70 28             	mov    0x28(%eax),%esi
  10181e:	8b 45 08             	mov    0x8(%ebp),%eax
  101821:	8b 58 24             	mov    0x24(%eax),%ebx
  101824:	8b 45 08             	mov    0x8(%ebp),%eax
  101827:	8b 40 24             	mov    0x24(%eax),%eax
  10182a:	50                   	push   %eax
  10182b:	e8 52 fe ff ff       	call   101682 <get_exception_message>
  101830:	83 c4 04             	add    $0x4,%esp
  101833:	89 c2                	mov    %eax,%edx
  101835:	a1 70 98 10 00       	mov    0x109870,%eax
  10183a:	8d 48 01             	lea    0x1(%eax),%ecx
  10183d:	89 0d 70 98 10 00    	mov    %ecx,0x109870
  101843:	83 ec 0c             	sub    $0xc,%esp
  101846:	56                   	push   %esi
  101847:	53                   	push   %ebx
  101848:	52                   	push   %edx
  101849:	50                   	push   %eax
  10184a:	68 08 34 10 00       	push   $0x103408
  10184f:	e8 8f fc ff ff       	call   1014e3 <kprintf>
  101854:	83 c4 20             	add    $0x20,%esp
        );
    } else {
        dispatch_irq(frameptr);
        pic_ack(frameptr->int_no);
    }
}
  101857:	eb 20                	jmp    101879 <interrupt_handler+0x71>
        dispatch_irq(frameptr);
  101859:	83 ec 0c             	sub    $0xc,%esp
  10185c:	ff 75 08             	pushl  0x8(%ebp)
  10185f:	e8 26 03 00 00       	call   101b8a <dispatch_irq>
  101864:	83 c4 10             	add    $0x10,%esp
        pic_ack(frameptr->int_no);
  101867:	8b 45 08             	mov    0x8(%ebp),%eax
  10186a:	8b 40 24             	mov    0x24(%eax),%eax
  10186d:	83 ec 0c             	sub    $0xc,%esp
  101870:	50                   	push   %eax
  101871:	e8 79 02 00 00       	call   101aef <pic_ack>
  101876:	83 c4 10             	add    $0x10,%esp
}
  101879:	90                   	nop
  10187a:	8d 65 f8             	lea    -0x8(%ebp),%esp
  10187d:	5b                   	pop    %ebx
  10187e:	5e                   	pop    %esi
  10187f:	5d                   	pop    %ebp
  101880:	c3                   	ret    

00101881 <set_idt_gate>:

extern uint32_t handlers[IDT_ENTRIES];


static void set_idt_gate(int i, uint16_t selector, uint8_t type, uint32_t isr) {
  101881:	55                   	push   %ebp
  101882:	89 e5                	mov    %esp,%ebp
  101884:	83 ec 08             	sub    $0x8,%esp
  101887:	8b 45 0c             	mov    0xc(%ebp),%eax
  10188a:	8b 55 10             	mov    0x10(%ebp),%edx
  10188d:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
  101891:	89 d0                	mov    %edx,%eax
  101893:	88 45 f8             	mov    %al,-0x8(%ebp)
    idt_entries[i].zero = 0;
  101896:	8b 45 08             	mov    0x8(%ebp),%eax
  101899:	c6 04 c5 64 50 10 00 	movb   $0x0,0x105064(,%eax,8)
  1018a0:	00 
    idt_entries[i].selector = selector;
  1018a1:	8b 45 08             	mov    0x8(%ebp),%eax
  1018a4:	0f b7 55 fc          	movzwl -0x4(%ebp),%edx
  1018a8:	66 89 14 c5 62 50 10 	mov    %dx,0x105062(,%eax,8)
  1018af:	00 
    idt_entries[i].type_attr = type;
  1018b0:	8b 45 08             	mov    0x8(%ebp),%eax
  1018b3:	0f b6 55 f8          	movzbl -0x8(%ebp),%edx
  1018b7:	88 14 c5 65 50 10 00 	mov    %dl,0x105065(,%eax,8)

    idt_entries[i].offset_low = isr & 0xffff;
  1018be:	8b 45 14             	mov    0x14(%ebp),%eax
  1018c1:	89 c2                	mov    %eax,%edx
  1018c3:	8b 45 08             	mov    0x8(%ebp),%eax
  1018c6:	66 89 14 c5 60 50 10 	mov    %dx,0x105060(,%eax,8)
  1018cd:	00 
    idt_entries[i].offset_high = (isr >> 16) & 0xffff;
  1018ce:	8b 45 14             	mov    0x14(%ebp),%eax
  1018d1:	c1 e8 10             	shr    $0x10,%eax
  1018d4:	89 c2                	mov    %eax,%edx
  1018d6:	8b 45 08             	mov    0x8(%ebp),%eax
  1018d9:	66 89 14 c5 66 50 10 	mov    %dx,0x105066(,%eax,8)
  1018e0:	00 
}
  1018e1:	90                   	nop
  1018e2:	c9                   	leave  
  1018e3:	c3                   	ret    

001018e4 <init_idt>:

void init_idt()
{
  1018e4:	55                   	push   %ebp
  1018e5:	89 e5                	mov    %esp,%ebp
  1018e7:	83 ec 18             	sub    $0x18,%esp
    kassert(sizeof(idt_entry_t) == 8);
    kassert(sizeof(idt_desc_t) == 6);

    idt_desc.size = (sizeof(idt_entry_t) * IDT_ENTRIES) - 1;
  1018ea:	66 c7 05 68 58 10 00 	movw   $0x7ff,0x105868
  1018f1:	ff 07 
    idt_desc.ptr = (uint32_t) idt_entries;
  1018f3:	b8 60 50 10 00       	mov    $0x105060,%eax
  1018f8:	a3 6a 58 10 00       	mov    %eax,0x10586a

    for (int i = 0; i < IDT_ENTRIES; i++) {
  1018fd:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  101904:	eb 21                	jmp    101927 <init_idt+0x43>
        set_idt_gate(i, 0x08, 0x8e, handlers[i]);
  101906:	8b 45 f4             	mov    -0xc(%ebp),%eax
  101909:	8b 04 85 e8 0a 10 00 	mov    0x100ae8(,%eax,4),%eax
  101910:	50                   	push   %eax
  101911:	68 8e 00 00 00       	push   $0x8e
  101916:	6a 08                	push   $0x8
  101918:	ff 75 f4             	pushl  -0xc(%ebp)
  10191b:	e8 61 ff ff ff       	call   101881 <set_idt_gate>
  101920:	83 c4 10             	add    $0x10,%esp
    for (int i = 0; i < IDT_ENTRIES; i++) {
  101923:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  101927:	81 7d f4 ff 00 00 00 	cmpl   $0xff,-0xc(%ebp)
  10192e:	7e d6                	jle    101906 <init_idt+0x22>
    }

    load_idt((uint32_t) &idt_desc);
  101930:	b8 68 58 10 00       	mov    $0x105868,%eax
  101935:	83 ec 0c             	sub    $0xc,%esp
  101938:	50                   	push   %eax
  101939:	e8 dc f5 ff ff       	call   100f1a <load_idt>
  10193e:	83 c4 10             	add    $0x10,%esp
    pic_init(IRQ_OFFSET);
  101941:	83 ec 0c             	sub    $0xc,%esp
  101944:	6a 20                	push   $0x20
  101946:	e8 8b 00 00 00       	call   1019d6 <pic_init>
  10194b:	83 c4 10             	add    $0x10,%esp
    asm("sti");
  10194e:	fb                   	sti    
  10194f:	90                   	nop
  101950:	c9                   	leave  
  101951:	c3                   	ret    

00101952 <_panic>:
{
  101952:	55                   	push   %ebp
  101953:	89 e5                	mov    %esp,%ebp
  101955:	83 ec 08             	sub    $0x8,%esp
    kprintf("panic: %s at line %d. %s\n", file, line, error);
  101958:	ff 75 10             	pushl  0x10(%ebp)
  10195b:	ff 75 0c             	pushl  0xc(%ebp)
  10195e:	ff 75 08             	pushl  0x8(%ebp)
  101961:	68 1c 34 10 00       	push   $0x10341c
  101966:	e8 78 fb ff ff       	call   1014e3 <kprintf>
  10196b:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  10196e:	fa                   	cli    
  10196f:	fc                   	cld    
    while (true) {}
  101970:	eb fe                	jmp    101970 <_panic+0x1e>

00101972 <_kassert>:
{
  101972:	55                   	push   %ebp
  101973:	89 e5                	mov    %esp,%ebp
  101975:	83 ec 18             	sub    $0x18,%esp
  101978:	8b 45 10             	mov    0x10(%ebp),%eax
  10197b:	88 45 f4             	mov    %al,-0xc(%ebp)
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
  10197e:	ff 75 14             	pushl  0x14(%ebp)
  101981:	ff 75 0c             	pushl  0xc(%ebp)
  101984:	ff 75 08             	pushl  0x8(%ebp)
  101987:	68 38 34 10 00       	push   $0x103438
  10198c:	e8 52 fb ff ff       	call   1014e3 <kprintf>
  101991:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  101994:	fa                   	cli    
  101995:	fc                   	cld    
    while (true) {}
  101996:	eb fe                	jmp    101996 <_kassert+0x24>

00101998 <outb>:
#include <stdbool.h>
#include <stdint.h>


static inline void outb(uint16_t port, uint8_t val)
{
  101998:	55                   	push   %ebp
  101999:	89 e5                	mov    %esp,%ebp
  10199b:	83 ec 08             	sub    $0x8,%esp
  10199e:	8b 45 08             	mov    0x8(%ebp),%eax
  1019a1:	8b 55 0c             	mov    0xc(%ebp),%edx
  1019a4:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
  1019a8:	89 d0                	mov    %edx,%eax
  1019aa:	88 45 f8             	mov    %al,-0x8(%ebp)
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
  1019ad:	0f b6 45 f8          	movzbl -0x8(%ebp),%eax
  1019b1:	0f b7 55 fc          	movzwl -0x4(%ebp),%edx
  1019b5:	ee                   	out    %al,(%dx)
}
  1019b6:	90                   	nop
  1019b7:	c9                   	leave  
  1019b8:	c3                   	ret    

001019b9 <inb>:

static inline uint8_t inb(uint16_t port)
{
  1019b9:	55                   	push   %ebp
  1019ba:	89 e5                	mov    %esp,%ebp
  1019bc:	83 ec 14             	sub    $0x14,%esp
  1019bf:	8b 45 08             	mov    0x8(%ebp),%eax
  1019c2:	66 89 45 ec          	mov    %ax,-0x14(%ebp)
    uint8_t ret;
    asm volatile ( "inb %1, %0"
  1019c6:	0f b7 45 ec          	movzwl -0x14(%ebp),%eax
  1019ca:	89 c2                	mov    %eax,%edx
  1019cc:	ec                   	in     (%dx),%al
  1019cd:	88 45 ff             	mov    %al,-0x1(%ebp)
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
  1019d0:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
}
  1019d4:	c9                   	leave  
  1019d5:	c3                   	ret    

001019d6 <pic_init>:
	argument offset. This is required, as the PIC 8259 by defaults routes 
	those in the first 16 interrupts, which are reserved by Intel. As such, 
	offset needs to be a number between [32, 255 - 16]
*/
void pic_init(uint8_t offset)
{
  1019d6:	55                   	push   %ebp
  1019d7:	89 e5                	mov    %esp,%ebp
  1019d9:	83 ec 28             	sub    $0x28,%esp
  1019dc:	8b 45 08             	mov    0x8(%ebp),%eax
  1019df:	88 45 e4             	mov    %al,-0x1c(%ebp)
	if (offset < 16 || offset > 256 - 16) {
  1019e2:	80 7d e4 0f          	cmpb   $0xf,-0x1c(%ebp)
  1019e6:	76 06                	jbe    1019ee <pic_init+0x18>
  1019e8:	80 7d e4 f0          	cmpb   $0xf0,-0x1c(%ebp)
  1019ec:	76 1c                	jbe    101a0a <pic_init+0x34>
		panic("offset needs to be a value between 16 and 239");
  1019ee:	83 ec 04             	sub    $0x4,%esp
  1019f1:	68 64 34 10 00       	push   $0x103464
  1019f6:	6a 19                	push   $0x19
  1019f8:	68 92 34 10 00       	push   $0x103492
  1019fd:	e8 50 ff ff ff       	call   101952 <_panic>
  101a02:	83 c4 10             	add    $0x10,%esp
		return ;
  101a05:	e9 e3 00 00 00       	jmp    101aed <pic_init+0x117>
	}
	uint8_t mask1, mask2;

	mask1 = inb(PIC1_DATA);
  101a0a:	83 ec 0c             	sub    $0xc,%esp
  101a0d:	6a 21                	push   $0x21
  101a0f:	e8 a5 ff ff ff       	call   1019b9 <inb>
  101a14:	83 c4 10             	add    $0x10,%esp
  101a17:	88 45 f7             	mov    %al,-0x9(%ebp)
	mask2 = inb(PIC2_DATA);
  101a1a:	83 ec 0c             	sub    $0xc,%esp
  101a1d:	68 a1 00 00 00       	push   $0xa1
  101a22:	e8 92 ff ff ff       	call   1019b9 <inb>
  101a27:	83 c4 10             	add    $0x10,%esp
  101a2a:	88 45 f6             	mov    %al,-0xa(%ebp)

	outb(PIC1_COMMAND, 0x11);
  101a2d:	83 ec 08             	sub    $0x8,%esp
  101a30:	6a 11                	push   $0x11
  101a32:	6a 20                	push   $0x20
  101a34:	e8 5f ff ff ff       	call   101998 <outb>
  101a39:	83 c4 10             	add    $0x10,%esp
	outb(PIC2_COMMAND, 0x11);
  101a3c:	83 ec 08             	sub    $0x8,%esp
  101a3f:	6a 11                	push   $0x11
  101a41:	68 a0 00 00 00       	push   $0xa0
  101a46:	e8 4d ff ff ff       	call   101998 <outb>
  101a4b:	83 c4 10             	add    $0x10,%esp
	outb(PIC1_DATA, offset);
  101a4e:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101a52:	83 ec 08             	sub    $0x8,%esp
  101a55:	50                   	push   %eax
  101a56:	6a 21                	push   $0x21
  101a58:	e8 3b ff ff ff       	call   101998 <outb>
  101a5d:	83 c4 10             	add    $0x10,%esp
	outb(PIC2_DATA, offset + 8);
  101a60:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101a64:	83 c0 08             	add    $0x8,%eax
  101a67:	0f b6 c0             	movzbl %al,%eax
  101a6a:	83 ec 08             	sub    $0x8,%esp
  101a6d:	50                   	push   %eax
  101a6e:	68 a1 00 00 00       	push   $0xa1
  101a73:	e8 20 ff ff ff       	call   101998 <outb>
  101a78:	83 c4 10             	add    $0x10,%esp
	outb(PIC1_DATA, 0x04);
  101a7b:	83 ec 08             	sub    $0x8,%esp
  101a7e:	6a 04                	push   $0x4
  101a80:	6a 21                	push   $0x21
  101a82:	e8 11 ff ff ff       	call   101998 <outb>
  101a87:	83 c4 10             	add    $0x10,%esp
	outb(PIC2_DATA, 0x02);
  101a8a:	83 ec 08             	sub    $0x8,%esp
  101a8d:	6a 02                	push   $0x2
  101a8f:	68 a1 00 00 00       	push   $0xa1
  101a94:	e8 ff fe ff ff       	call   101998 <outb>
  101a99:	83 c4 10             	add    $0x10,%esp
	outb(PIC1_DATA, 0x01);
  101a9c:	83 ec 08             	sub    $0x8,%esp
  101a9f:	6a 01                	push   $0x1
  101aa1:	6a 21                	push   $0x21
  101aa3:	e8 f0 fe ff ff       	call   101998 <outb>
  101aa8:	83 c4 10             	add    $0x10,%esp
	outb(PIC2_DATA, 0x01);
  101aab:	83 ec 08             	sub    $0x8,%esp
  101aae:	6a 01                	push   $0x1
  101ab0:	68 a1 00 00 00       	push   $0xa1
  101ab5:	e8 de fe ff ff       	call   101998 <outb>
  101aba:	83 c4 10             	add    $0x10,%esp

	outb(PIC1_DATA, mask1);
  101abd:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101ac1:	83 ec 08             	sub    $0x8,%esp
  101ac4:	50                   	push   %eax
  101ac5:	6a 21                	push   $0x21
  101ac7:	e8 cc fe ff ff       	call   101998 <outb>
  101acc:	83 c4 10             	add    $0x10,%esp
	outb(PIC2_DATA, mask2);
  101acf:	0f b6 45 f6          	movzbl -0xa(%ebp),%eax
  101ad3:	83 ec 08             	sub    $0x8,%esp
  101ad6:	50                   	push   %eax
  101ad7:	68 a1 00 00 00       	push   $0xa1
  101adc:	e8 b7 fe ff ff       	call   101998 <outb>
  101ae1:	83 c4 10             	add    $0x10,%esp

	irq_offset = offset;
  101ae4:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101ae8:	a3 74 98 10 00       	mov    %eax,0x109874
}
  101aed:	c9                   	leave  
  101aee:	c3                   	ret    

00101aef <pic_ack>:
	before.
	irq_number: The number of the IRQ, without considering the offset
*/ 

void pic_ack(uint32_t irq_number)
{
  101aef:	55                   	push   %ebp
  101af0:	89 e5                	mov    %esp,%ebp
  101af2:	83 ec 08             	sub    $0x8,%esp
	if (irq_offset == 0) {
  101af5:	a1 74 98 10 00       	mov    0x109874,%eax
  101afa:	85 c0                	test   %eax,%eax
  101afc:	75 19                	jne    101b17 <pic_ack+0x28>
		panic("pic_init was not called before pic_ack");
  101afe:	83 ec 04             	sub    $0x4,%esp
  101b01:	68 a8 34 10 00       	push   $0x1034a8
  101b06:	6a 3a                	push   $0x3a
  101b08:	68 92 34 10 00       	push   $0x103492
  101b0d:	e8 40 fe ff ff       	call   101952 <_panic>
  101b12:	83 c4 10             	add    $0x10,%esp
		return ;
  101b15:	eb 2e                	jmp    101b45 <pic_ack+0x56>
	}
	if (irq_number >= irq_offset + 8) {
  101b17:	a1 74 98 10 00       	mov    0x109874,%eax
  101b1c:	83 c0 08             	add    $0x8,%eax
  101b1f:	39 45 08             	cmp    %eax,0x8(%ebp)
  101b22:	72 12                	jb     101b36 <pic_ack+0x47>
		outb(PIC2_COMMAND, 0x20);
  101b24:	83 ec 08             	sub    $0x8,%esp
  101b27:	6a 20                	push   $0x20
  101b29:	68 a0 00 00 00       	push   $0xa0
  101b2e:	e8 65 fe ff ff       	call   101998 <outb>
  101b33:	83 c4 10             	add    $0x10,%esp
	}
	outb(PIC1_COMMAND, 0x20);
  101b36:	83 ec 08             	sub    $0x8,%esp
  101b39:	6a 20                	push   $0x20
  101b3b:	6a 20                	push   $0x20
  101b3d:	e8 56 fe ff ff       	call   101998 <outb>
  101b42:	83 c4 10             	add    $0x10,%esp
  101b45:	c9                   	leave  
  101b46:	c3                   	ret    

00101b47 <inb>:
{
  101b47:	55                   	push   %ebp
  101b48:	89 e5                	mov    %esp,%ebp
  101b4a:	83 ec 14             	sub    $0x14,%esp
  101b4d:	8b 45 08             	mov    0x8(%ebp),%eax
  101b50:	66 89 45 ec          	mov    %ax,-0x14(%ebp)
    asm volatile ( "inb %1, %0"
  101b54:	0f b7 45 ec          	movzwl -0x14(%ebp),%eax
  101b58:	89 c2                	mov    %eax,%edx
  101b5a:	ec                   	in     (%dx),%al
  101b5b:	88 45 ff             	mov    %al,-0x1(%ebp)
    return ret;
  101b5e:	0f b6 45 ff          	movzbl -0x1(%ebp),%eax
}
  101b62:	c9                   	leave  
  101b63:	c3                   	ret    

00101b64 <keyboard_irq>:
#include <kernel/timer.h>
#include <lib/input/keyboard.h>


void keyboard_irq(struct intframe_t *intframe)
{
  101b64:	55                   	push   %ebp
  101b65:	89 e5                	mov    %esp,%ebp
  101b67:	83 ec 18             	sub    $0x18,%esp
    unsigned char byte = inb(0x60);
  101b6a:	6a 60                	push   $0x60
  101b6c:	e8 d6 ff ff ff       	call   101b47 <inb>
  101b71:	83 c4 04             	add    $0x4,%esp
  101b74:	88 45 f7             	mov    %al,-0x9(%ebp)
    kbd_handle_byte(byte);
  101b77:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101b7b:	83 ec 0c             	sub    $0xc,%esp
  101b7e:	50                   	push   %eax
  101b7f:	e8 21 02 00 00       	call   101da5 <kbd_handle_byte>
  101b84:	83 c4 10             	add    $0x10,%esp
}
  101b87:	90                   	nop
  101b88:	c9                   	leave  
  101b89:	c3                   	ret    

00101b8a <dispatch_irq>:

void dispatch_irq(struct intframe_t *intframe)
{
  101b8a:	55                   	push   %ebp
  101b8b:	89 e5                	mov    %esp,%ebp
  101b8d:	83 ec 08             	sub    $0x8,%esp
    switch (intframe->int_no) {
  101b90:	8b 45 08             	mov    0x8(%ebp),%eax
  101b93:	8b 40 24             	mov    0x24(%eax),%eax
  101b96:	83 f8 20             	cmp    $0x20,%eax
  101b99:	74 07                	je     101ba2 <dispatch_irq+0x18>
  101b9b:	83 f8 21             	cmp    $0x21,%eax
  101b9e:	74 09                	je     101ba9 <dispatch_irq+0x1f>
  101ba0:	eb 17                	jmp    101bb9 <dispatch_irq+0x2f>
    case IRQ_TIMER:
        __timer_tick();
  101ba2:	e8 5f 00 00 00       	call   101c06 <__timer_tick>
        break;
  101ba7:	eb 2f                	jmp    101bd8 <dispatch_irq+0x4e>
    case IRQ_KEYBOARD:
        keyboard_irq(intframe);
  101ba9:	83 ec 0c             	sub    $0xc,%esp
  101bac:	ff 75 08             	pushl  0x8(%ebp)
  101baf:	e8 b0 ff ff ff       	call   101b64 <keyboard_irq>
  101bb4:	83 c4 10             	add    $0x10,%esp
        break;
  101bb7:	eb 1f                	jmp    101bd8 <dispatch_irq+0x4e>
    default:
        kprintf("Unknown IRQ(%d - %d)\n", intframe->int_no, intframe->err_code);
  101bb9:	8b 45 08             	mov    0x8(%ebp),%eax
  101bbc:	8b 50 28             	mov    0x28(%eax),%edx
  101bbf:	8b 45 08             	mov    0x8(%ebp),%eax
  101bc2:	8b 40 24             	mov    0x24(%eax),%eax
  101bc5:	83 ec 04             	sub    $0x4,%esp
  101bc8:	52                   	push   %edx
  101bc9:	50                   	push   %eax
  101bca:	68 cf 34 10 00       	push   $0x1034cf
  101bcf:	e8 0f f9 ff ff       	call   1014e3 <kprintf>
  101bd4:	83 c4 10             	add    $0x10,%esp
        
    }
  101bd7:	90                   	nop
  101bd8:	90                   	nop
  101bd9:	c9                   	leave  
  101bda:	c3                   	ret    

00101bdb <outb>:
{
  101bdb:	55                   	push   %ebp
  101bdc:	89 e5                	mov    %esp,%ebp
  101bde:	83 ec 08             	sub    $0x8,%esp
  101be1:	8b 45 08             	mov    0x8(%ebp),%eax
  101be4:	8b 55 0c             	mov    0xc(%ebp),%edx
  101be7:	66 89 45 fc          	mov    %ax,-0x4(%ebp)
  101beb:	89 d0                	mov    %edx,%eax
  101bed:	88 45 f8             	mov    %al,-0x8(%ebp)
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
  101bf0:	0f b6 45 f8          	movzbl -0x8(%ebp),%eax
  101bf4:	0f b7 55 fc          	movzwl -0x4(%ebp),%edx
  101bf8:	ee                   	out    %al,(%dx)
}
  101bf9:	90                   	nop
  101bfa:	c9                   	leave  
  101bfb:	c3                   	ret    

00101bfc <timer_get_ticks>:


uint32_t ticks = 0;

uint32_t timer_get_ticks()
{
  101bfc:	55                   	push   %ebp
  101bfd:	89 e5                	mov    %esp,%ebp
    return ticks;
  101bff:	a1 78 98 10 00       	mov    0x109878,%eax
}
  101c04:	5d                   	pop    %ebp
  101c05:	c3                   	ret    

00101c06 <__timer_tick>:
/*
    Called every timer tick by the interrupt handler.
    DO NOT CALL THIS OUTSIDE OF 'irq_dispatch'
*/
void __timer_tick()
{
  101c06:	55                   	push   %ebp
  101c07:	89 e5                	mov    %esp,%ebp
    ticks++;
  101c09:	a1 78 98 10 00       	mov    0x109878,%eax
  101c0e:	83 c0 01             	add    $0x1,%eax
  101c11:	a3 78 98 10 00       	mov    %eax,0x109878
}
  101c16:	90                   	nop
  101c17:	5d                   	pop    %ebp
  101c18:	c3                   	ret    

00101c19 <timer_init>:
/*
    Sets the timer to send an interrupt every 'milliseconds' ms. Note that 
    it is not accurate
*/
void timer_init(uint16_t frequency)
{
  101c19:	55                   	push   %ebp
  101c1a:	89 e5                	mov    %esp,%ebp
  101c1c:	83 ec 14             	sub    $0x14,%esp
  101c1f:	8b 45 08             	mov    0x8(%ebp),%eax
  101c22:	66 89 45 ec          	mov    %ax,-0x14(%ebp)
    /*
        The PIC 8259 by default sends an interrupt every 1193180Hz, to change 
        this we can send a number to divide this frequency. 
        See: https://wiki.osdev.org/Programmable_Interval_Timer
    */
    uint32_t divisor = 1193182 / frequency;
  101c26:	0f b7 4d ec          	movzwl -0x14(%ebp),%ecx
  101c2a:	b8 de 34 12 00       	mov    $0x1234de,%eax
  101c2f:	99                   	cltd   
  101c30:	f7 f9                	idiv   %ecx
  101c32:	89 45 fc             	mov    %eax,-0x4(%ebp)

    outb(0x43, 0x36);
  101c35:	6a 36                	push   $0x36
  101c37:	6a 43                	push   $0x43
  101c39:	e8 9d ff ff ff       	call   101bdb <outb>
  101c3e:	83 c4 08             	add    $0x8,%esp
    outb(0x40, (uint8_t) (divisor & 0xff));
  101c41:	8b 45 fc             	mov    -0x4(%ebp),%eax
  101c44:	0f b6 c0             	movzbl %al,%eax
  101c47:	50                   	push   %eax
  101c48:	6a 40                	push   $0x40
  101c4a:	e8 8c ff ff ff       	call   101bdb <outb>
  101c4f:	83 c4 08             	add    $0x8,%esp
    outb(0x40, (uint8_t) ((divisor >> 8) & 0xff));
  101c52:	8b 45 fc             	mov    -0x4(%ebp),%eax
  101c55:	c1 e8 08             	shr    $0x8,%eax
  101c58:	0f b6 c0             	movzbl %al,%eax
  101c5b:	50                   	push   %eax
  101c5c:	6a 40                	push   $0x40
  101c5e:	e8 78 ff ff ff       	call   101bdb <outb>
  101c63:	83 c4 08             	add    $0x8,%esp
  101c66:	90                   	nop
  101c67:	c9                   	leave  
  101c68:	c3                   	ret    

00101c69 <_panic>:
{
  101c69:	55                   	push   %ebp
  101c6a:	89 e5                	mov    %esp,%ebp
  101c6c:	83 ec 08             	sub    $0x8,%esp
    kprintf("panic: %s at line %d. %s\n", file, line, error);
  101c6f:	ff 75 10             	pushl  0x10(%ebp)
  101c72:	ff 75 0c             	pushl  0xc(%ebp)
  101c75:	ff 75 08             	pushl  0x8(%ebp)
  101c78:	68 e8 34 10 00       	push   $0x1034e8
  101c7d:	e8 61 f8 ff ff       	call   1014e3 <kprintf>
  101c82:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  101c85:	fa                   	cli    
  101c86:	fc                   	cld    
    while (true) {}
  101c87:	eb fe                	jmp    101c87 <_panic+0x1e>

00101c89 <_kassert>:
{
  101c89:	55                   	push   %ebp
  101c8a:	89 e5                	mov    %esp,%ebp
  101c8c:	83 ec 18             	sub    $0x18,%esp
  101c8f:	8b 45 10             	mov    0x10(%ebp),%eax
  101c92:	88 45 f4             	mov    %al,-0xc(%ebp)
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
  101c95:	ff 75 14             	pushl  0x14(%ebp)
  101c98:	ff 75 0c             	pushl  0xc(%ebp)
  101c9b:	ff 75 08             	pushl  0x8(%ebp)
  101c9e:	68 04 35 10 00       	push   $0x103504
  101ca3:	e8 3b f8 ff ff       	call   1014e3 <kprintf>
  101ca8:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  101cab:	fa                   	cli    
  101cac:	fc                   	cld    
    while (true) {}
  101cad:	eb fe                	jmp    101cad <_kassert+0x24>

00101caf <eventqueue_add>:
    Returns:
        1 if it was added successfully
        0 if the queue is full
*/
static int eventqueue_add(struct KeyAction action)
{
  101caf:	55                   	push   %ebp
  101cb0:	89 e5                	mov    %esp,%ebp
  101cb2:	83 ec 10             	sub    $0x10,%esp
    if (event_queue.size == EVENTQUEUE_SIZE) {
  101cb5:	a1 a4 ad 10 00       	mov    0x10ada4,%eax
  101cba:	3d 00 01 00 00       	cmp    $0x100,%eax
  101cbf:	75 07                	jne    101cc8 <eventqueue_add+0x19>
        return 0;
  101cc1:	b8 00 00 00 00       	mov    $0x0,%eax
  101cc6:	eb 62                	jmp    101d2a <eventqueue_add+0x7b>
    }

    int newindex = (event_queue.from + event_queue.size) % EVENTQUEUE_SIZE;
  101cc8:	8b 15 a0 ad 10 00    	mov    0x10ada0,%edx
  101cce:	a1 a4 ad 10 00       	mov    0x10ada4,%eax
  101cd3:	01 c2                	add    %eax,%edx
  101cd5:	89 d0                	mov    %edx,%eax
  101cd7:	c1 f8 1f             	sar    $0x1f,%eax
  101cda:	c1 e8 18             	shr    $0x18,%eax
  101cdd:	01 c2                	add    %eax,%edx
  101cdf:	0f b6 d2             	movzbl %dl,%edx
  101ce2:	29 c2                	sub    %eax,%edx
  101ce4:	89 d0                	mov    %edx,%eax
  101ce6:	89 45 fc             	mov    %eax,-0x4(%ebp)
    event_queue.events[newindex] = action;
  101ce9:	8b 55 fc             	mov    -0x4(%ebp),%edx
  101cec:	89 d0                	mov    %edx,%eax
  101cee:	c1 e0 02             	shl    $0x2,%eax
  101cf1:	01 d0                	add    %edx,%eax
  101cf3:	c1 e0 02             	shl    $0x2,%eax
  101cf6:	05 a0 99 10 00       	add    $0x1099a0,%eax
  101cfb:	8b 55 08             	mov    0x8(%ebp),%edx
  101cfe:	89 10                	mov    %edx,(%eax)
  101d00:	8b 55 0c             	mov    0xc(%ebp),%edx
  101d03:	89 50 04             	mov    %edx,0x4(%eax)
  101d06:	8b 55 10             	mov    0x10(%ebp),%edx
  101d09:	89 50 08             	mov    %edx,0x8(%eax)
  101d0c:	8b 55 14             	mov    0x14(%ebp),%edx
  101d0f:	89 50 0c             	mov    %edx,0xc(%eax)
  101d12:	8b 55 18             	mov    0x18(%ebp),%edx
  101d15:	89 50 10             	mov    %edx,0x10(%eax)
    event_queue.size++;
  101d18:	a1 a4 ad 10 00       	mov    0x10ada4,%eax
  101d1d:	83 c0 01             	add    $0x1,%eax
  101d20:	a3 a4 ad 10 00       	mov    %eax,0x10ada4

    return 1;
  101d25:	b8 01 00 00 00       	mov    $0x1,%eax
}
  101d2a:	c9                   	leave  
  101d2b:	c3                   	ret    

00101d2c <eventqueue_read>:
    Returns:
        1 if it was read successfully
        0 if the queue was empty
*/
static int eventqueue_read(struct KeyAction *action)
{
  101d2c:	55                   	push   %ebp
  101d2d:	89 e5                	mov    %esp,%ebp
    if (event_queue.size == 0) {
  101d2f:	a1 a4 ad 10 00       	mov    0x10ada4,%eax
  101d34:	85 c0                	test   %eax,%eax
  101d36:	75 07                	jne    101d3f <eventqueue_read+0x13>
        return 0;
  101d38:	b8 00 00 00 00       	mov    $0x0,%eax
  101d3d:	eb 64                	jmp    101da3 <eventqueue_read+0x77>
    }
    *action = event_queue.events[event_queue.from];
  101d3f:	8b 0d a0 ad 10 00    	mov    0x10ada0,%ecx
  101d45:	8b 55 08             	mov    0x8(%ebp),%edx
  101d48:	89 c8                	mov    %ecx,%eax
  101d4a:	c1 e0 02             	shl    $0x2,%eax
  101d4d:	01 c8                	add    %ecx,%eax
  101d4f:	c1 e0 02             	shl    $0x2,%eax
  101d52:	05 a0 99 10 00       	add    $0x1099a0,%eax
  101d57:	8b 08                	mov    (%eax),%ecx
  101d59:	89 0a                	mov    %ecx,(%edx)
  101d5b:	8b 48 04             	mov    0x4(%eax),%ecx
  101d5e:	89 4a 04             	mov    %ecx,0x4(%edx)
  101d61:	8b 48 08             	mov    0x8(%eax),%ecx
  101d64:	89 4a 08             	mov    %ecx,0x8(%edx)
  101d67:	8b 48 0c             	mov    0xc(%eax),%ecx
  101d6a:	89 4a 0c             	mov    %ecx,0xc(%edx)
  101d6d:	8b 40 10             	mov    0x10(%eax),%eax
  101d70:	89 42 10             	mov    %eax,0x10(%edx)
    event_queue.size--;
  101d73:	a1 a4 ad 10 00       	mov    0x10ada4,%eax
  101d78:	83 e8 01             	sub    $0x1,%eax
  101d7b:	a3 a4 ad 10 00       	mov    %eax,0x10ada4
    event_queue.from = (event_queue.from + 1) % EVENTQUEUE_SIZE;
  101d80:	a1 a0 ad 10 00       	mov    0x10ada0,%eax
  101d85:	8d 50 01             	lea    0x1(%eax),%edx
  101d88:	89 d0                	mov    %edx,%eax
  101d8a:	c1 f8 1f             	sar    $0x1f,%eax
  101d8d:	c1 e8 18             	shr    $0x18,%eax
  101d90:	01 c2                	add    %eax,%edx
  101d92:	0f b6 d2             	movzbl %dl,%edx
  101d95:	29 c2                	sub    %eax,%edx
  101d97:	89 d0                	mov    %edx,%eax
  101d99:	a3 a0 ad 10 00       	mov    %eax,0x10ada0

    return 1;
  101d9e:	b8 01 00 00 00       	mov    $0x1,%eax
}
  101da3:	5d                   	pop    %ebp
  101da4:	c3                   	ret    

00101da5 <kbd_handle_byte>:
    This is used to handle the special scancodes for print screen & pause
*/
static unsigned int skip_next = 0;

void kbd_handle_byte(unsigned char byte)
{
  101da5:	55                   	push   %ebp
  101da6:	89 e5                	mov    %esp,%ebp
  101da8:	83 ec 28             	sub    $0x28,%esp
  101dab:	8b 45 08             	mov    0x8(%ebp),%eax
  101dae:	88 45 e4             	mov    %al,-0x1c(%ebp)
        of the previous one. Some scancodes are composed of 2 bytes, with the first
        being '0xe0'
    */
    static bool escape_code = false;

    if (skip_next > 0) {
  101db1:	a1 a8 ad 10 00       	mov    0x10ada8,%eax
  101db6:	85 c0                	test   %eax,%eax
  101db8:	74 12                	je     101dcc <kbd_handle_byte+0x27>
        skip_next--;
  101dba:	a1 a8 ad 10 00       	mov    0x10ada8,%eax
  101dbf:	83 e8 01             	sub    $0x1,%eax
  101dc2:	a3 a8 ad 10 00       	mov    %eax,0x10ada8
        return;
  101dc7:	e9 d5 00 00 00       	jmp    101ea1 <kbd_handle_byte+0xfc>
    }

    if (!escape_code) {
  101dcc:	0f b6 05 ac ad 10 00 	movzbl 0x10adac,%eax
  101dd3:	83 f0 01             	xor    $0x1,%eax
  101dd6:	84 c0                	test   %al,%al
  101dd8:	74 3c                	je     101e16 <kbd_handle_byte+0x71>
        if (byte == SCANCODE_ESCAPECODE) {
  101dda:	80 7d e4 e0          	cmpb   $0xe0,-0x1c(%ebp)
  101dde:	75 0c                	jne    101dec <kbd_handle_byte+0x47>
            escape_code = true;
  101de0:	c6 05 ac ad 10 00 01 	movb   $0x1,0x10adac
            return;
  101de7:	e9 b5 00 00 00       	jmp    101ea1 <kbd_handle_byte+0xfc>
        } else if (byte == (SCANCODE_PAUSE & 0xff)) {
  101dec:	80 7d e4 e1          	cmpb   $0xe1,-0x1c(%ebp)
  101df0:	75 24                	jne    101e16 <kbd_handle_byte+0x71>
                This is the first byte of the 'pause' key. It is made of 6 
                consecutive bytes. Here we signal to ignore the next 5 bytes 
                that will come. We also already handle the scancode in full.
                The value in kbd_handle_scancode is the 6 bytes
            */
            kbd_handle_scancode(SCANCODE_PAUSE);
  101df2:	83 ec 08             	sub    $0x8,%esp
  101df5:	68 9d c5 00 00       	push   $0xc59d
  101dfa:	68 e1 1d 45 e1       	push   $0xe1451de1
  101dff:	e8 9f 00 00 00       	call   101ea3 <kbd_handle_scancode>
  101e04:	83 c4 10             	add    $0x10,%esp
            skip_next = 5;
  101e07:	c7 05 a8 ad 10 00 05 	movl   $0x5,0x10ada8
  101e0e:	00 00 00 
            return;
  101e11:	e9 8b 00 00 00       	jmp    101ea1 <kbd_handle_byte+0xfc>
        }
    }

    if (escape_code) {
  101e16:	0f b6 05 ac ad 10 00 	movzbl 0x10adac,%eax
  101e1d:	84 c0                	test   %al,%al
  101e1f:	74 6a                	je     101e8b <kbd_handle_byte+0xe6>
        uint8_t print_pressed_2ndbyte = (SCANCODE_PRINT_PRESSED & 0xff00) >> 8;
  101e21:	c6 45 f7 2a          	movb   $0x2a,-0x9(%ebp)
        uint8_t print_released_2ndbyte = (SCANCODE_PRINT_RELEASED & 0xff00) >> 8;
  101e25:	c6 45 f6 b7          	movb   $0xb7,-0xa(%ebp)
        if (byte == print_pressed_2ndbyte || byte == print_released_2ndbyte) {
  101e29:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101e2d:	3a 45 f7             	cmp    -0x9(%ebp),%al
  101e30:	74 09                	je     101e3b <kbd_handle_byte+0x96>
  101e32:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101e36:	3a 45 f6             	cmp    -0xa(%ebp),%al
  101e39:	75 3f                	jne    101e7a <kbd_handle_byte+0xd5>
                Here we signal to ignore the next 3 bytes that will come. 
                These are the bytes sent (in order) for these keys:
                'print pressed': e0 2a e0 37 
                'print released': e0 b7 e0 aa
            */
            kbd_handle_scancode(
  101e3b:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101e3f:	3a 45 f7             	cmp    -0x9(%ebp),%al
  101e42:	75 0c                	jne    101e50 <kbd_handle_byte+0xab>
  101e44:	b8 e0 2a e0 37       	mov    $0x37e02ae0,%eax
  101e49:	ba 00 00 00 00       	mov    $0x0,%edx
  101e4e:	eb 0a                	jmp    101e5a <kbd_handle_byte+0xb5>
  101e50:	b8 e0 b7 e0 aa       	mov    $0xaae0b7e0,%eax
  101e55:	ba 00 00 00 00       	mov    $0x0,%edx
  101e5a:	83 ec 08             	sub    $0x8,%esp
  101e5d:	52                   	push   %edx
  101e5e:	50                   	push   %eax
  101e5f:	e8 3f 00 00 00       	call   101ea3 <kbd_handle_scancode>
  101e64:	83 c4 10             	add    $0x10,%esp
                byte == print_pressed_2ndbyte ? 
                    SCANCODE_PRINT_PRESSED : 
                    SCANCODE_PRINT_RELEASED
            );
            skip_next = 3;
  101e67:	c7 05 a8 ad 10 00 03 	movl   $0x3,0x10ada8
  101e6e:	00 00 00 
            escape_code = false;
  101e71:	c6 05 ac ad 10 00 00 	movb   $0x0,0x10adac
            return;
  101e78:	eb 27                	jmp    101ea1 <kbd_handle_byte+0xfc>
        }
        kbd_handle_scancode((SCANCODE_ESCAPECODE << 8) || byte);
  101e7a:	83 ec 08             	sub    $0x8,%esp
  101e7d:	6a 00                	push   $0x0
  101e7f:	6a 01                	push   $0x1
  101e81:	e8 1d 00 00 00       	call   101ea3 <kbd_handle_scancode>
  101e86:	83 c4 10             	add    $0x10,%esp
        return;
  101e89:	eb 16                	jmp    101ea1 <kbd_handle_byte+0xfc>
    }

    kbd_handle_scancode(byte);
  101e8b:	0f b6 45 e4          	movzbl -0x1c(%ebp),%eax
  101e8f:	ba 00 00 00 00       	mov    $0x0,%edx
  101e94:	83 ec 08             	sub    $0x8,%esp
  101e97:	52                   	push   %edx
  101e98:	50                   	push   %eax
  101e99:	e8 05 00 00 00       	call   101ea3 <kbd_handle_scancode>
  101e9e:	83 c4 10             	add    $0x10,%esp
}
  101ea1:	c9                   	leave  
  101ea2:	c3                   	ret    

00101ea3 <kbd_handle_scancode>:

void kbd_handle_scancode(Scancode scancode)
{
  101ea3:	55                   	push   %ebp
  101ea4:	89 e5                	mov    %esp,%ebp
  101ea6:	57                   	push   %edi
  101ea7:	56                   	push   %esi
  101ea8:	83 ec 30             	sub    $0x30,%esp
  101eab:	8b 45 08             	mov    0x8(%ebp),%eax
  101eae:	89 45 d0             	mov    %eax,-0x30(%ebp)
  101eb1:	8b 45 0c             	mov    0xc(%ebp),%eax
  101eb4:	89 45 d4             	mov    %eax,-0x2c(%ebp)
    KeyCode keycode = kbd_scancode_to_keycode(scancode);
  101eb7:	83 ec 08             	sub    $0x8,%esp
  101eba:	ff 75 d4             	pushl  -0x2c(%ebp)
  101ebd:	ff 75 d0             	pushl  -0x30(%ebp)
  101ec0:	e8 f1 00 00 00       	call   101fb6 <kbd_scancode_to_keycode>
  101ec5:	83 c4 10             	add    $0x10,%esp
  101ec8:	88 45 f7             	mov    %al,-0x9(%ebp)
    keymap_status[keycode] = SCANCODE_KEY_PRESSED(scancode);
  101ecb:	8b 45 d0             	mov    -0x30(%ebp),%eax
  101ece:	25 80 00 00 00       	and    $0x80,%eax
  101ed3:	89 c6                	mov    %eax,%esi
  101ed5:	8b 45 d4             	mov    -0x2c(%ebp),%eax
  101ed8:	83 e0 00             	and    $0x0,%eax
  101edb:	89 c7                	mov    %eax,%edi
  101edd:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101ee1:	89 f2                	mov    %esi,%edx
  101ee3:	09 fa                	or     %edi,%edx
  101ee5:	85 d2                	test   %edx,%edx
  101ee7:	0f 94 c2             	sete   %dl
  101eea:	88 90 80 98 10 00    	mov    %dl,0x109880(%eax)

    struct KeyAction action;
    action.character = kbd_keycode_to_char(keycode);
  101ef0:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101ef4:	83 ec 0c             	sub    $0xc,%esp
  101ef7:	50                   	push   %eax
  101ef8:	e8 6c 01 00 00       	call   102069 <kbd_keycode_to_char>
  101efd:	83 c4 10             	add    $0x10,%esp
  101f00:	88 45 e0             	mov    %al,-0x20(%ebp)
    action.keycode = keycode;
  101f03:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101f07:	88 45 e1             	mov    %al,-0x1f(%ebp)
    action.scancode = scancode;
  101f0a:	8b 45 d0             	mov    -0x30(%ebp),%eax
  101f0d:	8b 55 d4             	mov    -0x2c(%ebp),%edx
  101f10:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  101f13:	89 55 e8             	mov    %edx,-0x18(%ebp)
    action.pressed = keymap_status[keycode];
  101f16:	0f b6 45 f7          	movzbl -0x9(%ebp),%eax
  101f1a:	0f b6 80 80 98 10 00 	movzbl 0x109880(%eax),%eax
  101f21:	88 45 ec             	mov    %al,-0x14(%ebp)
    // TODO:
    action.modifiers.capslock   = caps_lock_status;
  101f24:	0f b6 05 80 99 10 00 	movzbl 0x109980,%eax
  101f2b:	83 e0 01             	and    $0x1,%eax
  101f2e:	8d 14 85 00 00 00 00 	lea    0x0(,%eax,4),%edx
  101f35:	0f b6 45 f0          	movzbl -0x10(%ebp),%eax
  101f39:	83 e0 fb             	and    $0xfffffffb,%eax
  101f3c:	09 d0                	or     %edx,%eax
  101f3e:	88 45 f0             	mov    %al,-0x10(%ebp)
    action.modifiers.shift      = keymap_status[KEYCODE_SHIFT];
  101f41:	0f b6 05 aa 98 10 00 	movzbl 0x1098aa,%eax
  101f48:	83 e0 01             	and    $0x1,%eax
  101f4b:	89 c2                	mov    %eax,%edx
  101f4d:	0f b6 45 f0          	movzbl -0x10(%ebp),%eax
  101f51:	83 e0 fe             	and    $0xfffffffe,%eax
  101f54:	09 d0                	or     %edx,%eax
  101f56:	88 45 f0             	mov    %al,-0x10(%ebp)
    action.modifiers.alt        = keymap_status[KEYCODE_ALT];
    action.modifiers.altgr      = keymap_status[KEYCODE_ALTGR];
    action.modifiers.ctrl       = keymap_status[KEYCODE_CTRL];
    action.modifiers.ctrlr      = keymap_status[KEYCODE_CTRLR];
    */
    if (keycode == KEYCODE_CAPSLOCK && action.pressed) {
  101f59:	80 7d f7 3a          	cmpb   $0x3a,-0x9(%ebp)
  101f5d:	75 25                	jne    101f84 <kbd_handle_scancode+0xe1>
  101f5f:	0f b6 45 ec          	movzbl -0x14(%ebp),%eax
  101f63:	84 c0                	test   %al,%al
  101f65:	74 1d                	je     101f84 <kbd_handle_scancode+0xe1>
        caps_lock_status = !caps_lock_status;
  101f67:	0f b6 05 80 99 10 00 	movzbl 0x109980,%eax
  101f6e:	0f b6 c0             	movzbl %al,%eax
  101f71:	85 c0                	test   %eax,%eax
  101f73:	0f 95 c0             	setne  %al
  101f76:	83 f0 01             	xor    $0x1,%eax
  101f79:	0f b6 c0             	movzbl %al,%eax
  101f7c:	83 e0 01             	and    $0x1,%eax
  101f7f:	a2 80 99 10 00       	mov    %al,0x109980
    }

    eventqueue_add(action);
  101f84:	83 ec 0c             	sub    $0xc,%esp
  101f87:	ff 75 f0             	pushl  -0x10(%ebp)
  101f8a:	ff 75 ec             	pushl  -0x14(%ebp)
  101f8d:	ff 75 e8             	pushl  -0x18(%ebp)
  101f90:	ff 75 e4             	pushl  -0x1c(%ebp)
  101f93:	ff 75 e0             	pushl  -0x20(%ebp)
  101f96:	e8 14 fd ff ff       	call   101caf <eventqueue_add>
  101f9b:	83 c4 20             	add    $0x20,%esp
}
  101f9e:	90                   	nop
  101f9f:	8d 65 f8             	lea    -0x8(%ebp),%esp
  101fa2:	5e                   	pop    %esi
  101fa3:	5f                   	pop    %edi
  101fa4:	5d                   	pop    %ebp
  101fa5:	c3                   	ret    

00101fa6 <kbd_get_keyaction>:
    - 0 if there is no KeyAction to read
    - 1 if a KeyAction was read and put in the argument
    Once a KeyAction is read it is removed from the queue 
*/
int kbd_get_keyaction(struct KeyAction *action)
{
  101fa6:	55                   	push   %ebp
  101fa7:	89 e5                	mov    %esp,%ebp
    return eventqueue_read(action);
  101fa9:	ff 75 08             	pushl  0x8(%ebp)
  101fac:	e8 7b fd ff ff       	call   101d2c <eventqueue_read>
  101fb1:	83 c4 04             	add    $0x4,%esp
}
  101fb4:	c9                   	leave  
  101fb5:	c3                   	ret    

00101fb6 <kbd_scancode_to_keycode>:

/*
    Convers a scancode to a keycode, a 1byte generic identifier.
*/
KeyCode kbd_scancode_to_keycode(Scancode scancode)
{
  101fb6:	55                   	push   %ebp
  101fb7:	89 e5                	mov    %esp,%ebp
  101fb9:	57                   	push   %edi
  101fba:	56                   	push   %esi
  101fbb:	53                   	push   %ebx
  101fbc:	83 ec 1c             	sub    $0x1c,%esp
  101fbf:	8b 45 08             	mov    0x8(%ebp),%eax
  101fc2:	89 45 e8             	mov    %eax,-0x18(%ebp)
  101fc5:	8b 45 0c             	mov    0xc(%ebp),%eax
  101fc8:	89 45 ec             	mov    %eax,-0x14(%ebp)
          KEYCODE_PRINT and KEYCODE_PAUSE
    */
    // The 7th bit is used to represents if a key was pressed.
    // The same key pressed & released are still the same key though
    // We set this bit to 0 so that we can treat the 2 scancodes the same
    scancode = scancode & ~(1 << 7);
  101fcb:	81 65 e8 7f ff ff ff 	andl   $0xffffff7f,-0x18(%ebp)
  101fd2:	83 65 ec ff          	andl   $0xffffffff,-0x14(%ebp)
    
    if (scancode == SCANCODE_PRINT_PRESSED) {
  101fd6:	8b 45 e8             	mov    -0x18(%ebp),%eax
  101fd9:	35 e0 2a e0 37       	xor    $0x37e02ae0,%eax
  101fde:	89 c1                	mov    %eax,%ecx
  101fe0:	8b 45 ec             	mov    -0x14(%ebp),%eax
  101fe3:	80 f4 00             	xor    $0x0,%ah
  101fe6:	89 c3                	mov    %eax,%ebx
  101fe8:	89 d8                	mov    %ebx,%eax
  101fea:	09 c8                	or     %ecx,%eax
  101fec:	85 c0                	test   %eax,%eax
  101fee:	75 07                	jne    101ff7 <kbd_scancode_to_keycode+0x41>
        return KEYCODE_PRINT;
  101ff0:	b8 fe ff ff ff       	mov    $0xfffffffe,%eax
  101ff5:	eb 6a                	jmp    102061 <kbd_scancode_to_keycode+0xab>
    } else if (scancode == SCANCODE_PAUSE) {
  101ff7:	8b 45 e8             	mov    -0x18(%ebp),%eax
  101ffa:	35 e1 1d 45 e1       	xor    $0xe1451de1,%eax
  101fff:	89 45 e0             	mov    %eax,-0x20(%ebp)
  102002:	8b 45 ec             	mov    -0x14(%ebp),%eax
  102005:	35 9d c5 00 00       	xor    $0xc59d,%eax
  10200a:	89 45 e4             	mov    %eax,-0x1c(%ebp)
  10200d:	8b 55 e0             	mov    -0x20(%ebp),%edx
  102010:	8b 4d e4             	mov    -0x1c(%ebp),%ecx
  102013:	89 c8                	mov    %ecx,%eax
  102015:	09 d0                	or     %edx,%eax
  102017:	85 c0                	test   %eax,%eax
  102019:	75 07                	jne    102022 <kbd_scancode_to_keycode+0x6c>
        return KEYCODE_PAUSE;
  10201b:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
  102020:	eb 3f                	jmp    102061 <kbd_scancode_to_keycode+0xab>
    
    /*
        We re-map all the 2 bytes scancodes to where all the 'key released' 
        scancodes started, at 0x81 (10000000 in binary)
    */
    if ( ((scancode & 0xff00) >> 8) == SCANCODE_ESCAPECODE ) {
  102022:	8b 45 e8             	mov    -0x18(%ebp),%eax
  102025:	8b 55 ec             	mov    -0x14(%ebp),%edx
  102028:	0f ac d0 08          	shrd   $0x8,%edx,%eax
  10202c:	c1 ea 08             	shr    $0x8,%edx
  10202f:	0f b6 f0             	movzbl %al,%esi
  102032:	89 d0                	mov    %edx,%eax
  102034:	83 e0 00             	and    $0x0,%eax
  102037:	89 c7                	mov    %eax,%edi
  102039:	89 f0                	mov    %esi,%eax
  10203b:	34 e0                	xor    $0xe0,%al
  10203d:	89 45 d8             	mov    %eax,-0x28(%ebp)
  102040:	89 f8                	mov    %edi,%eax
  102042:	80 f4 00             	xor    $0x0,%ah
  102045:	89 45 dc             	mov    %eax,-0x24(%ebp)
  102048:	8b 5d d8             	mov    -0x28(%ebp),%ebx
  10204b:	8b 75 dc             	mov    -0x24(%ebp),%esi
  10204e:	89 f0                	mov    %esi,%eax
  102050:	09 d8                	or     %ebx,%eax
  102052:	85 c0                	test   %eax,%eax
  102054:	75 08                	jne    10205e <kbd_scancode_to_keycode+0xa8>
        return (scancode & 0xff) | (1 << 7);
  102056:	8b 45 e8             	mov    -0x18(%ebp),%eax
  102059:	83 c8 80             	or     $0xffffff80,%eax
  10205c:	eb 03                	jmp    102061 <kbd_scancode_to_keycode+0xab>
    }

    return scancode;
  10205e:	8b 45 e8             	mov    -0x18(%ebp),%eax
}
  102061:	83 c4 1c             	add    $0x1c,%esp
  102064:	5b                   	pop    %ebx
  102065:	5e                   	pop    %esi
  102066:	5f                   	pop    %edi
  102067:	5d                   	pop    %ebp
  102068:	c3                   	ret    

00102069 <kbd_keycode_to_char>:
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    '7', '8', '9', '-', '4', '5', '6', '+', '1', '2', '3', '0', '.'
};

char kbd_keycode_to_char(KeyCode keycode)
{
  102069:	55                   	push   %ebp
  10206a:	89 e5                	mov    %esp,%ebp
  10206c:	83 ec 14             	sub    $0x14,%esp
  10206f:	8b 45 08             	mov    0x8(%ebp),%eax
  102072:	88 45 ec             	mov    %al,-0x14(%ebp)
    /*
        TODO: Use a different keymap for caps lock. Expected behaviour is that
        pressing the numbers with caps on should still write numbers
    */
    char *charmap = charmap_normal;
  102075:	c7 45 fc 00 40 10 00 	movl   $0x104000,-0x4(%ebp)
    if (keymap_status[KEYCODE_SHIFT] ^ caps_lock_status) {
  10207c:	0f b6 15 aa 98 10 00 	movzbl 0x1098aa,%edx
  102083:	0f b6 05 80 99 10 00 	movzbl 0x109980,%eax
  10208a:	38 c2                	cmp    %al,%dl
  10208c:	74 07                	je     102095 <kbd_keycode_to_char+0x2c>
        charmap = charmap_shift;
  10208e:	c7 45 fc 60 40 10 00 	movl   $0x104060,-0x4(%ebp)
    }
    if (keycode < CHARMAP_SIZE)
  102095:	80 7d ec 54          	cmpb   $0x54,-0x14(%ebp)
  102099:	77 0e                	ja     1020a9 <kbd_keycode_to_char+0x40>
        return charmap[keycode];
  10209b:	0f b6 55 ec          	movzbl -0x14(%ebp),%edx
  10209f:	8b 45 fc             	mov    -0x4(%ebp),%eax
  1020a2:	01 d0                	add    %edx,%eax
  1020a4:	0f b6 00             	movzbl (%eax),%eax
  1020a7:	eb 05                	jmp    1020ae <kbd_keycode_to_char+0x45>
    else
        return 0;
  1020a9:	b8 00 00 00 00       	mov    $0x0,%eax
  1020ae:	c9                   	leave  
  1020af:	c3                   	ret    

001020b0 <_panic>:
{
  1020b0:	55                   	push   %ebp
  1020b1:	89 e5                	mov    %esp,%ebp
  1020b3:	83 ec 08             	sub    $0x8,%esp
    kprintf("panic: %s at line %d. %s\n", file, line, error);
  1020b6:	ff 75 10             	pushl  0x10(%ebp)
  1020b9:	ff 75 0c             	pushl  0xc(%ebp)
  1020bc:	ff 75 08             	pushl  0x8(%ebp)
  1020bf:	68 30 35 10 00       	push   $0x103530
  1020c4:	e8 1a f4 ff ff       	call   1014e3 <kprintf>
  1020c9:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  1020cc:	fa                   	cli    
  1020cd:	fc                   	cld    
    while (true) {}
  1020ce:	eb fe                	jmp    1020ce <_panic+0x1e>

001020d0 <_kassert>:
{
  1020d0:	55                   	push   %ebp
  1020d1:	89 e5                	mov    %esp,%ebp
  1020d3:	83 ec 18             	sub    $0x18,%esp
  1020d6:	8b 45 10             	mov    0x10(%ebp),%eax
  1020d9:	88 45 f4             	mov    %al,-0xc(%ebp)
    kprintf("kernel assert: %s at line %d. %s == false\n", file, line, strcond);
  1020dc:	ff 75 14             	pushl  0x14(%ebp)
  1020df:	ff 75 0c             	pushl  0xc(%ebp)
  1020e2:	ff 75 08             	pushl  0x8(%ebp)
  1020e5:	68 4c 35 10 00       	push   $0x10354c
  1020ea:	e8 f4 f3 ff ff       	call   1014e3 <kprintf>
  1020ef:	83 c4 10             	add    $0x10,%esp
    asm("cli; cld");
  1020f2:	fa                   	cli    
  1020f3:	fc                   	cld    
    while (true) {}
  1020f4:	eb fe                	jmp    1020f4 <_kassert+0x24>

001020f6 <page_roundup>:

/*
    Rounds up to the nearest multiple of PGSIZE
*/
int page_roundup(int address)
{
  1020f6:	55                   	push   %ebp
  1020f7:	89 e5                	mov    %esp,%ebp
    if (address % PGSIZE > 0)
  1020f9:	8b 45 08             	mov    0x8(%ebp),%eax
  1020fc:	99                   	cltd   
  1020fd:	c1 ea 14             	shr    $0x14,%edx
  102100:	01 d0                	add    %edx,%eax
  102102:	25 ff 0f 00 00       	and    $0xfff,%eax
  102107:	29 d0                	sub    %edx,%eax
  102109:	85 c0                	test   %eax,%eax
  10210b:	7e 1e                	jle    10212b <page_roundup+0x35>
        return address + (PGSIZE - (address % PGSIZE));
  10210d:	8b 45 08             	mov    0x8(%ebp),%eax
  102110:	99                   	cltd   
  102111:	c1 ea 14             	shr    $0x14,%edx
  102114:	01 d0                	add    %edx,%eax
  102116:	25 ff 0f 00 00       	and    $0xfff,%eax
  10211b:	29 d0                	sub    %edx,%eax
  10211d:	ba 00 10 00 00       	mov    $0x1000,%edx
  102122:	29 c2                	sub    %eax,%edx
  102124:	8b 45 08             	mov    0x8(%ebp),%eax
  102127:	01 d0                	add    %edx,%eax
  102129:	eb 03                	jmp    10212e <page_roundup+0x38>
    else
        return address;
  10212b:	8b 45 08             	mov    0x8(%ebp),%eax
}
  10212e:	5d                   	pop    %ebp
  10212f:	c3                   	ret    

00102130 <page_rounddown>:

/*
    Rounds down to the nearest multiple of PGSIZE
*/
int page_rounddown(int address)
{
  102130:	55                   	push   %ebp
  102131:	89 e5                	mov    %esp,%ebp
    return address & ~(PGSIZE-1);
  102133:	8b 45 08             	mov    0x8(%ebp),%eax
  102136:	25 00 f0 ff ff       	and    $0xfffff000,%eax
}
  10213b:	5d                   	pop    %ebp
  10213c:	c3                   	ret    

0010213d <page_index>:
/*
    Returns the index of the page in the 'pages' array given the address 
    it represents
*/
int page_index(int address)
{
  10213d:	55                   	push   %ebp
  10213e:	89 e5                	mov    %esp,%ebp
    return address >> PGSIZE_BIT;
  102140:	8b 45 08             	mov    0x8(%ebp),%eax
  102143:	c1 f8 0c             	sar    $0xc,%eax
}
  102146:	5d                   	pop    %ebp
  102147:	c3                   	ret    

00102148 <boot_alloc>:
    not be deleted in the future! This only returns memory in pages. The size 
    of a page is defined in PGSIZE. All memory is guaranteed to be aligned to 
    PGSIZE.
*/
static void *boot_alloc(size_t pages)
{
  102148:	55                   	push   %ebp
  102149:	89 e5                	mov    %esp,%ebp
  10214b:	53                   	push   %ebx
  10214c:	83 ec 14             	sub    $0x14,%esp
    static char *nextfree;

    if (!nextfree) {
  10214f:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  102154:	85 c0                	test   %eax,%eax
  102156:	75 42                	jne    10219a <boot_alloc+0x52>
        /*
            'end' is an external symbol defined in the linker script that 
            points to the end of the kernel in memory
        */
        extern char *end;
        kprintf("npages: %d\n", npages);
  102158:	a1 b4 ad 10 00       	mov    0x10adb4,%eax
  10215d:	83 ec 08             	sub    $0x8,%esp
  102160:	50                   	push   %eax
  102161:	68 77 35 10 00       	push   $0x103577
  102166:	e8 78 f3 ff ff       	call   1014e3 <kprintf>
  10216b:	83 c4 10             	add    $0x10,%esp
        kprintf("end: %x\n", end);
  10216e:	a1 00 b0 10 00       	mov    0x10b000,%eax
  102173:	83 ec 08             	sub    $0x8,%esp
  102176:	50                   	push   %eax
  102177:	68 83 35 10 00       	push   $0x103583
  10217c:	e8 62 f3 ff ff       	call   1014e3 <kprintf>
  102181:	83 c4 10             	add    $0x10,%esp
        nextfree = (char*) page_roundup((int) end);
  102184:	a1 00 b0 10 00       	mov    0x10b000,%eax
  102189:	83 ec 0c             	sub    $0xc,%esp
  10218c:	50                   	push   %eax
  10218d:	e8 64 ff ff ff       	call   1020f6 <page_roundup>
  102192:	83 c4 10             	add    $0x10,%esp
  102195:	a3 c0 ad 10 00       	mov    %eax,0x10adc0
    }
    kprintf("current: %d\n", page_index(nextfree));
  10219a:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  10219f:	83 ec 0c             	sub    $0xc,%esp
  1021a2:	50                   	push   %eax
  1021a3:	e8 95 ff ff ff       	call   10213d <page_index>
  1021a8:	83 c4 10             	add    $0x10,%esp
  1021ab:	83 ec 08             	sub    $0x8,%esp
  1021ae:	50                   	push   %eax
  1021af:	68 8c 35 10 00       	push   $0x10358c
  1021b4:	e8 2a f3 ff ff       	call   1014e3 <kprintf>
  1021b9:	83 c4 10             	add    $0x10,%esp
    kprintf("calculated end: %d\n", page_index((nextfree + PGSIZE * pages)));
  1021bc:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  1021c1:	8b 55 08             	mov    0x8(%ebp),%edx
  1021c4:	c1 e2 0c             	shl    $0xc,%edx
  1021c7:	01 d0                	add    %edx,%eax
  1021c9:	83 ec 0c             	sub    $0xc,%esp
  1021cc:	50                   	push   %eax
  1021cd:	e8 6b ff ff ff       	call   10213d <page_index>
  1021d2:	83 c4 10             	add    $0x10,%esp
  1021d5:	83 ec 08             	sub    $0x8,%esp
  1021d8:	50                   	push   %eax
  1021d9:	68 99 35 10 00       	push   $0x103599
  1021de:	e8 00 f3 ff ff       	call   1014e3 <kprintf>
  1021e3:	83 c4 10             	add    $0x10,%esp
    if ((uint32_t) (nextfree + PGSIZE * pages) >= get_total_memory()) {
  1021e6:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  1021eb:	8b 55 08             	mov    0x8(%ebp),%edx
  1021ee:	c1 e2 0c             	shl    $0xc,%edx
  1021f1:	01 d0                	add    %edx,%eax
  1021f3:	89 c3                	mov    %eax,%ebx
  1021f5:	e8 84 01 00 00       	call   10237e <get_total_memory>
  1021fa:	39 c3                	cmp    %eax,%ebx
  1021fc:	72 2c                	jb     10222a <boot_alloc+0xe2>
        kprintf("base mem: %d, nextfree+pgsize*pages=%d", get_total_memory(), nextfree + PGSIZE * pages);
  1021fe:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  102203:	8b 55 08             	mov    0x8(%ebp),%edx
  102206:	c1 e2 0c             	shl    $0xc,%edx
  102209:	8d 1c 10             	lea    (%eax,%edx,1),%ebx
  10220c:	e8 6d 01 00 00       	call   10237e <get_total_memory>
  102211:	83 ec 04             	sub    $0x4,%esp
  102214:	53                   	push   %ebx
  102215:	50                   	push   %eax
  102216:	68 b0 35 10 00       	push   $0x1035b0
  10221b:	e8 c3 f2 ff ff       	call   1014e3 <kprintf>
  102220:	83 c4 10             	add    $0x10,%esp
        return NULL;
  102223:	b8 00 00 00 00       	mov    $0x0,%eax
  102228:	eb 1d                	jmp    102247 <boot_alloc+0xff>
    }

    void *result = nextfree;
  10222a:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  10222f:	89 45 f4             	mov    %eax,-0xc(%ebp)
    nextfree += PGSIZE * pages;
  102232:	a1 c0 ad 10 00       	mov    0x10adc0,%eax
  102237:	8b 55 08             	mov    0x8(%ebp),%edx
  10223a:	c1 e2 0c             	shl    $0xc,%edx
  10223d:	01 d0                	add    %edx,%eax
  10223f:	a3 c0 ad 10 00       	mov    %eax,0x10adc0

    return result;
  102244:	8b 45 f4             	mov    -0xc(%ebp),%eax
}
  102247:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  10224a:	c9                   	leave  
  10224b:	c3                   	ret    

0010224c <mb_read_memory>:


void mb_read_memory(multiboot_info_t *mbh) 
{
  10224c:	55                   	push   %ebp
  10224d:	89 e5                	mov    %esp,%ebp
    if (mbh->flags & 1) {
  10224f:	8b 45 08             	mov    0x8(%ebp),%eax
  102252:	8b 00                	mov    (%eax),%eax
  102254:	83 e0 01             	and    $0x1,%eax
  102257:	85 c0                	test   %eax,%eax
  102259:	74 16                	je     102271 <mb_read_memory+0x25>
        // The multiboot header stores the memory in KB
        base_memory = (mbh->mem_lower + mbh->mem_upper) * 1024;
  10225b:	8b 45 08             	mov    0x8(%ebp),%eax
  10225e:	8b 50 04             	mov    0x4(%eax),%edx
  102261:	8b 45 08             	mov    0x8(%ebp),%eax
  102264:	8b 40 08             	mov    0x8(%eax),%eax
  102267:	01 d0                	add    %edx,%eax
  102269:	c1 e0 0a             	shl    $0xa,%eax
  10226c:	a3 b0 ad 10 00       	mov    %eax,0x10adb0
    }

    
}
  102271:	90                   	nop
  102272:	5d                   	pop    %ebp
  102273:	c3                   	ret    

00102274 <mb_find_free_pages>:

int mb_find_free_pages(multiboot_info_t *mbh)
{
  102274:	55                   	push   %ebp
  102275:	89 e5                	mov    %esp,%ebp
  102277:	83 ec 28             	sub    $0x28,%esp
    if ( !(mbh->flags & (1 << 6)) ) {
  10227a:	8b 45 08             	mov    0x8(%ebp),%eax
  10227d:	8b 00                	mov    (%eax),%eax
  10227f:	83 e0 40             	and    $0x40,%eax
  102282:	85 c0                	test   %eax,%eax
  102284:	75 0a                	jne    102290 <mb_find_free_pages+0x1c>
        return 0;
  102286:	b8 00 00 00 00       	mov    $0x0,%eax
  10228b:	e9 ec 00 00 00       	jmp    10237c <mb_find_free_pages+0x108>
    }
    multiboot_memory_map_t *mmap = (multiboot_memory_map_t*) mbh->mmap_addr;
  102290:	8b 45 08             	mov    0x8(%ebp),%eax
  102293:	8b 40 30             	mov    0x30(%eax),%eax
  102296:	89 45 f4             	mov    %eax,-0xc(%ebp)
    multiboot_memory_map_t *end = (multiboot_memory_map_t*) (mbh->mmap_addr + mbh->mmap_length);
  102299:	8b 45 08             	mov    0x8(%ebp),%eax
  10229c:	8b 50 30             	mov    0x30(%eax),%edx
  10229f:	8b 45 08             	mov    0x8(%ebp),%eax
  1022a2:	8b 40 2c             	mov    0x2c(%eax),%eax
  1022a5:	01 d0                	add    %edx,%eax
  1022a7:	89 45 ec             	mov    %eax,-0x14(%ebp)
    while (mmap < end) {
  1022aa:	e9 bc 00 00 00       	jmp    10236b <mb_find_free_pages+0xf7>
        kprintf(
            "[%d]: %x for %d bytes\n",
            mmap->type, 
            (int) mmap->addr,
            (int) mmap->len
  1022af:	8b 45 f4             	mov    -0xc(%ebp),%eax
  1022b2:	8b 50 10             	mov    0x10(%eax),%edx
  1022b5:	8b 40 0c             	mov    0xc(%eax),%eax
        kprintf(
  1022b8:	89 c1                	mov    %eax,%ecx
            (int) mmap->addr,
  1022ba:	8b 45 f4             	mov    -0xc(%ebp),%eax
  1022bd:	8b 50 08             	mov    0x8(%eax),%edx
  1022c0:	8b 40 04             	mov    0x4(%eax),%eax
        kprintf(
  1022c3:	89 c2                	mov    %eax,%edx
  1022c5:	8b 45 f4             	mov    -0xc(%ebp),%eax
  1022c8:	8b 40 14             	mov    0x14(%eax),%eax
  1022cb:	51                   	push   %ecx
  1022cc:	52                   	push   %edx
  1022cd:	50                   	push   %eax
  1022ce:	68 d7 35 10 00       	push   $0x1035d7
  1022d3:	e8 0b f2 ff ff       	call   1014e3 <kprintf>
  1022d8:	83 c4 10             	add    $0x10,%esp
        );
        
        size_t from     = page_index(mmap->addr);
  1022db:	8b 45 f4             	mov    -0xc(%ebp),%eax
  1022de:	8b 50 08             	mov    0x8(%eax),%edx
  1022e1:	8b 40 04             	mov    0x4(%eax),%eax
  1022e4:	83 ec 0c             	sub    $0xc,%esp
  1022e7:	50                   	push   %eax
  1022e8:	e8 50 fe ff ff       	call   10213d <page_index>
  1022ed:	83 c4 10             	add    $0x10,%esp
  1022f0:	89 45 e8             	mov    %eax,-0x18(%ebp)
        size_t to       = page_index(page_roundup(mmap->addr + mmap->len));
  1022f3:	8b 45 f4             	mov    -0xc(%ebp),%eax
  1022f6:	8b 50 08             	mov    0x8(%eax),%edx
  1022f9:	8b 40 04             	mov    0x4(%eax),%eax
  1022fc:	89 c1                	mov    %eax,%ecx
  1022fe:	8b 45 f4             	mov    -0xc(%ebp),%eax
  102301:	8b 50 10             	mov    0x10(%eax),%edx
  102304:	8b 40 0c             	mov    0xc(%eax),%eax
  102307:	01 c8                	add    %ecx,%eax
  102309:	83 ec 0c             	sub    $0xc,%esp
  10230c:	50                   	push   %eax
  10230d:	e8 e4 fd ff ff       	call   1020f6 <page_roundup>
  102312:	83 c4 10             	add    $0x10,%esp
  102315:	83 ec 0c             	sub    $0xc,%esp
  102318:	50                   	push   %eax
  102319:	e8 1f fe ff ff       	call   10213d <page_index>
  10231e:	83 c4 10             	add    $0x10,%esp
  102321:	89 45 e4             	mov    %eax,-0x1c(%ebp)
        bool available  = (mmap->type == MULTIBOOT_MEMORY_AVAILABLE);
  102324:	8b 45 f4             	mov    -0xc(%ebp),%eax
  102327:	8b 40 14             	mov    0x14(%eax),%eax
  10232a:	83 f8 01             	cmp    $0x1,%eax
  10232d:	0f 94 c0             	sete   %al
  102330:	88 45 e3             	mov    %al,-0x1d(%ebp)
        for (size_t i = from; i < to; i++) {
  102333:	8b 45 e8             	mov    -0x18(%ebp),%eax
  102336:	89 45 f0             	mov    %eax,-0x10(%ebp)
  102339:	eb 18                	jmp    102353 <mb_find_free_pages+0xdf>
            pages[i].available = available;
  10233b:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  102340:	8b 55 f0             	mov    -0x10(%ebp),%edx
  102343:	c1 e2 03             	shl    $0x3,%edx
  102346:	01 c2                	add    %eax,%edx
  102348:	0f b6 45 e3          	movzbl -0x1d(%ebp),%eax
  10234c:	88 42 01             	mov    %al,0x1(%edx)
        for (size_t i = from; i < to; i++) {
  10234f:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
  102353:	8b 45 f0             	mov    -0x10(%ebp),%eax
  102356:	3b 45 e4             	cmp    -0x1c(%ebp),%eax
  102359:	72 e0                	jb     10233b <mb_find_free_pages+0xc7>
        }

        mmap = (multiboot_memory_map_t*) ( (unsigned int)mmap + mmap->size + sizeof(mmap->size) );
  10235b:	8b 45 f4             	mov    -0xc(%ebp),%eax
  10235e:	8b 10                	mov    (%eax),%edx
  102360:	8b 45 f4             	mov    -0xc(%ebp),%eax
  102363:	01 d0                	add    %edx,%eax
  102365:	83 c0 04             	add    $0x4,%eax
  102368:	89 45 f4             	mov    %eax,-0xc(%ebp)
    while (mmap < end) {
  10236b:	8b 45 f4             	mov    -0xc(%ebp),%eax
  10236e:	3b 45 ec             	cmp    -0x14(%ebp),%eax
  102371:	0f 82 38 ff ff ff    	jb     1022af <mb_find_free_pages+0x3b>
    }

    return 1;
  102377:	b8 01 00 00 00       	mov    $0x1,%eax
}
  10237c:	c9                   	leave  
  10237d:	c3                   	ret    

0010237e <get_total_memory>:

uint32_t get_total_memory() {
  10237e:	55                   	push   %ebp
  10237f:	89 e5                	mov    %esp,%ebp
    return base_memory;
  102381:	a1 b0 ad 10 00       	mov    0x10adb0,%eax
}
  102386:	5d                   	pop    %ebp
  102387:	c3                   	ret    

00102388 <pages_init>:

static void pages_init()
{
  102388:	55                   	push   %ebp
  102389:	89 e5                	mov    %esp,%ebp
  10238b:	53                   	push   %ebx
  10238c:	83 ec 14             	sub    $0x14,%esp
    kprintf("Available memory: %d\n", get_total_memory());
  10238f:	e8 ea ff ff ff       	call   10237e <get_total_memory>
  102394:	83 ec 08             	sub    $0x8,%esp
  102397:	50                   	push   %eax
  102398:	68 ee 35 10 00       	push   $0x1035ee
  10239d:	e8 41 f1 ff ff       	call   1014e3 <kprintf>
  1023a2:	83 c4 10             	add    $0x10,%esp
    npages = get_total_memory() / PGSIZE;
  1023a5:	e8 d4 ff ff ff       	call   10237e <get_total_memory>
  1023aa:	c1 e8 0c             	shr    $0xc,%eax
  1023ad:	a3 b4 ad 10 00       	mov    %eax,0x10adb4
    pages = (struct PageInfo *) boot_alloc(npages);
  1023b2:	a1 b4 ad 10 00       	mov    0x10adb4,%eax
  1023b7:	83 ec 0c             	sub    $0xc,%esp
  1023ba:	50                   	push   %eax
  1023bb:	e8 88 fd ff ff       	call   102148 <boot_alloc>
  1023c0:	83 c4 10             	add    $0x10,%esp
  1023c3:	a3 b8 ad 10 00       	mov    %eax,0x10adb8
    kassert(pages != NULL);
  1023c8:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  1023cd:	85 c0                	test   %eax,%eax
  1023cf:	75 17                	jne    1023e8 <pages_init+0x60>
  1023d1:	83 ec 04             	sub    $0x4,%esp
  1023d4:	68 04 36 10 00       	push   $0x103604
  1023d9:	6a 7e                	push   $0x7e
  1023db:	68 12 36 10 00       	push   $0x103612
  1023e0:	e8 cb fc ff ff       	call   1020b0 <_panic>
  1023e5:	83 c4 10             	add    $0x10,%esp
    
    for (size_t i = 0; i < npages-1; i++) {
  1023e8:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%ebp)
  1023ef:	eb 39                	jmp    10242a <pages_init+0xa2>
        pages[i].used = false;
  1023f1:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  1023f6:	8b 55 f4             	mov    -0xc(%ebp),%edx
  1023f9:	c1 e2 03             	shl    $0x3,%edx
  1023fc:	01 d0                	add    %edx,%eax
  1023fe:	c6 00 00             	movb   $0x0,(%eax)
        pages[i].nextfree = &pages[i+1];
  102401:	8b 15 b8 ad 10 00    	mov    0x10adb8,%edx
  102407:	8b 45 f4             	mov    -0xc(%ebp),%eax
  10240a:	83 c0 01             	add    $0x1,%eax
  10240d:	8d 1c c5 00 00 00 00 	lea    0x0(,%eax,8),%ebx
  102414:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  102419:	8b 4d f4             	mov    -0xc(%ebp),%ecx
  10241c:	c1 e1 03             	shl    $0x3,%ecx
  10241f:	01 c8                	add    %ecx,%eax
  102421:	01 da                	add    %ebx,%edx
  102423:	89 50 04             	mov    %edx,0x4(%eax)
    for (size_t i = 0; i < npages-1; i++) {
  102426:	83 45 f4 01          	addl   $0x1,-0xc(%ebp)
  10242a:	a1 b4 ad 10 00       	mov    0x10adb4,%eax
  10242f:	83 e8 01             	sub    $0x1,%eax
  102432:	39 45 f4             	cmp    %eax,-0xc(%ebp)
  102435:	72 ba                	jb     1023f1 <pages_init+0x69>
    }

    pages[npages-1].used = false;
  102437:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  10243c:	8b 15 b4 ad 10 00    	mov    0x10adb4,%edx
  102442:	81 c2 ff ff ff 1f    	add    $0x1fffffff,%edx
  102448:	c1 e2 03             	shl    $0x3,%edx
  10244b:	01 d0                	add    %edx,%eax
  10244d:	c6 00 00             	movb   $0x0,(%eax)
    pages[npages-1].nextfree = NULL;
  102450:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  102455:	8b 15 b4 ad 10 00    	mov    0x10adb4,%edx
  10245b:	81 c2 ff ff ff 1f    	add    $0x1fffffff,%edx
  102461:	c1 e2 03             	shl    $0x3,%edx
  102464:	01 d0                	add    %edx,%eax
  102466:	c7 40 04 00 00 00 00 	movl   $0x0,0x4(%eax)
    pages_free_list = &pages[0];
  10246d:	a1 b8 ad 10 00       	mov    0x10adb8,%eax
  102472:	a3 bc ad 10 00       	mov    %eax,0x10adbc

    /*
        Not all memory is actually available: here we defined which pages
        are free
    */
}
  102477:	90                   	nop
  102478:	8b 5d fc             	mov    -0x4(%ebp),%ebx
  10247b:	c9                   	leave  
  10247c:	c3                   	ret    

0010247d <memory_init>:

void memory_init(multiboot_info_t *mbh, uint32_t magic)
{
  10247d:	55                   	push   %ebp
  10247e:	89 e5                	mov    %esp,%ebp
  102480:	83 ec 08             	sub    $0x8,%esp
    kassert(magic == MULTIBOOT_BOOTLOADER_MAGIC);
  102483:	81 7d 0c 02 b0 ad 2b 	cmpl   $0x2badb002,0xc(%ebp)
  10248a:	74 1a                	je     1024a6 <memory_init+0x29>
  10248c:	83 ec 04             	sub    $0x4,%esp
  10248f:	68 2c 36 10 00       	push   $0x10362c
  102494:	68 91 00 00 00       	push   $0x91
  102499:	68 12 36 10 00       	push   $0x103612
  10249e:	e8 0d fc ff ff       	call   1020b0 <_panic>
  1024a3:	83 c4 10             	add    $0x10,%esp
    mb_read_memory(mbh);
  1024a6:	83 ec 0c             	sub    $0xc,%esp
  1024a9:	ff 75 08             	pushl  0x8(%ebp)
  1024ac:	e8 9b fd ff ff       	call   10224c <mb_read_memory>
  1024b1:	83 c4 10             	add    $0x10,%esp
    pages_init();
  1024b4:	e8 cf fe ff ff       	call   102388 <pages_init>
  1024b9:	90                   	nop
  1024ba:	c9                   	leave  
  1024bb:	c3                   	ret    
