#include        "dp256reg.asm"  

    org $800
arrary1 db 'A','A','A','A'                   
arrary2 dw $100,$100,$100,$100      
                                        
  org $1000

  ldx #arrary2

  ldd '\0'
  std 6, x

  ldd #$-1
  std 4,x

END


