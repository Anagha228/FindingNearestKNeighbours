#include "givenA1.h"
#include "helper.h"



int main(int argc, char* argv[]) {
    struct Animal dataZoo [NUM_SAMPLES];
    //struct Animal dataZoo1 [NUM_SAMPLES];
    struct Animal testData [NUM_TEST_DATA];
    //struct Animal testData1 [NUM_TEST_DATA];
    int v1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int v2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    float euclideanDistance, jaccardSimilarity;
    int hammingDistance;
    int newSample [NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int k =5, myClass;
    float myAccuracy=0;
    int choice=0, choice1executed = 0;
    //int whichDistanceFunction=1; 
    int kNearestNeighbors [NUM_SAMPLES];

    //printf ("hello!!");
    do {
        printf ("\nHere is the menu - enter a number between 1 and 5. \n\n");
        printf ("1.   Read from a animal data file.\n");
        printf ("2.   Distance functions between vector 1 and vector2.\n");
        printf ("3.   Finding k nearest neighbours to the features of the animals. \n");
        printf ("4.   Predict the class.\n");
        printf ("5.   Find accuracy to evaluate the performance of the algorithm.\n");
        printf ("\nEnter your choice: ");
        scanf ("%d", &choice);
        

        if (choice <1 || choice >5){
            return 0;
        }       

        if (choice ==1){
            choice1executed = 1;
        }

        if (choice1executed == 1){
    
            switch (choice) {
                case 1:
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
                break;
                case 2:
                    // task 2
                    distanceFunctions(v1, v2, &euclideanDistance, &hammingDistance, &jaccardSimilarity); 
                    printf("EuclideanDistance: %f\n", euclideanDistance);
                    printf("Hamming distance: %d\n", hammingDistance);
                    printf("Jaccard Similarity: %f\n", jaccardSimilarity);
                    printf ("\n");
                break;
                case 3:
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
                break;
                case 4:
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
                break;
                case 5:
                    // task 5
                    readFromTestFile(argv[2], testData);
                    //readFromTestFile(argv[2], testData1);
                    //findAccuracy(dataZoo, 1, testData, k);
                    myAccuracy=findAccuracy(dataZoo, 1, testData, k);
                    printf("\nThe accuracy for the test data is %f\n\n", myAccuracy);
                    myAccuracy=0;
                    //printf("second function");
                    myAccuracy=findAccuracy(dataZoo, 2, testData, k);
                    printf("\nThe accuracy for the test data is %f\n\n", myAccuracy);
                    myAccuracy=0;
                    myAccuracy=findAccuracy(dataZoo, 3, testData, k);
                    printf("\nThe accuracy for the test data is %f\n\n", myAccuracy);
                break;
            }// end switch choice
        } else{
            printf("\nSelect choice 1 before any other choice\n");
        }
    }while(choice >= 1 && choice <= 5);
    return 0;
}


  
