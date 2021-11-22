/********************************************************************
 Name: Sehra Elahi
 Date: 08/12/2017
 *********************************************************************/
//===========================================================================================================================================================
//Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <ctype.h>

#define NUMBER_OF_POINTS 400
//frame buffer 60x30
//variables and char used
//dec is the same as i = 0
int dec = 0;
int pair_num = -1;
char choice;
//fname used for the save and load commands
char fname1[]={"star_universe.dat"};
char fname2[]={"star_pair.dat"};
char fname3[]={"para_meter.dat"};

//Coordinates of the stars
double getDistance(double x1, double y1, double x2, double y2)
{
    return (sqrt((x2 - x1)* (x2 - x1) + (y2 - y1) *(y2 - y1)));
}

struct stars *mybang;
//Data structure for stars
struct stars
{
    int id;
    char name[30];
    double x;
    double y;
};
//The pair structure: serial number ID of stars for both partners and the distance apart (light years)
struct pair *mypair;
struct pair
{
    int id_1st;
    int id_2nd;
    double distance;
};
//Used for the save and load command
struct parameter
{
    int total;
    int len_p;
};
//===========================================================================================================================================================
//Defining the function needed for the frame buffer --> graphic operation.

//The closest pair of stars
void find_closest()
{
    int i, j = 0, p1 = 0, p2 = 1;
    double points[NUMBER_OF_POINTS][2];
    int k = 0;
    for (k = 0; k < dec; k++) {
        points[k][0] = mybang[k].x;
        points[k][1] = mybang[k].y;
    }
    //The distance between two stars
    //getDistance refer to the coordinates
    //mypair refers to ID of the stars
    double shortestDistance = getDistance(points[p1][0], points[p1][1], points[p2][0], points[p2][1]);
    for (i = 0; i<dec; i++) {
        for (j = i + 1; j < dec; j++) {
            double distance = getDistance(points[i][0], points[i][1], points[j][0], points[j][1]);
            bool egg = false;
            int h = 0;
            for (h = 0; h < dec; h++) {
                if (mypair[h].id_1st > -1) {
                    if (mypair[h].distance == distance) {
                        egg = true;
                    }
                }
            }
            if (egg == false) {
                if (shortestDistance > distance) {
                    p1 = i;
                    p2 = j;
                    shortestDistance = distance;
                }
            }
        }
    }
    //Finding closest pair --> part of naming command:
    printf("The closest pair of stars are no. %d and %d\n",p1,p2);
    printf("They are %0.3f light years apart\n", shortestDistance);

    printf("Would you like to name this pair (y/n)\n");
    scanf("%c",&choice);

    if (choice == 'y' || choice == 'Y')
    {
        pair_num++;
        mypair[pair_num].id_1st = p1;
        mypair[pair_num].id_2nd = p2;
        mypair[pair_num].distance = shortestDistance;

        printf("Enter your full name: ");
        scanf(" %[^\n]s",&*mybang[p1].name);
        printf("Enter your spouse full name: ");
        scanf(" %[^\n]s",&*mybang[p2].name);
        //using %s and %s to store the names rather than saying "a pair of star has been named after you and your spouse", this caused problems, confisuing the names
        printf("Congratulations a pair of stars has been named after %s and %s! \n", mybang[p1].name, mybang[p2].name);
    }
}
//===========================================================================================================================================================
int main()
{
    time_t t;
    int i;
    // Intializes random number generator
    srand((unsigned)time(&t));
    srand((int)time(0));

    int status = 0;
    char u_input[40];
    printf(">>>>");
    //Using fgets instead of gets, gets do not check array bound, characters more longer than 40 will also be stored.
    fgets( u_input, 40, stdin);
    //===========================================================================================================================================================
    //The quit command
    status = 1;
    while (status != 0) {
        //Without strncmp the commands do not work (except for bang command), I changed all string comapare to strncmp and commands started to work.
        if (strncmp(u_input, "quit", 4) == 0){ //Using strncmp instead of strcmp and adding , 4 at the end.
            printf("*** Quiting the program ***\n");
            status = 0;
            break;
        }
        //===========================================================================================================================================================
        //List command:
        else if (strncmp(u_input, "list", 4) == 0) { //Again strncmp:
            bool a = false;
            for (i = 0; i < dec; i++) {
                printf("Star %d\n", mybang[i].id);
                printf("Coords: (%0.3f, %0.3f)\n", mybang[i].x, mybang[i].y);
                a = true;
            }

            if (a == false)
            {
                printf("No star exists! Please use the bang command.");
            }
            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Name Command:
        else if(strncmp(u_input, "name", 4) == 0) {
            find_closest(); //using function find_closest
            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Pair command:
        else if (strncmp(u_input, "pair", 4) == 0) {

            for (int i = 0; i < dec; i++) {
                if (mypair[i].id_1st > -1) {
                    //printf("%d", i);
                    printf("Star %d\n", mypair[i].id_1st);
                    printf("Distance %0.3f\n", mypair[i].distance);
                    printf("Name %s\n", mybang[mypair[i].id_1st].name);
                    printf("Coords: (%0.3f, %0.3f)\n", mybang[mypair[i].id_1st].x, mybang[mypair[i].id_1st].y);
                    printf("Star %d\n", mypair[i].id_2nd);
                    printf("Name %s\n", mybang[mypair[i].id_2nd].name);
                    printf("Coords: (%0.3f, %0.3f)\n", mybang[mypair[i].id_2nd].x, mybang[mypair[i].id_2nd].y);
                    printf("***********************************\n");
                }
            }

            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Draw command:

        else if (strncmp(u_input, "draw", 4) == 0) {
            system("clear");

            bool a = false;
            int row = 0;
            for(row = 0; row<30; row++)
            {
                int col = 0;
                for(col=0; col<60; col++)
                {
                    int e = 0;
                    for (e = 0; e < dec; e++) {
                        if(col==(int)mybang[e].y && row==(int)mybang[e].x)
                        {
                            if (strlen(mybang[e].name) >0)
                            {
                                printf("*");
                            }
                            else {
                                printf(".");
                            }
                        }
                        a = true;
                    }
                    printf(" ");
                }
                printf("\n");
            }

            if (a == false)
            {
                printf("No stars exist! Please use the bang command.");
            }

            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Show command:
        else if (strncmp(u_input, "show", 4) == 0) {
            char yourname[30];
            int loc = -1;
            int loc_in_pair = -1;
            printf("Enter your full name: ");

            //scanf(" %s", &*yourname);
            scanf(" %[^\n]s", &*yourname);
            int g = 0;
            for (g = 0; g < dec; g++) {
                if (strncmp(mybang[g].name, yourname, 30) == 0) {
                    loc = g;
                }
            }

            if (loc != -1) {
                int d = 0;
                for (d = 0; d < dec; d++) {
                    if (loc == mypair[d].id_1st || loc == mypair[d].id_2nd)
                    {
                        printf("Record found\n");
                        loc_in_pair = d;
                    }
                }
            }
            else {
                printf("Record Not found\n");
            }

            if (loc_in_pair != -1) {
                system("clear");
                char temp1[30],temp2[30];
                strcpy(temp1, "");
                strcpy(temp2, "");
                int row = 0;
                for(row=0; row<30; row++)
                {
                    int col = 0;
                    for(col=0; col<60; col++)
                    {
                        int e = 0;
                        for (e = 0; e < dec; e++) {
                            if(col==(int)mybang[e].y && row==(int)mybang[e].x)
                            {
                                if (e == mypair[loc_in_pair].id_1st) {
                                    while (strncmp(temp1, mybang[e].name, 30) != 0) { //temp1 variable does not get stored in RAM
                                        strcpy(temp1, mybang[e].name);
                                    }
                                    printf("*");
                                }else if(e == mypair[loc_in_pair].id_2nd){
                                    printf("*");
                                    printf("%s & %s",temp1,mybang[e].name);
                                    while (strncmp(temp1, "", 0) != 0) {
                                        strcpy(temp1, "");
                                    }
                                }else{
                                    printf(".");
                                }

                            }
                        }
                        printf(" ");
                    }
                    printf("\n");
                }
            }

            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Save command:
        else if (strncmp(u_input, "save", 4) == 0) {

            FILE *fp1, *fp2, *fp3;
            struct stars t1[dec];

            fp1=fopen(fname1,"ab");
            int e = 0;
            for (e = 0; e < dec; e++) {
                t1[e].id=mybang[e].id;
                strcpy(t1[e].name, mybang[e].name);
                t1[e].x=mybang[e].x;
                t1[e].y=mybang[e].y;
            }

            fwrite(&t1,sizeof(t1[dec]),dec,fp1);

            fclose(fp1);

            struct pair t2[dec];

            fp2=fopen(fname2,"ab");

            for (e = 0; e < dec; e++) {
                t2[e].id_1st=mypair[e].id_1st;
                t2[e].id_2nd=mypair[e].id_2nd;
                t2[e].distance=mypair[e].distance;
            }

            fwrite(&t2,sizeof(t2[dec]),dec,fp2);

            fclose(fp2);

            struct parameter a1;

            fp3=fopen(fname3,"ab");
            a1.total=dec;
            a1.len_p=pair_num;
            fwrite(&a1,sizeof(a1),1,fp3);
            fclose(fp3);

            printf("Thanks: you have saved the universe\n");
            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        //Load Command:
        else if (strncmp(u_input, "load", 4) == 0) {
            FILE *fp1, *fp2, *fp3;

            struct parameter a1;
            fp3=fopen(fname3,"rb");
            while(1)
            {
                fread(&a1,sizeof(a1),1,fp3);

                if(feof(fp3))
                {
                    break;
                }
                dec=a1.total;
                pair_num=a1.len_p;
                mybang = realloc(mybang, dec * sizeof *mybang);
                mypair = realloc(mypair, dec * sizeof *mypair);
            }

            fclose(fp3);

            struct stars t[dec];

            fp1=fopen(fname1,"rb");

            while(1)
            {
                fread(&t,sizeof(t[dec]),dec,fp1);

                if(feof(fp1))
                {
                    break;
                }
                int e = 0;
                for (e = 0; e < dec; e++) {
                    mybang[e].id=t[e].id;
                    strcpy(mybang[e].name, t[e].name);
                    mybang[e].x=t[e].x;
                    mybang[e].y=t[e].y;
                }
            }

            fclose(fp1);

            struct pair t2[dec];

            fp2=fopen(fname2,"rb");

            while(1)
            {
                fread(&t2,sizeof(t2[dec]),dec,fp2);

                if(feof(fp2))
                {
                    break;
                }
                int ee = 0;
                for (ee = 0; ee < dec; ee++) {

                    mypair[ee].id_1st=t2[ee].id_1st;
                    mypair[ee].id_2nd=t2[ee].id_2nd;
                    mypair[ee].distance=t2[ee].distance;
                }
            }

            fclose(fp2);

            printf("Congratulations: your saved universe was restored!\n");
            printf(">>>>");
            fgets( u_input, 40, stdin);
            status = 1;
        }
        //===========================================================================================================================================================
        else {
            if(strlen(u_input)>3 || u_input=="bang"){

                char str[40];
                strcpy(str, u_input);
                char piece1[20] = ""
                , piece2[20] = "";
                char * p;

                p = strtok(str, " "); // call the strtok with str as 1st arg for the 1st time.
                if (p != NULL) // check if we got a token.
                {
                    strcpy(piece1, p); // save the token.
                    p = strtok(NULL, " "); // subsequent call should have NULL as 1st arg.
                    if (p != NULL) // check if we got a token.
                        strcpy(piece2, p); // save the token.
                }

                int ig = atoi (piece2);
                dec=ig;
                printf ("The Big Bang has occured!");

                if ((strcmp(piece1, "bang") == 0) && (dec==floor(dec))) {
                    //system("clear");
                    mybang = realloc(mybang, dec * sizeof *mybang);
                    mypair = realloc(mypair, dec * sizeof *mypair);
                    int e = 0;
                    for (e = 0; e < dec; e++) {
                        mypair[e].id_1st = -1;
                        mypair[e].id_2nd = -1;
                        mypair[e].distance = 0;
                    }

                    // Print bang random numbers stars
                    for (i = 0; i < dec; i++) {

                        int x = rand() % 30;
                        int y = rand() % 60;
                        mybang[i].id = i;
                        mybang[i].x = x;
                        mybang[i].y = y;
                        strcpy(mybang[i].name, "\0");

                        //Plot(x, y, '.');
                    }
                    int row = 0;
                    for(row=0; row<30; row++)
                    {
                        int col = 0;
                        for(col=0; col<60; col++)
                        {
                            for (e = 0; e < dec; e++) {
                                if(col==(int)mybang[e].y && row==(int)mybang[e].x)
                                {
                                    printf(".");
                                }
                            }
                            printf(" ");
                        }
                        printf("\n");
                    }

                    printf(">>>>");
                    fgets( u_input, 40, stdin);
                    status = 1;
                }
                else {
                    printf(">>>>");
                    fgets( u_input, 40, stdin);
                    status = 1;
                }
            }else{
                printf(">>>>");
                fgets( u_input, 40, stdin);
                status = 1;
            }
        }
        //===========================================================================================================================================================
    }

    //_getch();
    return 0;
}
//===========================================================================================================================================================
