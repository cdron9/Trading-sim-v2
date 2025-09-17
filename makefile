trading_sim: main.c ui.c user.c stocks.c
	gcc -o trading_sim main.c ui.c user.c stocks.c

clean:
	rm -f trading_sim
