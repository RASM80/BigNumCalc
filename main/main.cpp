#include <string>
#include <iostream>
using namespace std;

string trimString(string input , int position , int length){
    string output = ""; //functions like substr in the <string>
    for(int i=0 ; i<length ; i++)
    {
        output += input[position + i];
    }
    return output;
}
int stringLength(string input , int mode){//0 = whole number , 1 = decimal part , 2 = integer part
    int charactarCount = 0; //functions like length in the <string> but improved
    if(mode == 1){
        bool pointExistance = false;
        int length = stringLength(input , 0);
        for(int i=0 ; i<length ; i++)
        {
            if(input[i] == '.'){
                pointExistance = true;
                break;
            }
        }
        return stringLength(input , 0) - stringLength(input , 2) - pointExistance;
    }
    while(true){
        if(input[charactarCount] == '.' && mode == 2)
            return charactarCount;
        else if(input[charactarCount] == 0)
            return charactarCount;
        charactarCount++;
    }
}
string removeSpaces(string input){
    //if it finds any space char it will move rest of the number 1 step backward.
    //reapeats until all spaces are gone
    int i , b;
    int cap = stringLength(input,0);
    int length = cap;
    for(i = 0 ; i < cap ; i++){
        if(input[i] == ' '){
            for(b = i; b < cap ; b++){
                input[b]= input[b+1];
            }
            i--; //chars are moved 1 step backward.
            length--;
        }
    }
    input = trimString(input ,0 , length); //remove NULL chars at the end of number
    return input;
}
string removeZero(string input){
    int i , zeroNumber = 0;
    int length = stringLength(input , 0);
    for(i=0 ; i < length ; i++)
    {
        if(input[i] == '0')zeroNumber++;
        else break;
        if(zeroNumber == length) return "0";
    }
    input = trimString(input ,zeroNumber , length - zeroNumber + 1);
    //cut the zeroes off the number
    if(input[0] == '.') input = "0" + input;
    return input;
}
string removeDecimalZero(string input)
{
    int length = stringLength(input,0);
    bool pointExistance = false;
    int zeroes = 0;
    for(int i=0 ; i<length ; i++)//checking point existance
    {
        if(input[i] == '.')
        {
            pointExistance = true;
            break;
        }
    }
    if(input[length - 1] == '0')//checking unnecessary zeros
    {
        for(int i=length - 1 ; i>1 ; i--)
        {
            if(input[i] == '0')
                zeroes++;
            else{
                break;
            }
        }
    }
    if(pointExistance)
    {
        input = trimString(input , 0 ,length - zeroes); //cutting zeros off.
        length -= zeroes;
    }
    if(input[length - 1] == '.')//if decimal part is removed completely, removes the point
        input = trimString(input ,0 ,length - 1);
    return input;
}
string removePoint(string input, int *decimalPart){
    //removes the point and saves the length of decimalPart.
    int length = stringLength(input,0);
    int pointPosition = 0;
    *decimalPart = 0;
    bool pointExistance = false;
    for(int i=0 ; i<length ; i++)
    {
        if(input[i] == '.')//find position of point.
        {
            pointExistance = true;
            pointPosition = i;
            break;
        }
    }
    if(pointExistance == true)//cut the point off.
    {
        *decimalPart = length - pointPosition - 1;
        input = trimString(input ,0 , pointPosition) + trimString(input ,pointPosition + 1 ,*decimalPart);
    }
    return input;
}
string addPoint(string input ,int decimalPart){
    //adds the point with given decimalPart.
    if(decimalPart == 0) return input; //decimal 0 exception.
    int length = stringLength(input,0);
    string zeros = "";
    if(decimalPart >= length)
    {//adds 0. and 0 to left size of number
        zeros += "0.";
        for(int i=0 ; i<decimalPart - length ; i++)
        {
            zeros += "0";
        }
        input = zeros + input;
    }
    else if( (decimalPart < length) && (decimalPart > 0))
    {//puts the point in the given position
        input = trimString(input ,0 ,length - decimalPart) + "." + trimString(input ,length - decimalPart,decimalPart);
    }
    return input;
}
void matchNumbers(string* Num_1 ,string* Num_2 ,int* length_1 ,int *length_2 ,int* dp ,int dp_1 ,int dp_2){ //dp = decimal part
    //adds zero to the number with smaller decimal part.
    //it's used in substraction and division
    if(dp_1 >= dp_2)
    {
        *dp = dp_1;
        for( int i=0 ; i<dp_1 - dp_2 ; i++)
        {
            *Num_2 += "0";
            *length_2 += 1;
        }
    }
    else if(dp_2 > dp_1)
    {
        *dp = dp_2;
        for( int i=0 ; i<dp_2 - dp_1 ; i++)
        {
            *Num_1 += "0";
            *length_1 += 1;
        }
    }
    if(dp_1 >0) *length_1 -= 1;// point is removed. 1 char is gone.
    if(dp_2 >0) *length_2 -= 1;
    *Num_1 = removeZero(*Num_1);//removing possible unnecessary zeroes
    *Num_1 = trimString(*Num_1 ,0 ,stringLength(*Num_1,0));
    *Num_2 = removeZero(*Num_2);
    *Num_2 = trimString(*Num_2 ,0 ,stringLength(*Num_2,0));
}
bool numberSizeComparison(string Num_1 ,string Num_2 , bool equalityCheck){//1 = normal , 0 = no equality check
    //returns true if Num_1 is bigger and
    //returns false if it's smaller.
    Num_1 = removeZero(Num_1);
    Num_1 = trimString(Num_1 , 0 , stringLength(Num_1 , 0));
    Num_2 = removeZero(Num_2);
    Num_2 = trimString(Num_2 , 0 , stringLength(Num_2 , 0));
    Num_1 = removeDecimalZero(Num_1);
    Num_2 = removeDecimalZero(Num_2);

    int decimalPart_1 = 0 , decimalPart_2 = 0;
    int *fake = new int;
    *fake = 0;
    Num_1 = removePoint(Num_1 , &decimalPart_1);
    Num_2 = removePoint(Num_2 , &decimalPart_2);
    if(decimalPart_1 > 0 || decimalPart_2 > 0)
        matchNumbers(&Num_1 , &Num_2 , fake , fake , fake , decimalPart_1 , decimalPart_2);

    int num_1_length = stringLength(Num_1 , 0);
    int num_2_length = stringLength(Num_2 , 0);
    if(num_1_length > num_2_length)return true; //checks if 1 number is longer
    else if(num_1_length < num_2_length)return false;
    else if(num_1_length == num_2_length)
    {
        bool flag = true;
        int i;
        for(i=0 ; i < num_1_length ; i++)//both numbers has same length it'll check the digits one by one
        {
            if(Num_1[i] > Num_2[i])return true;
            else if(Num_1[i] == Num_2[i])continue;
            else break;
        }
        if(equalityCheck)
        {
            for(i=0 ; i<num_1_length ; i++)//both numbers has same length it'll check if they're equal
            {
                if(Num_1[i] != Num_2[i])
                {
                    flag = false;
                    break;
                }
            }
            if(flag)return true;
        }
    }
    return false;//since none of 3 loops return any result , Num_2 is bigger.
}
bool evenChecker(string input)//if number is even returns true , if odd returns false
{//used in checkExceptionName for sqrt
    int length = stringLength(input,0);
    if(input[length - 1] == '0');
    else if(input[length - 1] == '2');
    else if(input[length - 1] == '4');
    else if(input[length - 1] == '6');
    else if(input[length - 1] == '8');
    else{
        return false;
    }
    return true;
}

