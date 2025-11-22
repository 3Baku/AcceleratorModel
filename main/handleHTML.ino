String processor(const String& var) {
  
  // The Chart Data
  if(var == "DATA_ARRAY") {
    // LOGIC: Only send numbers if showPlot is TRUE. Otherwise send empty.
    if (showPlot) {
      return get_array_string(); 
    } else {
      return "[]"; 
    }
  }

  // Button for Calibration
  if(var == "BUTTON_1") {
    if(calibration) return F("<button class='btn btn-calib' disabled>BUSY...</button>");
    return F("<a href='/calibrate'><button class='btn btn-calib'>CALIBRATE</button></a>");
  }

  // Button for Plotting
  if(var == "BUTTON_2") {
    // If plot is already shown, maybe show a "Hide" or "Update" button?
    if (showPlot) {
       return F("<a href='/plot'><button class='btn btn-plot'>UPDATE PLOT</button></a>");
    } else {
       return F("<a href='/plot'><button class='btn btn-plot'>PLOT DATA</button></a>");
    }
  }

  return String();
}

// --- ROUTES ---
void handle_root() {
    String s = index_html;
    s.replace("%DATA_ARRAY%", processor("DATA_ARRAY"));
    s.replace("%BUTTON_1%", processor("BUTTON_1"));
    s.replace("%BUTTON_2%", processor("BUTTON_2"));
    server.send(200, "text/html", s);
}

void handle_calibrate() {
    calibration = 1;
    Serial.println("Button Pressed: Requesting Calibration...");
    showPlot = 0;
   
    server.sendHeader("Location", "/");
    server.send(303);
}

void handle_plot() {
  showPlot = 1;
  
  Serial.println("User requested plot. Sending data...");
  
  server.sendHeader("Location", "/");
  server.send(303);
}