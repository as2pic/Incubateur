void ethernet()
{

   // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<font size=7>");
          client.print("***********************");
          client.println("<br />");
          client.print("* Incubateur oeuf de tortue *");
          client.println("<br />");
          client.println("***********************");
          client.print("<br />");
          client.println("<font size=5>");
          client.print("heure: ");
          client.print(heures);
          client.print(":");
          client.print(minutes/10);
          client.println(minutes%10);
          client.print("<br />");
          client.print("temperature sonde DS18B20: ");
          client.print(temp_DS18B20);
          client.println("</font>");
          client.print("<br />");
          client.print("DHT22 regul :");
          client.println("<br />");
          client.print("</font>");
          client.println("<font size=5>");
          client.print("temperature :  ");
          client.println(temp);
          client.println("<br />");
          client.print("humidite :  ");
          client.println(humd);
          client.println("<br />");
          client.println("<br />");
          client.print("</font>");
          client.println("<font size=7>");
          client.print("DHT22 secu :");
          client.println("<br />");
          client.print("</font>");
          client.println("<font size=5>");
          client.print("temperature:  ");
          client.println(t2);
          client.println("<br />");
          client.print("humidite :  ");
          client.println(h2);
          client.println("<br />");
          client.println("<br />");
          client.print("</font>");
          client.println("<font size=7>");
          client.print("Parametres regul :");
          client.print("</font>");
          client.println("<font size=5>");
          client.println("<br />");
          client.print("consigne :  ");
          client.print(consigne);
          client.println("<br />");
          client.print("PIsum :  ");
          client.print(PIsum);
          client.println("<br />");
          client.print("temperature mini :  ");
          client.println(tempMini);
          client.println("<br />");
          client.print("temperature maxi :  ");
          client.print(tempMaxi);
          client.print("</font>");
          client.println("<br />"); 
          client.println("<br />");

          client.println("<font size=7>");
          if (mem_relais_secu ==0){
              client.println("Relais Secu ON");
          }
          else {
             client.println("Relais Secu OFF");
          }

                    
          client.print("</font>");
                  
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
}
