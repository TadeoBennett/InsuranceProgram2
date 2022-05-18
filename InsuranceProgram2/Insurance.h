#ifndef INSURANCE_H
#define INSURANCE_H


class Insurance
{
public:
    Insurance();
    Insurance(int id, float mpayment, int mpaid, int mlimit);

private:
    int insuranceid;
    float monthlypayment;
    int monthspaid;
    int monthlimit;

    float paymentremaining;
    bool enabled;

public:
    //setters
    void set_insuranceid(int id);
    void set_monthlypayment(float amount);
    void set_monthspaid(int num);
    void set_monthlimit(int num);

    void set_paymentremaining(float num);

    //getters
    int get_insuranceid();
    float get_monthlypayment();
    int get_monthspaid();
    int get_monthlimit();

    float get_paymentremaining();
    bool get_enabled();

    //other
    float addmonthspaid(float amount); //gets the amount paid by a customer, increments the monthspaid and returns the change.
    void resetInsurance();
    float renewInsurance(float amount);

    virtual void cast(){} //helps with dynamic cast
};

#endif // INSURANCE_H
