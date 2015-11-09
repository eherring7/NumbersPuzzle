#include <iostream>
#include <algorithm>
#include <string>
#include <deque>

using namespace std;

#define HUNDRED        "hundred"
#define THOUSAND       "thousand"
#define MILLION        "million"
#define MAGICNUMBER    51000000000
#define TOTALTHOUSANDS 499999500000
#define TOTALONES      499500

// Define our functions
long long CheckNumber(string, string);
void FindMagicNumber();

// String array to hold numbers 1 - 20
string numOnesWords[20] = {"zero", "one", "two", "three", "four", "five", "six", "seven",
                           "eight", "nine", "ten", "eleven", "twelve", "thirteen", 
                           "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
                           "nineteen"};

// string array to hold tens up to 100
string numTensWords[10] = {"zero", "ten", "twenty", "thirty", "forty", "fifty", "sixty",
                           "seventy", "eighty", "ninety"};

// Structure for holding the numbers and the word
struct numWords
{
   string    numWord;
   long long numDigit;
};

// Holds total values for all numWords
long long hundredsTotal = 0;
long long thousandsTotal = 0;

// Deques to hold the values
deque<numWords> numMillion;
deque<numWords> numThousand;
deque<numWords> numHundred;

// Structure to hold values
numWords numberStruct;

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  ROUTINE NAME: sortNumStruct                                        //
//                                                                     //
//  DESCRIPTION: This routine is used with the sort routine to sort    //
//  the deques alphabetically by word name                             //
//                                                                     //
/////////////////////////////////////////////////////////////////////////
int sortNumStruct( numWords const &a, numWords const &b)
{
   return a.numWord < b.numWord;
}

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  ROUTINE NAME: FindMagicNumber                                      //
//                                                                     //
//  DESCRIPTION: This routine counts up the numbers and characters     //
//  until it gets to the MAGICNUMBER.  Then it prints the results to   //
//  standard output                                                    //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

void FindMagicNumber()
{
   long long totalCharCount = 0;
   long long num = 0;
   unsigned long long numberHold = 0;
   unsigned long long numberCount = 0;
   string finalString, finalWord;
   deque<numWords>::const_iterator i, j, a;

   // Loop through the Millions deque to count all the characters and numbers
   for(i = numMillion.begin(); i != numMillion.end(); i++)
   {
      finalString = (*i).numWord;
      // Check the prefix of the number word and count the characters and numbers accordingly
      if(num = CheckNumber(finalString, MILLION))
      {
         totalCharCount += num;
         numberHold = (*i).numDigit + ((*i).numDigit * 999999) + TOTALTHOUSANDS;
         numberCount += numberHold;
      }
      else if(num = CheckNumber(finalString, THOUSAND))
      {
         totalCharCount += num;
         numberHold = ((*i).numDigit * 1000) + TOTALONES;
         numberCount += numberHold;
      }
      else
      {
         num = finalString.size();
         totalCharCount += num;
         numberHold = (*i).numDigit;
         numberCount += numberHold;
      }
      // Check to see if we have gone over the Magic Number
      if(totalCharCount > MAGICNUMBER)
      {
         // Subtract off the last number added
         totalCharCount -= num - finalString.size();
         numberCount -= numberHold - (*i).numDigit;

         // Search the prefix of the last word added
         finalWord = (*i).numWord;
         size_t found;
         found = finalWord.find(MILLION);
         if(found != string::npos)
         {
            // Now that we know the Million word, lets find the Thousand Word
            for(j = numThousand.begin(); j != numThousand.end(); j++)
            {
               totalCharCount += finalWord.size() + (*j).numWord.size();
               numberCount += (*i).numDigit + (*j).numDigit; 

               // If word has prefix of Thousand, lets add the values in
               found = (*j).numWord.find(THOUSAND);
               if(found != string::npos)
               {
                  totalCharCount += (finalWord.size() * 999) + ((*j).numWord.size() * 999) + hundredsTotal;
                  numberHold = ((*i).numDigit * 999) + ((*j).numDigit * 999) + TOTALONES;
                  numberCount += numberHold;
               }
               // Check to see if we have reached the Magic Number
               if(totalCharCount > MAGICNUMBER)
               {
                  // Subtract off the last number added
                  totalCharCount -= (finalWord.size() * 999) + ((*j).numWord.size() * 999) + hundredsTotal;
                  numberCount -= numberHold;
                  // Now that we have the million and the thousand number, lets now get the hundreds, tens, and ones numbers
                  for(a = numHundred.begin(); a != numHundred.end(); a++)
                  {
                     totalCharCount += finalWord.size() + (*j).numWord.size() + (*a).numWord.size();
                     numberCount += (*i).numDigit + (*j).numDigit + (*a).numDigit;
                     // Check to see if we have reached the Magic Number
                     if(totalCharCount >= MAGICNUMBER)
                     {
                        cout << "Total Char Count = " << totalCharCount << endl;
                        cout << "Full Number is: " << finalWord + (*j).numWord + (*a).numWord << endl;
                        cout << "Digits added up is: " << numberCount << endl;
                        break;
                     }
                  }
                  break;
               }
            } // end for loop through Thousands
         } // end find word Million
         break;
      } // Check character count for Magic Number
   } // end main for loop through Millions
   return;
}

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  ROUTINE NAME: CheckNumber                                          //
//                                                                     //
//  DESCRIPTION: This routine reads in the digits place for a number   //
//  and returns the character count for that number                    //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

