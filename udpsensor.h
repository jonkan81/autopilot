#include "esphome.h"
#include <ESPAsyncUDP.h>
#include <cstddef>

class UdpSensor : public Component, public TextSensor {
 char packet[255];
 AsyncUDP udp;
 public:
  float get_setup_priority() const override { return esphome::setup_priority::AFTER_WIFI; }
  //static UdpSensor _this = NULL;

  void setup() override {
    if(udp.listen(2000)) {
        udp.onPacket([this](AsyncUDPPacket packet) {
            this->onIncoming(packet);
        });
    }


  }

  void onIncoming(AsyncUDPPacket packet) {
    const std::string payload ((char*)packet.data());
    publish_state(payload);
  }

  void loop() override {
     //if(_this == NULL) {
     //  _this = this;
    // }
  }
};
