  #pragma once
  #include <ESP8266WiFi.h>
  #include <ESP8266WebServer.h>
  #include <LittleFS.h>

  class WebDriver {
  public:
    WebDriver(const char* ssid, const char* pass)
    : _server(80), _ssid(ssid), _pass(pass) {}

    bool begin() {
      if (!LittleFS.begin()) return false;

      WiFi.mode(WIFI_AP);
      WiFi.softAP(_ssid, _pass);

      _server.on("/",     [this]{ handleRoot(); });
      _server.on("/state",[this]{ _server.send(200,"application/json", _running ? "{\"running\":true}" : "{\"running\":false}"); });
      _server.on("/start",[this]{ start(); _server.send(200,"text/plain","OK"); });
      _server.on("/stop", [this]{ stop();  _server.send(200,"text/plain","OK"); });
      _server.on("/distance",[this]{ sendDistance(); });

      _server.begin();
      return true;
    }

    void handle() { _server.handleClient(); }

    void start() { _running = true;  _done = false; onStart(); }
    void stop()  { _running = false; onStop();  }

    void setDistance(float cm) { _distance = cm; }

    void markDone()   { _done = true; }
    void clearDone()  { _done = false; }

    bool running() const { return _running; }

    virtual void onStart() {}
    virtual void onStop()  {}

  private:
    ESP8266WebServer _server;
    const char* _ssid;
    const char* _pass;
    const char* _indexPath = "/index.html";
    bool _running = false;
    bool _done = false; 
    float _distance = NAN;

    void handleRoot() {
      File f = LittleFS.open(_indexPath, "r");
      if (!f) { _server.send(404, "text/plain", "index.html missing"); return; }
      _server.streamFile(f, "text/html");
      f.close();
    }

    void sendDistance() {
      if (isnan(_distance)) {
        _server.send(200,"application/json","{\"ok\":false}");
        return;
      }
      String body = String("{\"ok\":true,\"cm\":") + String(_distance,1) + "}";
      _server.send(200,"application/json",body);
    }
  };
