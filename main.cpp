
#include <cstdio>
#include <cstdlib> //für Heap notwendig
//#include <memory.h> //je nach Betriebssystem dass auch noch erforderlich
#include <cstring> //für struct

void swap(int *ptrB, int *ptrC);
void fill(char *text);
char *createTextArray();
void deleteTextArray(char *abc);
struct person;
struct person *createPerson(char *firstname, char *lastname, int age);
int PKW(int n, int r);
long f(int n);
long f2(int n);
struct element;
struct element *insert(int data, int p, struct element **list);

int main() {

    int x = 2;
    int y = 4;
    int result = x;

    for(int i=1; i<y; i++){
        result *= x;
    }
    printf("x^y = %i\n", result);

//POINTER
    int a = 42;
    int* ptr; //nennt man Zeigervariablen da sie auf die adresse zeigt wo ein Wert drinnen gespeichert ist

    ptr = &a; // liefert adresse/speicherort von a zurück

    printf("x =    %i\n", a);
    printf("ptr =  %p\n", ptr); // == &a
    printf("&a =   %p\n", &x);
    printf("*ptr =   %i\n", *ptr); //dereferenzierungsoperator //kriegen wert an der speicherstelle ptr zurück

    *ptr = 189;
    printf("*ptr =   %i\n", *ptr);

//SWAP

    int b = 52;
    int c = 37;
    printf("b = %i, c = %i\n",b, c);

    swap(&b, &c);
    printf("b = %i, c = %i\n",b, c);


//ARRAYS
    char text[100]; //das steht schon zur compile Zeit fest
    fill(text);//fill(text, 100)
    printf("%s\n", text); //funktioniert nur für Zeichen Ausgabe, für Ziffern brauch ich eine schleife



//Malloc
    char *abc;
    //int size;

    //printf("Bitte gib ein Größe ein: ");
    //scanf("%i", &size);
    abc = createTextArray();
    printf("%s\n", abc);
    deleteTextArray(abc);


//STRUCT
    struct person *p1;
    p1 = createPerson("Clarissa", "Treml", 31);
    //printf("%s %s ist %i Jahre alt.\n", (*p1).firstname, p1->lastname, p1->age);

    free(p1);



//Algorithmus
//n Anzahl der wagen   r anzahl der Räder
    printf("Anzahl PKWs: %i\n", PKW(4, 10));
    printf("Anzahl PKWs: %i\n", PKW(5, 6)); //Fehlermeldung weil r und n nicht zusammen passen



//REKURSION
    long r = f(6);
    printf("6! = %li\n", r);

    //iterrative variante
    r = f2(6);
    printf("6! = %li\n", r);



//Verkettete Listen
    struct element *list = NULL;
    insert(10, 0, &list);
    insert(6, 0, &list);


    return 0;
}





void swap(int *ptrB, int *ptrC){
    int tmp = *ptrB;
    *ptrB = *ptrC;
    *ptrC = tmp;
}

void fill(char*text){ //void fill(car *text, int size)
    int i;
    for(i = 0; i < 26; i++){ //i=0; i < size-1; i++      size-1 wegen der \0
        text[i] = 'A' + i; //unter einfachen '' ist es eigentlich nur der ASCII-Code und daher können Operationen damit durchgeführt werden
    //gleich wie *(text + i) = 'A' + i;    statt A geht auch 65 (ascii code für A)
    //*(text + i) = 65 + (i%26);  da wird das alphabet so oft ausgegeben bis das Array aufgefühlt ist also 99 weil \0 braucht 1 byte
    }
    text[i] ='\0';
    //*(text + i) = '\0';

}

char *createTextArray(){

    //pendant to New in java
    //why not char abc = [100]   weil sobald funktion beendet ist lokale variable nicht mehr benutzbar
    //malloc reserviert Speicherplatz am Heap und das bleibt erhalten über das Ende der Funktion gültig
    char *abc = (char *)malloc(sizeof(char)*100); //need (char *) before malloc because malloc is of type void and text is of type char
    int i;
    for( i = 0; i < 99; i++){
        abc[i] = 'a' + (i % 26);
    }
    abc[i] = '\0';
    return abc;//kann nur zurückliefern über die Funktion wenn es eine adresse ist


    //char *createTextArray(int size){
    //char *abc = (char *)malloc(sizeof(char)*size);.....
}

void deleteTextArray(char *abc){
    free(abc);
}

struct person { //die größe von so eine Person ist 74 byte weil pro char 1 byte und int sind 4 byte
    char firstname[20];
    char lastname[50];
    int age;

};

struct person *createPerson(const char *firstname, const char *lastname, int age){
    struct person *p;
    p = (struct person *)malloc(sizeof(struct person));
        //ich habe jetzt eine pointer variable und muss die direferenzieren um auf den Inhalt zuzugreifen
        //p selber beinhaltet nur eine Speicheradresse und zwar die von malloc zurückgegeben wurde

        //(*p) muss in klammer sein weil der punkt operator eine höhere priorität halt als der * operator....es muss ja zuerst dereferenziert werden

    //(*p).age = age;
    p->age = age;
    //strcpy((*p).firstname, firstname);
    strcpy(p->firstname, firstname);
    //strcpy((*p).lastname, lastname);
    strcpy(p->lastname, lastname);


    return p;

}