bool numberChecker(string number){
    int length = stringLength(number,0);
    int i=0;
    bool dotFlag = true;
    while(i<length)
    {
        if(number[i] == '.' && dotFlag) dotFlag = false; //making sure that there is only 1 dot
        else if (number[i] == '.' && !dotFlag) return false;
        else if(number[i] == '0');
        else if(number[i] == '1');
        else if(number[i] == '2');
        else if(number[i] == '3');
        else if(number[i] == '4');
        else if(number[i] == '5');
        else if(number[i] == '6');
        else if(number[i] == '7');
        else if(number[i] == '8');
        else if(number[i] == '9');
        else return false;
        i++;
    }
    return true;
}
string toString(int input)
{
    string output = "";
    string Temp = "";
    int temp = input;
    while(true){
        if(input == 0)
            break;
        temp = input;
        temp %= 10;
        Temp = 48 + temp;
        output = Temp + output;
        input /= 10;
    }
    return output;
}
int toInt(string input)
{
    int length = stringLength(input,0);
    int output = 0;
    for(int i=0 ; i<length ; i++)
    {
        output *= 10;
        output += input[i] - 48;
    }
    return output;
}
string digitSum(string input , int amount , int position , bool mode)//1 = integer , 0 = decimal
{
    int length = stringLength(input,0);
    int pointPosition = 0;
    for(int i=0 ; i<length ; i++)
    {
        if(input[i] == '.')
        {
            pointPosition = i;
            break;
        }
    }
    if(mode)
    {
        if(pointPosition > 0)
            input[pointPosition - position] += amount;
        else
            input[length - position] += amount;
    }
    else if(!mode)
    {
        input[pointPosition + position] += amount;
    }
    return input;
}

void printRules(){
    cout << "===========================================================================" << endl;
    cout <<  "Rules : " << endl << "1_ Spaces will be ignored so no matter how many spaces are in the input." << endl;
    cout << "2_An equal sign should be at the end of the numbers." << endl;
    cout << "3_pow doesn't support decimal pow." << endl;
    cout <<  "An example of an input : \" -234.543 * 2345.43  =  \"" << endl;
    cout << "===========================================================================" << endl;
}
string consoleIn(string input){
    cout << "============================" << endl;
    cout << "Please enter your input : " << endl ;
    getline(cin ,input); //gets all the line
    input = removeSpaces(input);  //calls the function to remove spaces in input string
    return input;
}
char opr_1(char input){
    switch(input){
    case '+' :
        return '+';
    case '-' :
        return '-';
    default :
        return 0; //NULL because it helps to find numbers in input
    }
}
void opr_2_3(string input , char *a , char *b , int *flag){
    int i , length;
    length = stringLength(input,0);
    for(i = 1 ; i < length; i++)
    {
        switch (input[i]){
        case '+' : *a = '+';
            break;
        case '-' : *a = '-';
            break;
        case '*' : *a = '*';
            break;
        case '/' : *a = '/';
            break;
        case '^' : *a = '^';
            break;
        case '%' : *a = '%';
            break;
        default  : *a = 0; //it will return error in checkExceptions func.
        }
        if(*a != 0){//opr_3 is is right next to opr_2 (if it's entered)
            switch(input[i+1]){
            case '+': *b = '+';
                break;
            case '-': *b = '-';
                break;
            default : *b = 0; //NULL because it helps to find numbers in input
            }
            *flag = i;
            break;
        }
    }
    return;
}

