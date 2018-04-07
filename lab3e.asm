  org $800
O equ 0
N equ 2
M equ 20
  org $1000
result rmb 2

ldaa #2
ldab N
mul
staa result
stab result
ldaa M
suba result
ldab #3
mul 
staa result
stab result
swi