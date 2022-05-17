#include "Insurance.h"

Insurance::Insurance()
{

}

Insurance::Insurance(int id, float mpayment, int mpaid, int mlimit):
    insuranceid(id), monthlypayment(mpayment), monthspaid(mpaid), monthlimit(mlimit)
{}

void Insurance::set_insuranceid(int id)
{ insuranceid = id; }

void Insurance::set_monthlypayment(float amount)
{ monthlypayment = amount; }

void Insurance::set_monthspaid(int num)
{ monthspaid = num; }

void Insurance::set_monthlimit(int num)
{ monthlimit = num; }

void Insurance::set_paymentremaining(float num)
{ paymentremaining = num; }

//-----------------------------------------------------------------------------------

int Insurance::get_insuranceid()
{ return insuranceid; }

float Insurance::get_monthlypayment()
{ return monthlypayment; }

int Insurance::get_monthspaid()
{ return monthspaid; }

int Insurance::get_monthlimit()
{ return monthlimit; }

float Insurance::get_paymentremaining()
{ return paymentremaining; }

//-----------------------------------------------------------------------------------

float Insurance::addmonthspaid(float amount)
{
    int months = amount/monthlypayment; //get the number of valid payments that can be paid with the amount
    monthspaid += months; //increment the monthspaid

    return (amount - (months * monthlypayment)); //returns the change for the user
}

void Insurance::resetInsurance()
{ monthspaid = 0; }

float Insurance::renewInsurance(float amount)
{
    //first check if the customer has an overpaid balance
    paymentremaining = (monthlimit - monthspaid) * monthlypayment;

    if(paymentremaining == 0){ //the customer has paid for all months already
        resetInsurance();
        addmonthspaid(amount); //deal with the payment given by the customer for a new set of months
    }

    if(paymentremaining < 0){ //the customer had previously overpaid some months
        resetInsurance();
        addmonthspaid(amount); //deal with the payment given by the customer for a new set of months
        return -1 * paymentremaining; //returns the change
    }

    if(paymentremaining > 0){
        addmonthspaid(amount);
    }

    return 0; //returns 0 if months paid was incremented; returns positive number if change was needed to be given
}