string sum(string number_1,string number_2 ,bool RemoveZero , bool addZero){
    int length_1 = stringLength(number_1,0);//removing point operation
    int length_2 = stringLength(number_2,0);
    int decimalPart_1 = 0;
    int decimalPart_2 = 0;
    int decimalPart = 0;
    number_1 = removePoint(number_1 ,&decimalPart_1);
    number_2 = removePoint(number_2 ,&decimalPart_2);
    if(decimalPart_1 > 0 || decimalPart_2 > 0)
        matchNumbers(&number_1 , &number_2 , &length_1 , &length_2 , &decimalPart , decimalPart_1 , decimalPart_2);
    string zero = "";
    length_1 = stringLength(number_1,0);
    length_2 = stringLength(number_2,0);
    int Break;
    if(addZero) //used for better optimization in multiplication
    {
        if(length_1>length_2)//adding enough zeroes to the left side of the numbers to prevent issues
        {
            Break = length_1 - length_2;
            for(int k = 0; k <= Break ; k++)
            {
                zero += "0";
            }
            number_2 = zero + number_2;
            number_1 = "0" + number_1;
            length_1++;
            length_2 = length_1;
        }
        else if(length_1<length_2)
        {
            Break = length_2 - length_1;
            for(int k = 0; k <= Break ; k++)
            {
                zero += "0";
            }
            number_1 = zero + number_1;
            number_2 = "0" + number_2;
            length_2++;
            length_1 = length_2;
        }
        else
        {
            number_1 = "0" + number_1;
            number_2 = "0" + number_2;
            length_1++;
            length_2++;
        }
    }
    length_1 -= 1; //for preventing -1 in all brackets
    for(int i=length_2 - 1; i>=0 ;i--) //main sum loop
    {
        number_1[length_1] = number_1[length_1] + number_2[i] - '0';
        if(number_1[length_1] > '9')
        {
            number_1[length_1] -= 10;
            number_1[length_1-1] = number_1[length_1-1] + 1;
        }
        length_1--;
    }
    number_1 = addPoint(number_1 ,decimalPart);//Adding the point back
    number_1 = removeDecimalZero(number_1);
    if(RemoveZero) //used for better optimization in multiplication
    {
        number_1 = removeZero(number_1);
    }
    number_1 = trimString(number_1 ,0 ,stringLength(number_1,0));
    return number_1 ;
}
string substraction(string Num_1 , string Num_2 , char *outputOpr){
    int length_1 = stringLength(Num_1,0); //removing points from numbers
    int length_2 = stringLength(Num_2,0);
    int decimalPart_1 = 0; //decimal part count
    int decimalPart_2 = 0;
    int decimalPart = 0;
    Num_1 = removePoint(Num_1 ,&decimalPart_1);
    Num_2 = removePoint(Num_2 ,&decimalPart_2);
    if(decimalPart_1 > 0 || decimalPart_2 > 0)
        matchNumbers(&Num_1 ,&Num_2 ,&length_1 ,&length_2 ,&decimalPart ,decimalPart_1 ,decimalPart_2);
    int carry = 0 ,m = 0,i = 0;
    bool number1_2_comp = numberSizeComparison(Num_1 ,Num_2 , 1);
    if(number1_2_comp)
        *outputOpr = '+';
    if(!number1_2_comp)//swaping 2 numbers if 2nd one is bigger
    {
        *outputOpr = '-';
        string temp = "";
        temp = Num_1;
        Num_1 = Num_2;
        Num_2 = temp;
    }
    m = stringLength(Num_2,0);
    i = stringLength(Num_1,0);
    while(m+1 > 0)//substraction main loop
    {
        Num_1[i] += carry;
        carry = 0;
        if(Num_1[i] >= Num_2[m])
        {
            Num_1[i] = Num_1[i] - Num_2[m] + 48;
        }
        else
        {
            Num_1[i] = Num_1[i] - Num_2[m] + 58;
            carry = -1;
        }

        i--;
        m--;
    }
    Num_1[i] += carry;//adding the last carry that was ignored in the loop
    do
    {
        if(Num_1[i] == 47)//fixing the next corrupted digits
        {
            Num_1[i] += 10;
            Num_1[i-1] -= 1;
        }
        i--;
    }while(i>0);
    Num_1 = addPoint(Num_1 ,decimalPart);//adding the point back
    Num_1 = removeDecimalZero(Num_1);//removing the unnecessary zeros in decimal part
    Num_1 = removeZero(Num_1);//removing the unnecessary zeros in integer part
    Num_1 = trimString(Num_1 ,0 ,stringLength(Num_1,0));
    return Num_1;
}
string tempLoop(string* temp ,string* output ,string Num_1 ,string Num_2 ,int length_1 ,int* tal ) //tal = tempAdditionLength
{//Adds Num_1 digits to temp one by one
    // until temp is bigger than Num_2
    char flag = true;
    for(int k=0 ; k<length_1 ; k++)
    {
        *temp += trimString(Num_1 ,k ,1);
        *tal += 1;
        if(flag)
        {
            flag = false;
        }
        else{
            *output += "0";
        }
        if(numberSizeComparison(*temp ,Num_2 , 1))break;
        if(length_1 == 0)break;
    }
    return *temp;
}
string tempSubstr(string temp ,string Num_2 ,int* Output)
{//divides temp by Num_2
    //Output will be used in division func.
    char fake = 0;
    while(true)
    {
        if(!numberSizeComparison(temp ,Num_2 , 1))break;
        temp = substraction(temp ,Num_2 ,&fake);
        *Output += 1;
    }
    return temp;
}
string tempLoopDecimal(string* temp ,string* output,string Num_2 ,int* i)
{//since all Num_1 digits are used in main loop
    //it adds zero digits to temp until it's bigger than Num_2
    bool flag = true;
    while(true)
    {
        if(numberSizeComparison(*temp ,Num_2 , 1) == 1)break;
        *temp += "0";
        if(flag == true)
        {
            flag = false;
            continue;
        }
        *output += "0";
        i++;
    }
    return *temp;
}
string division(string Num_1 , string Num_2 , int mode , int decimalPartLength)//mode : 0 = full operation , 1 = modulus , 2 = division without decimal part
{
    int length_1 = stringLength(Num_1,0) ,length_2 = stringLength(Num_2,0);//removing the point operation
    int decimalPart_1 = 0 ,decimalPart_2 = 0;
    int decimalPart = 0 ,Output = 0;
    Num_1 = removePoint(Num_1 ,&decimalPart_1);
    Num_2 = removePoint(Num_2 ,&decimalPart_2);
    if(decimalPart_1 > 0 || decimalPart_2 > 0)
        matchNumbers(&Num_1 ,&Num_2 ,&length_1 ,&length_2 ,&decimalPart ,decimalPart_1 ,decimalPart_2);
    string temp = "" ,output = "";
    int tempAdditionLength = 0;
    bool main_loop = numberSizeComparison(Num_1 , Num_2 , 1);
    if(main_loop)//using a piece of Num_1 as temp and dividing temp by Num_2
        //and reapeat until both temp and Num_1 are smaller than Num_2
    {
        while(true){
            tempAdditionLength = 0;
            temp = tempLoop(&temp ,&output ,Num_1 ,Num_2 ,length_1 ,&tempAdditionLength);
            temp = removeZero(temp);
            temp = trimString(temp , 0 ,stringLength(temp,0));
            if(!(numberSizeComparison(Num_1 , Num_2 , 1)) && !(numberSizeComparison(temp , Num_2 , 1)) )
                break; //it's put after temp loop to assign the temp's last value
            Output = 0;
            temp = tempSubstr(temp , Num_2 ,&Output);
            output += 48 + Output;
            if(length_1 > 0)
            {
                Num_1 = trimString(Num_1 ,tempAdditionLength ,length_1 - tempAdditionLength);
                length_1 -= tempAdditionLength;
            }
        }
        Num_1 = removeZero(Num_1);
        Num_1 = trimString(Num_1 ,0 ,stringLength(Num_1,0));
        if(Num_1[0] != 0)
            output += "0";
    }
    else{
        temp = Num_1;
        output += "0"; //for decimal part result
    }
    if(mode == 2){// division without decimal part in output.
        output = removeZero(output);
        output = trimString(output , 0 , stringLength(output , 0));
        return output;
    }
    else if(mode == 1){//modulus %
        temp = addPoint(temp , decimalPart);
        temp = removeDecimalZero(temp);
        temp = removeZero(temp);
        return temp;
    }
    if(numberSizeComparison(temp , "1" , 1))
    {
        output += ".";
        for(int i=0 ; i<decimalPartLength ; ){//decimal part loop :
            //calculate decimal part. adds zero to temp in place of Num_1 digits.
            Output = 0;
            temp = tempLoopDecimal(&temp ,&output,Num_2 ,&i);
            Output = 0;
            temp = tempSubstr(temp , Num_2 ,&Output);
            output += 48 + Output;
            i++;
            if(numberSizeComparison(temp , "1" , 1) == 0) break;
            temp = removeZero(temp);
            temp = trimString(temp ,0 ,stringLength(temp,0));
        }
    }
    if(main_loop == true) output = removeZero(output);
    //using main_loop condition because decimal part loop doesn't add unnecessary zeroes
    output = removeDecimalZero(output);
    return output;
}
string multiplication(string Num_1 , string Num_2){
    int length_1 = stringLength(Num_1,0);//removing point operation
    int length_2 = stringLength(Num_2,0);
    int decimalPart_1 = 0;
    int decimalPart_2 = 0;
    int decimalPart = 0;
    Num_1 = removePoint(Num_1 ,&decimalPart_1);
    Num_2 = removePoint(Num_2 ,&decimalPart_2);
    decimalPart = decimalPart_1 + decimalPart_2;
    if(decimalPart_1 > 0) length_1--;//point is removed. 1 less char in numbers
    if(decimalPart_2 > 0) length_2--;
    string zeros = "";
    string temp = Num_2;
    for( int i=length_2 + length_1; 0 < i ; i--)//adding zeros as long as the Num_2 to left side of the Num_1
    {
        zeros += "0";
    }
    string output = zeros;
    int i = length_1 - 1;
    int num_1_digit = 0;
    while(0 <= i)//main multiplication loop
    {
        num_1_digit = Num_1[i] - 48;
        while(num_1_digit > 0)
        {
            output = sum(output , temp , 0 , 0);
            num_1_digit--;
        }
        i--;
        temp += "0"; //Adding zero to right side of temp(Num_2) for multiplication
    }
    output = removeZero(output);
    output = trimString(output , 0 ,stringLength(output,0));
    output = addPoint(output ,decimalPart);
    output = removeDecimalZero(output);
    return output;
}
string pow(string Num_1 , string Num_2 ){
    string output = Num_1;
    if(removeZero(Num_2)[0] == '0')//checking the zero power possibility.
    {
        Num_2 = removeDecimalZero(Num_2);
        Num_2 = removeZero(Num_2);
        if(stringLength(Num_2,0) == 1 && Num_2[0] == '0')
            return "1";
    }
    char fake = 0;
    do//main pow loop.
    {  //it simply uses other functions fro calculation
        Num_2 = substraction(Num_2 , "1" ,&fake);
        if(!numberSizeComparison(Num_2 , "1" , 1))break;
        output = multiplication(output ,Num_1);
    }
    while(true);
    return output;
}

