/*
    These interrupts push an error code: 8, 10, 11, 12, 13, 14
    We create 2 macros that declare an interrupt service routine.
    ISR_ERRCODE pushes its argument and calls 'interrupt_handler'
    IST_NOERRCODE pushes its argument, a zero and jumps to 'alltraps' (below)
    This way both stacks are the same for all interrupts
*/

.macro ISR_NOERRCODE name, num
    .global \name
    .type \name, @function
    .align 2
    \name:
        push $0
        push $(\num)
        jmp alltraps
.endm


.macro ISR_ERRCODE name, num
    .global \name
    .type \name, @function
    .align 2
    \name:
        push $(\num)
        jmp alltraps
.endm

/*
    [%ds]
    [registri]
    [INT NUM]
    [$0]
    [roba CPU]
*/

alltraps:
    pusha
    
    mov %ds, %eax
    push %eax

    mov $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs

    push %esp
    call interrupt_handler
    add $4, %esp

    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %gs
    mov %ax, %fs
    
    popa
    add $8, %esp    # to remove the error code + int number
    
    iret

ISR_NOERRCODE isr0, 0
ISR_NOERRCODE isr1, 1
ISR_NOERRCODE isr2, 2
ISR_NOERRCODE isr3, 3
ISR_NOERRCODE isr4, 4
ISR_NOERRCODE isr5, 5
ISR_NOERRCODE isr6, 6
ISR_NOERRCODE isr7, 7
ISR_ERRCODE isr8, 8
ISR_NOERRCODE isr9, 9
ISR_ERRCODE isr10, 10
ISR_ERRCODE isr11, 11
ISR_ERRCODE isr12, 12
ISR_ERRCODE isr13, 13
ISR_ERRCODE isr14, 14
ISR_NOERRCODE isr15, 15
ISR_NOERRCODE isr16, 16
ISR_NOERRCODE isr17, 17
ISR_NOERRCODE isr18, 18
ISR_NOERRCODE isr19, 19
ISR_NOERRCODE isr20, 20
ISR_NOERRCODE isr21, 21
ISR_NOERRCODE isr22, 22
ISR_NOERRCODE isr23, 23
ISR_NOERRCODE isr24, 24
ISR_NOERRCODE isr25, 25
ISR_NOERRCODE isr26, 26
ISR_NOERRCODE isr27, 27
ISR_NOERRCODE isr28, 28
ISR_NOERRCODE isr29, 29
ISR_NOERRCODE isr30, 30
ISR_NOERRCODE isr31, 31
ISR_NOERRCODE isr32, 32
ISR_NOERRCODE isr33, 33
ISR_NOERRCODE isr34, 34
ISR_NOERRCODE isr35, 35
ISR_NOERRCODE isr36, 36
ISR_NOERRCODE isr37, 37
ISR_NOERRCODE isr38, 38
ISR_NOERRCODE isr39, 39
ISR_NOERRCODE isr40, 40
ISR_NOERRCODE isr41, 41
ISR_NOERRCODE isr42, 42
ISR_NOERRCODE isr43, 43
ISR_NOERRCODE isr44, 44
ISR_NOERRCODE isr45, 45
ISR_NOERRCODE isr46, 46
ISR_NOERRCODE isr47, 47
ISR_NOERRCODE isr48, 48
ISR_NOERRCODE isr49, 49
ISR_NOERRCODE isr50, 50
ISR_NOERRCODE isr51, 51
ISR_NOERRCODE isr52, 52
ISR_NOERRCODE isr53, 53
ISR_NOERRCODE isr54, 54
ISR_NOERRCODE isr55, 55
ISR_NOERRCODE isr56, 56
ISR_NOERRCODE isr57, 57
ISR_NOERRCODE isr58, 58
ISR_NOERRCODE isr59, 59
ISR_NOERRCODE isr60, 60
ISR_NOERRCODE isr61, 61
ISR_NOERRCODE isr62, 62
ISR_NOERRCODE isr63, 63
ISR_NOERRCODE isr64, 64
ISR_NOERRCODE isr65, 65
ISR_NOERRCODE isr66, 66
ISR_NOERRCODE isr67, 67
ISR_NOERRCODE isr68, 68
ISR_NOERRCODE isr69, 69
ISR_NOERRCODE isr70, 70
ISR_NOERRCODE isr71, 71
ISR_NOERRCODE isr72, 72
ISR_NOERRCODE isr73, 73
ISR_NOERRCODE isr74, 74
ISR_NOERRCODE isr75, 75
ISR_NOERRCODE isr76, 76
ISR_NOERRCODE isr77, 77
ISR_NOERRCODE isr78, 78
ISR_NOERRCODE isr79, 79
ISR_NOERRCODE isr80, 80
ISR_NOERRCODE isr81, 81
ISR_NOERRCODE isr82, 82
ISR_NOERRCODE isr83, 83
ISR_NOERRCODE isr84, 84
ISR_NOERRCODE isr85, 85
ISR_NOERRCODE isr86, 86
ISR_NOERRCODE isr87, 87
ISR_NOERRCODE isr88, 88
ISR_NOERRCODE isr89, 89
ISR_NOERRCODE isr90, 90
ISR_NOERRCODE isr91, 91
ISR_NOERRCODE isr92, 92
ISR_NOERRCODE isr93, 93
ISR_NOERRCODE isr94, 94
ISR_NOERRCODE isr95, 95
ISR_NOERRCODE isr96, 96
ISR_NOERRCODE isr97, 97
ISR_NOERRCODE isr98, 98
ISR_NOERRCODE isr99, 99
ISR_NOERRCODE isr100, 100
ISR_NOERRCODE isr101, 101
ISR_NOERRCODE isr102, 102
ISR_NOERRCODE isr103, 103
ISR_NOERRCODE isr104, 104
ISR_NOERRCODE isr105, 105
ISR_NOERRCODE isr106, 106
ISR_NOERRCODE isr107, 107
ISR_NOERRCODE isr108, 108
ISR_NOERRCODE isr109, 109
ISR_NOERRCODE isr110, 110
ISR_NOERRCODE isr111, 111
ISR_NOERRCODE isr112, 112
ISR_NOERRCODE isr113, 113
ISR_NOERRCODE isr114, 114
ISR_NOERRCODE isr115, 115
ISR_NOERRCODE isr116, 116
ISR_NOERRCODE isr117, 117
ISR_NOERRCODE isr118, 118
ISR_NOERRCODE isr119, 119
ISR_NOERRCODE isr120, 120
ISR_NOERRCODE isr121, 121
ISR_NOERRCODE isr122, 122
ISR_NOERRCODE isr123, 123
ISR_NOERRCODE isr124, 124
ISR_NOERRCODE isr125, 125
ISR_NOERRCODE isr126, 126
ISR_NOERRCODE isr127, 127
ISR_NOERRCODE isr128, 128
ISR_NOERRCODE isr129, 129
ISR_NOERRCODE isr130, 130
ISR_NOERRCODE isr131, 131
ISR_NOERRCODE isr132, 132
ISR_NOERRCODE isr133, 133
ISR_NOERRCODE isr134, 134
ISR_NOERRCODE isr135, 135
ISR_NOERRCODE isr136, 136
ISR_NOERRCODE isr137, 137
ISR_NOERRCODE isr138, 138
ISR_NOERRCODE isr139, 139
ISR_NOERRCODE isr140, 140
ISR_NOERRCODE isr141, 141
ISR_NOERRCODE isr142, 142
ISR_NOERRCODE isr143, 143
ISR_NOERRCODE isr144, 144
ISR_NOERRCODE isr145, 145
ISR_NOERRCODE isr146, 146
ISR_NOERRCODE isr147, 147
ISR_NOERRCODE isr148, 148
ISR_NOERRCODE isr149, 149
ISR_NOERRCODE isr150, 150
ISR_NOERRCODE isr151, 151
ISR_NOERRCODE isr152, 152
ISR_NOERRCODE isr153, 153
ISR_NOERRCODE isr154, 154
ISR_NOERRCODE isr155, 155
ISR_NOERRCODE isr156, 156
ISR_NOERRCODE isr157, 157
ISR_NOERRCODE isr158, 158
ISR_NOERRCODE isr159, 159
ISR_NOERRCODE isr160, 160
ISR_NOERRCODE isr161, 161
ISR_NOERRCODE isr162, 162
ISR_NOERRCODE isr163, 163
ISR_NOERRCODE isr164, 164
ISR_NOERRCODE isr165, 165
ISR_NOERRCODE isr166, 166
ISR_NOERRCODE isr167, 167
ISR_NOERRCODE isr168, 168
ISR_NOERRCODE isr169, 169
ISR_NOERRCODE isr170, 170
ISR_NOERRCODE isr171, 171
ISR_NOERRCODE isr172, 172
ISR_NOERRCODE isr173, 173
ISR_NOERRCODE isr174, 174
ISR_NOERRCODE isr175, 175
ISR_NOERRCODE isr176, 176
ISR_NOERRCODE isr177, 177
ISR_NOERRCODE isr178, 178
ISR_NOERRCODE isr179, 179
ISR_NOERRCODE isr180, 180
ISR_NOERRCODE isr181, 181
ISR_NOERRCODE isr182, 182
ISR_NOERRCODE isr183, 183
ISR_NOERRCODE isr184, 184
ISR_NOERRCODE isr185, 185
ISR_NOERRCODE isr186, 186
ISR_NOERRCODE isr187, 187
ISR_NOERRCODE isr188, 188
ISR_NOERRCODE isr189, 189
ISR_NOERRCODE isr190, 190
ISR_NOERRCODE isr191, 191
ISR_NOERRCODE isr192, 192
ISR_NOERRCODE isr193, 193
ISR_NOERRCODE isr194, 194
ISR_NOERRCODE isr195, 195
ISR_NOERRCODE isr196, 196
ISR_NOERRCODE isr197, 197
ISR_NOERRCODE isr198, 198
ISR_NOERRCODE isr199, 199
ISR_NOERRCODE isr200, 200
ISR_NOERRCODE isr201, 201
ISR_NOERRCODE isr202, 202
ISR_NOERRCODE isr203, 203
ISR_NOERRCODE isr204, 204
ISR_NOERRCODE isr205, 205
ISR_NOERRCODE isr206, 206
ISR_NOERRCODE isr207, 207
ISR_NOERRCODE isr208, 208
ISR_NOERRCODE isr209, 209
ISR_NOERRCODE isr210, 210
ISR_NOERRCODE isr211, 211
ISR_NOERRCODE isr212, 212
ISR_NOERRCODE isr213, 213
ISR_NOERRCODE isr214, 214
ISR_NOERRCODE isr215, 215
ISR_NOERRCODE isr216, 216
ISR_NOERRCODE isr217, 217
ISR_NOERRCODE isr218, 218
ISR_NOERRCODE isr219, 219
ISR_NOERRCODE isr220, 220
ISR_NOERRCODE isr221, 221
ISR_NOERRCODE isr222, 222
ISR_NOERRCODE isr223, 223
ISR_NOERRCODE isr224, 224
ISR_NOERRCODE isr225, 225
ISR_NOERRCODE isr226, 226
ISR_NOERRCODE isr227, 227
ISR_NOERRCODE isr228, 228
ISR_NOERRCODE isr229, 229
ISR_NOERRCODE isr230, 230
ISR_NOERRCODE isr231, 231
ISR_NOERRCODE isr232, 232
ISR_NOERRCODE isr233, 233
ISR_NOERRCODE isr234, 234
ISR_NOERRCODE isr235, 235
ISR_NOERRCODE isr236, 236
ISR_NOERRCODE isr237, 237
ISR_NOERRCODE isr238, 238
ISR_NOERRCODE isr239, 239
ISR_NOERRCODE isr240, 240
ISR_NOERRCODE isr241, 241
ISR_NOERRCODE isr242, 242
ISR_NOERRCODE isr243, 243
ISR_NOERRCODE isr244, 244
ISR_NOERRCODE isr245, 245
ISR_NOERRCODE isr246, 246
ISR_NOERRCODE isr247, 247
ISR_NOERRCODE isr248, 248
ISR_NOERRCODE isr249, 249
ISR_NOERRCODE isr250, 250
ISR_NOERRCODE isr251, 251
ISR_NOERRCODE isr252, 252
ISR_NOERRCODE isr253, 253
ISR_NOERRCODE isr254, 254
ISR_NOERRCODE isr255, 255

