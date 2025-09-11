mkbin:
	mkdir -p ../bin

main1: mkbin
	gcc -g sigint_count.c -o ../bin/signal_main1

main2: mkbin
	gcc -g sigalrm_count -o ../bin/signal_main2

main3: mkbin
	gcc -g sigusr1 -o ../bin/signal_main3

main4: mkbin
	gcc -g mix_select_fd.c -o ../bin/signal_main4