string factoriel (string x){
    string i="1", result="1";

    if (x == "0")
        return result;
    else
        while (i <= x)
        {
            result = multiplication(result, i);
            i =  sum(i ,"1" ,1 ,1);
        }

    return result;
}
string sin(string x , char* opr)  //corrupt
{
    string i, k, result_1 = "0", result_2 = "0";//"3.141592653589793238462643383279502"
    string c = "" , b = "";
    char a = '-';
    x = division(multiplication(x, "3.141592653589793238462643383279502"),"180",0,10);

    for(i="0" ; i != "16" ; )
    {

        k = sum(multiplication(i,"2"),"1",1,1);
        b = pow(x,k);
        c = factoriel(k);
        b = division(b , c,0,4);
        result_1 = sum(result_1 , b , 1 , 1);
        i = sum(i,"2",1,1);
    }
    for(i="1" ; i != "17" ; )
    {
        k = sum(multiplication(i,"2"),"1",1,1);
        result_2 = sum(result_2 , division(pow(x,k) , factoriel(k),0,4) , 1 , 1);
        i = sum(i,"2",1,1);
    }
    return substraction(result_1,result_2,&a);
}
string cos(string x , char* opr)  //corrupt
{
    string i, k, result_1 = "0", result_2 = "0";
    char a = '-';
    x = division(multiplication(x, "3.141592653589793238462643383279502"),"180",0 , 100);

    for(i="0" ; i != "1000" ; sum(i,"2",1,1))
    {
        k = multiplication(i,"2");
        result_1 = sum(result_1 , division(pow(x,k) , factoriel(k),0,4) , 0 , 0);
    }
    for(i="1" ; i != "1001" ; sum(i,"2",1,1))
    {
        k = multiplication(i,"2");
        result_2 = sum(result_2 , division(pow(x,k) , factoriel(k),0,4) , 0 , 0);
    }
    return substraction(result_1 , result_2 , &a);
}
string tan(string input , char* opr)  //corrupt
{
    return "tan";
}
string cot(string input , char* opr)  //corrupt
{
    return "cot";
}
string sqrtPrevious(string input , string root , int decimalPartLength)// if integer length > root . start from adding 1.
{
    if (input[0] == '1' && stringLength(input , 0) == 1)
        return "1";
    //    int length = stringLength(input,0); //normal
    string temp = "";
    int integerLength = stringLength(input,2);//extract integer part
    string integerPart = trimString(input , 0 , integerLength);
    integerLength = toInt( division( toString(integerLength) , root , 2 , 0) );//calculating how long is the integer part of the output.
    integerLength++;
    string output = "";
    string tempOutput = "";
    string sizeComp = "";
    for(int i=0 ; i<integerLength ; i++)
        output += "0";
    for(int i = 0 ; i<integerLength ; i++)
    {//calculate integer part separately to save time
        for(int j=0 ; j<10 ; j++)
        {
            tempOutput = output;
            output = digitSum(output , 1 , integerLength - i , 1);
            sizeComp = removeZero(output);
            sizeComp = trimString(sizeComp , 0 , stringLength(sizeComp,0));
            sizeComp = pow(sizeComp  , root);
            if(numberSizeComparison( sizeComp , integerPart  ,0))
            {
                output = tempOutput;
                break;
            }
        }
    }
    output += ".";
    for(int i = 1 ; i <= decimalPartLength ; i++)
    {//output decimal part
        output += "0";
        for(int j=0 ; j<10 ; j++)
        {
            tempOutput = output;
            output = digitSum(output , 1 , i , 0);
            sizeComp = removeZero(output);
            sizeComp = trimString(sizeComp , 0 , stringLength(sizeComp,0));
            sizeComp = pow(sizeComp  , root);
            if(numberSizeComparison( sizeComp , input  ,0))
            {
                output = tempOutput;
                break;
            }
        }
    }
    output = removeDecimalZero(output);
    output = removeZero(output);
    return output;
}
string sqrt(string input , string root , int decimalPartLength)// if integer length > root . start from adding 1.
{
    if (input[0] == '1' && stringLength(input , 0) == 1)
        return "1";
    //    int length = stringLength(input,0); //normal
    string temp = "";
    int integerLength = stringLength(input,2);//extract integer part
    string integerPart = trimString(input , 0 , integerLength);
    integerLength = toInt( division( toString(integerLength) , root , 2 , 0) );//calculating how long is the integer part of the output.
    integerLength++;
    string output = "";
    string tempOutput = "";
    string sizeComp = "";
    for(int i=0 ; i<integerLength ; i++)
        output += "0";
    for(int i = 0 ; i<integerLength ; i++)
    {//calculate integer part separately to save time
        output = digitSum(output , 5 , integerLength - i , 1);
        sizeComp = removeZero(output);
        sizeComp = trimString(sizeComp , 0 , stringLength(sizeComp,0));
        sizeComp = pow(sizeComp  , root);
        for(int j=0 ; j<10 ; j++)
        {
            if(numberSizeComparison( sizeComp , integerPart  ,0))
            {
                output = digitSum(output , -1 , integerLength - i , 1);
                sizeComp = removeZero(output);
                sizeComp = trimString(sizeComp , 0 , stringLength(sizeComp,0));
                sizeComp = pow(sizeComp  , root);
                if(!numberSizeComparison( sizeComp , integerPart  ,0))
                    break;
            }
            else
            {
                tempOutput = output;
                output = digitSum(output , 1 , integerLength - i , 1);
                sizeComp = removeZero(output);
                sizeComp = trimString(sizeComp , 0 , stringLength(sizeComp,0));
                sizeComp = pow(sizeComp  , root);
                if(numberSizeComparison( sizeComp , integerPart  ,0))
                {
                    output = tempOutput;
                    break;
                }
            }
        }
    }
    output += ".";
    for(int i = 1 ; i <= decimalPartLength ; i++)//fix errors , match sizeComp and output
    {//output decimal part
        output += "0";
        output = digitSum(output , 5 , i , 0);
        sizeComp = pow(output , root);
        for(int j=0 ; j<10 ; j++)
        {
            if(numberSizeComparison(sizeComp , input  ,0))
            {
                output = digitSum(output , -1 , i , 0);
                sizeComp = pow(output  , root);
                if(!numberSizeComparison( sizeComp , input  ,0))
                    break;
            }
            else
            {
                tempOutput = output;
                output = digitSum(output , 1 , i , 0);
                sizeComp = pow(output , root);
                if(numberSizeComparison( sizeComp , input  ,0))
                {
                    output = tempOutput;
                    break;
                }
            }
        }
    }
    output = removeDecimalZero(output);
    output = removeZero(output);
    return output;
}

