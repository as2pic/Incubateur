void dial_serie()
{

#ifdef soft_incub
 
    char carlu = 0; //variable contenant le caractère à lire
    int cardispo = 0; //variable contenant le nombre de caractère disponibles dans le buffer
    
    cardispo = Serial.available();
    
    while(cardispo > 0) //tant qu'il y a des caractères à lire
    {
        carlu = Serial.read(); //on lit le caractère
        switch(carlu)
        {
          case 'h':
            Serial.println(humd);
          break;
            
          case 't':
            Serial.println(temp);
          break;
          
          case 'a':
            Serial.println(consigneH);
          break;
          
          case 'D':
            Serial.println(humDelta);
          break;         
          
          case 'p' :
            Serial.println(Pvalue);
          break;
          
          case 'i':
            Serial.println(Ivalue);
          break;
            
          case 's':
            Serial.println(PIsum);
          break;
            
          case 'd':
            Serial.println(PIdelta);
            break;
          
          case 'C':
            Serial.println(Pcoeff);
            break;
          
          case 'c':
            Serial.println(Icoeff);
            break;
            
          case 'o':
            Serial.println(consigne);
            break;  
           
        }
        delay(60);
        cardispo = Serial.available(); //on relit le nombre de caractères dispo
    }
#endif

#ifdef com_serie
  Serial.print(heures);
  Serial.print(":");
  Serial.print(minutes/10);
  Serial.print(minutes%10);
  Serial.print("   ");
  Serial.print("H1: ");
  Serial.print(humd);
  Serial.print(" %   ");
  Serial.print("T1: ");
  Serial.print(temp);
  Serial.print(" C   ");
  Serial.print("H2: ");
  Serial.print(h2);
  Serial.print(" %  ");
  Serial.print("T2: ");
  Serial.print(t2);
  Serial.print(" C  ");
  Serial.print("consigne: ");
  Serial.println(consigne);
  Serial.print("PIdelta ");
  Serial.print(PIdelta);
  Serial.print("  ");
  Serial.print("Pvalue ");
  Serial.print(Pvalue);
  Serial.print("  ");
  Serial.print("Ivalue ");
  Serial.print(Ivalue);
  Serial.print("  ");
  Serial.print("PIsum ");
  Serial.println(PIsum);
  if (temp > consigne+2 || temp > consigne + 0.3 || temp > consigne + 0.3 || temp < consigne - 0.3 || temp > t2+1) Serial.println("Erreur ! ");
  Serial.print("mem_relais_secu  ");
  Serial.println(mem_relais_secu);
  Serial.println("  ");
#endif  

#ifdef com_sdcard
    //Ouverture du fichier
    fichierSD = SD.open("log.txt", FILE_WRITE);
    //Test pour écriture
    if(fichierSD) {
      Serial.println("ecriture carte SD");
      fichierSD.print(heures);
      fichierSD.print(":");
      fichierSD.print(minutes/10);
      fichierSD.print(minutes%10);
      fichierSD.print("   ");
      fichierSD.print("H1: ");
      fichierSD.print(humd);
      fichierSD.print(" %   ");
      fichierSD.print("T1: ");
      fichierSD.print(temp);
      fichierSD.print(" C   ");
      fichierSD.print("H2: ");
      fichierSD.print(h2);
      fichierSD.print(" %  ");
      fichierSD.print("T2: ");
      fichierSD.print(t2);
      fichierSD.print(" C  ");
      fichierSD.print("consigne: ");
      fichierSD.println(consigne);
      fichierSD.print("PIdelta ");
      fichierSD.print(PIdelta);
      fichierSD.print("  ");
      fichierSD.print("Pvalue ");
      fichierSD.print(Pvalue);
      fichierSD.print("  ");
      fichierSD.print("Ivalue ");
      fichierSD.print(Ivalue);
      fichierSD.print("  ");
      fichierSD.print("PIsum ");
      fichierSD.println(PIsum);
      if (temp > consigne+2 || temp > consigne + 0.3 || temp > consigne + 0.3 || temp < consigne - 0.3 || temp > t2+1) fichierSD.println("Erreur ! ");
      fichierSD.print("mem_relais_secu  ");
      fichierSD.println(mem_relais_secu);
      fichierSD.println("  ");
      fichierSD.close();
    }  
#endif 


}
