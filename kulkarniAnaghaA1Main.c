int main(int argc, char* argv[]) {
    struct Animal dataZoo [NUM_SAMPLES];
    struct Animal testData [NUM_TEST_DATA];
    int v1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int v2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1};
    float euclideanDistance, jaccardSimilarity;
    int hammingDistance;
    int newSample [NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1};
    int k =5, myClass;
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
    findAccuracy(dataZoo, 1, testData, k);

    return 0;
}
