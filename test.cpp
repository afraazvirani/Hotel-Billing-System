// ============================================================
// Name    : Afraaz Virani
// Course  : COSC 1437 — Programming Fundamentals II
// Date    : 6/8/26
// Program : Chapter 4 Major Project
// Option  : A — Hotel Billing
// Purpose : Creates a hotel billing system that offering discounts, and generatung a relevant billing receipt.
// ============================================================


// ===== Section 1 — Pseudocode Design Block =====


// ===== Program Start =====

#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>
#include <cassert>
#include <cmath>
#include <fstream>
 
using namespace std;
 
int main()
{
    const double MIN_NIGHTLY_RATE = 0.0;
    const int MIN_ROOMS = 0;
    const int MIN_NIGHTS = 0;
    const double MIN_SALES_TAX_RATE = 0.0;
    const double NO_DISCOUNT = 0.0;
    const double DISCOUNT_TIER_ONE = 10.0;
    const double DISCOUNT_TIER_TWO = 20.0;
    const double DISCOUNT_TIER_THREE = 30.0;
    const double LOYALTY_DISCOUNT = 5.0;
    const int MIN_ROOMS_TIER_ONE = 10;
    const int MIN_ROOMS_TIER_TWO = 20;
    const int MIN_ROOMS_TIER_THREE = 30;
    const int MIN_NIGHTS_LOYALTY = 3;
    const double EPSILON = 0.01;


    // ===== Section 2 — Input & Validation =====

    double nightlyRate;
    int roomsBooked;
    int nightsStayed;
    double salesTaxRate;

    cout << "Enter nightly rate per room: ";
    cin >> nightlyRate;

    assert(nightlyRate > MIN_NIGHTLY_RATE);
    // this assert makes sure the nightly rate is greater than zero
    // at runtime, if the user enters zero or a negative value, the program will stop.

    cout << "Enter number of rooms booked: ";
    cin >> roomsBooked;

    assert(roomsBooked > MIN_ROOMS);
    // this assert makes sure the amount of rooms booked is greater than zero
    // at runtime, if the user enters zero or a negative value, the program will stop.
    
    cout << "Enter number of nights: ";
    cin >> nightsStayed;

    assert(nightsStayed > MIN_NIGHTS);
    // this assert makes sure the amount of nights stayed is greater than zero
    // at runtime, if the user enters zero or a negative value, the program will stop.

    cout << "Enter sales tax rate as a percentage: ";
    cin >> salesTaxRate;

    assert(salesTaxRate >= MIN_SALES_TAX_RATE);
    // this assert makes sure the sales text is not negative
    // at runtime, if the user enters a negative value, the program will stop.

    
    
    // ===== Section 3 — Operator Precedence Reference =====
    
    
    /*
    Precedence Table

    Precedence     Operator(s)     Category         Associativity

    1 (highest)    !               Logical NOT      Right-to-left
    2              *, /, %         Multiplicative   Left-to-right
    3              +, -            Additive         Left-to-right
    4              <, <=, >, >=    Relational       Left-to-right
    5              ==, !=          Equality         Left-to-right
    6              &&              Logical AND      Left-to-right
    7              ||              Logical OR       Left-to-right      
    
    
    Step by Step Evaluation
    
    Expression:
    !(rooms > 0) || (rate >= 50.0 && rooms != nights)

    Sample Values:
    roomsBooked = 12
    nightlyRate = 120.0
    nightsStayed = 3

    Evaluation:
    !(12 > 0)  ||  (120.0 >= 50.0 && 12 != 3)
    !(TRUE)    ||  (TRUE && TRUE)
    FALSE      ||  TRUE
    TRUE

    Final Result:
    This expression evaluates to TRUE.
    */

    // ===== Section 4 — Core Logic =====
    double roomDiscountPercent;
    double loyaltyDiscountPercent;
    double originalSubtotal;
    double roomDiscountAmount;
    double subtotalAfterRoomDiscount;
    double loyaltyDiscountAmount;
    double subtotalBeforeTax;
    double totalDiscountPercent;
    int discounTier;
    double salesTaxAmount;
    double subtotal;


    // checking the group discount the customer will qualify (30%,20%,10%) based on the amount of rooms booked. 
    if (roomsBooked >= MIN_ROOMS_TIER_THREE)             // Section 6: >= relational operator was used.
    {
        roomDiscountPercent = DISCOUNT_TIER_THREE;
        discounTier = 3;
    }
    else if (roomsBooked >= MIN_ROOMS_TIER_TWO)
    {
        roomDiscountPercent = DISCOUNT_TIER_TWO;
        discounTier = 2;
    }
    else if (roomsBooked >= MIN_ROOMS_TIER_ONE)
    {
        roomDiscountPercent = DISCOUNT_TIER_ONE;
        discounTier = 1;
    }
    else
    {
        roomDiscountPercent = NO_DISCOUNT;
        discounTier = 0;
    }

    // checking whether the customer has atleast three nights AND atleast one room booked to apply the 5% discount.
    if (nightsStayed >= MIN_NIGHTS_LOYALTY && roomsBooked > MIN_ROOMS)       // Section 6: > relational operator was used AND && logical operator was used.
    {
        loyaltyDiscountPercent = LOYALTY_DISCOUNT;
    }
    else
    {
        loyaltyDiscountPercent = NO_DISCOUNT;
    }

    originalSubtotal = nightlyRate * roomsBooked * nightsStayed;
    roomDiscountAmount = originalSubtotal * (roomDiscountPercent / 100);
    subtotalAfterRoomDiscount = originalSubtotal - roomDiscountAmount;
    loyaltyDiscountAmount = subtotalAfterRoomDiscount * (loyaltyDiscountAmount / 100);
    subtotalBeforeTax = subtotalAfterRoomDiscount - loyaltyDiscountAmount;
    
    totalDiscountPercent = roomDiscountPercent + loyaltyDiscountPercent;
    salesTaxAmount = subtotalBeforeTax * (salesTaxRate / 100);
    subtotal = subtotalBeforeTax + salesTaxAmount;


    // ===== Section 5 — Switch Statement =====
    cout << endl;
    cout << "Discount Tier Information" << endl;

    switch (discounTier)
    {
    case 0:
        cout << "Tier 0: No room discount" << endl;
        cout << "Explanation: Fewer than " << MIN_ROOMS_TIER_ONE << " were booked." << endl;
        break;
    
    case 1:
        cout << "Tier 1: 10% room discount" << endl;
        cout << "Explanation: The customer booked atleast " << MIN_ROOMS_TIER_ONE << " rooms." << endl;
        break;
    
    case 2:
        cout << "Tier 2: 20% room discount" << endl;
        cout << "Explanation: The customer booked atleast " << MIN_ROOMS_TIER_TWO << " rooms." << endl;
        break;
    
    case 3:
        cout << "Tier 3: 30% room discount" << endl;
        cout << "Explanation: The customer booked atleast " << MIN_ROOMS_TIER_THREE << " rooms." << endl;
        break;
    
    default:
        cout << "Tier: Unknown discount tier" << endl;
        cout << "Explanation: Discount Tier could not be determined." << endl;
        break;
    }


    // ===== Section 6 — Relational & Logical Operator Showcase =====

    if (nightlyRate < MIN_NIGHTLY_RATE)  // < relational operator was used
    {
        cout << "Error: Nightly Rate is below the allowed minimum." << endl;
    }

    if (nightsStayed == MIN_NIGHTS)     // == relational operator was used
    {
        cout << "Error: Nights stayed must be greater than zero." << endl;
    }

    if (roomsBooked <= MIN_ROOMS)       // <= relational operator was used
    {
        cout << "Error: Rooms booked must be greater than zero." << endl;
    }

    if (nightlyRate < MIN_NIGHTLY_RATE || salesTaxRate < MIN_SALES_TAX_RATE)      // || operational operator was used
    {
        cout << "Error: One of the money related inputs are invalid." << endl;
    }

    if (!(subtotalBeforeTax >= 0.0))        // ! operational operator was used
    {
        cout << "Error: Subtotal is not valid for billing." << endl;
    }

    // ===== Section 7 — Floating-Point Bug Guard =====

    /*
    Floating-Point Equality Warning

    Why == is unreliable for floating-point comparison:
    Using == with floating-point values can be unreliable as decimals may be stored with
    tiny rounding errors in memory.

    What technique you used instead (epsilon comparison, tolerance band, or restructured logic):
    Instead of checking whether two money values are exactly equal, this program uses an epsilon comparison. 
    EPSILON is set to 0.01 because this program works with money, and one cent is a reasonable tolerance for billing output.

    The specific epsilon or tolerance value you chose and why:
    The condition below checks whether the calculated subtotal is close enough to zero without comparing subtotalBeforeTax == 0.0.
    */

    if (abs(subtotalBeforeTax - NO_DISCOUNT) < EPSILON)
    {
        cout << "Floating-Point Check: Subtotal is close to zero." << endl;
    }

    // ===== Section 8 — Formatted Output / Receipt =====
    cout << endl;
    cout << fixed << setprecision(2);

    cout << endl;
    cout << right << setw(30) << "HOTEL BILLING RECEIPT" << endl;
    cout << endl;

    cout << left << setw(28) << "Nightly Rate:" << right << "$" << setw(9) << nightlyRate << endl;

    cout << left << setw(28) << "Room Discount Applied:" << right << setw(9) << roomDiscountPercent << "%" << endl;

    cout << left << setw(28) << "Loyalty Discount Applied:" << right << setw(9) << loyaltyDiscountPercent << "%" << endl;

    cout << left << setw(28) << "Number of rooms booked:" << right << setw(10) << roomsBooked << endl;

    cout << left << setw(28) << "Number of nights booked:" << right << setw(10) << nightsStayed << endl;

    cout << "---------------------------------------" << endl;

    cout << left << setw(28) << "Subtotal before Tax:" << right << "$" << setw(9) << subtotalBeforeTax << endl;

    cout << left << setw(28) << "Sales Tax Amount:" << right << "$" << setw(9) << salesTaxAmount << endl;

    cout << left << setw(28) << "Total Due:" << right << "$" << setw(9) << subtotal << endl;

    cout << "---------------------------------------" << endl;


    // ===== Section 9 — Known Bug Risks =====
    /*
    1. Dangling else:
    I prevented this by using braces with every if, else if, and else statements.
    This makes it more clear which else belongs to which if statement.

    2. Wrong discount order:
    The loyalty discount must be applied after the room discount, not directly to the original subtotal.
    To prevent this I first calculated subtotalAfterRoomDiscount and then applied the loyalty discount to that amount.
    
    3. Invalid Input:
    Values such as 0 rooms, 0 nights, a negative nightly rate, etc, would make the final bill invalid.
    I prevented this by using assert() checks immediately after reading each input.
    */

    return 0;
}