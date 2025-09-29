This project began as a simple orderbook written in C. The initial plan was straighfoward: build a basic matching engine to simulate how buy and sell orders interact. As the project expanded, I decided that I would like users to be able to interact with the orderbook, the project seemed less abstract to me that way, and slightly more digestable as one could SEE what was happening in the code.

It quickly dawned on me that because of this, I needed plenty more data points than I planned for: the main thing I needed was stock pricing ability, but after deciding that stochastic - or randomised - pricing models like Brownian motion weren't what I wanted for the project, I shifted direction again.
Therefore, I decided that stock pricing in this simulator would not be as a 'dice-roll', but the emergent result of each program 'tick', and driven by the application of logic, to sets of bots, based on real world strategies used in HFT and retail traders. 

Each bot acts as a trader, making decisions based on market conditions which are the sum of user and bot behaviour.

the Could be enhanced with multithreading to avoid a per tick market update, and library based graphical UI for displaying the orderbook as one would expect. 

