#include "Trade.h"



Trade::Trade(trade_type type, float shares, double sharePrice,std::string stockSymbol)
{
    this->type = type;
    this->shares = shares;
    this->sharePrice = sharePrice;
    this->stockSymbol = stockSymbol;
}


std::ostream& operator<<(std::ostream& out, const Trade& trade)
{
    
    if (trade.type == BUY)
        std::cout << "[BUY]";
    else
        std::cout << "[SELL]";
    std::cout << " " << trade.shares << " shares of " << trade.stockSymbol << " at price " << trade.sharePrice;
    
    return out;
}