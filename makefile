trading_sim: main.c ui.c user.c stocks.c order.c
	gcc -o trading_sim main.c ui.c user.c stocks.c order.c

clean:
	rm -f trading_sim
