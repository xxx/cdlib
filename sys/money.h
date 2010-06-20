/*
 * /sys/money.h
 *
 * This file defines some macros that are usefull for handling money.
 */

#ifndef MONEY_DEFINITIONS
#define MONEY_DEFINITIONS

/*
 * Documentation for functions can be found in this file:
 */
#define MONEY_FN ("/sys/global/money.c")

/*
 * MONEY_COINS return an array with the number of coins for each type.
 * The array is ({ cc, sc, gc, pc })
 */
#define MONEY_COINS(ob)        ((int *)MONEY_FN->what_coins(ob))

/*
 * MONEY_SPLIT returns an array with the minimum number of coins that is
 * needed to make the total sum of cp coppers. The returned array is of
 * form ({ cc, sc, gc, pc })
 */
#define MONEY_SPLIT(cp)        ((int *)MONEY_FN->split_values(cp))

/*
 * MONEY_MERGE returns the combined value of the coins in the carr. The
 * array should be ({ cc, sc, gc, pc })
 */
#define MONEY_MERGE(carr)      ((int)MONEY_FN->merge_values(carr))

/*
 * TOTAL_MONEY returns the total value of all coins carried by (or in) who.
 */
#define TOTAL_MONEY(who)       ((int)MONEY_FN->total_money(who))

/*
 * MONEY_MAKE does what we've always wanted. It creates money and returns
 * the objectpointer. Use MONEY_MAKE_CC and such to create money of a
 * specific type.
 */
#define MONEY_MAKE(num, ctype) ((object)MONEY_FN->make_coins(ctype, num))

/*
 * MONEY_MAKE_HERE does the same beautiful thing as MONEY_MAKE and also
 * delivers it to the inventory of the calling object. Use MONEY_MAKE_HERE_CC
 * and such to create money of a specific type.
 */
#define MONEY_MAKE_HERE(num, ctype) \
    MONEY_MAKE((num), (ctype))->move(this_object(), 1)

/*
 * MONEY_MOVE moves a certain amount of coins from 'from' to 'to'. You
 * can move s particular type of coins with MONEY_MOVE_CC and such.
 *
 * Returns: -1 - money (type) not found
 *           0 - money moved
 *          >1 - an error generated by the move-function in /std/object
 */
#define MONEY_MOVE(num, ctype, from, to) \
    ((int)MONEY_FN->move_coins(ctype, num, from, to))

/*
 * MONEY_MOVE_COIN_TYPES moves a specified number of each coin type from
 * 'from' to 'to'. The coin array 'carr' should match MONEY_TYPES. The
 * result will be identical to MOVE_MONEY.
 *
 * Returns: -1 - money (type) not found
 *           0 - money moved
 *          >1 - an error generated by the move-function in /std/object
 */
#define MONEY_MOVE_COIN_TYPES(carr, from, to) \
    ((int)MONEY_FN->move_cointypes(carr, from, to))

/*
 * MONEY_ADD will add 'amount' of money to 'who' in the largest
 * denominations possible. If amount < 0 money will be taken in the
 * smallest denominations possible.
 *
 * Returns:
 * amount >= 0: always 1
 * amount <  0: 1 - the money was removed
 *              0 - not enough money to remove 'amount' (nothing is taken)
 */
#define MONEY_ADD(who, amount) ((int)MONEY_FN->add_money(who, amount))

/*
 * MONEY_TEXT will return a string describing the money in the array.
 * MONEY_TEXT_NUM will return the same, but using numerical values.
 *
 * MONEY_COL_TEXT will return a string in columns using the short code
 * for each coin and two digits per number.
 * MONEY_WCOL_TEXT will do the same, but with an arbitrary column width.
 * The array must be ({ cc, sc, gc, pc })
 */
#define MONEY_TEXT(arr)     ((string)MONEY_FN->money_text(arr))
#define MONEY_TEXT_NUM(arr) ((string)MONEY_FN->money_text((arr), 1))
#define MONEY_COL_TEXT(arr) ((string)MONEY_FN->money_col_text(arr, 2))
#define MONEY_WCOL_TEXT(arr, width) ((string)MONEY_FN->money_col_text(arr, width))

/*
 * MONEY_TEXT_SPLIT returns a string describing the value of the coins
 * in the smallest denomination.
 * MONEY_TEXT_NUM_SPLIT returns the same, but using numerical values.
 */
#define MONEY_TEXT_SPLIT(cc)     MONEY_TEXT(MONEY_SPLIT(cc))
#define MONEY_TEXT_NUM_SPLIT(cc) MONEY_TEXT_NUM(MONEY_SPLIT(cc))

/* 
 * MONEY_UNIQUE_NAME(ct) returns the value for the HEAP_S_UNIQUE_ID property
 * added to coins of the coin type ct.
 */
#define MONEY_UNIQUE_NAME(ct)  ("_coin_" + (ct))

/*
 * MONEY_EXPAND(obj) and MONEY_CONDENSE(obj) allow to respectively the
 * expansion of a money-property to real coins and the condensation of the
 * real coins to a money-property: OBJ_M_HAS_MONEY
 */
#define MONEY_CONDENSE(obj) MONEY_FN->money_condense(obj)
#define MONEY_EXPAND(obj)   MONEY_FN->money_expand(obj)

/*
 * MONEY_PARSE(str) parses a string and returns an array of integers of the
 * form ({ cc, sc, gc, pc }).  Each element indicates how many coins of that
 * type were specified by the parsed string.  A -1 value for any coin type
 * means that all coins of that type are to be used.  If 0 is returned,
 * the string could not be parsed.
 *
 * For example, MONEY_PARSE("all silver coins and 3 gold coins") would
 * return ({ 0, -1, 3, 0 }) (no copper coins, all silver coins, 3 gold coins,
 * and no platinum coins).
 */
#define MONEY_PARSE(str) MONEY_FN->parse_coins(str)

/*
 * MONEY_PARSE_OB(str, ob) parses a string and returns an array of integers
 * of the form ({ cc, sc, gc, pc }).  Each element indicates how many coins
 * of that type were specified by the parsed string.  Unlike MONEY_PARSE, -1
 * is not returned if all coins of a particular type are specified.  Instead,
 * the object ob is searched for coins of that type, and the exact number of
 * coins is used.  If 0 is returned, the string could not be parsed.
 *
 * For example, 
 * MONEY_PARSE_OB("all silver coins and 3 gold coins", this_player()) would
 * return ({ 0, 20, 3, 0 }) (no copper coins, 20 silver coins, 3 gold coins,
 * and no platinum coins), assuming this_player() possesses 20 silver coins.
 */
#define MONEY_PARSE_OB(str, ob) MONEY_FN->parse_coins(str, ob)

/* We include the file keeping the mud-specific coin types. */
#include "/config/sys/money2.h"

/* No new definitions beyond this line. */
#endif MONEY_DEFINITIONS