int PKW(int n, int r){
    //Vorbedingungen
    if(n < 0 || r < 0){
        printf("Anzahl r oder n ist unglültig.\n");
        return -1; //man nimmt negative werte als Fehlermeldung da oft es von etwas nichts negatives gibt
    }
    if (r % 2 != 0){
        printf("Nur gerade Anzahl an Rädern möglich.\n");
        return -1;
    }
    if(2*n > r || r > 4*n){
        printf("r und n passen nicht zusammen.\n");
        return -1;
    }
    //Algorithmus
    return (r - 2*n)/2;

}

long f(int n){
  if (n <= 1){
      return 1;                                                                                        // 1
  }
  return n* f(n-1); //n* ist der letzte Befehl der durchgeführt wird, daher keine Endrekursion       1+1+1
}                                                                                                     //T(n) = 4 * (n-1) + 1 => O(n)

//Rekursion und Laufzeit
long f2(int n){
    long r = 1;                         //kosten von 1
    for(int i = 2; i <= n; i++){        //1 + n + n-1  int i=2  wird 1 mal ausgeführt und i<=n wird  n-mal verglichen und i++ wird n-1 mal durchgeführt
        r *= i;                         //n-1   r*=i wird n-1 mal durchgeführt
    }
    return r;                           //1
    //T(n) = 1 + 1+n+n-1 + n-1 + 1 = 3n + 1
    //eine lineare Laufzeitfunktion

}


int f3(int n){
    int r = 1;                              //1
    for(int i = 0; i < n; i++){             //1 + n+1 + n
        for(int j = 0; j < 2*n; j++){       //(1 + 2n+1 + 2n)  *n
            r += i+j;                       //(2 * 2n) * n
        }
    }
    return r;                               //1
    //T(n) = 4 + 2n +2n +4n^2 + 2n +2n^2 = 6n^2 + 6n + 4 => O(n^2)  eine quadratische Funktion
}

int f4(int n){
    int r = 1;                              //1
    for(int i = 1; i < n; i = i*2){         //1 + (log2(n) + 1 + 1) + 2* (log2(n)+1)
        for(int j = 0; j < 2*n; j++){       //(1 + 2n+1 + 2n) * log2(n)
            r += i+j;                       //(2 * 2n) * log2(n)
        }
    }
    return r;                               //1
    // T(n) = 4 + 5*log2(n) + 10*n*log2(n)  => O(n*log(n))
}
/*
 zb n = 100
 i = 1
 i = 2
 i = 4
 i = 8
 i = 16
 i = 32
 i = 64
 i = 128
 => 8 Durchläufe
 1 * 2 * 2 * 2 * ... * 2 >= n
 die zweier kann ich so zusammenfassen (das ist ja auch das was mich interessiert
 2^k >= n => k >= log2(n) => log2(100) ca. 7.5 => aufgerundet 8


 */

int f5(int n) {
    int r = 1;                         // 1

    for (int i = n; i >= 1; i /= 2) {        // 1 + log2(n) + 1 + log2(n)
        for (int j = 0; j < 2 * n; j++) {   // (1 + (2*n + 1) + 2*n)          * log2(n)
            r += i * j;                // (2*n + 2*n)                      * log2(n)
        }
    }
    return r;                          // 1
}
// 1 * 2 * 2 * 2 ... * 2 < n => 2^k < n => k < log2(n)
// 1, 2, 4, 8, 16, 32, 64 f. n = 100
// T(n) = 4 + 5*log2(n) + 10*n*log2(n)  => O(n*log(n))



//Laufzeit abhänging von den Daten (hier was in dem Array drinnen steht)
int f6(int n, int a[]) {
    int r = 1;                              //1

    for (int i = 0; i < n ; i++) {          //1 + (n+1) + n
        if(a[i] > 100){                     //1 * n
            for (int j = 0; j < n; j++) {   //(1 + (n+1) + n) * n
                r += i * j;                 //2 * n
            }
        }

    }
    return r;                               //1
}
//i++ primitive operation
//Best Case: Alle Elemente im Array sind kleiner oder gleich 100  alle a[i] <=100
//lineare laufzeit, die innere schlaufe fällt weg => O(n)

//Worst Case: alle a[i] > 100 => O(n^2) quadratische Laufzeit

//Average Case: situations abhängig zb 1/3 aller a[i] > 100: O(n^2) unterscheidet sich nur um 1/3 vom Worst Case = ((n^2)/3)



//VERKETTETE LISTEN
struct element { //zur definition von so einem element
    int data; //um es allgemeiner zu machen kann man auch einen void pointer nehmen          //grün
    struct element *next; //struct element ist Datentyp                                      //weiß
    struct element *prev; //denn zeiger zeigt wieder auf ein element                        //blau
};
struct element *insert(int data, int p, struct element **list){
    struct element *h = *list; //hilfsvariable h auf listen anfang gestellt
    struct element *n;

    n = (struct element *) malloc((sizeof(struct element))); //(struct element *) ist ein type case und notwendig da malloc void ist
    n->data = data;

    if (*list == NULL){ //dann zeigt next wieder auf sich selber und prev auch das es nur ein einziges element in der Liste gibt und zwar das gerade jetzt erstellte
        n->next = n;
        n->prev = n;
        return n;
    }

    for (int i = 0; i < p-1; i++){
        h = h->next;  //(*h).next;   hilfspointer falls ich es irgendwo anders einsetzten möchte
    }

    n->prev = h;
    n->next = h->next;
    n->next->prev = n;
    n->prev->next = n;

    if (p == 0){
        *list = n;
    }
    return n;
}



