#ifndef lexical_analysis_hpp
#define lexical_analysis_hpp

#include "lexical_analysis.h"
#include "global_variable.h"

#include <iostream>
#include <string>
#include <cctype>
#include <set>
using namespace std;

// "string int real else if return while "
// matching the second line of enum (for initializing)
// "in out void main"
// matching the third line

// token list.
enum {
    // integer constant, floating point constant, function, system operation, identifier
    Inum = 128, Fnum, Cstr, Fun, Sys, Id,
    String, Int, Real, Else, If, Return, While,
    In, Out, Void, Main,
    // the former are pre-defined identifier
    Assign, Cond, Bor, Band, Or, Xor, And, Eq, Ne, Lt, Gt, Le, Ge,
    Shl, Shr, Add, Sub, Mul, Div, Mod, Inc, Dec, Brak, Not, Rev
    // these are operators
};

struct identifier {
    int token;
    int hash; // the hash value of token
    string name; // the name of identifier
    
    // later processing
    int ctype; // int, real, cstring
    unsigned int addr; // address
} ; // current parsed idntifier

extern identifier *id_list = NULL, *cur_id = NULL;

void get_next_token() {
    char *last_pos;
    
    while ((token = *src)) {
        if (*src == '\n' || *src == ' ') {
            if (*src == '\n')
                ++line;
            ++src;
            continue;
        }
        if (isalpha(token) || token == '_') { // id
            last_pos = src; // ??
            int hash = token;
            string new_name;
            while (isalpha(*src) || isdigit(*src) || *src == '_') {
                new_name.push_back(*src);
                hash = hash * 147 + *src;
                src++;
            }
            // writing in the empty space closest from begin.
            for (cur_id = id_list; cur_id->token > 0; cur_id++) { // tokens begin with 128, 0 -> unused
                if (cur_id->hash == hash && new_name == cur_id->name) {
                    token = cur_id->token;
                    return ;
                }
            }
            cur_id->name = new_name;
            cur_id->hash = hash;
            token = cur_id->token = Id; // is a identifier
            return ;
        }
        // dealing with integer value and floating-point value
        else if (isdigit(token)) { // numbers
            char tmp[50];
            int size = 0;
            bool is_float = false;
            while (isdigit(*src) || *src == '.') {
                if (*src == '.') {
                    is_float = true;
                }
                tmp[size++] = *src++;
            }
            // token_val unused?
            if (is_float) {
                token = Fnum;
                ftoken_val = atof(tmp);
            }
            else {
                token = Inum;
                token_val = atoi(tmp);
            }
            return ;
        }
        // strings
        else if (token == '"') {
            last_pos = Data;
            ++src;
            while (*src != 0 && *src != '"') {
                token_val = *src++;
                // supporting only '\n' and '\t' for now
                if (token_val == '\\') {
                    token_val = *src++;
                    if (token_val == 'n') {
                        token_val = '\n';
                    }
                    if (token_val == 't') {
                        token_val = '\t';
                    }
                }
                *Data++ = token_val;
            }
            src++;
            token = Cstr;
            token_val = (long)last_pos; // return the address of string
            *Data = '\0';
            return ;
        }
        else if (token == '/') { // comment?
            if (*(src + 1) == '/') {
                while (*src != 0 && *src != '\n') {
                    ++src;
                }
                continue;
            }
            else {
                token = Div;
                return ;
            }
        }
        else if (token == '=') {
            if (*(src + 1) == '=') { // ==
                ++src;
                token = Eq;
            }
            else {
                token = Assign;
            }
        }
        else if (token == '+') {
            if (*(src + 1) == '+') {
                ++src;
                token = Inc;
            }
            else {
                token = Add;
            }
        }
        else if (token == '-') {
            if (*(src + 1) == '-') { // "--"
                ++src;
                token = Dec;
            }
            else { // "-"
                token = Sub;
            }
        }
        else if (token == '!') {
            if (*(src + 1) == '=') {
                ++src;
                token = Ne;
            }
            else {
                token = Not;
            }
            // not adding "!id" yet
        }
        else if (token == '<') {
            if (*(src + 1) == '=') {
                ++src;
                token = Le;
            }
            else if (*(src + 1) == '<') { // >>
                ++src;
                token = Shl;
            }
            else {
                token = Lt;
            }
        }
        else if (token == '>') {
            if (*(src + 1) == '=') {
                ++src;
                token = Ge;
            }
            else if (*(src + 1) == '>') { // >>
                ++src;
                token = Shr;
            }
            else {
                token = Gt;
            }
        }
        else if (token == '&') {
            if (*(src + 1) == '&') {
                ++src;
                token = And;
            }
            else {
                token = Band;
            }
        }
        else if (token == '|') {
            if (*(src + 1) == '|') {
                ++src;
                token = Or;
            }
            else {
                token = Bor;
            }
        }
        else if (token == '~') {
            token = Rev;
        }
        else if (token == '^') {
            token = Xor;
        }
        else if (token == '%') {
            token = Mod;
        }
        else if (token == '*') {
            token = Mul;
        }
        else if (token == '?') { // ????
            token = Cond;
        }
        else if (token == '[') { // ????
            token = Brak;
        }
        // ???
        else if (token == '~' || token == ';' || token == '{' || token == '}' || token == '(' || token == ')' || token == ']' || token == ',' || token == ':') {
            // directly return the character as token;
        }
        ++src;
        return ;
    }
    return ;
}

void id_list_inintialize() {
    // supporting only 1000 different identifer.
    if ((id_list = (identifier *)malloc(sizeof(identifier) * 1000)) == NULL) {
        printf("failed to allocate memory for identifier list.\n");
        return ;
    }
    memset(id_list, 0, sizeof(identifier) * 1000);
    src = (char *)"string int real else if return while in out void main";
    for (int tok = String; tok <= Main; tok++) {
        get_next_token();
        cur_id->token = tok;
    } // loading predefined identifier into id_list.
}













// testing part:
// WARNING: will cause side effect of src and id_list

void test() {
    static const string mat[] = {
        "Inum", "Fnum", "Cstr", "Fun", "Sys", "Id",
        "String", "Int", "Real", "Else", "If", "Return", "While",
        "In", "Out", "Void", "Main",
        // the former are pre-defined identifier
        "Assign", "Cond", "Bor", "Band", "Or", "Xor", "And", "Eq", "Ne", "Lt", "Gt", "Le", "Ge",
        "Shl", "Shr", "Add", "Sub", "Mul", "Div", "Mod", "Inc", "Dec", "Brak", "Not", "Rev"
    };
    while (*src != 0) {
        get_next_token();
        if (token == 0)
            break;
        if (token >= 128) {
            if (Id <= token && token <= While)
                printf("<%s>\n", cur_id->name.data());
            else {
                printf("<%s, %ld, %lf>\n", mat[token-128].data(), token_val, ftoken_val);
                if (token == Cstr) {
                    cout << (char *)token_val << endl;
                }
            }
        }
        else
            printf("<%c>\n", token);
        ftoken_val = token = token_val = 0; // delete pre
    }
}


#endif /* lexical_analysis_hpp */
