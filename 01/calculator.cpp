#include <iostream>

using namespace std;

int flag = 0;

string trim(string& str)
{
    str.erase(0, str.find_first_not_of(' '));
    str.erase(str.find_last_not_of(' ')+1); 
    return str;
}

int exec (string str)
{

    string str1, str2;
    int ind = str.find("+");
    if(ind != string::npos)
    {
        str1 = str.substr(0, ind);
        str2 = str.substr(ind + 1, (str.size() - ind + 1));
        str1 = trim(str1);
        str2 = trim(str2);

        if (str1.empty() || str2.empty())
        {
            cout << "Error";
            flag = -1;
            return 0;
        }
        return (exec(str1) + exec(str2));
    }

    int ind2 = str.rfind("-");
    if (ind2 != string::npos)
    {
        str1 = str.substr(0, ind2);
        str2 = str.substr(ind2 + 1, (str.size() - ind2 + 1));
        str1 = trim(str1);
        str2 = trim(str2);

        if ( (str1[str1.size() - 1] == '-') || (str1[str1.size() - 1] == '+') || (str1[str1.size() - 1] == '*') || (str1[str1.size() - 1] == '/') )
        {
            switch (str1[str1.size() - 1])
            {
                case '+':
                    str1.erase(str1.size() - 1, 1);
                    return (exec(str1) - exec(str2));
                case '-':
                    str1.erase(str1.size() - 1, 1);
                    return (exec(str1) + exec(str2));
                case '*':
                    str1.erase(str1.size() - 1, 1);
                    return (exec(str1) * (-exec(str2)));
                case '/':
                    str1.erase(str1.size() - 1, 1);
                    return (exec(str1) / (-exec(str2)));
            }
        }

        if ((str1.empty()) && (!str2.empty()))
        {
            return (-exec(str2));
        }
        if (str1.empty() || str2.empty())
        {
            cout << "Error";
            flag = -1;
            return 0;
        }
    return (exec(str1) - exec(str2));
    }

    int ind3 = str.find("*");
    if (ind3 != string::npos)
    {
        str1 = str.substr(0, ind3);
        str2 = str.substr(ind3 + 1, (str.size() - ind3 + 1));
        str1 = trim(str1);
        str2 = trim(str2);

        if (str1.empty() || str2.empty())
        {
            cout << "Error";
            flag = -1;
            return 0;
        }
        return (exec(str1) * exec(str2));
    }

    int ind4 = str.rfind("/");
    if (ind4 != string::npos)
    {
        str1 = str.substr(0, ind4);
        str2 = str.substr(ind4 + 1, (str.size() - ind4 + 1));
        str1 = trim(str1);
        str2 = trim(str2);

    if (str1.empty() || str2.empty())
    {
        cout << "Error";
        flag = -1;
        return 0;
    }
    if (exec(str2) == 0)
    {
        cout << "Error";
        flag = -1;
        return 0;
    }

    return (exec(str1) / exec(str2));
    }
    return (stoi(str));
    

    
}

bool check_chars(string tmp)
{
    for (int i = 0; i < tmp.size(); i++){
            if (isdigit(tmp[i]))
                tmp.replace(i, 1," ");
        }
                for (int i = 0; i < tmp.size(); i++){
            if (tmp[i]=='+'){
                tmp.replace(i,1," ");
                }            
        }
        for (int i = 0; i < tmp.size(); i++){
            if (tmp[i]=='-' ){
                tmp.replace(i,1," ");
            }
        }
                for (int i = 0; i < tmp.size(); i++){
            if (tmp[i]=='*'){
                tmp.replace(i,1," ");
            }
        }
                for (int i = 0; i < tmp.size(); i++){
            if (tmp[i]=='/'){
                tmp.replace(i,1," ");
            }
        }
               
        tmp = trim(tmp);
        if (!tmp.empty()){
            flag = -1;
            return false;
        }
        return true;

}

int main(int argc, char *argv[])
{
        if (argc != 2)
        {
            cout << "Error";
            return -1;
        }
        string str = argv[1];
        if (!check_chars(str)){
            cout << "Error";
            return -1;
        }
        int value = exec(str);
        if (flag == -1){
            return -1;
        }
        cout << value;
        return 0;
}
