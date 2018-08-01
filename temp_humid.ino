void temp_humid()
{ 

  // lecture 1er DHT22 (régul)
  int chk = DHT.read22(DHT221_PIN);
  temp = (DHT.temperature);
  humd = (DHT.humidity);

  ///////////////////////////////////////////////////////////////////////////////
  //        Vérification fonctionnement capteur régul et mise en replis
  ///////////////////////////////////////////////////////////////////////////////
  switch (chk)
    {
      case DHTLIB_OK:  
 //         Serial.println("DHT regul OK,\t"); 
            digitalWrite(relais_secu, LOW);
            mem_relais_secu =0;
             // Surveillance dépassement température
            if (temp>consigne+2 || temp>t2+1 || temp<t2-1) {
              digitalWrite(relais_secu, HIGH);
              mem_relais_secu =1;
              mem_decl_relais_secu =1;
             }
           break;
      case DHTLIB_ERROR_CHECKSUM: 
          Serial.println("Erreur DHT regul Checksum,\t");
          digitalWrite(relais_secu, HIGH); 
          mem_relais_secu =1;
          mem_decl_relais_secu =1;       
          break;
      case DHTLIB_ERROR_TIMEOUT: 
          Serial.println("Erreur DHT regul Time out,\t");
          digitalWrite(relais_secu, HIGH);
          mem_relais_secu =1;
          mem_decl_relais_secu =1;        
          break;
      default: 
          Serial.println("Erreur DHT regul Unknown error,\t");
          digitalWrite(relais_secu, HIGH);
          mem_relais_secu =1;
          mem_decl_relais_secu =1;        
          break;
  }
  ///////////////////////////////////////////////////////////////////////////////
  
  // lecture 2eme DHT22 (sécu)
  chk = DHT.read22(DHT222_PIN);
  t2 = (DHT.temperature);
  h2 = (DHT.humidity);

  ///////////////////////////////////////////////////////////////////////////////
  //        Vérification fonctionnement capteur sécu
  ///////////////////////////////////////////////////////////////////////////////
  switch (chk)
    {
      case DHTLIB_OK:  
//          Serial.println("DHT secu OK,\t"); 
          break;
      case DHTLIB_ERROR_CHECKSUM: 
          Serial.println("Erreur DHT secu Checksum,\t");
          break;
      case DHTLIB_ERROR_TIMEOUT: 
          Serial.println("Erreur DHT secu Time out,\t");
          break;
      default: 
          Serial.println("Erreur DHT secu Unknown error,\t");
          break;
  }
  ///////////////////////////////////////////////////////////////////////////////

  humDelta = consigneH - humd; 
  if(humd > 100)
  {
    humd =100;
  }
  
  if(humd > humMaxi)
  {
    humMaxi = humd ;
  }
  
  if(humd < humMini)
  {
    humMini = humd;
  }
  
  
  if (tempMini > temp)
  {
    tempMini = temp;
  }
  if (tempMaxi < temp)
  {
    tempMaxi = temp;
  }

  if (mem_relais_secu == 1) {
          mem_mois=mois;
          mem_jour=jour;
          mem_heures=heures;
          mem_minutes=minutes;
  }

}
