/********************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Sehra Elahi
Date: 25/10/2017

*********************************************************************/
/* This program is written to calculate and display certain aspects of bill calculations (e.g. tax, profit, average consumption etc) for the water consumption of two different consumers; Domestic and Commercial */

#include <stdio.h>
#include <math.h>

int main ()
{
  int x, Customer, Consumption, band_1, band_2, band_3, band_4, band_5, Total_consumption, Total_customer1=0, Total_customer2=0, Domestic_customer=0;
  float bill, waste_water, fixed_fee, fixed_charge, Total_bill, VAT, Total_Revenue, Total_domestic_bill, Total_commercial_bill, Total_cost, Profit, Income_tax, Av_dom_bill, Max=0;
  //the loop
  while (1)
  {
//===========================================================================================================================================================
//The menu for choosing options regarding the bill and also quitting the program:

    printf ("\n****** Please select from the following options ******\n");
    printf ("\n1. Compute and Print the Bill for a Customer.");
    printf ("\n2. Show Sums and Statistics.");
    printf ("\n3. Quit the program.\n");
    printf ("Pick your option:\n");
    scanf ("%i", &x);
//===========================================================================================================================================================
// After selecting option 1 from the menu, the Customer chooses from its Consumer type; 1 Domestic or 2 Commercial, again choosing a number.

  if (x==1)
    {
      printf ("\n****** Please choose from the Customer type ******\n\n1. Domestic \n2. Commercial\n");
      printf ("Pick your option:\n");
      scanf ("%i", &Customer);
//===========================================================================================================================================================
// This part is for after the Consumer has chosen option 1 (Domestic), where customer==1 is the Domestic option.
  if (Customer==1)
      {
        printf ("\nPlease state your water Consumption (in m^3?):\n");
        scanf ("%i", &Consumption);
        // The calculation will be done after the consumer inserts the value in m^3 and the bill gets displayed.
        printf ("\n****** YOUR BILL ******\n");
        Total_customer1 += Consumption;
        //Where Total_customer1 is the total water consumption for domestic users, this part is defined for option 2 SUMS AND STATS.
        //I have also defined the bands in this section from 1-5, which will determine the fresh water charges.
        band_1 = (Consumption <=5);
        band_2 = (Consumption <=12);
        band_3 = (Consumption <=25);
        band_4 = (Consumption <=40);
        band_5 = (Consumption >40);

        if (band_1)
        {
         bill = Consumption * 0.20;
         printf("\nFresh Water Charge: £%0.2f", bill );
        }

        else if (band_2)
        {
         bill = (5 * 0.20) + ((Consumption - 5) * 0.35);
         printf("\nFresh Water Charge: £%0.2f", bill);
        }

        else if (band_3)
        {
         bill = (5 * 0.20) + (7 * 0.35) + ((Consumption - 12) * 0.5);
         printf("\nFresh Water Charge: £%0.2f", bill );
        }

        else if (band_4)
        {
         bill = (5 * 0.20) + (7 * 0.35) + (13 * 0.5) + ((Consumption - 25) * 0.75);
         printf("\nFresh Water Charge: £%0.2f", bill );
        }

        else if (band_5)
        {
         bill = (5 * 0.20) + (7 * 0.35) + (13 * 0.5) + (15 * 0.75) + ((Consumption - 40) * 2.5);
         printf("\nFresh Water Charge: £%0.2f", bill );
        }

        else
        {
          printf(" ");
        }
          // The additional charges, which will then add up and print 'Total bill' by combining all of the charges for domestic user are as followed:
          waste_water = ((Consumption * 0.95) * 0.25);
          printf("\nWaste Water Charge: £%0.2f", waste_water);
          fixed_fee = 10;
          printf("\nSurface Water Charge: £%0.2f", fixed_fee);
          fixed_charge = (91 * 0.10);
          printf("\nStanding Charge: £%0.2f", fixed_charge);
          Total_bill = bill + waste_water + fixed_charge + fixed_fee;
          printf ("\nTOTAL BILL: £%0.2f\n\n", Total_bill);
          Total_domestic_bill += Total_bill;
          // ^This is done for option 2 (sums and stats --> Total_Revenue).
          Domestic_customer += 1;
          // ^ For option 2 (sums and stats --> Av_dom_bill).
          if (Total_bill>Max)
        {
          Max = Total_bill;
          // ^This is to calculate 'maximum domestic bill' for when selecting option 2 (sums and stats).
        }
      }

    if (Customer==2)
    //This is for when the Consumer picks option 2, where Customer==2 is the Commercial option.
    //Furthermore the bill calculation for commercial will be printed and VAT is also included since its commercial.

          {
            printf ("\nPlease state your water consumption in m^3?:\n");
            scanf ("%i", &Consumption);
            // The calculation will be done after the consumer inserts the value in m^3 and the bill gets displayed.
            printf ("\n****** YOUR BILL ******\n");
            Total_customer2 += Consumption;
            //^ Total_customer2 refers to the total water consumption for Commercial users, This part will be used for option 2 SUMS AND STATS.
            //Commercial consumption is above 40, hence band 5:
            band_5 = (Consumption >40);
            bill = Consumption * 2.5;
            //It is (* 2.5) since its in band 5
            printf ("\nFresh Water Charge: £%0.2f", bill);
            waste_water = ((Consumption * 0.95) * 2);
            printf("\nWaste Water Charge: £%0.2f", waste_water);
            fixed_fee = 50;
            printf("\nSurface Water Charge: £%0.2f", fixed_fee);
            fixed_charge = (91 * 1.30);
            printf("\nStanding Charge: £%0.2f", fixed_charge);
            Total_bill = bill + waste_water + fixed_charge + fixed_fee;
            // VAT is included since commercial:
            VAT = Total_bill * 0.2;
            printf("\nAmount of VAT: £%0.2f", VAT);
            printf ("\nTOTAL BILL: £%0.2f\n\n", Total_bill+ VAT);
            Total_commercial_bill += Total_bill;
            // ^This part is for the Total_Revenue calculation for option 2 SUMS AND STATS, to exclude VAT
          }
    }
//===========================================================================================================================================================
// This part is for the SUMS AND STATS (x==2 is SUMS AND STATS) for when the user selects option 2 from the main menu.
  else if (x==2)
      {
       Total_consumption = Total_customer1 + Total_customer2;
       // ^ Adding the separate consumptions of both Domestic (Total_customer1) and commercial (Total_customer2)
       printf ("\n****** SUMS AND STATISTICS ******\n");
       printf ("\nTotal Fresh Water Consumption: %i", Total_consumption);
       printf ("\nTotal Fresh Water Consumed by Domestic users: %i", Total_customer1);
       Total_Revenue = Total_domestic_bill + Total_commercial_bill;
       //Revenue is without VAT, hence we use Total_commercial_bill
       printf("\nTotal Revenue: £%0.2f", Total_Revenue);
       Total_cost = Total_consumption * 1;
       printf("\nTotal Cost: £%0.2f", Total_cost);
       Profit = Total_Revenue - Total_cost;
       printf("\nProfit: £%0.2f", Profit);
       Income_tax = Profit * 0.25;
       // ^Tax is taken from the profit..such injustice! :(
       printf("\nIncome Tax: £%0.2f", Income_tax);
       Av_dom_bill = Total_domestic_bill/Domestic_customer;
       printf("\nAverage Domestic Bill: £%0.2f", Av_dom_bill);
       printf("\nMaximum Domestic Bill: £%0.2f\n", Max);
      }
//===========================================================================================================================================================
//option for quitting the program!
  else if (x==3)
      {
       printf ("\nThank you for using our service and have a nice day!\n");
       break;
      }
  }
    return 0;
}
//===========================================================================================================================================================
