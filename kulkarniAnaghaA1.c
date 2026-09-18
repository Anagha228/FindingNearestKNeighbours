#include "givenA1.h"
#include "helper.h"


/* Task 1 */
int readFromFile (  char fName [30], 
                    struct Animal dataZoo [NUM_SAMPLES]){
                
    FILE * fileHandle;
    fileHandle = fopen (fName, "r");
    char allData[NUM_SAMPLES][NUM_SAMPLES];
    int noOfRows=0;
    

    if (fileHandle == NULL){
        printf("couldnt open file %s \n", fName);
        return -1; // -1 indicates an error 
    }
    else {
        while ((!feof (fileHandle)) && (noOfRows <= 100)){

            fgets(allData[noOfRows], NUM_SAMPLES, fileHandle);
            noOfRows = noOfRows+1;
        }
        fclose(fileHandle);
        for(int i = 0; i<100; i++){
            sscanf(allData[i], "%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d"
            ,dataZoo[i].animalName
            ,&dataZoo[i].features[0]
            ,&dataZoo[i].features[1]
            ,&dataZoo[i].features[2]
            ,&dataZoo[i].features[3]
            ,&dataZoo[i].features[4]
            ,&dataZoo[i].features[5]
            ,&dataZoo[i].features[6]
            ,&dataZoo[i].features[7]
            ,&dataZoo[i].features[8]
            ,&dataZoo[i].features[9]
            ,&dataZoo[i].features[10]
            ,&dataZoo[i].features[11]
            ,&dataZoo[i].features[12]
            ,&dataZoo[i].features[13]
            ,&dataZoo[i].features[14]
            ,&dataZoo[i].features[15]
            , &dataZoo[i].classLabel);
            }
        
        return 1;
        
    }
}//end of readFromFile

//Task 2

void distanceFunctions (int vector1 [NUM_FEATURES],
                        int vector2 [NUM_FEATURES],
                        float * euclideanDistance,
                        int * hammingDistance,
                        float * jaccardSimilarity
){
    
    float sum=0, powerSum=0;
    float oneMatch = 0, zeroMatch = 0;
    float difference =0; 


    for (int i = 0; i<=15; i++){
        
        sum = (vector1[i] - vector2[i]);
        powerSum= pow(sum, 2) + powerSum; 
    }

    *euclideanDistance = pow(powerSum, 0.5);
    
    *hammingDistance = 0;

    for (int i = 0; i<=15; i++){
        if (vector1[i] != vector2 [i]){
            *hammingDistance = *hammingDistance+1;
        }

    }//loop end 
    *hammingDistance = *hammingDistance+ 0;
    for (int i = 0; i<=15; i++){

        if(vector1[i] == 1 && vector2[i] == 1){
            oneMatch += 1; 
        }

        if (vector1[i]==0 && vector2[i] == 0){
            zeroMatch += 1;
        }

    }

    difference = NUM_FEATURES-zeroMatch;
    *jaccardSimilarity = oneMatch/difference;
}//task 2 done 

// Task 3 

void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], 
                            int newSample [NUM_FEATURES], 
                            int k, 
                            int whichDistanceFunction, 
                            int kNearestNeighbors [NUM_SAMPLES]){
    float euclideanDistance;
    int hammingDistance;
    float jaccardSimilarity;
    float tempDistance [NUM_SAMPLES];
    int indices[NUM_SAMPLES], j;

    for (int i = 0; i<NUM_SAMPLES; i++) {
        indices[i]=0;

    }

    for (int i = 0; i<NUM_SAMPLES; i++) {
        indices[i]=i;

        distanceFunctions(newSample, dataZoo[i].features, &euclideanDistance, &hammingDistance, 
        &jaccardSimilarity); 

        if (whichDistanceFunction == 1){
            tempDistance[i] = euclideanDistance;
        }else if (whichDistanceFunction == 2){
            tempDistance[i] = (float) hammingDistance;
        }else if (whichDistanceFunction == 3){
            tempDistance[i] = jaccardSimilarity;
        }
    }

    if(whichDistanceFunction== 1||whichDistanceFunction == 2){
        sortDistances(tempDistance, indices, 1);
    }else if (whichDistanceFunction == 3){
        sortDistances(tempDistance, indices, 0);
    }
    for (j = 0; j < k; j++) {
        kNearestNeighbors[j] = indices[j];
    }
} //task 3 done 

