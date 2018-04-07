  org $800
O equ 0
N equ 45
M equ 4
  org $1000
  ldaa M
  adda #7
  suba N
  staa O
end	