//to be fixed for decimal power
string exp(string input)  //corrupt
{
    string i, result = "0";
    string temp = "";
    i = "0";
    while(!numberSizeComparison(i , "15" , 1))
    {
        temp = pow(input , i);
        temp = division(temp , factoriel(i) , 0 , 10);
        result = sum(result , temp , 1 , 1);
        i = sum(i , "1" , 1 , 1);
    }
    return result;
}
string log(string input , char* opr)// 0 < x < 1 , 1 <= x < inf  //corrupt
{//ln(input)
    if(numberSizeComparison(input , "1" , 1))
        *opr = '+';
    else
        *opr = '-';
    char fake = 0;
    string result = "0" , temp = "";
    string i = "1";
    while(!numberSizeComparison(i , "30" , 1))//totally diffrent
    {
        temp = substraction(input , "1" , &fake);
        temp = division(temp , sum(input , "1" , 1 , 1) , 0 , 10);
        temp = pow(temp , i);
        temp = division(temp , i , 0 , 10);
        result = sum(result , temp , 1 , 1);
        i = sum(i , "2" , 1 , 1);
    }
    result = multiplication(result , "2");
    return result;
}

/*string decimalPow(string number_1 , string number_2)
{
    char fake = 0;
    number_1 = log(number_1 , &fake);
    number_1 = multiplication(number_1 , number_2);
    return exp(number_1);
}*/