//sorting funtion 
void sortDistances(float distances[NUM_SAMPLES], int indices[NUM_SAMPLES], int isAscending) {
    for (int i = 0; i < NUM_SAMPLES - 1; i++) {
        for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
            int condition = isAscending 
                ? (distances[j] > distances[j + 1]) 
                : (distances[j] < distances[j + 1]);

            if (condition) {
                // Swap distances
                float tempDistance = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = tempDistance;

                // Swap indices
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }
}// end of helper function

/* Task 4 */
int predictClass (  struct Animal dataZoo [NUM_SAMPLES], 
                    int newSample [NUM_FEATURES], 
                    int whichDistanceFunction, 
                    int k){
    int kNearestNeighbors [NUM_SAMPLES];
    int myClasses[k], nOU=0, myMax, predictClass =9999;
    int UniqueClass[k], myCount[k]; 
    //printf("in predict class\n");
    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction,kNearestNeighbors);
   // printf("in find nearest\n");
    for(int i = 0; i<k; i++){
        myClasses[i]= dataZoo[kNearestNeighbors[i]].classLabel; 
    }
    for (int i = 0; i<k; i++){
        UniqueClass[i]=0;
        myCount [i] =0;
    }

    UniqueClass[0] = myClasses[0];

    //printf("start of sorting the classes\n");
    for (int i = 0; i<k; i++){
        //printf ("\n all class %d\n", myClasses[i]);
        for (int j = 0; j<k; j++){
            //printf("\n%d UniqueClass, %d myClasses", UniqueClass[j], myClasses[i]);
            if (myClasses[i] == UniqueClass[j] && UniqueClass[j] !=0){
                //printf ("\n double class found %d\n", myClasses[i]);
                myCount[j]++;
                break;
            }
                
            if(UniqueClass[j] == 0){
                UniqueClass[j] = myClasses[i];
                //printf ("\n i = [%d] new class found[%d] %d\n",i, j,UniqueClass[j]);
                nOU =j;
                myCount[j]++;
                break;
            }  
        }
    }
    //printf("end of for loop unique class %d\n", nOU);
    myMax =0;
    for (int i=0; i<=nOU; i++){
        if (myCount[i]> myMax){
            myMax= myCount[i];
            //predictClass = UniqueClass[i];
        }  
    }
    
    for (int i=0; i<=nOU; i++){
        if (myCount[i] == myMax){
            //printf("\n%d UniqueClass, %d myCount[%d]", UniqueClass[i], myCount[i], i);
            if (predictClass>UniqueClass[i]){
                predictClass = UniqueClass[i];
            }
         }  
    }
    return predictClass; 
}

/* Task 5 */
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], 
                    int whichDistanceFunction, 
                    struct Animal testData [NUM_TEST_DATA], 
                    int k){
    int myPredictedClass[NUM_TEST_DATA];
    float myCounter=0;
    float myAccuracyPercent;
    
    //printf("%f\n", a);
    //printf("in findAccuracy %d\n", whichDistanceFunction);
    for (int i =0; i<NUM_TEST_DATA; i++){
        //printf("Calling predict class\n");
        myPredictedClass[i] =  predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);
        if (myPredictedClass[i] == testData[i].classLabel){
            myCounter++;

        }
    }
    
   
    for (int i =0; i<NUM_TEST_DATA; i++){
        //printf("\nmy predicted: %d , my accual: %d", myPredictedClass[i], testData[i].classLabel );
        printf("%d ", myPredictedClass[i]);
    }
    
    myAccuracyPercent = (myCounter)/((float)NUM_TEST_DATA);

    printf("\n%.f \n%d ",myCounter, NUM_TEST_DATA);
    return myAccuracyPercent;
}

// helper function reads test data
int readFromTestFile(char fileName[30], struct Animal testData [NUM_TEST_DATA]){
    char allData[NUM_TEST_DATA][NUM_SAMPLES];
    int x=0;
    //int j; 
    char * token;
    FILE * fptr = fopen (fileName, "r");
    
    
    if (fptr == NULL) {
        printf("Could not open file %s\n", fileName);
        return -1; // Error
    }else {
        while (!feof (fptr) || x<NUM_TEST_DATA){
        
            fgets(allData[x],NUM_SAMPLES, fptr );
            //printf("Fgets all data %s\n", allData[x]);
            token = strtok(allData[x], ",");
            
            //printf("token: %s\n", token);
            strcpy(testData[x].animalName, token);
           
                for (int j =0; j<NUM_FEATURES; j++){
                    
                    token = strtok(NULL, ",");
                    testData[x].features[j] = atoi(token);
                    //printf("Features:%d ", testData[x].features[j]);
                }
                token = strtok(NULL, ",");
                testData[x].classLabel = atoi(token);
                
                x++;
            //printf("Name: %s\n",testData[i].animalName);
        }

    }
    
    fclose(fptr);
    return 1;
}
