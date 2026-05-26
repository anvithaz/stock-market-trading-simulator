/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#ifndef __TRADE_SIMULATOR_H__
#define __TRADE_SIMULATOR_H__

#define NUMBER_OF_TRADING_DECISIONS 5

/* Information elements for a company */
typedef struct
{
    char            s_company_name[50];     /* Company name                 */
    char            s_tick_symbol[15];      /* Ticker symbol                */
    unsigned long   ul_outstanding_shares;  /* Number of outstanding shares */
    double          f_market_capital;       /* Market capital               */
    double          f_past_revenue;         /* Revenue                      */
    double          f_past_profit;          /* Profit                       */
    float           f_prev_open_value;      /* Previous open value          */
    float           f_prev_close_value;     /* Previous close value         */
    float           f_purchase_value;       /* Purchase value               */
}company_info;

/* Trading account balance */
static double stc_f_trading_acc_balance;

/* Shares holding */
static unsigned long stc_ul_shares_holding;

/* Index of selected company */
static int stc_i_company_ind;

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Print all the company information that has been stored in the database
 * 
 */
static void print_company_list(void);

/*
 * Input: Ticker symbol
 *
 * Output: Status of ticker symbol search in database
 * 
 * Description:
 * Check if the ticker symbol input by the user is found in the company database
 * 
 */
static int check_valid_tick_symbol(char *par_s_tick_symbol);

/*
 * Input: Number of shares to purchase
 *
 * Output: NA
 * 
 * Description:
 * Buy the number of shares specified and deduct the available funds accordingly
 */
static void buy_shares(unsigned long par_ul_shares_to_buy);

/*
 * Input: Number of shares to sell
 *
 * Output: NA
 * 
 * Description:
 * Sell the number of shares specified and credit the available funds accordingly
 */
static void sell_shares(unsigned long par_ul_shares_to_sell);

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Read the number of shares to purchase and buy them
 */
static void make_valid_purchase(void);

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Read the number of shares to sell and sell them
 */
static void make_valid_sale(void);

/*
 * Input: NA
 *
 * Output: An array with new purchase values
 * 
 * Description:
 * Generate five new purchase values using a random values in the range [-10, 10]
 * and adding that to the previous purchase values
 */
static void generate_new_purchase_values(double *par_a_purchase_values);

/*
 * Input: NA
 *
 * Output: NA
 * 
 * Description:
 * Update the purchase value after simulation
 */
static void simulate_new_share_prices(void);

#endif /* __TRADE_SIMULATOR_H__ */
#ifndef __COMPANY_DATABASE_H__
#define __COMPANY_DATABASE_H__

//#include "trade_simulator.h"

/* Multiple company informations useful for selecting to trade */
company_info database[] =
{
    /* Company 1 */
    {
        .s_company_name         = "Ford Motor Co",
        .s_tick_symbol          = "F",
        .ul_outstanding_shares  = 4000000000,
        .f_market_capital       = 48073000000,
        .f_past_revenue         = 158057000000,
        .f_past_profit          = -1981000000,
        .f_prev_open_value      = 11.98,
        .f_prev_close_value     = 12.06,
        .f_purchase_value       = 12.06
    },
    /* Company 2 */
    {
        .s_company_name         = "Tata Motors Ltd",
        .s_tick_symbol          = "TATAMOTORS",
        .ul_outstanding_shares  = 764866397,
        .f_market_capital       = 1510000000000,
        .f_past_revenue         = 2765766900,
        .f_past_profit          = 857534200,
        .f_prev_open_value      = 419,
        .f_prev_close_value     = 1417.95,
        .f_purchase_value       = 1417.95 
    },
    /* Company 3 */
    {
        .s_company_name         = "Mahindra And Mahindra Ltd",
        .s_tick_symbol          = "M&M",
        .ul_outstanding_shares  = 1240000000,
        .f_market_capital       = 1579000000000,
        .f_past_revenue         = 892570500,
        .f_past_profit          = 372780800,
        .f_prev_open_value      = 1263.70,
        .f_prev_close_value     = 1275.35,
        .f_purchase_value       = 1275.35
    },
    /* Company 4 */
    {
        .s_company_name         = "Maruti Suzuki India Ltd",
        .s_tick_symbol          = "MARUTI",
        .ul_outstanding_shares  = 302071492,
        .f_market_capital       = 2605000000000,
        .f_past_revenue         = 851688000,
        .f_past_profit          = 157375000,
        .f_prev_open_value      = 8650,
        .f_prev_close_value     = 8654,
        .f_purchase_value       = 8654
    },
    /* Company 5 */
    {
        .s_company_name         = "Eicher Motors Ltd",
        .s_tick_symbol          = "EICHERMOT",
        .ul_outstanding_shares  = 273473606,
        .f_market_capital       = 849420000000,
        .f_past_revenue         = 101270700,
        .f_past_profit          = 39728300,
        .f_prev_open_value      = 3132,
        .f_prev_close_value     = 3105,
        .f_purchase_value       = 3105
    }
};

