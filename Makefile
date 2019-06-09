all:
	@sudo gcc -O3 -DTL_TL thinklight.c -o thinklight
	@sudo chmod +s thinklight
	@sudo gcc -O3 -DTL_CL thinklight.c -o capslock
	@sudo chmod +s capslock
	@sudo gcc -O3 -DTL_SB thinklight.c -o standby
	@sudo chmod +s standby
	@sudo gcc -O3 -DTL_PW thinklight.c -o power
	@sudo chmod +s power
	@sudo gcc -O3 -DTL_WL thinklight.c -o wifi
	@sudo chmod +s wifi

install:
	@sudo cp thinklight /usr/bin/
	@sudo chmod +s /usr/bin/thinklight
	@sudo cp capslock /usr/bin/
	@sudo chmod +s /usr/bin/capslock
	@sudo cp standby /usr/bin/
	@sudo chmod +s /usr/bin/standby
	@sudo cp power /usr/bin/power
	@sudo chmod +s /usr/bin/power
	@sudo cp wifi /usr/bin/wifi
	@sudo chmod +s /usr/bin/wifi
