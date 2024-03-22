LCD_REG  = $7c00
LCD_DATA = $7c01

lcd_init:
  lda #%00111000 ; function 8-bit mode; 2 line display; 5x8 char font
  sta LCD_REG

  jsr lcd_wait
  lda #%00001110 ; turn on display
  sta LCD_REG

  jsr lcd_wait
  lda #%00000110 ; inc cursor after write
  sta LCD_REG
  rts

lcd_clear:
  jsr lcd_wait
  lda #%00000001 ; clear
  sta LCD_REG
  rts

lcd_wait:
  lda LCD_REG
  and #%10000000 ; test busy flag
  bne lcd_wait
  rts