static int s_i_database_size = (int)(sizeof(database) / sizeof(company_info));

#endif /* __COMPANY_DATABASE_H__ */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "trade_simulator.h"
//#include "company_database.h"

static void print_company_list(void)
{
    int loc_i_ind;

    printf("+------------------------+----------------------------------------+\n");
    for(loc_i_ind = 0; loc_i_ind < s_i_database_size; loc_i_ind++)
    {
        printf("|Company name            |%-40s|\n",   database[loc_i_ind].s_company_name);
        printf("|Ticker symbol           |%-40s|\n",   database[loc_i_ind].s_tick_symbol);
        printf("|Market capital          |%-40.3f|\n", database[loc_i_ind].f_market_capital);
        printf("|Outstanding shares      |%-40ld|\n",  database[loc_i_ind].ul_outstanding_shares);
        printf("|Last FY profit          |%-40.3f|\n", database[loc_i_ind].f_past_profit);
        printf("|Last FY revenue         |%-40.3f|\n", database[loc_i_ind].f_past_revenue);
        printf("|Previous opening value  |%-40.3f|\n", database[loc_i_ind].f_prev_open_value);
        printf("|Previous closing value  |%-40.3f|\n", database[loc_i_ind].f_prev_close_value);
        printf("+------------------------+----------------------------------------+\n");
    }

    return;
}

static int check_valid_tick_symbol(char *a_s_tick_symbol)
{
    int loc_i_check_status;
    int loc_i_index;

    loc_i_check_status = 1;

    for(loc_i_index = 0; loc_i_index < s_i_database_size; loc_i_index++)
    {
        loc_i_check_status = strcmp(database[loc_i_index].s_tick_symbol, &a_s_tick_symbol[0]);

        if(loc_i_check_status == 0)
        {
            stc_i_company_ind = loc_i_index;
            break;
        }
    }

    return loc_i_check_status;
}

static void buy_shares(unsigned long a_ul_shares_to_buy)
{
    /* Update the number of shares holding */
    stc_ul_shares_holding += a_ul_shares_to_buy;

    /* Update the balance amount in the trading account after the purchse */
    stc_f_trading_acc_balance = stc_f_trading_acc_balance - (a_ul_shares_to_buy * database[stc_i_company_ind].f_purchase_value);

    printf("\nNumber of shares holding: %ld\tBalance amount: %.3f\n\n", stc_ul_shares_holding, stc_f_trading_acc_balance);

    return;
}

static void sell_shares(unsigned long par_ul_shares_to_sell)
{
    /* Update the number of shares holding */
    stc_ul_shares_holding -= par_ul_shares_to_sell;

    /* Update the balance amount in the trading account after the sale */
    stc_f_trading_acc_balance = stc_f_trading_acc_balance + (par_ul_shares_to_sell * database[stc_i_company_ind].f_purchase_value);

    printf("\nNumber of shares holding: %ld\tBalance amount: %.3f\n\n", stc_ul_shares_holding, stc_f_trading_acc_balance);

    return;
}

static void make_valid_purchase(void)
{
    unsigned long   loc_ul_shares_to_buy;
    int             loc_i_valid_buy_flag;

    loc_ul_shares_to_buy    = 0;
    loc_i_valid_buy_flag    = 1;

    /* Read the number of shares to buy from the user, till a valid number of shares is input */
    do
    {
        printf("\nHow many shares to purchase?\n");
        scanf("%ld", &loc_ul_shares_to_buy);

        if ((database[stc_i_company_ind].f_purchase_value * loc_ul_shares_to_buy) <= stc_f_trading_acc_balance)
        {
            loc_i_valid_buy_flag = 0;
        }

        if(loc_i_valid_buy_flag != 0)
        {
            printf("ERR: Insufficient funds, please try again\n\n");
        }
    } while (loc_i_valid_buy_flag);

    /* Buy the number of shares and update the trading account balance */
    buy_shares(loc_ul_shares_to_buy);

    return;
}

static void make_valid_sale(void)
{
    unsigned long   loc_ul_shares_to_sell;
    int             loc_i_valid_sale_flag;

    loc_ul_shares_to_sell   = 0;
    loc_i_valid_sale_flag   = 1;

    /* Read the number of shares to sell from the user, till a valid number of shares is input */
    do
    {
        printf("\nHow many shares to sell?\n");
        scanf("%ld", &loc_ul_shares_to_sell);

        if (loc_ul_shares_to_sell <= stc_ul_shares_holding)
        {
            loc_i_valid_sale_flag = 0;
        }

        if (loc_i_valid_sale_flag != 0)
        {
            printf("ERR: Invalid number of shares to sell, you are not holding %ld number of shares\n\n", loc_ul_shares_to_sell);
        }
    } while (loc_i_valid_sale_flag);

    /* Sell the number of shares and update the trading account balance */
    sell_shares(loc_ul_shares_to_sell);

    return;
}

