trading_sim: main.c ui.c user.c stocks.c order.c orderbook.c
	gcc -o trading_sim main.c ui.c user.c stocks.c order.c orderbook.c

clean:
	rm -f trading_sim
