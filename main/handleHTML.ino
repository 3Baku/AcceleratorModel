String processor(const String& var) {
  
  // 1. Standard Array (Graph 1)
  if(var == "DATA_ARRAY") {
    if (showPlot) return get_array_string();
    else return "[]";
  }

  // 2. XY Data (Graph 2)
  if(var == "XY_DATA") {
    if (showPlot) return get_xy_data_string();
    else return "[]";
  }

  // 3. Statistics Section
  if(var == "STATS_HTML") {
    if (!showPlot || velocityIndex == 0) return "No data available.";
    
    float avgV = calc_avg_velocity();
    float avgE = calc_avg_ekin(avgV);
    
    String stats = "Average Velocity: <span class='val'>" + String(avgV) + " cm/s</span><br>";
    stats += "Avg. Kinetic Energy: <span class='val'>" + String(avgE) + " uJ</span>";
    return stats;
  }

  // 4. Buttons
  if(var == "BUTTON_1") {
    if(calibration) return F("<button class='btn btn-calib' disabled>BUSY...</button>");
    return F("<a href='/calibrate'><button class='btn btn-calib'>CALIBRATE</button></a>");
  }

  if(var == "BUTTON_2") {
    if (showPlot) return F("<a href='/plot'><button class='btn btn-plot'>UPDATE PLOT</button></a>");
    else return F("<a href='/plot'><button class='btn btn-plot'>PLOT DATA</button></a>");
  }

  return String();
}

void handle_root() {
    String s = index_html;
    s.replace("%DATA_ARRAY%", processor("DATA_ARRAY"));
    s.replace("%XY_DATA%", processor("XY_DATA")); // Replaces new placeholder
    s.replace("%STATS_HTML%", processor("STATS_HTML")); // Replaces stats
    s.replace("%BUTTON_1%", processor("BUTTON_1"));
    s.replace("%BUTTON_2%", processor("BUTTON_2"));
    server.send(200, "text/html", s);
}

void handle_calibrate() {
    calibration = 1;
    showPlot = 0;
    server.sendHeader("Location", "/");
    server.send(303);
}

void handle_plot() {
  showPlot = 1;
  server.sendHeader("Location", "/");
  server.send(303);
}