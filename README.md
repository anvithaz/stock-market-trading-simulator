# Stock Market Trading Simulator

> Terminal-based trading simulator built in C that replicates real-world market conditions using live Indian stock market data — for risk-free strategy testing and investment education.

---

## What It Does

Select a company from a database of real NSE/BSE-listed stocks. Buy shares with a virtual ₹10,00,000 trading account. Watch prices fluctuate across 5 simulated trading rounds. Make buy, sell, or hold decisions each round. At the end — all shares are liquidated and your final P&L is revealed.

---

## Companies in the Database

| Company | Ticker | Prev Close |
|---------|--------|-----------|
| Ford Motor Co | F | $12.06 |
| Tata Motors Ltd | TATAMOTORS | ₹1,417.95 |
| Mahindra & Mahindra | M&M | ₹1,275.35 |
| Maruti Suzuki India | MARUTI | ₹8,654 |
| Eicher Motors Ltd | EICHERMOT | ₹3,105 |

---

## How It Works

```
1. View full company database (market cap, revenue, profit, open/close prices)
2. Enter ticker symbol to select a company
3. Initial purchase with ₹10,00,000 virtual balance
4. Price simulation — 5 new values generated using random walk [-10, +10]
5. 5 trading rounds: Buy more / Sell / Hold
6. Final liquidation — all shares sold, P&L calculated
```

**Price simulation logic:**
```c
loc_f_random_value = (((float)rand()/(float)RAND_MAX) * 21) - 10.0f;
new_price = current_price + random_value;  // floor at 1.0 to prevent negative prices
```

---

## Core Data Structure

```c
typedef struct {
    char          s_company_name[50];
    char          s_tick_symbol[15];
    unsigned long ul_outstanding_shares;
    double        f_market_capital;
    double        f_past_revenue;
    double        f_past_profit;
    float         f_prev_open_value;
    float         f_prev_close_value;
    float         f_purchase_value;
} company_info;
```

---

## Run It

```bash
gcc stock_market_trading_simulator.c -o simulator
./simulator
```

Requires GCC. No external dependencies.

---

## Sample Session

```
+------------------------+----------------------------------------+
|Company name            |Tata Motors Ltd                         |
|Ticker symbol           |TATAMOTORS                              |
|Market capital          |1510000000000.000                       |
|Previous closing value  |1417.950                                |
+------------------------+----------------------------------------+

Enter ticker symbol: TATAMOTORS
Available balance: 1000000.000

How many shares to purchase? 500

Number of shares holding: 500    Balance amount: 289025.000

+-----------------------------+
|Change in company share price|
+-----------------------------+
|1421.323                     |
|1415.891                     |
|1408.234                     |
|1419.567                     |
|1423.102                     |
+-----------------------------+
```

---

## What I Learned

- Struct-based data modeling in C for real financial entities
- Random walk price simulation (basis of Monte Carlo methods used in real quant finance)
- Input validation loops and error handling without exceptions
- Static memory management and scope control

---

## Author

**Anvitha N C** — Industrial Engineering & Management, BMSCE Bengaluru  
ncanvitha@gmail.com
