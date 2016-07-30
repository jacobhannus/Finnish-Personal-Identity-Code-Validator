#include <stdio.h>

int main()
{
    char pic[12];
    char ctrl[32] = {'0','1','2','3','4','5','6','7','8','9',
                     'A','B','C','D','E','F',
                     'H',
                     'J','K','L','M','N',
                     'P',
                     'R','S','T','U','V','W','X','Y'};

    /* boolean switches */
    int chkLen;
    int chkNum;
    int chkSign;
    int chkMonth;
    int chkID;
    int chkDate;
    int chkSum;
    int chkTemp;
    int chkFemale;

    /* check-specific vars */
    int i;
    int month, year, leapYear, date;
    int sum;

    printf("Enter a Finnish Personal Identity Code: ");
    scanf(" %s", pic);

    /* check that pic has 11 characters */
    for(i = 0; pic[i] != '\0'; i++)
        ;
    chkLen = (i == 11) ? 1 : 0;


    /* check that elements 0-5 and 7-9 are numbers */
    chkNum = 1;
    for(i = 0; i < 6; i++){
        if(pic[i] < '0' || pic[i] > '9')
            chkNum = 0;
    }
    for(i = 7; i < 10; i++){
        if(pic[i] < '0' || pic[i] > '9')
            chkNum = 0;
    }

    /* check that element 6 is either '+', '-', or 'A' */
    chkSign = (pic[6] == '+' || pic[6] == '-' || pic[6] == 'A') ? 1 : 0;

    /* check that the month is between 01 and 12 */
    chkMonth = ((1 <= (pic[3] - '0') + (pic[2] - '0') * 10) &&
                ((pic[3] - '0') + (pic[2] - '0') * 10 <= 12)) ? 1 : 0;

    /* check that the individual number is at least 2 */
    chkID = (2 <= (pic[9] - '0') + (pic[8] - '0') * 10 + (pic[7] - '0') * 100) ? 1 : 0;

    /* check that date is within the bounds */
    month = pic[3] - '0' + (pic[2] - '0') * 10;
    date = pic[1] - '0' + (pic[0] - '0') * 10;

    if(pic[6] == '+')
        year = 1800 + (pic[5] - '0') + (pic[4] - '0') * 10;
    else if(pic[6] == '-')
        year = 1900 + (pic[5] - '0') + (pic[4] - '0') * 10;
    else
        year = 2000 + (pic[5] - '0') + (pic[4] - '0') * 10;

    if(!(year % 4) && year % 100)
        leapYear = 1;
    else if(!(year % 400))
        leapYear = 1;
    else
        leapYear = 0;

    if(month == 2){
        if(leapYear)
            chkDate = (date <= 29) ? 1 : 0;
        else
            chkDate = (date <= 28) ? 1 : 0;
    }else if(month == 4 || month == 6 || month == 9 || month == 11){
        chkDate = (date <= 30) ? 1 : 0;
    }else{
        chkDate = (date <= 31) ? 1 : 0;
    }

    /* check the control character */
    sum = pic[9] - '0' + (pic[8] - '0') * 10 + (pic[7] - '0') * 100 +
         (pic[5] - '0') * 1000 + (pic[4] - '0') * 10000 + (pic[3] - '0') * 100000 +
         (pic[2] - '0') * 1000000 + (pic[1] - '0') * 10000000 + (pic[0] - '0') * 100000000;
    chkSum = (ctrl[sum % 31] == pic[10]) ? 1 : 0;

    /* check if the Personal Identity Code is temporary */
    chkTemp = ((pic[9] - '0') + (pic[8] - '0') * 10 + (pic[7] - '0') * 100 >= 900) ? 1 : 0;

    /* check if the person is male or female */
    chkFemale = (!((pic[9] - '0') % 2) || pic[9] == '0') ? 1 : 0;



    if(chkLen &&
    chkNum &&
    chkSign &&
    chkMonth &&
    chkID &&
    chkDate &&
    chkSum){

        puts("This Personal Identity Code is valid.");
        if(chkTemp)
            puts("It is a temporary Personal Identity Code.");
        if(chkFemale)
            puts("The person is female.");
        else
            puts("The person is male.");
    }else{
        puts("This Personal Identity Code is INVALID.");
    }


    return 0;
}



