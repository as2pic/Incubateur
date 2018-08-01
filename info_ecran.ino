void ecran()
{
  switch(page)
  {
    case 0: // Mesures DHT 1
        lcd.clear();
        lcd.setCursor(0,0);             
        lcd.print(heures);
        lcd.print(":");       
        lcd.print(minutes/10);
        lcd.print(minutes%10);
        lcd.setCursor(9,0);
        lcd.print("DHT 1");
        lcd.setCursor(0,1);  
        lcd.setCursor(0,1);           
        lcd.print("Temperature:");
        lcd.setCursor(13,1);
        lcd.print(temp,1);
        lcd.print((char)223);
        lcd.setCursor(0,2);
        lcd.print("Hygrometrie:");
        lcd.setCursor(13,2);
        lcd.print(humd,1);
        lcd.print("%");  
        lcd.setCursor(18,0);
        lcd.print("P");
        lcd.setCursor(19,0);
        lcd.print(page+1);
        lcd.setCursor(0,3);
        lcd.print("DS18B20    :");
        lcd.setCursor(13,3);
        lcd.print(temp_DS18B20);
        lcd.print((char)223);
    break;
    
    case 1: // Mesures DHT 2
        lcd.clear();
        lcd.setCursor(0,0);             
        lcd.print(heures);
        lcd.print(":");       
        lcd.print(minutes/10);
        lcd.print(minutes%10);
        lcd.setCursor(9,0);
        lcd.print("DHT 2");
        lcd.setCursor(0,1);  
        lcd.setCursor(0,1);           
        lcd.print("Temperature:");
        lcd.setCursor(13,1);
        lcd.print(t2,1);
        lcd.print((char)223);
        lcd.setCursor(0,2);
        lcd.print("Hygrometrie:");
        lcd.setCursor(13,2);
        lcd.print(h2,1);
        lcd.print("%");  
        lcd.setCursor(18,0);
        lcd.print("P");
        lcd.setCursor(19,0);
        lcd.print(page+1);
        lcd.setCursor(0,3);
        lcd.print("DS18B20    :");
        lcd.setCursor(13,3);
        lcd.print(temp_DS18B20);
        lcd.print((char)223);
    break;

    case 2 : //Consignes et Temperature mini / maxi 
        lcd.clear();
        lcd.setCursor(0,0);             
        lcd.print(heures);
        lcd.print(":");       
        lcd.print(minutes/10);
        lcd.print(minutes%10);
        lcd.setCursor(0,1);
        lcd.print("Consigne:");
        lcd.setCursor(12,1);  
        lcd.print(consigne);
        lcd.print((char)223);
        lcd.setCursor(0,2); 
        lcd.print("Temp. Mini:");
        lcd.setCursor(12,2);
        lcd.print(tempMini,1);
        lcd.print((char)223);
        lcd.setCursor(0,3);
        lcd.print("Temp. Maxi:");
        lcd.setCursor(12,3);
        lcd.print(tempMaxi,1);
        lcd.print((char)223);
        lcd.setCursor(18,0);
        lcd.print("P");
        lcd.setCursor(19,0);
        lcd.print(page+1);
    
    break;
    
    case 3: // Mémorisation détection sécurité
        lcd.clear();
        lcd.setCursor(0,0);             
        lcd.print(heures);
        lcd.print(":");       
        lcd.print(minutes/10);
        lcd.print(minutes%10);
        lcd.setCursor(0,1);             
        if (mem_decl_relais_secu == 1){
          lcd.print("dernier declench.");
          lcd.setCursor(0,2);
          lcd.print("relais secu:");
          lcd.setCursor(0,3);
          lcd.print(mem_jour);
          lcd.print("/"); 
          lcd.print(mem_mois);
          lcd.print("-");
          lcd.print(mem_heures);
          lcd.print(":");
          lcd.print(mem_minutes/10);
          lcd.print(mem_minutes%10);
        }
        else{
          lcd.print("Pas alarme");
        }
        lcd.setCursor(18,0);
        lcd.print("P");
        lcd.setCursor(19,0);
        lcd.print(page+1);
        break;
    
  
  }
}
