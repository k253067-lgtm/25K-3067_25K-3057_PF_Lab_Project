// REMOVE DISPLAYING CPU HAND IN FINALIZED EXCEPT WILDCARD
// cpuplay()  likho code similar as userplay
#include <stdio.h>
#include <stdlib.h>               //<-for rand(), exit()
#include <time.h>                 //making sure ke val har run pe random ho
#include <string.h>               //for string functions, fgets, strscspn, and strcpy
#include <ctype.h>                //for converting input card to all uppercase to perform checks
#include <unistd.h>               // for sleep(), making delay b4 line of code execution so its easier to track with eye for user
int randomind(int start, int end) // to generate a random index to pick card from/shuffle etc
{
    int randomind = 0;
    randomind = (start) + rand() % (end - start + 1); // from range start to end, end-start+1, +1 bcuz runs till rand()% num-1. end-start bcuz otherwise it will add 0 to start to the end, instead of going 10-44, ill go to 10-(44+10)
    return randomind;
}
int searchcard(char hand[][3], char *search) // since hand must be sorted already, will search for card until encounters x
{
    for (int i = 0; i < 42; i++)
    {
        if (strcmp(hand[i], "x") == 0)
            return -1; // end of cards, restt is all x
        if (strcmp(hand[i], search) == 0)
        { // if card to search for matches card at index, return its index
            return i;
        }
    }
    return -1; // any other cass means card still not found, return -1
}

void sorthand(char hand[][3]) // shift all the x placeholders in hand to right hand side of the hand array while all cards shift to left side in same order
{                             // for when yow remove a card from hand leaves a gap in middle of hand, so group all cards back together
    int j = 0;                // position of card

    for (int i = 0; i < 42; i++)
    {
        if (strcmp(hand[i], "x") != 0)
        {
            if (i != j)
            {
                strcpy(hand[j], hand[i]);
                strcpy(hand[i], "x");
            }
            j++; // if card found, make j cardposn+1.
            // if j is not incremented, that means there is an x in position right after the latest real card found.
            //  then i!=j, therefore move the next card found by i to position j which is still storing position of that first x we found
            // unless the real card comes to j, j will not increment, ensuring that all cards get sorted and none left out
        }
    }
    // vv after the above loop is done, all cards shifted to left of arr
    // this means j now holds position of the first x, and from j till end everything should be made x now
    for (int k = j; k < 42; ++k)
    {
        strcpy(hand[k], "x");
    }
}

/* CHANGE: drawcard now checks bounds before copying to avoid UB when deck/hand exhausted */
void drawcard(char hand[][3], char deck[][3])
{

    int i = 0;
    for (i; i < 42; i++)
    {
        if (strcmp(hand[i], "x") == 0) // as soon as first gap/empty space/x is found in hand store its ind
        {
            break;
        }
    }
    int j = 0;
    for (j; j < 45; j++)
    {
        if (strcmp(deck[j], "x") != 0) // as soon as first CARD is found in deck store its ind
        {
            break;
        }
    }
    if (i < 42 && j < 45) // check both indices syill in array boundaries
    {
        strcpy(hand[i], deck[j]); // copy the card at j in deck -> at i in hand
        strcpy(deck[j], "x");
    }
}

void init_deck(char arr[][3]) // each colour should hav 2 sets of cards from 1-5 except W which has 1 set 1-5

{
    for (int i = 0; i < 5; i++) // 0-4=R1-R5
    {
        snprintf(arr[i], 3, "R%d", i + 1); // snprintf will let me store changing string to array
    }
    for (int i = 5; i < 10; i++) // 4-9= G1-G5
    {
        snprintf(arr[i], 3, "G%d", i - 4);
    }
    for (int i = 10; i < 15; i++) // 10-14=B1-B5
    {
        snprintf(arr[i], 3, "B%d", i - 9);
    }
    for (int i = 15; i < 20; i++) // y1-y5
    {
        snprintf(arr[i], 3, "Y%d", i - 14);
    }
    for (int i = 20; i < 25; i++) /// repeat for 2nd sets for each color
    {
        snprintf(arr[i], 3, "R%d", i - 19);
    }
    for (int i = 25; i < 30; i++)
    {
        snprintf(arr[i], 3, "G%d", i - 24);
    }
    for (int i = 30; i < 35; i++)
    {
        snprintf(arr[i], 3, "B%d", i - 29);
    }
    for (int i = 35; i < 40; i++)
    {
        snprintf(arr[i], 3, "Y%d", i - 34);
    }
    for (int i = 40; i < 45; i++) // finally, last five spaces go to w1-w5
    {
        snprintf(arr[i], 3, "W%d", i - 39);
    }
}

