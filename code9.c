#include <stdio.h>
#include <string.h>

void mirror(char str[], int index) {
    if (index < 0)
        return;   

    printf("%c", str[index]);
    mirror(str, index - 1);   
}

int main() {
    char str[100];

    scanf("%s", str);

    int length = strlen(str);

    mirror(str, length - 1);

    return 0;
}
