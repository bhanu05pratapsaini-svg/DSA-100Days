#include <stdio.h>
#include <string.h>

#define MAX 1000
#define NAME_LEN 100

int main() {
    int n;
    scanf("%d", &n);

    char names[MAX][NAME_LEN];
    int count[MAX];
    int unique = 0;

    char temp[NAME_LEN];

    for (int i = 0; i < n; i++) {
        scanf("%s", temp);

        int found = -1;

        for (int j = 0; j < unique; j++) {
            if (strcmp(names[j], temp) == 0) {
                found = j;
                break;
            }
        }

        if (found != -1) {
            count[found]++;
        } else {
            strcpy(names[unique], temp);
            count[unique] = 1;
            unique++;
        }
    }

    int maxVotes = 0;
    char winner[NAME_LEN];

    for (int i = 0; i < unique; i++) {
        if (count[i] > maxVotes) {
            maxVotes = count[i];
            strcpy(winner, names[i]);
        } 
        else if (count[i] == maxVotes) {
            if (strcmp(names[i], winner) < 0) {
                strcpy(winner, names[i]);
            }
        }
    }

    printf("%s %d\n", winner, maxVotes);

    return 0;
}