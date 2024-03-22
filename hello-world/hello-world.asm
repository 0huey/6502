  .ORG $8000

  .INCLUDE lcd.asm

reset:
  sei
  jsr lcd_init

print_start:
  jsr lcd_clear
  ldx #0
print_loop:
  jsr lcd_wait
  lda hello_msg, x
  cmp #0
  beq print_start
  sta LCD_DATA
  inx
  bra print_loop

exit:
  jmp halt

hello_msg: .ASCIIZ "Hello, World!"

  .ORG $ff69
halt:
  bra halt

  .ORG  $fffa
  .WORD halt  ; NMI
  .WORD reset ; reset
  .WORD halt  ; IRQ