long long CheckNumber(string numWord, string digitPlace)
{
   size_t found;
   string finalString;

   found = numWord.find(digitPlace);
   if(found != string::npos)
   {
      if(digitPlace == MILLION)
         return (1000000 * numWord.size()) + thousandsTotal + hundredsTotal;
      else if(digitPlace == THOUSAND)
         return (1000 * numWord.size()) + hundredsTotal;
   }
   return 0;
}

/////////////////////////////////////////////////////////////////////////
//                                                                     //
//  ROUTINE NAME: main                                                 //
//                                                                     //
//  DESCRIPTION: This is the main routine for the program.  This       //
//  routine sets up our storage containers to be used for counting     //
//                                                                     //
/////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
   string joinWords;
   long digit[10];
   long number;
   
   // Loop through the first 1000 numbers to build our base
   for(int x = 1; x < 1000; x++)
   {
      int y = 0;
      number = x;
      joinWords = "";
      while(number >= 1)
      {
         digit[y] = number % 10;
         y++;
         number /= 10;
      }
      for(int j = y - 1; j >= 0; j--)
      {
         switch(j)
         {
            case 0:
               if(digit[j + 1] != 1)
               {
                  if(digit[j] != 0)
                  { 
                     joinWords += numOnesWords[digit[j]];
                  } 
               }
               break;
            case 1:
               // Special case to handle the numbers between 10 and 19
               if(digit[j] == 1)
               {
                  joinWords += numOnesWords[digit[j - 1] + 10];
               }
               else
               {
                  if(digit[j] != 0)
                  {
                     joinWords += numTensWords[digit[j]];
                  }
               }
               break;
            case 2:
               if(digit[j] != 0)
               {
                  joinWords += numOnesWords[digit[j]];
                  joinWords += HUNDRED;
               }
               break;
          }
      }
      // Set up the hundreds deque
      numberStruct.numDigit = x;
      numberStruct.numWord = joinWords;
      numHundred.push_back(numberStruct);

      // Set up the thousands deque
      numberStruct.numDigit = x * 1000;
      numberStruct.numWord = joinWords + THOUSAND;
      numThousand.push_back(numberStruct);

      // Set up the millions deque
      numberStruct.numDigit = x * 1000000;
      numberStruct.numWord = joinWords + MILLION;
      numMillion.push_back(numberStruct);
   }

   // Sort the Hundreds deque
   sort(numHundred.begin(), numHundred.end(), sortNumStruct);

   deque<numWords>::const_iterator i;

   // Total the Hundreds and add them to the Thousands
   for(i = numHundred.begin(); i != numHundred.end(); i++)
   {
      hundredsTotal += (*i).numWord.size();
      numberStruct.numDigit = (*i).numDigit;
      numberStruct.numWord = (*i).numWord;
      numThousand.push_back(numberStruct);
   }

   // Total the Thousands and add them to the Millions
   for(i = numThousand.begin(); i != numThousand.end(); i++)
   {
      thousandsTotal += CheckNumber((*i).numWord, THOUSAND);
      numberStruct.numDigit = (*i).numDigit;
      numberStruct.numWord = (*i).numWord;
      numMillion.push_back(numberStruct);
   }

   // Sort the Thousands and Millions
   sort(numThousand.begin(), numThousand.end(), sortNumStruct);
   sort(numMillion.begin(), numMillion.end(), sortNumStruct);

   // Now that our storage containers are set up and sorted,
   // lets find the Magic Number
   FindMagicNumber();
   return(0);
}