void shuffle(char deck[][3])
{
    char tempshuffled[45][3];
    for (int i = 0; i < 45; i++)
    {
        strcpy(tempshuffled[i], deck[i]); // copy deck into tempshuffled
    }
    for (int i = 0; i < 45; i++)
    {
        int j = randomind(0, 44);
        char temp[3]; // to temporarily hold card while swapping around in shuffle
        strcpy(temp, tempshuffled[i]);
        strcpy(tempshuffled[i], tempshuffled[j]);
        strcpy(tempshuffled[j], temp);
    }
    for (int i = 0; i < 45; i++)
        strcpy(deck[i], tempshuffled[i]); // copy shuffled deck back into deck
}

/* void dispdeck(char arr[][3])
{ // dispdeck for printing deck, not used in actual game, for testing
    void redtxt();
    void whitetxt();
    void greentxt();
    void yellowtxt();
    void bluetxt();
    void purpletxt();
    printf("Deck: [ ");

    for (int i = 0; i < 45; i++)
    {
        if (arr[i][0] == 'R')
        {
            redtxt();
            printf("\n%s", arr[i]);
            whitetxt();
        }
        else if (arr[i][0] == 'G')
        {
            greentxt();
            printf("\n%s", arr[i]);
            whitetxt();
        }
        else if (arr[i][0] == 'B')
        {
            bluetxt();
            printf("\n%s", arr[i]);
            whitetxt();
        }
        else if (arr[i][0] == 'Y')
        {
            yellowtxt();
            printf("\n%s", arr[i]);
            whitetxt();
        }
        else if (arr[i][0] == 'W')
        {
            purpletxt();
            printf("\n%s", arr[i]);
            whitetxt();
        }
    }
    printf("\n ]");
} */
void purpletxt()
{
    printf("\033[0;35m");
}
void greentxt()
{
    printf("\033[0;32m");
}
void yellowtxt()
{
    printf("\033[0;33m");
}
void redtxt()
{
    printf("\033[0;31m");
}
void whitetxt()
{
    printf("\033[0;0m");
}
void bluetxt()
{
    printf("\033[0;34m");
}
void welcome() // message display when starting game
{
    printf("==============Welcome to");
    greentxt();
    printf(" Co");
    yellowtxt();
    printf("lor");
    redtxt();
    printf(" Bat");
    bluetxt();
    printf("tle");
    whitetxt();
    printf("!==============");
}

void init_startinghands(char user[][3], char cpu[][3], char deck[][3])
{
    for (int k = 0; k < 42; ++k) // initialise all hands with all x (placeholdeer)
    {
        strcpy(user[k], "x");
        strcpy(cpu[k], "x");
    }

    for (int i = 0; i < 3; i++) // first 3 cards to start off for each hand
    {
        int ind;
        do
        {
            ind = randomind(0, 44); // ensuring 1st 3 cards are still random if for some reason shuffle puts some in groups
        } while (strcmp(deck[ind], "x") == 0);
        strcpy(user[i], deck[ind]); // move random card from deck to user hand
        strcpy(deck[ind], "x");

        do // same procedure but forvcpu hand
        {
            ind = randomind(0, 44);
        } while (strcmp(deck[ind], "x") == 0);
        strcpy(cpu[i], deck[ind]);
        strcpy(deck[ind], "x");
    }
}

