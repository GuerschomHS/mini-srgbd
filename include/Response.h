#ifndef RESPONSE_H_INCLUDED
#define RESPONSE_H_INCLUDED

struct Reponse_{

    char action_titre[20];
    char msg[80];
    int etat;
};
typedef struct Reponse_ RE_;
void setReponse(RE_* r,char* action,char* msg,int etat);
void printReponse(RE_ r);
#endif // RESPONSE_H_INCLUDED
