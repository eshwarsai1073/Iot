String httpGETRequest(String serverName) {
  String payload = "--"; 
  HTTPClient http;
    WiFiClient client;
  // Your IP address with path or Domain name with URL path 
  http.begin(client,serverName);
  
  // Send HTTP POST request
  int httpResponseCode = http.GET();

  if (httpResponseCode>0) {
    // Serial.print("HTTP Response code: ");
    // Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
