void server_setup(){
    server.on("/", handle_root);
    server.on("/calibrate", handle_calibrate);
    server.on("/plot", handle_plot);
    server.begin();
}