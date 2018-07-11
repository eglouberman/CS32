    //
//  eval.cpp
//  Homework2_CS32
//
//  Created by Elon Glouberman on 2/5/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#include <stdio.h>
//#include "Map.h"
#include <iostream> 
#include <string> 
#include <stack>
#include <cctype>
#include <cassert>
using namespace std;

string convertToPostfix(string infix); // converts from infix to postfix
bool checkParentheses(string infix); //checks if paretheses are balanced
int getWeight(char ch); //gives weight to a certain operator
bool checkValid(string infix); //checks if comprised of lowercase letters and valid expressions

//int evaluate(string infix, const Map& values, string& postfix, int& result){
//    int result_copy = result;
//
//    if (checkValid(infix))
//    {
//        //postix is set to the postfix form of infix
//        postfix = convertToPostfix(infix);
//    }
//
//    else {
//        return 1;
//    }
//
//    //sytax is valid, but one letter is not in map
//    for (int i = 0; i < infix.length(); i++)
//    {
//        if (infix[i] <='z' && infix[i] >= 'a')
//        {
//            if (!values.contains(infix[i]))
//                return 2;
//        }
//    }
//
//    stack <int> operandStack;
//    for(int i =0; i< postfix.length(); i++)
//    {
//        if (postfix[i]>= 'a' && postfix[i] <= 'z')
//        {
//            int val  = 0;
//            values.get(postfix[i], val);
//            operandStack.push(val);
//        }
//        else //i is a binary operator
//        {
//            int operand2 = operandStack.top();
//            operandStack.pop();
//            int operand1 = operandStack.top();
//            operandStack.pop();
//            if (postfix[i] == '*')
//            {
//                result = operand1 * operand2;
//                operandStack.push(result);
//            }
//            else if (postfix[i] == '/')
//            {
//                if (operand2 == 0)
//                {
//                    result = result_copy;
//                    return 3;
//                }
//                else
//                {
//                    result = operand1 / operand2;
//                    operandStack.push(result);
//                }
//            }
//            else if (postfix[i] == '+')
//            {
//                result = operand1 + operand2;
//                operandStack.push(result);
//            }
//            else if (postfix[i] == '-')
//            {
//                result = operand1 - operand2;
//                operandStack.push(result);
//            }
//        }
//    }
//    if (!operandStack.empty())
//        result = operandStack.top();
//    return 0;
//}

bool checkParentheses(string infix) // code to check balanced paratheses.
{
    stack <char> a;
    
    for (int i = 0 ;i<infix.length(); i++)
    {
        if (infix[i]== '(') // we push an item onto the stack if there is an open parenthesis
        {
            a.push('(');
            continue;
        }
        
        if (infix[i] == ')') // everytime there is a closing paranthesis, we pop the top item off the stack.
        {
            if (a.empty())
                return false;
            a.pop(); //removes top item
        }
        
    }
    
    if (a.empty()) return true;
    return false;
}

int getWeight(char ch) {
    switch (ch) {
        case '/':
        case '*': return 1;
        case '+':
        case '-': return 0;
    }
    return -1;
}


bool checkValid(string infix) //checks if the string is valid. Does not take paretheses into account.
{
    if (!checkParentheses(infix)) return false; // we first check if the parentheses make sense
    
    
    
    for (size_t i = 0; i < infix.length(); i++)
    {
        if (infix[i] == '(' || infix[i] == ')')
            infix[i] = ' ';
        if  (infix[i]!= ' ' && infix[i] != '*' && infix[i]!= '/' && infix[i] != '+' && infix[i]!= '-' && !(infix[i] <='z' && infix[i] >= 'a'))
        {
            return false;
        }
    }
    
    int i = 0;
    int count = 0;
    bool lookingForLetter = true;
    bool lookingForOperand = false;
    while (i != infix.length())
    {
        if (lookingForLetter)
        {
            if (!(infix[i] <='z' && infix[i] >= 'a') && infix[i] != ' ')
            {
                return false;
            }
            
            if ((infix[i] <='z' && infix[i] >= 'a')) { // if we found letter
                count ++;
                lookingForLetter = false;
                lookingForOperand = true;
                i++;
            }
            
        }
        
        if (i!=infix.length() && lookingForOperand)
        {
            if ((infix[i] <='z' && infix[i] >= 'a') && infix[i] != ' '){ // if we know it isnt an operand that comes next
                return false;
            }
            
            if (!(infix[i] <='z' && infix[i] >= 'a') && infix[i] != ' ') // if we know its an operand
            {
                lookingForOperand= false;
                lookingForLetter = true;
                i++;
                continue;
            }
        }
        
        if ( i!= infix.length() && infix[i]  == ' ')
            i++;
    }
    
    if (lookingForLetter) //indicates that we finished with an operand
        return false;
    
    //if (count ==1) return false; //indicates that there is only one letter
    
    
    return true;
}

string convertToPostfix(string infix)
{
    string postfix = "";
    stack <char> operatorStack;
    for (int ch  = 0; ch < infix.length(); ch++)
    {
        if (infix[ch] >='a' && infix[ch] <='z')
        {
            postfix += infix[ch];
            continue;
        }
        switch(infix[ch]){
            case '(':
                operatorStack.push(infix[ch]);
                break;
            case ')':
                //pop stack until matching '('
                while (operatorStack.top() != '(')
                {
                    postfix +=operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.pop();
                break;
            case '*':
            case '/':
            case '+':
            case '-':
                while (!operatorStack.empty() && (getWeight(infix[ch])<= getWeight(operatorStack.top()))&& (operatorStack.top() != '('))
                {
                    postfix += operatorStack.top();
                    operatorStack.pop();
                }
                operatorStack.push(infix[ch]);
                break;
        }
    }
    
    while (!operatorStack.empty())
    {
        char add = operatorStack.top();
        string a(1,add);
        postfix+=a;
        operatorStack.pop();
    }
    
    return postfix;
}

int main()
{
    string s= "a*((b*c)-d + e/(f*g))";
    cout<< convertToPostfix(s);
}

