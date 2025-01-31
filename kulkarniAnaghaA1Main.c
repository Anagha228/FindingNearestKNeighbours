#include "given.h"

//helper function to sort(algorithm)
void sortDistances(float distances[NUM_SAMPLES], int indices[NUM_SAMPLES], int isAscending);

//helper function to  read test data
int readFromTestFile(char fileName[30], struct Animal testData [NUM_TEST_DATA]);


int main(int argc, char* argv[]) {
    struct Animal dataZoo [NUM_SAMPLES];
    struct Animal dataZoo1 [NUM_SAMPLES];
    struct Animal testData [NUM_TEST_DATA];
    struct Animal testData1 [NUM_TEST_DATA];
    int v1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int v2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    float euclideanDistance, jaccardSimilarity;
    int hammingDistance;
    int newSample [NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int k =5, myClass;
    float myAccuracy=0;
    float myAccuracy2;
    //int whichDistanceFunction=1; 
    int kNearestNeighbors [NUM_SAMPLES];

    //printf ("hello!!");

    // task 1
    readFromFile(argv[1], dataZoo);
    for(int i =0; i<NUM_SAMPLES; i++){
        printf("%s   ", dataZoo[i].animalName);
        for (int j = 0; j<NUM_FEATURES; j++ ){
            printf("%d  ",  dataZoo[i].features[j]);
        }
        printf("%d \n", dataZoo[i].classLabel);
    }
    printf ("\n");

    // task 2
    distanceFunctions(v1, v2, &euclideanDistance, &hammingDistance, &jaccardSimilarity); 
    printf("EuclideanDistance: %f\n", euclideanDistance);
    printf("Hamming distance: %d\n", hammingDistance);
    printf("Jaccard Similarity: %f\n", jaccardSimilarity);
    printf ("\n");

    // task 3
    printf ("Nearest neighbors for new sample with Euclidean Distance: "); 
    findKNearestNeighbors(dataZoo, newSample, k, 1, kNearestNeighbors);
    for(int i = 0; i<k;i++){
        printf("%d ", kNearestNeighbors[i]);
    }
    printf ("\n"); 
    printf ("Nearest neighbors for new sample with Hamming Distance: "); 
    findKNearestNeighbors(dataZoo, newSample, k, 2, kNearestNeighbors);
    for(int i = 0; i<k;i++){
        printf("%d ", kNearestNeighbors[i]);
    }
    printf ("\n"); 
    printf("Nearest neighbors for new sample with Jaccard Similarity: ");
    findKNearestNeighbors(dataZoo, newSample, k, 3, kNearestNeighbors);
    for(int i = 0; i<k;i++){
        printf("%d ", kNearestNeighbors[i]);
    }
    printf ("\n");  
    printf ("\n");

    // task 4
    // euclideanDistance
    myClass = predictClass(dataZoo, newSample, 1, k);
    printf("The predicted class is: %d\n\n", myClass);
    //hammingDistance
    myClass = predictClass(dataZoo, newSample, 2, k);
    printf("The predicted class is: %d\n\n", myClass);
    //jaccardSimilarity
    myClass = predictClass(dataZoo, newSample, 3, k);
    printf("The predicted class is: %d\n\n", myClass);
    
    // task 5
    readFromTestFile(argv[2], testData);
    //readFromTestFile(argv[2], testData1);
    //findAccuracy(dataZoo, 1, testData, k);
    

    myAccuracy=findAccuracy(dataZoo, 3, testData, k);
    printf("\nThe accuracy for the test data is %f", myAccuracy);
    myAccuracy2=0;
    
    //myAccuracy2=findAccuracy(dataZoo, 3, testData, k);
    return 0;
}
