void regulation()
{
  PIdelta = ( consigne - temp );
        
  Pvalue  = ( Pcoeff * PIdelta );
  if(Pvalue >= 255){Pvalue = 255;}
  if(PIsum <= 220)Ivalue += ( Icoeff * PIdelta );         
  PIsum = Pvalue + Ivalue;
         
  if ( PIsum < 0   ) PIsum = 0;
  if ( PIsum > 255 ) PIsum = 255;
  if ( Ivalue < 0   ) Ivalue = 0;
  
  analogWrite(relais, (int)PIsum);
}
