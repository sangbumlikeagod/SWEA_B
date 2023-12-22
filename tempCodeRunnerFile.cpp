
    // for (int i = 0; i < 5; i++)
    // {
    //     for (int j = 1; j <= N - i; j++)
    //     {
    //         for (int k = 1; k <= N - i; k++)
    //         {

    //             int val = island[j][k] - 1;
    //             numConstructor[val]++;

    //             for (int p = 1; p <= i; p++)
    //             {
    //                 val *= 10;
    //                 val += island[j + p][k] - 1;
    //                 numConstructor[val]++;
    //             }   
                
    //             val = island[j][k] + 4;

    //             for (int p = 1; p <= i; p++)
    //             {
    //                 val *= 10;
    //                 val += island[j][k + p] + 4;
    //                 numConstructor[val]++;
    //             }   
    //         }
    //     }        
    // }