void displayhand(char hand[][3])
{ // all coloured text functions defined below
    void redtxt();
    void whitetxt();
    void greentxt();
    void yellowtxt();
    void bluetxt();
    void purpletxt();
    printf("Hand:");
    int i = 0;
    while (i < 42 && strcmp(hand[i], "x") != 0) // while index is still inside hand and is on an actual card
    // depending on card first character, display it in its text color
    {
        if (hand[i][0] == 'R') // if first char is R, make text red, print card, make text white back....
        {
            redtxt();
            printf("\n%s", hand[i]);
            whitetxt();
        }
        else if (hand[i][0] == 'G')
        {
            greentxt();
            printf("\n%s", hand[i]);
            whitetxt();
        }
        else if (hand[i][0] == 'B')
        {
            bluetxt();
            printf("\n%s", hand[i]);
            whitetxt();
        }
        else if (hand[i][0] == 'Y')
        {
            yellowtxt();
            printf("\n%s", hand[i]);
            whitetxt();
        }
        else if (hand[i][0] == 'W')
        {
            purpletxt();
            printf("\n%s", hand[i]);
            whitetxt();
        }
        i++;
    }
    printf("\n");
}

// count cards in hand
int hand_size(char hand[][3])
{
    int count = 0;
    for (int i = 0; i < 42; ++i) // in range of hand full array,
    {
        if (strcmp(hand[i], "x") == 0) // if you find x, since array is sorted,
                                       // there must be no cards after.
            break;
        count++; // if not x, is card so cardcount+1
    }
    return count;
}

// check if card is playable by comparing withh discardtop
int is_playable(char card[3], char discardtop[3])
{
    if (card[0] == 'W') // it its wildcard, can be played anytime so return 1
        return 1;
    if (card[0] == discardtop[0]) // if color matches can bbe plaeyed
        return 1;
    if (card[1] == discardtop[1]) // if number matches can be played
        return 1;
    return 0;
}