string doCalcualtions_Operator(string number_1 ,string number_2 ,char *outputOpr , char opr_1 ,char opr_2 ,char opr_3){
    switch(opr_2)
    {
    case '+'   :
        if((opr_1 == '-' && opr_3 == '-') || (opr_1 == '+' && opr_3 == '+'))
        {
            *outputOpr = opr_1;
            return sum(number_1 ,number_2 , 1 , 1);
        }
        else if(opr_1 == '+' && opr_3 == '-')
        {
            return substraction(number_1 ,number_2 , outputOpr);
        }
        else if(opr_1 == '-' && opr_3 == '+')
        {
            return substraction(number_2 ,number_1 , outputOpr);
        }
        break;
    case '-' : if((opr_1 == '-' && opr_3 == '+') || (opr_1 == '+' && opr_3 == '-'))
        {
            *outputOpr = opr_1;
            return sum(number_1 ,number_2 , 1 , 1);
        }
        if(opr_1 == '+' && opr_3 == '+')
        {
            return substraction(number_1 ,number_2 , outputOpr);
        }
        if(opr_1 == '-' && opr_3 == '-')
        {
            return substraction(number_2 ,number_1 , outputOpr);
        }
        break;
    case '*' : if((opr_1 == '-' && opr_3 == '-') || (opr_1 == '+' && opr_3 == '+'))
        {
            *outputOpr = '+';
            return multiplication(number_1 , number_2);
        }
        if((opr_1 == '+' && opr_3 == '-') || (opr_1 == '-' && opr_3 == '+'))
        {
            *outputOpr = '-';
            return multiplication(number_1 , number_2);
        }
        break;
    case '/' : if((opr_1 == '-' && opr_3 == '-') || (opr_1 == '+' && opr_3 == '+'))
        {
            *outputOpr = '+';
            return division(number_1 , number_2 , 0 , 100);
        }
        if((opr_1 == '+' && opr_3 == '-') || (opr_1 == '-' && opr_3 == '+'))
        {
            *outputOpr = '-';
            return division(number_1 , number_2 , 0 , 100);
        }
        break;
    case '^' :
        if((opr_1 == '+' && opr_3 == '+') || (opr_1 == '-' && opr_3 == '+'))
        {
            if((number_2[stringLength(number_2,0) - 1] - 48) % 2 == 1)
                *outputOpr = opr_1;
            else *outputOpr = '+';
            return pow(number_1 ,number_2);
        }
        else if((opr_1 == '+' && opr_3 == '-') || (opr_1 == '-' && opr_3 == '-'))
        {
            if((number_2[stringLength(number_2,0) - 1] - 48) % 2 == 1)
                *outputOpr = '-';
            else *outputOpr = '+';
            return division("1" ,pow(number_1 ,number_2) , 0 , 100);
        }
        break;
    case '%' :
        if(opr_1 == '+' || (opr_3 == '-' || opr_3 == '+'))
        {
            *outputOpr = '+';
            return division(number_1 , number_2 , 1 , 100);
        }
        else if(opr_1 == '-' || (opr_3 == '-' || opr_3 == '+'))
        {
            *outputOpr = '-';
            return division(number_1 , number_2 , 1 , 100);
        }
        break;
    default : return "";

    }
}
bool checkExceptions_Operator(string input ,string number_1 ,string number_2 ,char opr_2){
    if(input[stringLength(input,0) - 1] != '=')//checking equal sign existance.
    {
        cout << "Error : There isn't any equal sign." << endl;
        return 1;
    }
    if(opr_2 == 0)//checking if the main operator is entered.
    {
        cout << "Error : There isn't any proper operator entered." << endl;
        return 1;
    }
    if(number_1[0] == 0)//checking if first number is entered.
    {
        cout << "Error : You didn't enter the first number." << endl;
        return 1;
    }
    if(number_2[0] == 0)//checking if second number is entered.
    {
        cout << "Error : You didn't enter the second number." << endl;
        return 1;
    }
    if(number_1[0] != 0 && number_2[0] != 0)//checking if numbers were entered properly.
    {
        if(!numberChecker(number_1) || !numberChecker(number_2))
        {
            cout << "Error : Something is wrong with the numbers." << endl;
            return 1;
        }
    }
    if((stringLength(number_2,0) == 1 && number_2[0] == '0') && opr_2 == '/')//Prohibit division by zero
    {
        cout << "Error : Numbers cannot be devided by zero." << endl;
        return 1;
    }
    return 0;
}
void extractMaterials_Operator(string input ,string* number_1 ,string* number_2 ,char* Opr_1 ,char* Opr_2 ,char* Opr_3)
{
    int flag_endOfNumber1 = 0; //variable for position of main operator. helps to find first number
    *Opr_1 = opr_1(input[0]); //find opr_1
    opr_2_3(input , Opr_2 , Opr_3 , &flag_endOfNumber1);//find opr 2 , 3 and flag for numbers position
    bool opr_1_existance = true;
    bool opr_3_existance = true; // these 2 used for extracting the numbers.
    if(*Opr_1 == 0)opr_1_existance = false;
    if(*Opr_3 == 0)opr_3_existance = false;
    *number_1 = trimString(input ,opr_1_existance , flag_endOfNumber1 - opr_1_existance); //extracting the number_1 from input
    *number_2 = trimString(input ,flag_endOfNumber1 + 1 + opr_3_existance , stringLength(input,0) - flag_endOfNumber1 - 2 - opr_3_existance); //extract the number_2 from input
    //flag_endOfNumber1 is the position of main operator so add a 1 to skip it. then we add the opr_3_existance for skipping possible 2nd number sign
    // (stringLength(input) - flag_endOfNumber1 -2) is the length of number_2 and the 2 is for the equal sign(=)
    if(*Opr_1 == 0)*Opr_1 = '+';
    if(*Opr_3 == 0)*Opr_3 = '+';
    //remove useless zeroes
    *number_1 = removeZero(*number_1);
    *number_1 = trimString(*number_1 , 0 ,stringLength(*number_1,0));
    *number_2 = removeZero(*number_2);
    *number_2 = trimString(*number_2 , 0 ,stringLength(*number_2,0));
    return;
}
string callFunctions_Operator(string input ,char *outputOpr)
{
    string number_1 = "", number_2 = "" , output = "";
    char Opr_1 = 0, Opr_2 = 0 , Opr_3 = 0;
    *outputOpr = 0;
    extractMaterials_Operator(input ,&number_1 ,&number_2 ,&Opr_1 ,&Opr_2 ,&Opr_3); //extracting numbers and operators from input
    cout << "o";
    if(checkExceptions_Operator(input ,number_1 ,number_2 ,Opr_2)) //checking errors and commands
        return "";
    return doCalcualtions_Operator(number_1 ,number_2 , outputOpr ,Opr_1 ,Opr_2 ,Opr_3); //everything is ready now ,functions will be called.
}

