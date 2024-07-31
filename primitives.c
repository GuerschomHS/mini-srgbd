#include "wr/primitives.h"
#include <string.h>
#include <stdlib.h>
int getSeparator(char *chaine,char separator){

    size_t t = strlen(chaine);
    // position du separator
    int pos = 0;
    for(int i=0;i<t;i++){

        if(*(chaine+i) == separator){

            pos = i;
            break;
        }
    }
    return pos;
}

void attribPart2(char *dest,char *source,int sep,int part){

    int dest_pos = 0;
    int to = (part == 1)?sep:strlen(source);
    int from =(part == 1)?0:sep+1;
    for(int i=from;i<to;i++){

        if(i == to ){

            *(dest+dest_pos) = '\0';
            break;
        }else{

            if(*(source+i) != '\n'){

                *(dest+dest_pos) = *(source+i);
                dest_pos++;
            }
        }

    }

}

char * concate(char* chaine1,char* chaine2){

    int t = (strlen(chaine1)+strlen(chaine2)+1)*sizeof(char);
    char *dest = malloc(sizeof(*dest)*t);
    int pos = 0;
    for(int i=0;i<strlen(chaine1);i++){

        *(dest+pos) = *(chaine1+i);
        pos++;
    }
    *(dest+pos) = '\0';
    for(int i=0;i<strlen(chaine2);i++){

        *(dest+pos) = *(chaine2+i);
        pos++;
    }
    *(dest+pos) = '\0';
    //printf("result <%s>\n",dest);
    return dest;
}

char int2char(int x){

    char r='0';
    switch(x){

        case 0:r='0';
        break;
        case 1:r='1';
        break;
        case 2:r='2';
        break;
        case 3:r='3';
        break;
        case 4:r='4';
        break;
        case 5:r='5';
        break;
        case 6:r='6';
        break;
        case 7:r='7';
        break;
        case 8:r='8';
        break;
        case 9:r='9';
        break;
    }
    return r;
}
int* getArrayOfNumber(int x){

    static int tab[3]={-1,-1,-1};
    if(x < 10) tab[0] = x;
    else if( x > 9 && x < 100){

        int n1 = x / 10,
            n2 = x % 10;
        tab[0] = n1;
        tab[1] = n2;
    }
    else if( x > 99 && x < 1000){

        int n1 = x/100,
            n2 = x % 100;
        tab[0] = n1;
        if(n2 < 10){

            tab[1] = 0;
            tab[2] = n2;
        }else{

            int nv = n2/10;
            int nv2 = n2 % 10;
            tab[1] = nv;
            tab[2] = nv2;
        }
    }

    return tab;
}

char* toStr(int* tab){

    char* chaine = malloc(4 * sizeof(char));
    int pos = 0;
    for(int i=0;i<3;i++){

        char c = int2char(*(tab+i));
        *(chaine+pos) = c;
        pos++;
    }
    *(tab+pos) = '\0';

    return chaine;
}


char* type2str(DATA_TYPE type){

    char nameType[7];
    switch(type){

    case INT:
        strcpy(nameType,"INT");
        break;
    case STR:
        strcpy(nameType,"STRING");
        break;
    case FLT:
        strcpy(nameType,"FLOAT");
        break;
    }

    return nameType;
}

char* delN(char* ch){

    int t = strlen(ch);
    for(int i=0;i<t;i++){

        if(*(ch+i)=='\n') *(ch+i) = '\0';
        else *(ch+i) = *(ch+i);
    }

    return ch;
}
