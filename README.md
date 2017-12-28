# encoder-code-in-rpi3

this code was developed with reference from :https://www.sunfounder.com/learn/Super_Kit_V2_for_RaspberryPi/lesson-8-rotary-encoder-super-kit-for-raspberrypi.html

for controlling dc motor with mdds30 (motor sheild) follow this: https://tutorial.cytron.io/2016/07/26/raspberry-pi-control-dc-motor-using-mdds10/

the main problem i faced was:
the encoder we used gives actually 14k counts per revolution but while tetstsing the sensor gave 12k counts per revolution.

this issue has to addressed. (may be the problem is with sensor being physically damaged, idk why it happened..!)