static void generate_new_purchase_values(double *a_a_purchase_values)
{
    int loc_i_loop;
    double loc_f_random_value;

    srand(time(0));

    for (loc_i_loop = 0; loc_i_loop < 5; loc_i_loop++)
    {
        loc_f_random_value = (((float)rand()/(float)RAND_MAX) * 21) - 10.0f;
        a_a_purchase_values[loc_i_loop] = database[stc_i_company_ind].f_purchase_value + loc_f_random_value;

        if (a_a_purchase_values[loc_i_loop] < 0)
        {
            a_a_purchase_values[loc_i_loop] = 1.0f;
        }
    }
}

static void simulate_new_share_prices(void)
{
    double          loc_a_purchase_values[5] = {0};
    int             loc_i_loop;

    loc_i_loop  = 0;

    /* Generate five new purchase values using random number generator */
    generate_new_purchase_values(loc_a_purchase_values);

    printf("+-----------------------------+\n");
    printf("|Change in company share price|\n");
    printf("+-----------------------------+\n");
    for (loc_i_loop = 0; loc_i_loop < 5; loc_i_loop++)
    {
        printf("|%-29.3f|\n", loc_a_purchase_values[loc_i_loop]);
    }
    printf("+-----------------------------+\n\n");

    /* Update the purchase value with the latest random number */
    database[stc_i_company_ind].f_purchase_value = loc_a_purchase_values[4];

    return;
}

int main(void)
{
    char    loc_s_tick_symbol[15] = "";
    int     loc_i_comp_select_flag;
    int     loc_i_trade_choice;
    int     loc_i_trade_count;
    int     loc_i_trade_invalid;

    loc_i_comp_select_flag  = 0;
    loc_i_trade_choice      = 0;
    loc_i_trade_count       = 0;
    loc_i_trade_invalid     = 0;

    /* Print the list of all companies available for trading */
    print_company_list();

    /* Setup a trading account with 1000000 as available amount */
    stc_f_trading_acc_balance = 1000000;

    /* Read the ticker symbol input from the user, till a valid ticker symbol is input */
    do
    {
        printf("Enter the ticker symbol of the company to trade (in uppercase, as shown in the table above): ");
        scanf("%[^\n]%*c", &loc_s_tick_symbol[0]);
        printf("%s\n", loc_s_tick_symbol);

        loc_i_comp_select_flag = check_valid_tick_symbol(&loc_s_tick_symbol[0]);

        if(loc_i_comp_select_flag != 0)
        {
            printf("ERR: Invalid ticker symbol, please try again\n\n");
        }
    } while (loc_i_comp_select_flag);
    
    /* Print the available balance in the trading account */
    printf("\nAvailable balance for purchasing is: %.3f\n\n", stc_f_trading_acc_balance);

    make_valid_purchase();

    simulate_new_share_prices();

    printf("The new purchase value of \"%s\" is: %.3f\n", database[stc_i_company_ind].s_company_name, database[stc_i_company_ind].f_purchase_value);
    printf("The number of shares holding is: %ld\n", stc_ul_shares_holding);
    printf("The current trading account balance is: %.3f\n\n", stc_f_trading_acc_balance);

    do
    {
        printf("\nNumber of trade decisions pending: %d\n", (NUMBER_OF_TRADING_DECISIONS - loc_i_trade_count));
        printf("Make a choice from the following options:\n");
        printf("1. Buy more shares\n");
        printf("2. Sell shares\n");
        printf("3. Keep the shares\n");
        scanf("%d", &loc_i_trade_choice);

        switch(loc_i_trade_choice)
        {
            case 1:
                make_valid_purchase();
                break;

            case 2:
                make_valid_sale();
                break;

            case 3:
                break;
            
            default:
                printf("ERR: Invalid trade choice\n\n");
                loc_i_trade_invalid = 1;
                break;
        }

        if (loc_i_trade_invalid)
        {
            loc_i_trade_invalid = 0;

            continue;
        }

        loc_i_trade_invalid = 0;

        if (loc_i_trade_count != NUMBER_OF_TRADING_DECISIONS - 1)
        {
            simulate_new_share_prices();

            printf("The new purchase value of \"%s\" is: %.3f\n", database[stc_i_company_ind].s_company_name, database[stc_i_company_ind].f_purchase_value);
            printf("The number of shares holding is: %ld\n", stc_ul_shares_holding);
            printf("The current trading account balance is: %.3f\n\n", stc_f_trading_acc_balance);
        }

        loc_i_trade_count++;
    } while (loc_i_trade_count < NUMBER_OF_TRADING_DECISIONS);

    printf("Trading decisions complete. Selling all shares...\n");

    /* Sell all the shares holding and update the trading account balance */
    sell_shares(stc_ul_shares_holding);

    return 0;
}