#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cctype>
#include <cmath>

const short DEFINE_HAND_SIZE_IS_5 = 5;

using namespace std;

short convertStringToValue(string value)
{
    if(value == "2")
    {
        return 2;
    }
    else if(value == "3")
    {
        return 3;
    }
    else if(value == "4")
    {
        return 4;
    }
    else if(value == "5")
    {
        return 5;
    }
    else if(value == "6")
    {
        return 6;
    }
    else if(value == "7")
    {
        return 7;
    }
    else if(value == "8")
    {
        return 8;
    }
    else if(value == "9")
    {
        return 9;
    }
    else if(value == "10")
    {
        return 10;
    }
    else if((value == "q") || (value == "Q"))
    {
        return 11;
    }
    else if((value == "j") || (value == "J"))
    {
        return 12;
    }
    else if((value == "k") || (value == "K"))
    {
        return 13;
    }
    else if ((value == "a") || (value == "A"))
    {
        return 14;
    }
    else{
        return 0;
    }
}

void convertArray(string value_str[], short value[])
{
    for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        value[i] = convertStringToValue(value_str[i]);
    }
    return;
}


bool sameSuitCheck(string suit[])
{
    string test[5];
    
    for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        test[i]=suit[i];
    }
    for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        
        if(test[1] != suit[i])
        {
            return false;
        }
    }
    return true;
}

bool RoyalFlushHandCheck(short value[])
{
    short testValue[5]={10,11,12,13,14};
    for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        if(value[i]==testValue[i])
        {
            return true;
        }
    }
    return false;
}

bool StraightHandCheck(short value[])
{
    short min = value[0];
    for(short i = 1; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        if(value[i] < min)
        {
            min = value[i];
        }
    }

    short next = min + 1;
    short i = 0;
    while(i < DEFINE_HAND_SIZE_IS_5)
    {
        if(value[i] == next)
        {
            next++;
            i=0;
        }
        else
        {
            i++;
        }
    }

    //The while loop above will set "next" equal to 5 more than "min" if there is a StraightHandCheck
    if(next == (min+5))
    {
        return true;
    }
    else
    {
        return false;
    }
}
void PairHandCounter(short value[], short pairCounterArray[], short& size)
{
    short k = 0;
    short count;
    bool caught[] = {false, false, false, false, false};
    for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
    {
        if(!caught[i])
        {
            size++;
            caught[i] = true;
            count = 1;
            for(short j = 1;  j < DEFINE_HAND_SIZE_IS_5; j++)
            {
                if((!caught[j]) && (value[i] == value[j]))
                {
                    caught[j] = true;
                    count++;
                }
            }
            pairCounterArray[k] = count;
            k++;
        }
    }
    return;
}

void PairHandChecker(bool& fourPair, bool& threePair, bool& pair, bool& twoPair, short pairCounterArray[], short& size)
{
    short pairs(0);
    for(short i = 0; i < size; i++)
    {
        if(pairCounterArray[i] == 2)
        {
            pairs++;
        }
        if(pairCounterArray[i] == 3)
        {
            threePair = true;
        }
        if(pairCounterArray[i] == 4)
        {
            fourPair = true;
        }
    }

    if(pairs == 2)
    {
        twoPair = true;
    }
    else if(pairs == 1)
    {
        pair = true;
    }

    return;
}

int main()
{
      /*
        Test Cases by Rank
        1. RF  = {"S10","S11","S12","S13","S14"};
        2. SF  = {"H5","H6","H7","H8","H9"};
        3. 4X  = {"C3","S3","D3","H3","D13"};
        4. FH  = {"C13","S13","D13","H3","D3"};
        5.  F  = {"D3","D12","D13","D7","D5"};
        6. ST  = {"D3","H4","S5","S6","C7"};
        7. 3X  = {"S7","D7","C7","D4","C5"};
        8. 2X  = {"D9","S9","D13","H13","D5"};
        9. 1X  = {"D10","S10","D3","D12","H13"};
       10. 0   = {"C13","H2","D4","D8","S12"};
*/
    //************************************************************************************************//
    //
    //
    //                          maini functiion takes Hand array (5 Cards) as an arguement
    //                   Example of a hand must be Array like: {"H10","H11","H12","H13","H14"}; for hearts
    //                            Hand rank is saved in variable called "handRank"
    //
    //************************************************************************************************//


        //Receiving Cards From Dealer
    string card[DEFINE_HAND_SIZE_IS_5]=   {"H10","H11","H12","H13","H14"};
     
    
        short handRank;
        short value[DEFINE_HAND_SIZE_IS_5];
        string value_str[DEFINE_HAND_SIZE_IS_5];
        string suit[DEFINE_HAND_SIZE_IS_5];
    
        //Delimiter
        for(short i = 0; i < DEFINE_HAND_SIZE_IS_5; i++)
        {
            suit[i] = card[i].substr(0, 1);
            value_str[i] = card[i].substr(1, card[i].length() - 1);
        }
    
        convertArray(value_str, value);
    
        short pairCounterArray[DEFINE_HAND_SIZE_IS_5], size(0);
        PairHandCounter(value, pairCounterArray, size);
    
        bool onePair(false), twoPair(false), threePair(false), fourPair(false);

        
        PairHandChecker(fourPair, threePair, onePair, twoPair, pairCounterArray, size);
        
        bool is_RoyalFlushHandCheck = RoyalFlushHandCheck(value);
        bool is_StraightHandCheck = StraightHandCheck(value);
        bool is_sameSuitCheck = sameSuitCheck(suit);
    

        if(is_RoyalFlushHandCheck && is_sameSuitCheck)
        {
        cout << "\nPoker Hand\t\t:Royal Fush\n";
        handRank= 1;
        cout<<"Card Rank is\t: "<<handRank<<endl;
        }
    
        else  if(is_sameSuitCheck && is_StraightHandCheck)
        {
            cout << "\nStraight Flush\n";
           handRank= 2;
           cout<<"Card Rank is "<<handRank<<endl;
        }
        else if(fourPair)
        {
        cout << "\nFour of a kind\n";
        handRank= 3;
                cout<<"Card Rank is "<<handRank<<endl;
        }
        else if(threePair && onePair)
        {
        cout << "\nFull House\n";
        handRank= 4;
                   cout<<"Card Rank is "<<handRank<<endl;
        }
        else if(is_sameSuitCheck)
        {
        cout << "\nFlush\n";
        handRank= 5;
                    cout<<"Card Rank is "<<handRank<<endl;
        }
        else if(is_StraightHandCheck)
        {
        cout << "\nStraight\n";
        handRank= 6;
        cout<<"Card Rank is "<<handRank<<endl;
        }
    
        
        else if(threePair)
        {
        cout << "\nThree of a kind\n";
        handRank= 7;
                   cout<<"Card Rank is "<<handRank<<endl;
        }
    
        else if(twoPair)
        {
            cout << "\nTow of a kind\n";
            handRank= 8;
                       cout<<"Card Rank is "<<handRank<<endl;
        }
        else if(onePair)
        {
            cout << "\nOne Pair\n";
            handRank= 9;
                       cout<<"Card Rank is "<<handRank<<endl;
        }
        else
        {
            cout << "\nHigh Card\n";
            handRank= 10;
                       cout<<"Card Rank is "<<handRank<<endl;
        }
    return 0;
}