void userplay(char userhand[][3], char discardtop[], char cpuhand[][3], char deck[][3]) // cpuhand for special card reveal
{                                                                                       // Update function IF IMPLEMENTING SKIP AND DRAW 2, func for users turn
    char wcolor;
    char cardplayed[4];
    int nwrongplay = 0;
    char choice;
    // vv Using the lop to check if user entered card is valid
    do
    {
        if (nwrongplay > 0) // this implemented just to make sure users first time at the start doesnt show invalid
        {
            printf("Invalid card.\n");
        }

        printf("Do you want to draw a card from the deck?[Y/N]:\n");
        scanf(" %c", &choice);
        getchar(); // removing \n that scanf adds at the end which will harm fgets
        if (toupper(choice) == 'Y')
        {
            drawcard(userhand, deck);
            displayhand(userhand);
        }

        printf("Enter card to play from your hand, press Enter to skip and draw card from deck:\n");
        fgets(cardplayed, 4, stdin);                  // 3 was making problems sometimes would overflow sochanged to 4
        cardplayed[strcspn(cardplayed, "\n")] = '\0'; // changing newline to null terminator (pf theory ki tarah)
        cardplayed[0] = toupper(cardplayed[0]);       // convert to uppercase
        nwrongplay++;
    } while ((strlen(cardplayed) != 2) || (cardplayed[0] != 'W' && cardplayed[0] != 'R' && cardplayed[0] != 'G' && cardplayed[0] != 'B' && cardplayed[0] != 'Y') || (cardplayed[1] != '1' && cardplayed[1] != '2' && cardplayed[1] != '3' && cardplayed[1] != '4' && cardplayed[1] != '5'));
    //^^^keep saying invalid if the card string>2chars OR cardplayed is not any of the colors in game OR cardplayed is not any number 1-5 in game
    // vv Check if card even exists in user hand
    while (searchcard(userhand, cardplayed) == -1) // if searchcard cant find, returns -1, card not in hand
    {
        printf("Card is not in hand.\n");
        printf("Do you want to draw a card from the deck?[Y/N]:\n");
        scanf(" %c", &choice);
        getchar();                  // remove \n at end
        if (toupper(choice) == 'Y') // toupper capitalizes so i dont hav to check for lowercase too
        {                           // if user says yes to drawing card
            drawcard(userhand, deck);
            displayhand(userhand);
        }
        printf("Enter card to play from your hand, press Enter to skip and draw card from deck :\n");
        fgets(cardplayed, 4, stdin);
        cardplayed[strcspn(cardplayed, "\n")] = '\0';
        cardplayed[0] = toupper(cardplayed[0]);
    }

    // v Using loop to check if card can be played onto current discardtop
    while ((cardplayed[0] != discardtop[0]) && (cardplayed[1] != discardtop[1]) && (cardplayed[0] != 'W'))
    { // of discardtop and card to play, if color doesnt match and even the number doesnt match and the card isnt even a W:
        printf("Card does not match colour, number of previous card, and is not a special card.\n");
        printf("Do you want to draw a card from the deck?[Y/N]:\n"); // ask user to draw card
        scanf(" %c", &choice);
        getchar();
        if (toupper(choice) == 'Y')
        {
            drawcard(userhand, deck);
            displayhand(userhand);
        }
        printf("Enter card to play from your hand, press Enter to skip and draw card from deck:\n");
        fgets(cardplayed, 4, stdin);
        cardplayed[strcspn(cardplayed, "\n")] = '\0';
        cardplayed[0] = toupper(cardplayed[0]);
    }

    // finally, play the card
    if (cardplayed[0] != 'W')
    { // if card played is not special, just throw it onto discardpile since previous loops
        // already checked for invalid cards
        strcpy(discardtop, cardplayed); // discard card
        int searchedindex = searchcard(userhand, cardplayed);
        if (searchedindex != -1)
        { // find and remove the played card from hand
            strcpy(userhand[searchedindex], "x");
            sorthand(userhand);
        }
    }
    else
    { // then it must be special w card so show cpu hand, then ask user which color to force them to play
        printf("CPU ");
        displayhand(cpuhand); // show cpuhand
        printf("Which color do you want the opponent to play next?[R/G/B/Y]:\n");
        do
        { // make sure color is from the 4 colors of the game RGBY
            scanf(" %c", &wcolor);
            getchar();
            wcolor = toupper(wcolor);
        } while (wcolor != 'R' && wcolor != 'G' && wcolor != 'B' && wcolor != 'Y');
        displayhand(cpuhand); // show user the hidden cpu hand
        switch (wcolor)
        { // depending on what color chosen to proceed with, attach 0 to it so its there as a placeholder card
          // by adding 0, opponent will not be able to match number
        case 'R':
            strcpy(discardtop, "R0");
            break;
        case 'G':
            strcpy(discardtop, "G0");
            break;
        case 'B':
            strcpy(discardtop, "B0");
            break;
        case 'Y':
            strcpy(discardtop, "Y0");
            break;
        default:
            break;
        }
        int searchedindex = searchcard(userhand, cardplayed);
        if (searchedindex != -1)
        {
            strcpy(userhand[searchedindex], "x"); // remove card played from hand
            sorthand(userhand);
        }
    }
}

