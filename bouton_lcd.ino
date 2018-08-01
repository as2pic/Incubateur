 void key()
 {
 lcd_key = read_LCD_buttons();  // read the buttons

  switch(lcd_key)
  {
    case(btnRIGHT):    
          page+=1;
          delay(500);
          break;
      
    case(btnLEFT):
          page-=1;
          delay(500);
          break;  
  }    
  
  if(page ==2)
  {
    switch(lcd_key)
    {
      case(btnUP):   // Incrémente la consigne 
            consigne +=0.5;
            EEPROM.writeDouble(addr_eeprom, consigne);
            delay(500);
            break;
        
      case(btnDOWN): // Décrémente la consigne
            consigne -=0.5;
            EEPROM.writeDouble(addr_eeprom, consigne);
            delay(500);
            break;  
    }    
  }
  
  if(page ==2)
  {
    switch(lcd_key)
    {
      case(btnSELECT):  // Init TempMini et TempMaxi  
            tempMini = temp;
            tempMaxi = temp;
            delay(500);
            break;
        
    }    
  }

  if(page ==3)
  {
    switch(lcd_key)
    {
      case(btnSELECT):    // Remise à "0" memoire déclenchement relais sécu
            mem_decl_relais_secu =0;
            delay(500);
            break;
        
    }    
  }
  
  if(page <0)
  {
    page =3;
  }
  if(page >3)
  {
    page=0;
  }

  
 }


