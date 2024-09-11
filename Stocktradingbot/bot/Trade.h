#ifndef Trade_H
#define Trade_H

#include <iostream>

enum trade_type {BUY,SELL};

class Trade 
{
    public:
        Trade(trade_type type, float shares, double sharePrice,std::string stockSymbol);

        trade_type type;
        float shares;
        double sharePrice;
        std::string stockSymbol;


        friend std::ostream& operator<<(std::ostream& out, const Trade& trade);
};





#endif