void cpuplay(char cpuhand[][3], char userhand[][3], char discardtop[], char deck[][3]) // userhand for special w card reveal
{                                                                                      // plays first card it finds in hand that is playable
    void cardcolor(char arr[]);
    // find first playablecard in current hand
    int played = 0; // to check whether cpu played its turn or not
    for (int i = 0; i < 42; i++)
    {
        if (strcmp(cpuhand[i], "x") == 0)
        { // since hand sorted, if encounters x means all cards have been checked so end loop
            break;
        }
        if (is_playable(cpuhand[i], discardtop))
        {
            // play this card at i positon
            printf("CPU plays: ");
            cardcolor(cpuhand[i]);
            printf("\n");

            if (cpuhand[i][0] != 'W')
            { // if normal card, just throw into discardtop
                strcpy(discardtop, cpuhand[i]);
            }
            else
            { // this case, cpu played special w card

                // check which colours user has
                int userR = 0, userG = 0, userB = 0, userY = 0;

                for (int u = 0; u < 42; u++)
                {                                      // to search through userhand, since cpu cant just look the way user can
                    if (strcmp(userhand[u], "x") == 0) // checked all cards, so break loop
                        break;

                    char c = userhand[u][0]; // color of each card in user hand
                    // if a color found, set respective color presence to 1
                    if (c == 'R')
                        userR = 1;
                    else if (c == 'G')
                        userG = 1;
                    else if (c == 'B')
                        userB = 1;
                    else if (c == 'Y')
                        userY = 1;
                }

                if (userR == 0) // means user does not have red card,
                {
                    strcpy(discardtop, "R0"); // so its strateic to set color to red to force me to draw
                    printf("CPU chose color R\n");
                }
                else if (userG == 0) // same logic but for green.....
                {
                    strcpy(discardtop, "G0");
                    printf("CPU chose color G\n");
                }
                else if (userB == 0)
                {
                    strcpy(discardtop, "B0");
                    printf("CPU chose color B\n");
                }
                else if (userY == 0)
                {
                    strcpy(discardtop, "Y0");
                    printf("CPU chose color Y\n");
                }
                else
                { // means player has all colors, so might as well pick random color to set
                    int r = randomind(0, 3);
                    switch (r)
                    { // depending on random number select a color
                    case 0:
                        strcpy(discardtop, "R0"); // throw {color}{0} onto dicard SO THAT OPPONENT CANT MATCH NUMBEr
                        printf("CPU chose color R\n");
                        break;
                    case 1:
                        strcpy(discardtop, "G0");
                        printf("CPU chose color G\n");
                        break;
                    case 2:
                        strcpy(discardtop, "B0");
                        printf("CPU chose color B\n");
                        break;
                    case 3:
                        strcpy(discardtop, "Y0");
                        printf("CPU chose color Y\n");
                        break;
                    }
                }
            }

            strcpy(cpuhand[i], "x"); // remove the played  card from cpu hand

            sorthand(cpuhand);
            played = 1; // track that spu has made move
            break;
        }
    }
    // if not played draw until playable or deck empty
    if (played == 0)
    {
        int attempts = 0;
        while (!played)
        {
            int before = hand_size(cpuhand);
            drawcard(cpuhand, deck);
            int after = hand_size(cpuhand);
            // vv if hand size same b4 n after, deck emptyend loop
            if (after == before)
                break;
            // check last card (newly drawn) if playable
            int ind = after - 1;                                        // because sorthand makes sure cards are grouped to the left
            if (ind >= 0 && ind < 42 && strcmp(cpuhand[ind], "x") != 0) // if in boundsof cpuhand, and is real card
            {
                if (is_playable(cpuhand[ind], discardtop))
                {
                    // play drawn card
                    printf("CPU drew and plays: ");
                    cardcolor(cpuhand[ind]);
                    if (cpuhand[ind][0] != 'W') // if card not special just move to discardtop
                    {
                        strcpy(discardtop, cpuhand[ind]);
                    }
                    else
                    { // else...do w card work again (limitatio: not strategically choosing color this time)
                        int r = randomind(0, 3);
                        switch (r)
                        {
                        case 0:
                            strcpy(discardtop, "R0");
                            printf("CPU chose color R\n");
                            break;
                        case 1:
                            strcpy(discardtop, "G0");
                            printf("CPU chose color G\n");
                            break;
                        case 2:
                            strcpy(discardtop, "B0");
                            printf("CPU chose color B\n");
                            break;
                        case 3:
                            strcpy(discardtop, "Y0");
                            printf("CPU chose color Y\n");
                            break;
                        }
                    }
                    strcpy(cpuhand[ind], "x"); // remove card from hand
                    sorthand(cpuhand);
                    played = 1; // since cpu pplayed turn, update played
                    break;
                }
            }
            // safety guard to prevent infinite loops
            attempts++;
            if (attempts > 50) // the deck is not big enough to accomodate so many draws, so just end
                break;
        }
    }
}

