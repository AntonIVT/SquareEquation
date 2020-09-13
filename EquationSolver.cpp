#include <stdio.h>
#include <math.h>
#include <assert.h>

#define INFINITE_SOLVES -1
#define EPSILON 1E-6
#define DEBUG_MODE
#define NUMBER_OF_TESTS 10

/// \file

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
Approximate x with precision 1E-6
\param[in, out]  x
*/
void Approximation(double* x);

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
Solves a square equation ax^2 + bx + c = 0
\param[in]  a a-coef
\param[in]  b b-coef
\param[in]  c c-coef
\param[out] x1 pointer to the first  root
\param[out] x2 pointer to the second root
*/
int SquareEquationSolver(double a, double b, double c, double* x1, double* x2);

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
Solves line equation bx + c = 0
\param[in] b b-coef
\param[in] c c-coef
\param[out] x1 pointer to the first  root
\param[out] x2 pointer to the second root
*/
int LineEquationSolver(double b, double c, double* x1, double* x2);

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
Input coefficents a, b, c 
[in] a pointer to the coef a
[in] b pointer to the coef b
[in] c pointer to the coef c
*/
int Input(double* a, double* b, double* c);

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
UnitTest input 10 tests from in.txt and check result
*/
void UnitTest();

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
Solves one equation from terminal
*/
void ManualInput();

//-------------------------------------------------------------------------------------------------------------------------------------

/*!
main()
*/
int main() {
    #ifdef DEBUG_MODE
    UnitTest();
    #else
    ManualInput();
    #endif
    return 0;
}

//-------------------------------------------------------------------------------------------------------------------------------------

void Approximation(double* x){

    assert(x != NULL);

    if (fabs(*x) < EPSILON) *x = 0.0;
}

//-------------------------------------------------------------------------------------------------------------------------------------

int SquareEquationSolver(double a, double b, double c, double* x1, double* x2){

    assert(isfinite(a)); // 
    assert(isfinite(b)); //Checking does a, b, c are rational numbers 
    assert(isfinite(c)); //

    assert(x1 != NULL); //
    assert(x2 != NULL); //Checking does pointers exists

    assert(x1 != x2);   //Checking does pointers has different values

    double discr = b * b - 4 * a * c;

    Approximation(&discr);

    if (discr == 0.0) {
        *x1 = *x2 = (-1) * b / (2 * a);
        if (*x1 == -0.0) *x1 = *x2 = 0.0;
        return 1;
    }
    else if (discr > 0.0) {
        double discr_sqrt = sqrt(discr);

        *x1 = ((-1) * b + discr_sqrt) / (2 * a);
        *x2 = ((-1) * b - discr_sqrt) / (2 * a);

        if (*x1 == -0.0) *x1 = 0.0;
        if (*x2 == -0.0) *x2 = 0.0;

        return 2;
    }
    else return 0; //if (discr < 0)
}

//-------------------------------------------------------------------------------------------------------------------------------------

int LineEquationSolver(double b, double c, double* x1, double* x2){

    assert(isfinite(b)); //Checking does b, c are rational numbers 
    assert(isfinite(c)); //

    assert(x1 != NULL);  //
    assert(x2 != NULL);  //Checking does pointers exists

    assert(x1 != x2);    //Checking does pointers has different values

    if (b == 0.0) {
            return (c == 0.0) ? INFINITE_SOLVES : 0;
        }
        else {
            *x1 = *x2 = (-1) * c / b;
            if (*x1 == -0.0) *x1 = *x2 = 0.0;
            return 1;
        }
}

//-------------------------------------------------------------------------------------------------------------------------------------

int Input(double* a, double* b, double* c){

    assert(a != NULL); //
    assert(b != NULL); //Checking does pointers exists
    assert(c != NULL); //

    assert(a != b);    //
    assert(b != c);    //Checking does pointers has different values

    printf("Enter coeffiicients a, b, c\n");

    rewind(stdin);
    int check = scanf(" %lg %lg %lg", a, b, c);
    if (check != 3){
        printf("You entered wrong type\n");
        return Input(a, b, c);      
    }

    printf("a = %lg, b = %lg, c = %lg\n", *a, *b, *c);
    printf("Did you enter coefficents correctly? Y/N \n");

    char tmp = 0;
    scanf(" %c", &tmp);
    return (tmp == 'Y') ? 0 : Input(a, b, c);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void UnitTest(){

        FILE* input;

        input = fopen("in.txt", "r");
        if (input == NULL){
           printf("in.txt doesnt exists");
           return;
        }
        double a = 0.0, b = 0.0, c = 0.0;
        double truex1 = 0.0, truex2 = 0.0;
        int trueNumberOfRoots = 0;

        for(int i = 1; i <= NUMBER_OF_TESTS; i++){
            fscanf(input ," %lg %lg %lg %lg %lg %d", &a, &b, &c, &truex1, &truex2, &trueNumberOfRoots);

            Approximation(&a);
            Approximation(&b);
            Approximation(&c);

            double x1 = 0.0, x2 = 0.0;
            int NumberOfRoots = 0;

            if (a == 0.0) NumberOfRoots = LineEquationSolver(b, c, &x1, &x2);
            else NumberOfRoots = SquareEquationSolver(a, b, c, &x1, &x2);
            
            int flag = -1;

            switch (NumberOfRoots) {
                case 0 : if 
                    (!trueNumberOfRoots)
                        flag = 1;
                    break;

                case 1 : 
                    if (trueNumberOfRoots == 1 && truex1 == x1 && truex2 == x2)
                        flag = 1;
                    break;

                case 2 :
                    if (trueNumberOfRoots == 2 && ((truex1 == x1 && truex2 == x2) || (truex1 == x2 && truex2 == x1)))
                        flag = 1;
                    break;

                case INFINITE_SOLVES :
                    if (trueNumberOfRoots == -1)
                        flag = 1;
                    break;
    
                default : 
                    flag = -1;
            }
            if (flag == 1)
                printf("#TEST %2d PASSSED#\n", i);
            else
                printf("#TEST %2d FAILED#\n", i);
       }
       printf("All tests are done\n");
       fclose(input);
}

//-------------------------------------------------------------------------------------------------------------------------------------

void ManualInput(){

    printf("# EquationSolver 2000 by Anton\n"
           "# Solves square equations like ax^2 + bx + c = 0\n"
           "# a, b, c - rational numbers\n");
    
    double a = 0.0, b = 0.0, c = 0.0;
    Input(&a, &b, &c);

    Approximation(&a);
    Approximation(&b);
    Approximation(&c);
    
    double x1 = 0.0, x2 = 0.0;
    int NumberOfRoots = 0;
    if (a == 0.0) NumberOfRoots = LineEquationSolver(b, c, &x1, &x2);
    else NumberOfRoots = SquareEquationSolver(a, b, c, &x1, &x2);
    
    switch (NumberOfRoots) {
    case 0: printf("Yout equation doesnt have roots\n");
        break;

    case 1: printf("Your equation have one root x = %lg\n", x1);
        break;

    case 2: printf("Your equation have two roots: x1 = %lg, x2 = %lg\n", x1, x2);
        break;

    case INFINITE_SOLVES: printf("Your equation have infinite roots\n");
        break;
    
    default: printf("ERROR your equation have %d roots\n", NumberOfRoots);
    }
}