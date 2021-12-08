#include "AudioOut.h"

AudioOut::AudioOut () {

}
void AudioOut::begin () {
    // start wavTrigger
    wTrig.start();
    wTrig.stopAllTracks();
    //wTrig.samplerateOffset(0);
    wTrig.setReporting(true);

}
void AudioOut::update() {
    wTrig.update();
}
void AudioOut::playTrackSolo(int trackNum) {
    wTrig.trackPlaySolo(trackNum);
}
void AudioOut::playTrack(int trackNum) {
    wTrig.trackPlayPoly(trackNum);
}
void AudioOut::randomizePitch() {
  // Sets a random pitch playback from 1/2 speed to 2x speed
  wTrig.samplerateOffset(random(-32768, 32767));
}
void AudioOut::resetPitch() {
  wTrig.samplerateOffset(0);
}
void AudioOut::stopAllTracks() {
    wTrig.stopAllTracks();
}
