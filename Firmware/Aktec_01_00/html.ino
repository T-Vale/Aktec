void html_interface()
{
  // listen for incoming clients

  EthernetClient client = server.available();
  //Serial.println("Listening to possible connections");
  if (client)
  {
    Serial.println("HTML Communication Started");
    boolean currentLineIsBlank = true;

    String receivedLine = "";
    String receivedPost = "";
    boolean thereIsAPost = false;

    boolean deleteAll = false;

    boolean statusxml = false;
    boolean timeSet = false;
    boolean sensorAssign = false;
    boolean dataGraph = false;
    boolean defineAlarms = false;
    boolean rawData = false;
    boolean plotGraph = false;

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.print(c);
        if (receivedLine.length() < LINELENGTH)
        {
          receivedLine = receivedLine + c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank)
        {
          while (client.available())
          {
            char d = client.read();
            Serial.print(d);
            if (receivedPost.length() < LINELENGTH)
            {
              receivedPost = receivedPost + d;
            }
            else
            {
              client.flush();
            }
          }
          if ((receivedPost.length() > 0) && thereIsAPost)
          {
            receivedPost += "&";
            boolean thepostisfine = false;

            htmlRequest_delaySetting(receivedPost, netEndChar);
            htmlRequest_defineAlarms(receivedPost, netEndChar);
          }
          thereIsAPost = false;

          if (!statusxml)
          {
            // send a standard http response header
            client.println(F("HTTP/1.1 200 OK"));
            client.println(F("Content-Type: text/html"));
            client.println(F("Connection: close"));  // the connection will be closed after completion of the response
            client.println();
            client.println(F("<!DOCTYPE HTML>"));
            client.println(F("<html>"));
            client.println(F("<style>"));

            client.println(F("\t#rcorners {"));
            client.println(F("\t\tborder-radius: 15px 50px;"));
            client.println(F ("\t\tbackground: #000080;"));
            client.println(F("\t\tpadding: 25px 50px;"));
            client.println(F("\t\twidth: 65px;"));
            client.println(F("\t\theight: 25px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 35px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: white;"));
            client.println(F("\t}"));

            client.println(F("\t#titles {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\ttext-shadow: 1% 1% #f2f2f2;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("\t#buttons {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\t#buttonies {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\twidth: 30px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\t#fillin {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\t#textbox {"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\twidth: 40px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\t#hovertable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\t#hovertr:hover{background-color:#f5f5f5}"));

            client.println(F("\t#invisibletable {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tborder-collapse: collapse;"));
            client.println(F("\t\twidth: 300px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t}"));

            client.println(F("\tth, td {"));
            client.println(F("\t\tpadding: 8px 10px;"));
            client.println(F("\t\ttext-align: left;"));
            client.println(F("\t\tborder-bottom: 1px solid #ddd;"));
            client.println(F("\t}"));

            client.println(F("\ta {"));
            //client.println(F("\t\tpadding: 0px 50px;"));
            client.println(F("\t\ttext-decoration:none;"));
            //client.println(F("\t\tfont-family: verdana;"));
            //client.println(F("\t\tfont-size: 17px;"));
            client.println(F("\t\tdisplay: inline;"));
            client.println(F("\t}"));

            client.println(F("\tp {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-family: verdana;"));
            client.println(F("\t\tfont-size: 10px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("\tcode {"));
            client.println(F("\t\tpadding: 0px 10px;"));
            client.println(F("\t\tfont-size: 14px;"));
            client.println(F("\t\tcolor: black;"));
            client.println(F("\t}"));

            client.println(F("</style>"));
            client.print(F("<a href=\"http://"));
            client.print(ipAddress_[0]);
            client.print(F("."));
            client.print(ipAddress_[1]);
            client.print(F("."));
            client.print(ipAddress_[2]);
            client.print(F("."));
            client.print(ipAddress_[3]);
            client.println(F("\">"));
            client.println(F("<h3 id=\"rcorners\">"));
            client.println(F("\tAktec"));
            client.println(F("</h3>"));
            client.println(F("</a>"));


            if (deleteAll)
            {
              for (int data = 0; data <  MAXIMUMNUMBEROFDATAFILES; data++)
              {
                card_removeFile(String(data) + ".TXT");
              }
              dataFilesNumber = 0;
              card_removeFile(dataNumberFileName);
              String toWrite = "datafilesnumber=" + String(dataFilesNumber) + ";";
              card_writeFile(dataNumberFileName, toWrite);
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tData files deleted"));
              client.println(F("</h2>"));
              client.println(F("</body>"));
              client.println(F("</html>"));
            }
            else if (sensorAssign)
            {
            }
            else if (defineAlarms)
            {
            }
            else if (dataGraph)
            {
            }
            else if (dataGraph)
            {

            }

            else if (plotGraph) //mudar nome para dataGraph
            {
              client.println(F("<h2 id=\"titles\">"));
              client.print(F("\tData - "));
              client.println(dataFileReq);
              client.println(F("<br>"));
              client.println(F("</h2>"));
              client.println(F("<body>"));

              String fileLoc = String(dataFileReq) + ".TXT";
              File dataFile = SD.open(fileLoc);
              char ch;
              String line = "";
              String buff = "";
              String buff2 = "";
              long timeseconds = 0;

              if (dataFile)
              {
                client.println(F("<canvas id=\"graphic\" width=\"500\" height=\"250\" style=\"display: inline;\">"));
                client.println(F("Your browser does not support the HTML5 canvas tag.</canvas>"));
                client.println(F("<p><b>Minimum value measured:</b></p>"));
                client.println(F("<p id=\"mini\" style=\"display: inline;\"></p>"));
                client.println(F("<p><b>Maximum value measured:</b></p>"));
                client.println(F("<p id=\"maxi\" style=\"display: inline;\"></p>"));

                client.println(F("<script>"));
                client.println(F("\tvar w = document.getElementById(\"graphic\").offsetWidth;"));

                client.println(F("\tvar d = document.getElementById(\"graphic\");"));
                client.println(F("\tvar dL = d.getContext(\"2d\");"));

                client.println(F("\tvar imagex = document.getElementById(\"graphic\").offsetWidth;"));
                client.println(F("\tvar imagey = document.getElementById(\"graphic\").offsetHeight;"));
                client.println(F("\tvar leftmargin = imagex * 0.1;"));
                client.println(F("\tvar rightmargin = imagex * 0.04;"));
                client.println(F("\tvar topmargin = imagey * 0.1;"));
                client.println(F("\tvar bottommargin = imagey * 0.1;"));
                client.println(F("\tvar gxmin = leftmargin;"));
                client.println(F("\tvar gymin = topmargin;"));
                client.println(F("\tvar gxmax = document.getElementById(\"graphic\").offsetWidth - rightmargin;"));
                client.println(F("\tvar gymax = document.getElementById(\"graphic\").offsetHeight - bottommargin;"));
                client.println(F("\tvar gxlength = gxmax - gxmin;"));
                client.println(F("\tvar gylength = gymax - gymin;"));

                client.println(F("\tvar traceLen = 4;"));

                client.println(F("\tvar tmin = 0;"));
                client.println(F("\tvar tmax = 600;")); //10 minutos

                //client.println(F("\tvar tmed = tmax - tmin;"));

                client.print(F("\tvar vmin = "));
                client.print("0");
                client.println(F(";")); // AQUI
                client.print(F("\tvar vmax = "));
                client.print("1024");
                client.println(F(";")); // AQUI


                client.println(F("\tvar t = [];")); // AQUI
                client.println(F("\tvar v = [];")); // AQUI


                while (dataFile.available())
                {
                  ch = dataFile.read();
                  line += ch;

                  if (ch == '\n')
                  {
                    client.print(F("\tt.push("));
                    parse_parameterReader(line, "", buff, "\t");
                    timeseconds = buff.toInt();
                    client.print(timeseconds);
                    timeseconds = 0;
                    client.println(F(");")); // AQUI
                    client.print(F("\tv.push("));
                    parse_parameterReader(line, "\t", buff, "\n");
                    client.print(buff.toInt());
                    line = "";
                    client.println(F(");")); // AQUI
                  }
                }
                dataFile.close();


                client.println(F("\tif(Math.min.apply(null, v) < vmin)"));
                client.println(F("\t{"));
                client.println(F("\t\tvmin = Math.min.apply(null, v);"));
                client.println(F("\t}"));

                client.println(F("\tif(Math.max.apply(null, v) > vmax)"));
                client.println(F("\t{"));
                client.println(F("\t\tvmax = Math.max.apply(null, v);"));
                client.println(F("\t}"));

                client.println(F("\tdocument.getElementById('maxi').innerHTML = Math.max.apply(null, v);"));
                client.println(F("\tdocument.getElementById('mini').innerHTML = Math.min.apply(null, v);"));

                client.println(F("\tdL.strokeStyle = \"#000080\";"));
                client.println(F("\tdL.moveTo((((t[0] - tmin) * gxlength) / (tmax - tmin)) + gxmin, (gylength - (((v[0] - vmin) * gylength) / (vmax - vmin))) + gymin);"));

                client.println(F("\tfor(i = 1; i < t.length; i++)"));
                client.println(F("\t{"));
                client.println(F("\t\tdL.lineTo((((t[i] - tmin) * gxlength) / (tmax - tmin)) + gxmin, (gylength - (((v[i] - vmin) * gylength) / (vmax - vmin))) + gymin);"));
                client.println(F("\t}"));

                client.println(F("\tdL.stroke();"));
                client.println(F("\tdL.beginPath();"));
                client.println(F("\tdL.strokeStyle = '#000000';"));
                client.println(F("\tdL.moveTo(gxmin,gymin);")); //draws the axis
                client.println(F("\tdL.lineTo(gxmin,gymax);"));
                client.println(F("\tdL.lineTo(gxmax,gymax);"));

                client.println(F("\tdL.font = \"10px Verdana\";"));
                client.println(F("\tvar ytraces = 4;"));

                client.println(F("\tvar text;"));

                client.println(F("\tfor(i = 0; i <= ytraces; i++)"));
                client.println(F("\t{"));
                client.println(F("\t\ttext = vmax - i * (vmax - vmin)/ytraces;"));
                client.println(F("\t\ttext = text.toFixed(2);"));
                client.println(F("\t\tdL.fillText(text, gxmin - 10 * traceLen, i * gylength/ytraces + gymin);"));
                client.println(F("\tdL.moveTo(gxmin - traceLen, i * gylength/ytraces + gymin);"));
                client.println(F("\tdL.lineTo(gxmin + traceLen, i * gylength/ytraces + gymin);"));
                client.println(F("\t}"));

                client.println(F("\tdL.moveTo(gxmin - traceLen, gymax);"));
                client.println(F("\tdL.lineTo(gxmin + traceLen, gymax);"));

                client.println(F("\tvar xtraces = 24;"));
                client.println(F("\tfor(i = 0; i <= xtraces; i++)"));
                client.println(F("\t{"));
                client.println(F("\t\ttext = (i * (tmax/3600 - tmin/3600)/xtraces);"));
                client.println(F("\t\ttext = text.toFixed(0);"));
                client.println(F("\t\tdL.fillText(text, i * gxlength/xtraces + gxmin, gymax + 3 * traceLen);"));
                client.println(F("\t\tdL.moveTo(i * gxlength/xtraces + gxmin, gymax - traceLen);"));
                client.println(F("\t\tdL.lineTo(i * gxlength/xtraces + gxmin, gymax + traceLen);"));
                client.println(F("\t}"));

                client.println(F("\tdL.stroke();"));
                client.println(F("</script>"));

              }
              // if the file isn't open, pop up an error:
              else
              {
                client.print("<p>Error opening: ");
                client.print(fileLoc);
                client.println("</p>");
              }
            }

            else if (rawData)
            {
              String fileLoc = String(dataFileReq) + ".TXT";
              File dataFile = SD.open(fileLoc);
              char ch;
              String line = "";
              String buff = "";
              String buff2 = "";
              long timeseconds = 0;

              if (dataFile)
              {
                while (dataFile.available())
                {
                  ch = dataFile.read();
                  line += ch;

                  if (ch == '\n')
                  {
                    client.print("<code>");
                    client.print(line);
                    line = "";
                    client.println("</code><br>");
                  }
                }
                dataFile.close();
              }
              else
              {
                client.print("<p>Error opening: ");
                client.print(fileLoc);
                client.println("</p>");
              }
            }
            else
            {
              client.println(F("<h2 id=\"titles\">"));
              client.println(F("\tAcquired Data"));
              client.println(F("</h2>"));
              client.println(F("<body>"));
              client.println(F("<table id=\"hovertable\">"));
              client.println(F("\t<tr>"));
              client.println(F("\t\t<th>Data</th>"));
              client.println(F("\t\t<th>Text</th>"));
              client.println(F("\t\t<th>Graphic</th>"));
              client.println(F("\t</tr>"));

              for (int data = 0; data < dataFilesNumber; data++)
              {
                client.println(F("\t<tr id=\"hovertr\">"));
                client.print(F("\t\t<td>"));
                client.print(data);
                client.println(F("</td>"));

                /*
                  client.print(F("\t\t<td>"));
                  client.print(F("<form action=\"http://"));
                  client.print(ipAddress_[0]);
                  client.print(F("."));
                  client.print(ipAddress_[1]);
                  client.print(F("."));
                  client.print(ipAddress_[2]);
                  client.print(F("."));
                  client.print(ipAddress_[3]);
                  client.println(F("\" method=\"POST\">"));
                  client.print(F("\t<input type=\"submit\" value=\""));
                  client.print(data);
                  client.println(F("\" name=\"text\" id=\"buttonies\">"));
                  client.println("</form>");
                  client.println(F("</td>"));
                */

                client.print(F("\t\t<td>"));
                client.print(F("<a href=\"http://"));
                client.print(ipAddress_[0]);
                client.print(F("."));
                client.print(ipAddress_[1]);
                client.print(F("."));
                client.print(ipAddress_[2]);
                client.print(F("."));
                client.print(ipAddress_[3]);
                client.print(F("/text="));
                client.print(String(data));
                client.println(F("\"><input type=\"submit\" value=\"T\" id=\"buttonies\"></a>"));
                client.println(F("</td>"));


                client.print(F("\t\t<td>"));
                client.print(F("<a href=\"http://"));
                client.print(ipAddress_[0]);
                client.print(F("."));
                client.print(ipAddress_[1]);
                client.print(F("."));
                client.print(ipAddress_[2]);
                client.print(F("."));
                client.print(ipAddress_[3]);
                client.print(F("/graphic="));
                client.print(String(data));
                client.println(F("\"><input type=\"submit\" value=\"G\" id=\"buttonies\"></a>"));
                client.println(F("</td>"));
                client.println(F("\t</tr>"));
              }
              client.println(F("</table>"));
              client.println(F("<br>"));


              client.println(F("<br>"));
              client.print(F("<a href=\"http://"));
              client.print(ipAddress_[0]);
              client.print(F("."));
              client.print(ipAddress_[1]);
              client.print(F("."));
              client.print(ipAddress_[2]);
              client.print(F("."));
              client.print(ipAddress_[3]);
              client.println(F("/deleteall\"><input type=\"submit\" value=\"Delete Data\" id=\"buttons\"></a>"));

            }
            client.println(F("</body>"));
            client.println(F("</html>"));
          }
          break;
        }

        if (c == '\n')
        {
          // you're starting a new line
          currentLineIsBlank = true;
          String buffLine = "";

          if (parse_parameterReader(receivedLine, "GET /", buffLine, " HTTP"))
          {
            if ((buffLine.length() > 0))
            {
              statusxml = (buffLine == "status.xml");
              deleteAll = (buffLine == "deleteall");
              if (buffLine.indexOf("graphic=") >= 0)
              {
                plotGraph = htmlRequest_plotGraph(buffLine + netEndChar, netEndChar);
              }
              if (buffLine.indexOf("text=") >= 0)
              {
                rawData = htmlRequest_rawData(buffLine + netEndChar, netEndChar);
              }
            }
          }
          else if (parse_parameterReader(receivedLine, "POST /", buffLine, " HTTP"))
          {
            thereIsAPost = true;
          }
          receivedLine = "";
        }

        else if (c != '\r')
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
  else
  {
    //Serial.println("No one is coming");
  }
}