.global handlers
handlers:
    .long isr0
    .long isr1
    .long isr2
    .long isr3
    .long isr4
    .long isr5
    .long isr6
    .long isr7
    .long isr8
    .long isr9
    .long isr10
    .long isr11
    .long isr12
    .long isr13
    .long isr14
    .long isr15
    .long isr16
    .long isr17
    .long isr18
    .long isr19
    .long isr20
    .long isr21
    .long isr22
    .long isr23
    .long isr24
    .long isr25
    .long isr26
    .long isr27
    .long isr28
    .long isr29
    .long isr30
    .long isr31
    .long isr32
    .long isr33
    .long isr34
    .long isr35
    .long isr36
    .long isr37
    .long isr38
    .long isr39
    .long isr40
    .long isr41
    .long isr42
    .long isr43
    .long isr44
    .long isr45
    .long isr46
    .long isr47
    .long isr48
    .long isr49
    .long isr50
    .long isr51
    .long isr52
    .long isr53
    .long isr54
    .long isr55
    .long isr56
    .long isr57
    .long isr58
    .long isr59
    .long isr60
    .long isr61
    .long isr62
    .long isr63
    .long isr64
    .long isr65
    .long isr66
    .long isr67
    .long isr68
    .long isr69
    .long isr70
    .long isr71
    .long isr72
    .long isr73
    .long isr74
    .long isr75
    .long isr76
    .long isr77
    .long isr78
    .long isr79
    .long isr80
    .long isr81
    .long isr82
    .long isr83
    .long isr84
    .long isr85
    .long isr86
    .long isr87
    .long isr88
    .long isr89
    .long isr90
    .long isr91
    .long isr92
    .long isr93
    .long isr94
    .long isr95
    .long isr96
    .long isr97
    .long isr98
    .long isr99
    .long isr100
    .long isr101
    .long isr102
    .long isr103
    .long isr104
    .long isr105
    .long isr106
    .long isr107
    .long isr108
    .long isr109
    .long isr110
    .long isr111
    .long isr112
    .long isr113
    .long isr114
    .long isr115
    .long isr116
    .long isr117
    .long isr118
    .long isr119
    .long isr120
    .long isr121
    .long isr122
    .long isr123
    .long isr124
    .long isr125
    .long isr126
    .long isr127
    .long isr128
    .long isr129
    .long isr130
    .long isr131
    .long isr132
    .long isr133
    .long isr134
    .long isr135
    .long isr136
    .long isr137
    .long isr138
    .long isr139
    .long isr140
    .long isr141
    .long isr142
    .long isr143
    .long isr144
    .long isr145
    .long isr146
    .long isr147
    .long isr148
    .long isr149
    .long isr150
    .long isr151
    .long isr152
    .long isr153
    .long isr154
    .long isr155
    .long isr156
    .long isr157
    .long isr158
    .long isr159
    .long isr160
    .long isr161
    .long isr162
    .long isr163
    .long isr164
    .long isr165
    .long isr166
    .long isr167
    .long isr168
    .long isr169
    .long isr170
    .long isr171
    .long isr172
    .long isr173
    .long isr174
    .long isr175
    .long isr176
    .long isr177
    .long isr178
    .long isr179
    .long isr180
    .long isr181
    .long isr182
    .long isr183
    .long isr184
    .long isr185
    .long isr186
    .long isr187
    .long isr188
    .long isr189
    .long isr190
    .long isr191
    .long isr192
    .long isr193
    .long isr194
    .long isr195
    .long isr196
    .long isr197
    .long isr198
    .long isr199
    .long isr200
    .long isr201
    .long isr202
    .long isr203
    .long isr204
    .long isr205
    .long isr206
    .long isr207
    .long isr208
    .long isr209
    .long isr210
    .long isr211
    .long isr212
    .long isr213
    .long isr214
    .long isr215
    .long isr216
    .long isr217
    .long isr218
    .long isr219
    .long isr220
    .long isr221
    .long isr222
    .long isr223
    .long isr224
    .long isr225
    .long isr226
    .long isr227
    .long isr228
    .long isr229
    .long isr230
    .long isr231
    .long isr232
    .long isr233
    .long isr234
    .long isr235
    .long isr236
    .long isr237
    .long isr238
    .long isr239
    .long isr240
    .long isr241
    .long isr242
    .long isr243
    .long isr244
    .long isr245
    .long isr246
    .long isr247
    .long isr248
    .long isr249
    .long isr250
    .long isr251
    .long isr252
    .long isr253
    .long isr254
    .long isr255