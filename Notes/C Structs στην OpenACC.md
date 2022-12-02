# [C Structs στην OpenACC](https://docs.nvidia.com/hpc-sdk/compilers/openacc-gs/#openacc-c-struct)

Η OpenACC υποστηρίζει στατικά arrays και pointers σε δυναμικά arrays σε δομές struct.

```c
typedef struct{
    float x, y, z;
 }point;

extern point base[1000];

void vecaddgpu( point *restrict r, int n ){
    #pragma acc parallel loop present(base) copyout(r[0:n])
    for( int i = 0; i < n; ++i ){
        r[i].x = base[i].x;
        r[i].y = sqrtf( base[i].y*base[i].y + base[i].z*base[i].z );
        r[i].z = 0;
    }
}
```

Ένας pointer σε βαθμωτό struct αντιμετωπίζεται σαν arrays με ένα μόνο στοιχείο και το ορίζουμε σαν `r[0:1]` 

```c
typedef struct{
    base[1000];
    int n;
    float *x, *y, *z;
 }point;

extern point A;

void vecaddgpu(){
    #pragma acc parallel loop copyin(A) \
        copyout(A.x[0:A.n], A.y[0:A.n], A.z[0:A.n])
    for( int i = 0; i < A.n; ++i ){
        A.x[i] = A.base[i];
        A.y[i] = sqrtf( A.base[i] );
        A.z[i] = 0;
    }
}
```

Αντιγράφουμε το `A` στο device, και με αυτό τον τρόπο αντιγράφονται και τα μέλη του struct το στατικό array `A.base` και το βαθμωτό `A.n`. Τα δυναμικά μέλη `A.x`, `A.y` και `A.z` αντιγράφονται μετά στην συσκευή. Το struct `Α` πρέπει να αντιγραφεί πριν τα δυναμικά μέλη του, είτε τοποθετώντας το struct  νωρίτερα στο data clause , είτε κάνοντας copy ή create στο device. Εάν το struct δεν είναι preset στο device όταν αντιγράφονται τα δυναμικά μέλη, τότε δεν είναι δυνατή η πρόσβαση στα δυναμικά μέλη, όπως το `A.x[i]`

Ο pointer σε ένα struct αντιμετωπίζεται σαν array με ένα στοιχείο. Εάν το struct περιέχει μέλη pointers, πρέπει πρώτα να αντιγράψουμε το struct στο device και στη συνέχεια να δημιουργήσουμε ή να αντιγράψουμε τα μέλη pointers:

```c
typedef struct{
    int n;
    float *x, *y, *z;
 }point;

void vecaddgpu( point *A, float* base ){
    #pragma acc parallel loop copyin(A[0:1]) \
        copyout(A->x[0:A->n], A->y[0:A->n], A->z[0:A->n]) \
        present(base[0:A->n])
    for( int i = 0; i < A->n; ++i ){
        A->x[i] = base[i];
        A->y[i] = sqrtf( base[i] );
        A->z[i] = 0;
    }
}
```

Προσοχή κατά την αντιγραφή struct που  περιέχουν pointers στον host. Στο device τα μέλη με pointer ενημερώνονται με τους pointer στο device. Εάν γίνει αντιγραφή αυτών τον pointer στο host, δεν θα είναι έγκυροι.

Όταν δημιουργούμε ή αντιγράφουμε μέλη struct στο device δεσμεύουμε χώρο μνήμης για όλο το struct. Δεν υποστηρίζεται δέσμευση μνήμης για  μέρος του struct, ή δέσμευση μνήμης για μόνο ένα μέλος.

Τα structs και τα pointer μέλη τους διαχειρίζονται με τα δυναμικά data directive:

```c
typedef struct{
    int n;
    float *x, *y, *z;
 }point;

void move_to_device( point *A ){
    #pragma acc enter data copyin(A[0:1])
    #pragma acc enter data create(A->x[0:A->n], A->y[0:A->n], A->z[0:A->n])
}

void move_from_device( point* A ){
    #pragma acc enter data copyout(A->x[0:A->n], A->y[0:A->n], A->z[0:A->n])
    #pragma acc enter data delete(A[0:1])
}

void vecaddgpu( point *A, float* base ){
    #pragma acc parallel loop present(A[0:1]) \
        present(A->x[0:A->n], A->y[0:A->n], A->z[0:A->n]) \
        present(base[0:A->n])
    for( int i = 0; i < A->n; ++i ){
        A->x[i] = base[i];
        A->y[i] = sqrtf( base[i] );
        A->z[i] = 0;
    }
}
```