string doCalcualtions_Command(string number_1 , string number_2 , int command , char opr_1 , char* outputOpr)
{
    if(command == 0)
    {
        *outputOpr = opr_1;
        return sin(number_1 , outputOpr);
    }
    else if(command == 1)
    {
        *outputOpr = opr_1;
        return cos(number_1 , outputOpr);
    }
    else if(command == 2)
    {
        *outputOpr = opr_1;
        return tan(number_1 , outputOpr);
    }
    else if(command == 3)
    {
        *outputOpr = opr_1;
        return cot(number_1 , outputOpr);
    }
    else if(command == 4)
    {

        return log(number_1 , outputOpr);
    }
    else if(command == 5)
    {
        *outputOpr = opr_1;
        if(number_2[0] == 0)
            number_2 = "2";
        return sqrt(number_1 , number_2  , 20);
    }
}
bool checkExceptions_Command(string input , string number_1 , string number_2 , int command , char opr)
{
    if(input[stringLength(input,0) - 1] != '=')//checking equal sign existance.
    {
        cout << "Error : There isn't any equal sign." << endl;
        return 1;
    }

    if(command == 6)//checking if command has default value.
    {
        cout << "Error : Command wasn't entered properly." << endl;
        return 1;
    }
    else if(command == 5){//left parenthesis in sqrt command is at diffrent postion
        if(input[4] != '(')
        {
            cout << "Error : you didn't enter left parenthesis." << endl;
            return 1;
        }
        if(evenChecker(number_2) && opr == '-')
        {
            cout << "Error : the number cant be negative whereas root is even." << endl;
            return 1;
        }
    }
    else{ //checking left parenthesis for other commands
        if(input[3] != '(')
        {
            cout << "Error : you didn't enter left parenthesis." << endl;
            return 1;
        }//needs to be changed if commands with diffrent lengths are added

        if(stringLength(number_2,0) != 0)
        {
            cout << "Tip : no need to enter second number in this command. (result will be shown anyway)" << endl;
        }
    }

    bool rightParenthesisExist = false;
    int length = stringLength(input,0);
    for(int i=4 ; i < length ; i++)//checking right parenthesis existance.
    {
        if(input[i] == ')')
            rightParenthesisExist = true;
    }
    if(!rightParenthesisExist)
    {
        cout << "Error : you didn't enter right parenthesis." << endl;
        return 1;
    }

    if(number_1[0] == 0)//checking if first number is entered.
    {
        cout << "Error : You didn't enter any number." << endl;
        return 1;
    }

    if(!numberChecker(number_1))//checking if numbers were entered properly.
    {
        cout << "Error : something is wrong with the first number." << endl;
        return 1;
    }
    if(command == 5 && !numberChecker(number_2))
    {
        cout << "Error : something is wrong with the second number." << endl;
        return 1;
    }


    if(command == 4)//forhibit negative number in logarithm
        if(opr == '-')
        {
            cout << "Error : The number cannot be negative in the logarithm." << endl;
            return 1;
        }


    return 0;
}
void extractMaterials_Command(string input ,string* number_1 ,string* number_2 ,char* Opr)
{
    int length = stringLength(input,0);
    int position_1 = 0 , position_2 = 0; //number_1 first and last char positions
    for(int i=0 ; i<length ; i++)
    {
        if(input[i] == '('){
            if(input[i+1] == '+' || input[i+1] == '-'){
                position_1 = i+2;
                *Opr = input[i+1];
            }
            else{
                *Opr = '+';
                position_1 = i+1;
            }
        }
        if(input[i] == ')')
        {
            position_2 = i;
            if(input[i+1] != 0)
            {
                *number_2 = trimString(input , i+1 , length - i - 2);//additional 1 for equal sign in length section
            }
        }
    }
    *number_1 = trimString(input , position_1 , position_2 - position_1);
    return;
}
int extractCommand(string input)
{
    if(input[0] == 's' || input[0] == 'S'){
        if(input[1] == 'i' || input[1] == 'I'){
            if(input[2] == 'n' || input[2] == 'N')
                return 0;
        }
        else if(input[1] == 'q' || input[1] == 'Q'){
            if(input[2] == 'r' || input[2] == 'R')
                if(input[3] == 't' || input[3] == 'T')
                    return 5;
        }
    }
    if(input[0] == 'c' || input[0] == 'C')
        if(input[1] == 'o' || input[1] == 'O')
            if(input[2] == 's' || input[2] == 'S')
                return 1;
    if(input[0] == 't' || input[0] == 'T')
        if(input[1] == 'a' || input[1] == 'A')
            if(input[2] == 'n' || input[2] == 'N')
                return 2;
    if(input[0] == 'c' || input[0] == 'C')
        if(input[1] == 'o' || input[1] == 'O')
            if(input[2] == 't' || input[2] == 'T')
                return 3;
    if(input[0] == 'l' || input[0] == 'L')
        if(input[1] == 'o' || input[1] == 'O')
            if(input[2] == 'g' || input[2] == 'G')
                return 4;
    return 6;
}
string callFunctions_Command(string input , char *outputOpr)
{//using outputOpr as number_1 opr to prevent extra memory use
    string number_1 = "" , number_2 = "" , output = "";
    char opr_1 = 0;
    int command = 6; //assigning odd value to check if the value changes.
    extractMaterials_Command(input , &number_1 , &number_2 , &opr_1);
    cout << "n";
    command = extractCommand(input);
    //0=sin , 1=cos , 2=tan , 3=cot , 4=log  , 5=sqrt.
    if(checkExceptions_Command(input , number_1 , number_2 , command , opr_1))
        return "";
    return doCalcualtions_Command(number_1 , number_2 , command , opr_1 , outputOpr);
}

