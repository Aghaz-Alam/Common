#USB headphone is not working to fix this run the following command

dell@dell-Latitude-5420:~$ lsusb
Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 002 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
Bus 003 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
Bus 003 Device 002: ID 1bcf:28c4 Sunplus Innovation Technology Inc. Integrated_Webcam_HD
Bus 003 Device 016: ID 047f:c056 Plantronics, Inc. Blackwire C3220 Headset
Bus 004 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub

dell@dell-Latitude-5420:~$ aplay -l
**** List of PLAYBACK Hardware Devices ****
card 0: PCH [HDA Intel PCH], device 0: ALC3204 Analog [ALC3204 Analog]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: PCH [HDA Intel PCH], device 3: HDMI 0 [HDMI 0]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: PCH [HDA Intel PCH], device 7: HDMI 1 [HDMI 1]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: PCH [HDA Intel PCH], device 8: HDMI 2 [HDMI 2]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 0: PCH [HDA Intel PCH], device 9: HDMI 3 [HDMI 3]
  Subdevices: 1/1
  Subdevice #0: subdevice #0
card 1: Seri [Plantronics Blackwire 3220 Seri], device 0: USB Audio [USB Audio]
  Subdevices: 0/1
  Subdevice #0: subdevice #0

dell@dell-Latitude-5420:~$ pactl info | grep "Server Name"
Server Name: PulseAudio (on PipeWire 1.0.5)

dell@dell-Latitude-5420:~$ pactl list short sinks
55	alsa_output.pci-0000_00_1f.3.analog-stereo	PipeWire	s32le 2ch 48000Hz	SUSPENDED
657	alsa_output.usb-Plantronics_Plantronics_Blackwire_3220_Series_EC962F2B1F0C5C418890F3BF105FFC60-00.analog-stereo	PipeWire	s16le 2ch 48000Hz	SUSPENDED

dell@dell-Latitude-5420:~$ pactl set-default-sink alsa_output.usb-Plantronics_Plantronics_Blackwire_3220_Series_EC962F2B1F0C5C418890F3BF105FFC60-00.analog-stereo

dell@dell-Latitude-5420:~$ pactl get-default-sink
alsa_output.usb-Plantronics_Plantronics_Blackwire_3220_Series_EC962F2B1F0C5C418890F3BF105FFC60-00.analog-stereo
