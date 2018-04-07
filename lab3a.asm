   org $2000
NROWS equ 10
NCOLS equ 10
array1 rmb NROWS*NCOLS
arrary2 rmw NROWS*NCOLS
defaults equ 0
byteOffset equ 1
wordOffset equ 2
numelements equ NROWS*NCOLS


   org $4000
  ldy #numelements
  ldd #defaults
  ldx #array1
loop1:
  std byteOffset,x+
  dbne y,loop1
  ldy #numelements
  ldd #defaults
  ldx #arrary2
loop2:
  std wordOffset,x+
  dbne y,loop2
swi