void cardcolor(char arr[])
{ // check which color card passed as parameter is, depending on that print it in that color
    if (arr[0] == 'R')
    {
        redtxt();
        printf("\n%s", arr);
        whitetxt();
    }
    else if (arr[0] == 'G')
    {
        greentxt();
        printf("\n%s", arr);
        whitetxt();
    }
    else if (arr[0] == 'B')
    {
        bluetxt();
        printf("\n%s", arr);
        whitetxt();
    }
    else if (arr[0] == 'Y')
    {
        yellowtxt();
        printf("\n%s", arr);
        whitetxt();
    }
    else if (arr[0] == 'W')
    {
        purpletxt();
        printf("\n%s", arr);
        whitetxt();
    }
}

int main()
{
    char deck[45][3], userhand[42][3], cpuhand[42][3], discardtop[3]; // discardpile[45][3];//<-this one shud b stack;//var is enough
    srand(time(0));                                                   // makes sure ke jab program run ho truly random ho warna every runtime will make same choice of number

    /*for (int i = 0; i < 45; ++i)//initialize deck?? u did this already in inithands wala func
        strcpy(deck[i], "x");
    for (int i = 0; i < 42; ++i)
    {
        strcpy(userhand[i], "x");
        strcpy(cpuhand[i], "x");
    }*/

    // make loop for 1.play 2.help (tell abt wildcard etc) 3.exit
    int choice = 0;
    welcome();
    printf("\nPress 1 to play\nPress 2 for help\nPress 3 to Exit\n");
    scanf("%d", &choice);
    do
    {

        if (choice == 2)
        {
            printf("\nRules:\n1: Match either the number or colour of the last discarded card to play that card\n2:");
            purpletxt();
            printf(" There is the W card, this card can be played at any time, will reveal the Computer Player's hand,\n   and finally will then allow you to choose the color of card the Computer Player must play next.\n");
            whitetxt();
            printf("\n\tPress 1 to play\n\tPress 2 for help\n\tPress 3 to Exit\n");
            scanf("%d", &choice);
        }
        else if (choice == 1)
        {
            init_deck(deck);
            shuffle(deck);
            strcpy(discardtop, deck[0]); // start game, discard pile initialsed by card top of deck
            strcpy(deck[0], "x");        // top of deck card used so set to x
            init_startinghands(userhand, cpuhand, deck);
            printf("User ");
            displayhand(userhand);
            printf("Top of Discard Pile:");
            cardcolor(discardtop);
            printf("\n");

            bool loop = true;
            int turn = 0; // turn 0 = user turn , turn1 = CPU turn
            while (loop)
            {

                if (hand_size(userhand) == 0) // if user has no cards in hands, wins
                {
                    printf("\n\n=====You win!=====\n");
                    exit(1);
                }
                if (hand_size(cpuhand) == 0) // if cpu has no cards in hand, wins
                {
                    printf("\n\n=====CPU wins!=====\n");
                    exit(1);
                }

                if (turn == 0)
                { // user turn
                    printf("\n--- Your turn ---\n");
                    displayhand(userhand);
                    printf("Top of Discard Pile:");
                    cardcolor(discardtop);
                    printf("\n");
                    userplay(userhand, discardtop, cpuhand, deck);
                    sleep(1); // to give pleasant look of game progressing, otherwise everything just pops up at once
                    turn = 1; // next iteration of while loop will be cpu turn now
                }
                else
                {
                    printf("\n--- CPU turn ---\n");
                    printf("Top of Discard Pile:\n");
                    cardcolor(discardtop);
                    printf("\n");
                    cpuplay(cpuhand, userhand, discardtop, deck);
                    turn = 0; // next iteration will be user turn now
                }
            }
            // gameplay loop end
        }
        if ((hand_size(userhand) == 0 || hand_size(cpuhand) == 0) && (choice != 1))
        { // if userhand is empty or cpuhand is emptyn break=end game
            break;
        }
    } while (choice != 3);
    return 0;
}