bool nameVSopr(string input){
    if(input[0] == '+');
    else if(input[0] == '-');
    else if(input[0] == '0');
    else if(input[0] == '1');
    else if(input[0] == '2');
    else if(input[0] == '3');
    else if(input[0] == '4');
    else if(input[0] == '5');
    else if(input[0] == '6');
    else if(input[0] == '7');
    else if(input[0] == '8');
    else if(input[0] == '9');
    else return 0;
    return 1;
}
bool exitCommand(string input){
    bool exit = true;
    if(input[0] == 'e' || input[0] == 'E');
    else exit = false;
    if(input[1] == 'x' || input[1] == 'X');
    else exit = false;
    if(input[2] == 'i' || input[2] == 'I');
    else exit = false;
    if(input[3] == 't' || input[3] == 'T');
    else exit = false;
    if(exit)
    {
        cout << "The End" << endl;
        return 1;
    }
    else return 0;
}

int main()
{
    string output = "";
    char outputOpr = 0;
    bool Switch;
    printRules();
    while(true)
    {
        string *input = new string;
        *input = consoleIn(*input); //getting the input from user
        if(exitCommand(*input)){
            delete input;
            return 0;
        }
        Switch = nameVSopr(*input);
        if(Switch){
            output = callFunctions_Operator(*input ,&outputOpr);
        }
        else{
            output = callFunctions_Command(*input ,&outputOpr);
        }
        if(output[0] == 0)continue;
        delete input;
        if(stringLength(output,0) == 1 && output[0] == '0') //setting outputOpr to NULL if output is zero
            outputOpr = 0;
        cout << endl;
        cout << "Result is : " << endl << outputOpr << output << endl;
    }
}
